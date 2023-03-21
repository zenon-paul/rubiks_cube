/**
*This is a header file for drawing rubik's cube.
**/

#ifndef RUBIKS_CUBE_GRAPHIC_INCLUDE
#define RUBIKS_CUBE_GRAPHIC_INCLUDE

#include"rubiks_cube_definition.h"

/**
* These sre values of initial window size.
*/
#define WID 300
#define HIG 300

/**
* These are coordinates of axis of cube's rotation.
*/
#define X_AXIS 30
#define Y_AXIS 30
#define Z_AXIS 30

/**
* This is pi.
*/
#define PI 3.1415

/**
* These values spacify cube's lotaion.
*/
#define EG 20
#define LE 0
#define MI 20
#define RI 40

/**
* This is type of value that has rubik's cube's geometric state. 
*/
typedef struct data_face {
	double face[NUM_FOUR_CORNER][3];
	double color[3];
}d_face;

/**
* This is type of value that has pointer of function that rotate rubik's cube.
*/
typedef void(*rfunc)(double, double*);

/**
* This value is entity that has infomation about which pieces are on which faces of rubik's cube.
*/
extern int face_posi[NUM_FACE][8];

/**
* These values are entities that have coordinate and color of each piece.
*/
extern d_face corners[NUM_CORNER][NUM_FACE];
extern d_face edges[NUM_EDGE][NUM_FACE];
extern d_face axises[NUM_FACE][NUM_FACE];

/**
* This function spacify speed of rataion.
* the larger number you set as the argument,the more slowly cubes rotate.
* This returns 1 when it sucseeds and returns 0 when it fails.
*/
int set_rotaion_speed(int speed);

/**
* This function multiplies rotation matrix by ventor.
*/
void product(double matrix[3][3], double vector[3]);

/**
* These functions set coordinats of each piece based on value that has cube's state.
*/
void init_corner(d_state* cube_state);
void init_edge(d_state* cube_state);
void init_axises();

/**
* These functions set colors of each piece based on value that has cube's state.
*/
void init_shuffled_cube(d_state x, double fc[NUM_FACE][3]);

/**
* This function reconfigures data of which pieces are on which faces of rubik's cube.
*/
void update_cube_group(d_state x, int face[NUM_FACE][8]);

/**
* This function set keyboard.
* This returns 1 when it sucseeds and returns 0 when it fails.
*/
int set_keyboard(int index, char key);

/**
* This funcion start display of rubik's cube.
*/
void graphic(int argc, char** argv);
#endif
