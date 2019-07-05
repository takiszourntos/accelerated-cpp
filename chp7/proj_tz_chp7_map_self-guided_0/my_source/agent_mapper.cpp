/*
 * agent_mapper.cpp
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
#include "agentlib.h"

// declare STD uses
using std::map;				using std::string;
using std::vector;			using std::cout;
using std::cin;				using std::endl;

// declare/allocate associative map --- defines the
// agent's associative memory of the physical environment...
// this is what "meaning" the agent associates with a given
// context string; the context string tells the agent
// the relative locations of the landmarks from its vantage point,
// in terms of the eight map directions, defined in orient_t.
// For example, if the agent "sees" Landmark A to the North-West,
// Landmark B to South, and Landmark C to the East, it should be
// in Region 1.

map<string, region_t>		global_map;

int main()
{
	/* retrieve known contexts from file, knownfeatures.data */
	vector<read_data_t>		read_data;
	read_data = load_known_contexts_from_file("knownfeatures.data");

	/* transfer data to global map */
	load_global_map_with_file_data(global_map, read_data);

	/* create 2D space for agent */
	vvs_t	physenv;					// variable storing the "literal" environment in which agent navigates
	loc_t	lmA, lmB, lmC, lmD, lmE;	// variables storing the locations of landmarks A through E in the physical environment

	/* initialize physical environment */
		lmA.X = 5;	lmA.Y = 5;
		lmB.X = 50;	lmB.Y = 50;
		lmC.X = 85; lmC.Y = 7;
		lmD.X = 3;  lmD.Y = 90;
		lmE.X = 80; lmE.Y = 83;
		// load the physical environment with spaces by default
		for (vvs_sz_t i=0; i!=Nx; ++i)
		{
			for (vvs_sz_t j=0; j!=Ny; ++j)
			{
				physenv[i][j]=" ";
			}
		}
		// position the landmarks
		physenv[lmA.X][lmA.Y] = "A";
		physenv[lmB.X][lmB.Y] = "B";
		physenv[lmC.X][lmC.Y] = "C";
		physenv[lmD.X][lmD.Y] = "D";
		physenv[lmE.X][lmE.Y] = "E";

	/* start building the associative map */
	loc_t		r0, r1; // agent's initial and current positions
	orient_t 	theta;		// agent's orientation








	return 0;
}


