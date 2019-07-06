/*
 * agentlib.h
 *
 *  Created on: Jul. 5, 2019
 *      Author: takis
 */

#ifndef MY_INCLUDES_AGENTLIB_H_
#define MY_INCLUDES_AGENTLIB_H_


/********************************************************************************************************
 * 											INCLUDES
 * ******************************************************************************************************
 */
#include <vector>
#include <string>
#include <fstream>

/********************************************************************************************************
 * 											MACROS
 * ******************************************************************************************************
 */
#define		Nx				100		// number of columns in physical environment
#define		Ny				100 	// number of rows in physical environment
#define		MaxMapEntries	48		// maximum number of contexts
#define		MaxIterations	9999	// maximum number of times main mapping loop can execute

/********************************************************************************************************
 * 											TYPEDEFs
 * ******************************************************************************************************
 */
typedef	std::vector<std::vector<std::string> >	vvs_t;	// 2D vector type for the
														// physical environment

typedef	vvs_t::size_type	vvs_sz_t;	// size_type for 2D vector type

typedef		enum 	e_region_t 	// enumerate the possible regions
	{
		R0,
		R1,
		R2,
		R3,
		R4,
		R5
	}	region_t;

typedef		enum	e_orient_t	// enumerate the possible directions
	{
		North,
		NorthEast,
		East,
		SouthEast,
		South,
		SouthWest,
		West,
		NorthWest
	}	orient_t;

typedef		enum	e_scan_direction_t	// scan goes from top left to bottom right,
										// or from bottom right to top left
	{
		SE,
		NW
	} 	scan_direction_t;


typedef		struct	loc_t	// type for a location in the physical environment
{
	vvs_sz_t		X;
	vvs_sz_t		Y;
};

typedef		struct	read_data_t		// type for storing data read from file
{
	std::string		context;
	region_t		region;
};


/********************************************************************************************************
 * 											FUNCTION PROTOTYPES
 * ******************************************************************************************************
 */

/*
 * 		function: 	load_known_contexts_from_file
 * 		purpose:	reads pairs of tokens from a file of the form <string, unsigned_integer> <newline>
 * 		parameters:	string consisting of the file name
 * 		returns:	a vector of read_data_t elements
 *
 */
std::vector<read_data_t> loadKnownContextsfromFile(const std::string);

/*
 * 		function: 	load_global_map_with_file_data
 * 		purpose:	fills contextual/associative map data structure with information in vector of read_data_t elements
 * 		parameters:	the associate map (passed by reference), and the vector of read_data_t elements, passed by constant reference
 * 		returns:	nothing (void function)
 *
 */
void loadGlobalMapwithFileData(std::map<std::string, region_t>&, const std::vector<read_data_t>&);



#endif /* MY_INCLUDES_AGENTLIB_H_ */
