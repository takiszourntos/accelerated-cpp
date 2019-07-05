/*
 * agentlib.h
 *
 *  Created on: Jul. 5, 2019
 *      Author: takis
 */

#ifndef MY_INCLUDES_AGENTLIB_H_
#define MY_INCLUDES_AGENTLIB_H_


/*
 * my includes
 */
#include <vector>
#include <string>
#include <fstream>

/*
 * my macros
 */
#define		Nx		100		// number of columns in physical environment
#define		Ny		100 	// number of rows in physical environment

/*
 * my typedefs
 */
typedef	std::vector<std::vector<std::string> >				vvs_t;		// 2D vector type for physical environment
typedef	std::vector<std::vector<std::string> >::size_type	vvs_sz_t;	// size_type for 2D vector type

typedef		enum 	e_region_t			{R0, R1, R2, R3, R4, R5}		region_t; 			// enumerate the possible regions
typedef		enum	e_orient_t			{N, NE, E, SE, S, SW, W, NW}	orient_t; 			// enumerate the possible directions
typedef		enum	e_scan_direction_t	{SE, NW} 						scan_direction_t; 	// scan goes from top left to bottom right,
													// or from bottom right to top left
// type for a location in the physical environment
typedef		struct	loc_t
{
	vvs_sz_t		X;
	vvs_sz_t		Y;
};
// type for storing data read from file
typedef		struct	read_data_t
{
	std::string		context;
	region_t		region;
};


/*
 * function prototypes
 */
std::vector<read_data_t> load_known_contexts_from_file(const std::string);
void	load_global_map_with_file_data(std::map<std::string, region_t>&, const std::vector<read_data_t>&);



#endif /* MY_INCLUDES_AGENTLIB_H_ */
