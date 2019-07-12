/*
 * agent_mapper.cpp
 *
 * An associative map defines the agent's associative memory of the
 * physical environment... this is what "meaning" the agent associates
 * with a given context string; the context string tells the agent
 * the relative locations of the landmarks from its vantage point,
 * in terms of the eight map directions, defined in orient_t.
 * For example, if the agent "sees" Landmark A to the North-West,
 * Landmark B to South, and Landmark C to the East, it should be
 *  in Region 1.
 *
 *  Created on: Jul. 5, 2019
 *      Author: takis
 */

// components from STD Library
#include <vector>
#include <iostream>
#include <string>
#include <map>
// my own includes
#include <gsl/gsl_blas.h>
#include "agentlib.h"

// declare STD uses
using std::map;				using std::string;
using std::vector;			using std::cout;
using std::cin;				using std::endl;

// main code
int main()
{
	map<string, region_t>		global_map;
	bool						mappingfinished=false;	// flag indicating completion of associative map;
	/* retrieve known contexts from file, knownfeatures.data */
	vector<read_data_t>		read_data;
	read_data = loadKnownContextsfromFile("knownfeatures.data");

	/* transfer data to global map */
	loadGlobalMapwithFileData(global_map, read_data);

	/* create 2D space for agent */
	vvs_t			physenv;					// variable storing the "literal" environment in which agent navigates
	loc_t			lmA, lmB, lmC, lmD, lmE;	// variables storing the locations of landmarks A through E in the physical environment
	vector<loc_t> 	v_lm; // vector of landmarks
	lmA.X = 5;	lmA.Y = 5;	v_lm.push_back(lmA);
	lmB.X = 50;	lmB.Y = 50;	v_lm.push_back(lmB);
	lmC.X = 85; lmC.Y = 7;	v_lm.push_back(lmC);
	lmD.X = 3;  lmD.Y = 90;	v_lm.push_back(lmD);
	lmE.X = 80; lmE.Y = 83;	v_lm.push_back(lmE);

	/* initialize physical environment */
	for (vvs_sz_t i=0; i!=Nx; ++i)
	{
		for (vvs_sz_t j=0; j!=Ny; ++j)
		{
			physenv[i][j]=" ";
		}
	}
	physenv[lmA.X][lmA.Y] = "A"; // position of landmark A
	physenv[lmB.X][lmB.Y] = "B"; // position of landmark B
	physenv[lmC.X][lmC.Y] = "C"; // position of landmark C
	physenv[lmD.X][lmD.Y] = "D"; // position of landmark D
	physenv[lmE.X][lmE.Y] = "E"; // position of landmark E

	/* start building the associative map */
	loc_t				r0={0,0}; 				// agent's initial position
	loc_t				r1=r0;
	orient_t 			theta=North;			// agent's orientation
	scan_direction_t	scan_sense = SE;		// initial scanning sense
	loc_t				rA=r0;					// upper left corner of search space
	loc_t				rB={Nx-1, Ny-1};		// bottom right corner of search space
	scan(mappingfinished, scan_sense, rA, rB, r0, global_map, physenv, v_lm);

	return 0;
}


