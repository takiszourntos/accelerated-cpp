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


/********************************************************************************
 * 							GLOBAL VARIABLES									*
 ********************************************************************************/
// declare/allocate associative map --- defines the
// agent's associative memory of the physical environment...
// this is what "meaning" the agent associates with a given
// context string; the context string tells the agent
// the relative locations of the landmarks from its vantage point,
// in terms of the eight map directions, defined in orient_t.
// For example, if the agent "sees" Landmark A to the North-West,
// Landmark B to South, and Landmark C to the East, it should be
// in Region 1.
static	map<string, region_t>		global_map;
static	volatile	bool			mappingfinished=false;	// flag indicating completion of associative map;


void scan(const scan_direction_t dir, loc_t rA, loc_t rB, loc_t r0, map<string, region_t>& spatial_mem, vvs_t& physmap)
{
	if ( ((dir==SE) && ((r0.X==rB.X) && (r0.Y==rB.Y))) || ((dir==NW) && ((r0.X==rA.X) && (r0.Y==rA.Y)))  )
	{
		mappingfinished=true;
	}
	if (!mappingfinished)
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
			scan(dir, rA, rB, r1, spatial_mem, physmap); // recursion
		}
	}
	else // mapping process is finished (in the sense that all points have been visited)
	{
		agentScan360(r0, spatial_mem, physmap); // perform a scan at point r0
	}
	return;
}


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

	loc_t				rA=r0;					// upper left corner of search space
	loc_t				rB={Nx-1, Ny-1};		// bottom right corner of search space
	scan(scan_sense, rA, rB, r0, global_map, physenv);

	return 0;
}


