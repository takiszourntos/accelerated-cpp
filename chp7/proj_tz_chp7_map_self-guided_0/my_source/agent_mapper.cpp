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
	bool						mappingfinished=false;	// global flag indicating completion of associative map;
	vector<string> orient_str; // strings corresponding to eight orient_t directions
	orient_str.push_back("No"); orient_str.push_back("NE");
	orient_str.push_back("Ea"); orient_str.push_back("SE");
	orient_str.push_back("So"); orient_str.push_back("SW");
	orient_str.push_back("We"); orient_str.push_back("NW");

	/* retrieve known contexts from file, knownfeatures.data */
	vector<read_data_t>		read_data;
	read_data = loadKnownContextsfromFile("knownfeatures.data");

	/* transfer data to global map */
	loadGlobalMapwithFileData(global_map, read_data);

	/* initialize physical environment */
	vvs_t	physenv;					// variable storing the "literal" environment in which agent navigates
	for (vvs_sz_t i=0; i!=Nx; ++i)
	{
		for (vvs_sz_t j=0; j!=Ny; ++j)
		{
			physenv[i][j]=" ";
		}
	}

	/* create FIVE landmarks at fixed locations */
	string				lm_labels="ABCDE"; // there must be at least FIVE UNIQUE characters in this string
	vector<loc_t>		v_lm;	// variables storing the locations of landmarks A through E in the physical environment
	loc_t				lmA = {5, 5};	v_lm.push_back(lmA);
	loc_t				lmB = {50, 50};	v_lm.push_back(lmB);
	loc_t				lmC = {85, 7};	v_lm.push_back(lmC);
	loc_t				lmD = {3, 90};	v_lm.push_back(lmD);
	loc_t				lmE = {80, 83};	v_lm.push_back(lmE);
	map<char, loc_t> 	m_lm;	// container of landmarks with key-location relationship
	string::const_iterator siter=lm_labels.begin();		// iterator for landmarks string
	if ( lm_labels.size() < (string::size_type) v_lm.size() )
	{
		cout << "Error--- there are more landmarks than landmark labels!" << endl;
		return 1; // provide an error code
	}

	vector<loc_t>::size_type i=0; // index to landmark locations
	// invariant: siter points to the next landmark to be incorporated into our little key-landmark container
	while (siter != lm_labels.end())
	{
		m_lm[*siter]=v_lm[i]; // de-reference a string iterator produces a char-type value (*siter)
		physenv[v_lm[i].X][v_lm[i].Y]=*siter;
		++i;
		++siter;
	}

	/* start building the associative map */
	loc_t				r0={0,0}; 				// agent's initial position
	scan_direction_t	scan_sense = SE;		// initial scanning sense
	loc_t				rA=r0;					// upper left corner of search space
	loc_t				rB={Nx-1, Ny-1};		// bottom right corner of search space
	scan(mappingfinished, scan_sense, 					rA, 		rB, 		r0, 		global_map, 									physenv, 				m_lm, 									orient_str);
//  scan(bool& done,      const scan_direction_t dir, 	loc_t rA, 	loc_t rB, 	loc_t r0, 	std::map<std::string, region_t>& spatial_mem, 	const vvs_t& physmap, 	const std::map<char, loc_t>& landmarks, const std::vector<std::string>& orient_str)

	return 0;
}


