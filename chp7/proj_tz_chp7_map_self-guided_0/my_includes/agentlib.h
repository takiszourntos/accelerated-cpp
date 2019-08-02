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

// my own includes
#include <gsl/gsl_blas.h>
#include <gsl/gsl_math.h>
#include <math.h>



/********************************************************************************************************
 * 											MACROS
 * ******************************************************************************************************
 */
#define		Nx				100		// number of columns in physical environment
#define		Ny				100 	// number of rows in physical environment
#define		MaxMapEntries	48		// maximum number of contexts
#define		MaxIterations	9999	// maximum number of times main mapping loop can execute
#define		SenseRange		75		// units of distance that the agent can "see"
#define		MinVectorNorm	0.01	// a landmark must be further away than 1 cm from the agent
#define		MATSIZE			8		// matrix dimension (MATSIZE x MATSIZE) for analysis

/********************************************************************************************************
 * 											TYPEDEFs
 * ******************************************************************************************************
 */
typedef	std::vector<std::vector<std::string> >	vvs_t;	// 2D vector type for the
														// physical environment

typedef	vvs_t::size_type	vvs_sz_t;	// size_type for 2D vector type

typedef	enum 	e_region_t 	// enumerate the possible regions
	{
		R0,
		R1,
		R2,
		R3,
		R4,
		R5
	}	region_t;

typedef	enum	e_orient_t	// enumerate the possible directions
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


typedef	enum	e_scan_direction_t	// scan goes from top left to bottom right,
									// or from bottom right to top left
	{
		SE,
		NW
	} 	scan_direction_t;


struct	loc_t	// type for a location in the physical environment
{
	vvs_sz_t		X;
	vvs_sz_t		Y;
};

struct	read_data_t		// type for storing data read from file
{
	std::string		context;
	region_t		region;
};

struct dprec_t // define a type to store dot products and corresponding directions
{
	orient_t dir;
	double dp;
};



/********************************************************************************************************
 * 											FUNCTION PROTOTYPES
 * ******************************************************************************************************
 */


/*
 * 		function: 	sgn
 * 		purpose:	determines the sign of a double variable
 * 		parameters:	a real number (double)
 * 		returns:	+1 or -1 (short int)
 *
 */
short int	sgn(double);


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
 * 		returns:	nothing (void function)space
 *
 */
void loadGlobalMapwithFileData(std::map<std::string, region_t>&, const std::vector<read_data_t>&);


/*
 * 		function: 	convertContextStringtoMatrix
 * 		purpose:	takes a key string associated with the spatial associative map, and converts it into a matrix
 * 		parameters:	the context string
 * 		returns:	a matrix (of type gsl_matrix_float*)
 */
gsl_matrix_float *convertContextStringtoMatrix(const std::string&);


/*
 * 		function:	mat2Norm
 * 		purpose:	compute the 2-norm of a matrix from the definition on page 291 of
 * 					Matrix Analysis, Horn & Johnson
 * 		parameters:	a matrix of type gsl_matrix_float*
 * 		returns:	the matrix 2-norm value
 */
float mat2Norm(const gsl_matrix_float);


/*
 * 		function: 	matTr
 * 		purpose: 	yields the transformation matrix we need, T_k, where k=0,+/-1,+/-2,...
 * 		parameters:	an integer (k)
 * 		returns:	a matrix of type gsl_matrix_float*
 *
 */
gsl_matrix_float *matTr(int);


/*
 * 		function:	compareContexts
 * 		purpose:	compare context matrices, return the closeness value
 * 		parameters:	two matrices to be compared, of type gsl_matrix_float*
 * 		returns:	a closeness value, the greater, the closer the matrices are
 */
float	compareContexts(const gsl_matrix_float*, const gsl_matrix_float*);


/*
 * 		function: 	alphaK
 * 		purpose:	implements a continuous monotonically decreasing function
 * 		parameters: a real number, x (float)
 * 		returns:	(float) exp(-x)
 */
float alphaK(const float);


/*
 * 		function:	agentScan360
 * 		purpose:	at a fixed position (loc_t, first parameter) in the physical environment, deduce the context string,
 * 					which consists of relative position data, e.g., lm_A to East, lm_B to SW, to be identified
 * 					as the key AEBSW for the associative map;
 * 		parameters: the agent's location, the associative map, the physical map, and the landmark locations
 * 		returns:	nothing (changes are made to the associative map)
 */
void agentScan360(loc_t, std::map<std::string, region_t>&, const vvs_t&, const std::vector<loc_t>&, const std::vector<std::string>&);


/*
 * 		function:	scan
 * 		purpose:	survey a rectangular subset of 2D space, either in a SE or a NW sense, using recursion
 * 		parameters:	rA (top left corner of scan), rB (bottom right corner of scan), r0 (agent current location)
 * 					spatial_mem (associative map of space), physmap (physical map of space)
 * 		returns: 	nothing (void type, but changes are made to the spatial memory, a.k.a., the associate map)
 */
void scan(bool& done, const scan_direction_t, loc_t, loc_t, loc_t, std::map<std::string, region_t>&, const vvs_t&, const std::map<std::string, loc_t>&, const std::vector<std::string>&);


#endif /* MY_INCLUDES_AGENTLIB_H_ */
