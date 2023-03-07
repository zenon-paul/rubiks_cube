#ifndef INCLUDE_CUBE
#define INCLUDE_CUBE
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
//--------------opengl----------------------------
extern double cube[6][4][3];
extern int face_set[6][8];
extern int face_posi[6][8];
extern double corner_seed[8][3];
extern double edge_seed[12][3];
extern double corners[8][6][4][3];
extern double edges[12][6][4][3];
void init_corner();
void init_edge();
void init_cube_color();
void product(double matrix[3][3], double vector[3]);
//--------------rubik----------------------------
#define QLIM 20
#define MOVE 18
typedef struct s_data {
	int cp[8];
	int co[8];
	int ep[12];
	int eo[12];
}d_state;
typedef void(*func)(d_state*);
void simuration(d_state* state, int i);
void update_face_posi(d_state state, int face[6][8]);
void init_state(d_state* x);
void make_r(d_state* x);
void make_b(d_state* x);
void make_l(d_state* x);
void make_f(d_state* x);
void make_u(d_state* x);
void make_d(d_state* x);
void make();
void R(d_state* x);
void B(d_state* x);
void L(d_state* x);
void F(d_state* x);
void U(d_state* x);
void D(d_state* x);
void R2(d_state* x);
void B2(d_state* x);
void L2(d_state* x);
void F2(d_state* x);
void U2(d_state* x);
void D2(d_state* x);
void R_(d_state* x);
void B_(d_state* x);
void L_(d_state* x);
void F_(d_state* x);
void U_(d_state* x);
void D_(d_state* x);
#endif

