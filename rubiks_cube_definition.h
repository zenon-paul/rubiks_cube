#ifndef RUBIKS_CUBE_DEFINITION_INCLUDE
#define RUBIKS_CUBE_DEFINITION_INCLUDE
/**
*This is a header file for definition rubik's cube.
*
*
**/
#define PHASE1_MOVE 18
#define PHASE2_MOVE 10
#define VECTOR_LEN 60
#define NUM_CORNER 8
#define NUM_EDGE 12
#define R_CENTER 4
#define L_CENTER 13
#define F_CENTER 22
#define B_CENTER 31
#define U_CENTER 40
#define D_CENTER 49
#define NUM_FACE 6
#define NUM_3_SQUARED 9
//#define GENERATION 100

typedef struct s_data {
	int cp[8];
	int co[8];
	int ep[12];
	int eo[12];
}d_state;

typedef void(*func)(d_state*);
extern int path1[VECTOR_LEN];
extern int path2[VECTOR_LEN];
extern int mnum1;
extern int mnum2;
extern int motion_count;
extern int motion_list[VECTOR_LEN];
//extern func phase1_move[PHASE1_MOVE];
//extern func phase2_move[PHASE2_MOVE];
extern int coorresponding_table_from_phase2_move_to_phase1_move[PHASE2_MOVE];
//extern d_state state;
void disp_state(d_state x);
void init_state(d_state* x);
void clear_state(d_state* x);
void init_move();
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
void search(d_state start);
d_state* get_state_value_address();
void phase1_motion(d_state* x, int i);
void phase2_motion(d_state* x, int i);
void init_motion_list();
int read_csv_file();
#endif
