/*
 * agentlib.cpp
 *
 *  Created on: Jul. 11, 2019
 *      Author: takis
 */

// STDL includes
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

// my own includes
#include <gsl/gsl_blas.h>
#include <gsl/gsl_math.h>
#include <math.h>
#include "agentlib.h"

/*
 * sgn(x) function, one of my favourites!
 */
short int	sgn(double x)
{
	short int y=0;
	if (x >= 0)
	{
		y = 1;
	}
	else
	{
		y = -1;
	}
	return y;
}

/*
 * max
 */
bool maxdp(dprec_t A, dprec_t B)
{
	bool ret=false;
	if (A.dp >= B.dp)
	{
		ret = true;
	}
	return ret;
}

/*
 * load the global map with file data
 */
void loadGlobalMapwithFileData(std::map<std::string, region_t>& gmap, const std::vector<read_data_t>& mapdata)
{
	for (std::vector<read_data_t>::size_type i=0; i != mapdata.size(); ++i)
	{
		gmap[mapdata[i].context] = mapdata[i].region; // insert the feature into global_map
	}
}


/*
 * returns the transformation matrix we need, T_k, where k=0,+/-1,+/-2,...
 */
gsl_matrix_float *matTr(int k)
{
	if (k==0)
	{
		gsl_matrix_float *T0 = gsl_matrix_alloc(MATSIZE, MATSIZE);
		gsl_matrix_float_set_identity(T0);
		return T0;
	}
	else if (k>0)
	{
		gsl_matrix_float *Tp1 = gsl_matrix_alloc(MATSIZE, MATSIZE); // T_{+1}
		gsl_matrix_float_set_zero(Tp1);			// most elements are zero
		gsl_matrix_float_set(Tp1, MATSIZE-1, 1, 1.0); 	// put a leading 1 in the last row

		// set super-diagonal elements to 1
		for (int i=0;i!=(k-1);++i)
		{
			gsl_matrix_float_set(Tp1, i, (i+1), 1.0); // put a 1 in @ (i, i+1); i = 0, 1, ..., (k-2)
		}

		gsl_matrix_float *Tpk = Tp1;
		// multiply this matrix with itself k-1 times
		for (int i=1;i!=k; ++i)
		{
			gsl_blas_sgemm(CblasNoTrans, CblasNoTrans, 1.0, Tpk, Tp1, 0.0, Tpk);
		}
		return Tpk;
	}
	else if (k<0)
	{
		k=-k; // make it positive for the rest of our work
		gsl_matrix_float *Tm1 = gsl_matrix_alloc(MATSIZE, MATSIZE); // T_{-1}
		gsl_matrix_float_set_zero(Tm1);			// most elements are zero
		gsl_matrix_float_set(Tm1, 1, MATSIZE-1, 1.0); 	// put a trailing 1 in the first row
		// set sub-diagonal elements to 1
		for (int i=1;i!=k;++i)
		{
			gsl_matrix_float_set(Tm1, i, (i-1), 1.0); // put a 1 in @ (i, i-1); i = 1, 2, ..., (k-1)
		}
		gsl_matrix_float *Tmk = Tm1;
		// multiply this matrix with itself k-1 times
		for (int i=1;i!=k; ++i)
		{
			gsl_blas_sgemm(CblasNoTrans, CblasNoTrans, 1.0, Tmk, Tm1, 0.0, Tmk);
		}
		return Tmk;
	}
}

/*
 * convert a context string to a matrix for analysis
 */
gsl_matrix_float *convertContextStringtoMatrix(const std::string& context_string)
{
	std::string::size_type csi=0;
	std::string data_lm;	// stores the information associated with a landmark
	std::string lm_name; // the landmark identifier
	std::string lm_rd;	// the relative direction of the landmark relative to the agent

	// invariant: citer points to the substring to be processed
	while (csi != context_string.length())
	{
		// take three characters
		data_lm = context_string.substr(csi, 3);

		// determine landmark
		lm_name = data_lm.substr(1,1);
		switch lm_name
		{

		}

		data_lm.clear(); // empty the string variable
		csi += 3;

	}
}


/*
 * scan 360 (at a fixed point in space) function
 */
void agentScan360(loc_t r0, std::map<std::string, region_t>& spatial_mem, const vvs_t& physmap, const std::map<std::string, loc_t>& landmarks, const std::vector<std::string>& orient_str)
{
	// identify all the landmarks within sensor range
	std::map<std::string, loc_t>::const_iterator	lm_iter=landmarks.begin();

	double Xlm, Ylm; // storage for a landmark under consideration
	gsl_vector *p_lm = gsl_vector_alloc(2); // gsl vector containing current landmark
	gsl_vector *p_ag = gsl_vector_alloc(2);	// gsl vector to store agent's current position
	gsl_vector_set(p_ag, 0, (double) r0.X); // set X-position of agent
	gsl_vector_set(p_ag, 1, (double) r0.Y); // set Y-position of agent
	gsl_vector *err = gsl_vector_alloc(2); // "error" vector pointing from agent to landmark

	double size_err, dotp; // basic calculation storage

	std::string keylm, context;
	std::vector<dprec_t> dotprods; // store three dprec_t elements here, corresponding to the Quadrant we're in (see below)
	std::vector<dprec_t>::const_iterator iter = dotprods.begin();
	// lm_iter points to landmark to be checked w.r.t. this location (r0) of the agent
	while (lm_iter != landmarks.end())
	{
		Xlm = (double) (lm_iter->second).X;
		Ylm = (double) (lm_iter->second).Y;
		gsl_vector_set(p_lm, 0, Xlm); // set first element of p_lm
		gsl_vector_set(p_lm, 1, Ylm); // set second element of p_lm

		orient_t lmdir; // direction of landmark relative to agent (or result for each loop iteration)

		gsl_vector_memcpy(err, p_lm); // copy p_lm into err, to prepare for subtraction
		gsl_vector_sub(err, p_ag); // compute p_lm - p_ag, store the result in err

		size_err = gsl_blas_dnrm2(err); // compute the distance to the landmark

		if ( (size_err < SenseRange) && (size_err > MinVectorNorm) ) // is the landmark in range?
		{
			// compute the direction of the landmark relative to the agent,
			// rounding to the nearest 22.5 degrees (typical compass direction)
			gsl_vector_scale(err, 1/size_err); // re-scale err so that it is a unit vector
			double Xe = gsl_vector_get(err, 0);
			double Ye = gsl_vector_get(err, 1);
			dprec_t dpvar; // temporary storage here

			if ( (Xe >= 0) && (Ye >= 0) )
			{
				// in Quadrant I
				gsl_vector *p_N	= gsl_vector_alloc(2); gsl_vector_set_basis(p_N, 1);	// North unit vector
				gsl_vector *p_NE= gsl_vector_alloc(2); gsl_vector_set(p_NE, 0, 1/sqrt(2)); gsl_vector_set(p_NE, 1, 1/sqrt(2));	// North-East unit vector
				gsl_vector *p_E = gsl_vector_alloc(2); gsl_vector_set_basis(p_E, 0);	// East unit vector
				dpvar.dir = North;		gsl_blas_ddot(p_N, err, &dpvar.dp);		dotprods.push_back(dpvar);
				dpvar.dir = NorthEast;	gsl_blas_ddot(p_NE, err, &dpvar.dp);	dotprods.push_back(dpvar);
				dpvar.dir = East;		gsl_blas_ddot(p_E, err, &dpvar.dp); 	dotprods.push_back(dpvar);
			}
			else if ( (Xe >= 0) && (Ye <= 0) )
			{
				// in Quadrant II
				gsl_vector *p_E = gsl_vector_alloc(2); gsl_vector_set_basis(p_E, 0);	// East unit vector
				gsl_vector *p_SE= gsl_vector_alloc(2); gsl_vector_set(p_SE, 0, 1/sqrt(2)); gsl_vector_set(p_SE, 1, -1/sqrt(2));	// South-East unit vector
				gsl_vector *p_S = gsl_vector_alloc(2); gsl_vector_set_basis(p_S, 1); gsl_vector_scale(p_S, -1);	// South unit vector
				dpvar.dir = East;		gsl_blas_ddot(p_E, err, &dpvar.dp); 	dotprods.push_back(dpvar);
				dpvar.dir = SouthEast;	gsl_blas_ddot(p_SE, err, &dpvar.dp); 	dotprods.push_back(dpvar);
				dpvar.dir = South;		gsl_blas_ddot(p_S, err, &dpvar.dp); 	dotprods.push_back(dpvar);
			}
			else if ((Xe <= 0) && (Ye <= 0) )
			{
				// in Quadrant III
				gsl_vector *p_S = gsl_vector_alloc(2); gsl_vector_set_basis(p_S, 1); gsl_vector_scale(p_S, -1);	// South unit vector
				gsl_vector *p_SW= gsl_vector_alloc(2); gsl_vector_set(p_SW, 0, -1/sqrt(2)); gsl_vector_set(p_SW, 1, -1/sqrt(2));	// South-East unit vector
				gsl_vector *p_W = gsl_vector_alloc(2); gsl_vector_set_basis(p_W, 0); gsl_vector_scale(p_W, -1); // West unit vector
				dpvar.dir = South;		gsl_blas_ddot(p_S, err, &dpvar.dp); 	dotprods.push_back(dpvar);
				dpvar.dir = SouthWest;	gsl_blas_ddot(p_SW, err, &dpvar.dp); 	dotprods.push_back(dpvar);
				dpvar.dir = West;		gsl_blas_ddot(p_W, err, &dpvar.dp); 	dotprods.push_back(dpvar);
			}
			else
			{
				// in Quadrant IV
				gsl_vector *p_W = gsl_vector_alloc(2); gsl_vector_set_basis(p_W, 0); gsl_vector_scale(p_W, -1); // West unit vector
				gsl_vector *p_NW= gsl_vector_alloc(2); gsl_vector_set(p_NW, 0, -1/sqrt(2)); gsl_vector_set(p_NW, 1, 1/sqrt(2)); // North-West unit vector
				gsl_vector *p_N	= gsl_vector_alloc(2); gsl_vector_set_basis(p_N, 1);	// North unit vector
				dpvar.dir = West;		gsl_blas_ddot(p_W, err, &dpvar.dp); 	dotprods.push_back(dpvar);
				dpvar.dir = NorthWest;	gsl_blas_ddot(p_NW, err, &dpvar.dp);	dotprods.push_back(dpvar);
				dpvar.dir = North;		gsl_blas_ddot(p_N, err, &dpvar.dp);		dotprods.push_back(dpvar);
			}
			iter = std::max_element(dotprods.begin(),dotprods.end(),maxdp);
		}
		keylm=lm_iter->first; // name of current landmark
		context+=keylm + orient_str[iter->dir];
		++lm_iter; // point to next landmark in container
		dotprods.clear(); iter = dotprods.begin();
	} // end: while (lm_iter != landmarks.end())

	// Now, add context to spatial_mem, but what should the value (region_t) be for this context string?
	// Recall that if landmarks A, C and E are in sensor range and happen to be
	// in the directions (relative to the agent's position, facing North) of North,
	// South-East and East, respectively, then context = "ANoCSEEEa"
	// (anoxia is a word, BTW)
	//
	if (spatial_mem.find(context) != spatial_mem.end())
	{
		// this context has not been experienced before
		// so let's add a new entry... find the elements
		// "closest" (by key sorting) to this context
		// and median the results...
		std::map<std::string, region_t>::iterator sp_iter=spatial_mem.begin();
		closest = sp_iter->first; // closest will contain the string closest to context
		int closeness=0; // closeness is this if the strings match exactly

		gsl_matrix_float *M1, *M2; // matrices to represent agent's context and existing context in global map, respectively
		M1 = convertContextStringtoMatrix(context); // M1 represents the agent's current context
		M2 = convertContextStringtoMatrix(closest); // M2 represents a context string stored in spatial_mem, under consideration


		// check for the number of substring matches... take each legit substring from
		// context and scan each key; total up the number of matches, and the key with
		// the greatest number of substring matches will be the closest key--- use that
		// key's value as the value for this new context (key)

		while (sp_iter != spatial_mem.end())
		{
			if str_compare
		}
	} // if the context is in the spatial memory, no need to add it again!
	return;
}


/*
 * scan (physical space) function
 */
void scan(bool& done, const scan_direction_t dir, loc_t rA, loc_t rB, loc_t r0, std::map<std::string, region_t>& spatial_mem, const vvs_t& physmap, const std::vector<loc_t>& landmarks, const std::vector<std::string>& orient_str)
{
	if ( ((dir==SE) && ((r0.X==rB.X) && (r0.Y==rB.Y))) || ((dir==NW) && ((r0.X==rA.X) && (r0.Y==rA.Y)))  )
	{
		done=true;
	}
	if (!done)
	{
		loc_t		r1 = r0;
		vvs_sz_t	bX = 0;
		// vvs_sz_t	bY = 0;
		vvs_sz_t	eX = rB.X-rA.X;
		// vvs_sz_t	eY = rB.Y-rA.Y;
		if (dir==SE)
		{
			vvs_sz_t	offsetX = r0.X - rA.X;
			vvs_sz_t	offsetY = r0.Y - rA.Y;
			if (offsetX == bX) // start a new "scan line"
			{
				offsetX = ++offsetY;
				offsetY = offsetX;
			}
			else // keep going along scan line
			{
				--offsetX;
				++offsetY;
			}
			r1.X = rA.X + offsetX;
			r1.Y = rA.Y + offsetY;
		}
		if (dir==NW)
		{
			vvs_sz_t	offsetX = r0.X - rB.X;
			vvs_sz_t	offsetY = r0.Y - rB.Y;
			if (offsetX == eX) // start a new "scan line"
			{
				offsetX = --offsetY;
				offsetY = offsetX;
			}
			else // keep going along scan line
			{
				++offsetX;
				--offsetY;
			}
			r1.X = rB.X + offsetX;
			r1.Y = rB.Y + offsetY;
		}
		scan(done, dir, rA, rB, r1, spatial_mem, physmap, landmarks, orient_str); // R-E-C-U-R-S-I-O-N
	}
	else // (done=true) mapping process is finished (in the sense that all points have been visited)
	{
		agentScan360(r0, spatial_mem, physmap, landmarks, orient_str); // perform a scan at point r0
	}
	return;
}
