#ifndef RUBIKS_CUBE_GRAPHIC_INCLUDE
#define RUBIKS_CUBE_GRAPHIC_INCLUDE
/**
*This is a header file for drawing rubik's cube.
*
*
**/
#include"rubiks_cube_definition.h"

#define WID 300
#define HIG 300
#define X_AXIS 30
#define Y_AXIS 30
#define Z_AXIS 30
#define PI 3.1415
#define RA 180
#define EG 20
#define LE 0
#define MI 20
#define RI 40
#define MOVE 18

typedef struct data_face {
	double face[NUM_FOUR_CORNER][3];
	double color[3];
}d_face;
typedef void(*rfunc)(double, double*);
extern int face_posi[NUM_FACE][8];
extern d_face corners[NUM_CORNER][NUM_FACE];
extern d_face edges[NUM_EDGE][NUM_FACE];
extern d_face axises[NUM_FACE][NUM_FACE];
void init_corner(d_state* cube_state);
void init_edge(d_state* cube_state);
void init_axises();
void init_shuffled_cube(d_state x, double fc[NUM_FACE][3]);
void product(double matrix[3][3], double vector[3]);
void graphic(int argc, char** argv);
void key_setting(int index, char key);
void update_cube_group(d_state x, int face[NUM_FACE][8]);
#endif
