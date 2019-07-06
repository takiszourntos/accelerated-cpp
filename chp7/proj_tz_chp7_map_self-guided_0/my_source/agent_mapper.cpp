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
	read_data = loadKnownContextsfromFile("knownfeatures.data");

	/* transfer data to global map */
	loadGlobalMapwithFileData(global_map, read_data);

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
	loc_t				r0={0,0}; 				// agent's initial position
	loc_t				r1=r0;
	orient_t 			theta=North;			// agent's orientation
	scan_direction_t	scan_sense = SE;		// initial scanning sense
	int					t1=0, t2=0, counter=0; 	// time tracking variables
	bool				mapnotfinished=true;	// flag indicating completion of associative map;

	// invariant: mapnotfinished=TRUE means that we still have work to do
	while (mapnotfinished)
	{
		r2 = getAgentNextDest(t1++, r1,scan_sense);
		t2 = 0;
		// invariant: r1 is the next point to in physenv[][] to which the agent must move
		while (r1 != r2)
		{
			agentScan360(r1,theta,physenv);
			r1 = agentMove(t2++,r1,r2,scan_sense);
		}
		if (((global_map.size() >= MaxMapEntries)) || (counter==MaxIterations) )
			mapnotfinished=false;
		++counter;
	}

	dumpMappedEnv(); // check that we have a good sense of the world
	return 0;
}


