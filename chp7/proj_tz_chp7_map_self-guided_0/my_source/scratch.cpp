/*
 * scratch.cpp
 *
 *  Created on: Jul. 10, 2019
 *      Author: takis
 */


//	// invariant: mapnotfinished=TRUE means that we still have work to do
//	while (mapnotfinished)
//	{
//		r2 = getAgentNextDest(t1++, r1,scan_sense);
//		t2 = 0;
//		// invariant: r1 is the next point to in physenv[][] to which the agent must move
//		while (r1 != r2)
//		{
//			agentScan360(r1,theta,physenv);
//			r1 = agentMove(t2++,r1,r2,scan_sense);
//		}
//		if (((global_map.size() >= MaxMapEntries)) || (counter==MaxIterations) )
//			mapnotfinished=false;
//		++counter;
//	}
//
//	dumpMappedEnv(); // check that we have a good sense of the world


