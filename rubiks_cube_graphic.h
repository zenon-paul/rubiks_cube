#ifndef RUBIKS_CUBE_GRAPHIC_INCLUDE
#define RUBIKS_CUBE_GRAPHIC_INCLUDE
/**
*This is a header file for drawing rubik's cube.
*
*
**/
#include"rubiks_cube_definition.h"

#define WID 640
#define HIG 640
#define X_AXIS 30
#define Y_AXIS 30
#define Z_AXIS 30
#define PI 3.1415
#define RA 90
#define EG 20
#define LE 0
#define MI 20
#define RI 40
#define MOVE 18

typedef struct data_face {
	double face[4][3];
	double color[3];
}d_face;

typedef void(*rfunc)(double, double*);
extern double cube[6][4][3];
extern int face_set[6][8];
extern int face_posi[6][8];
extern double corner_seed[8][3];
extern double edge_seed[12][3];
extern d_face corners[8][6];
extern d_face edges[12][6];
extern d_face axises[6][6];
void init_corner();
void init_edge();
void init_axises();
void init_cube_color();
void init_face_posi(int posi[6][8]);
void product(double matrix[3][3], double vector[3]);
void simuration(d_state* state, int i);
void update_face_posi(d_state state, int face[6][8]);
void reset();
void graphic(int argc, char** argv);
#endif
