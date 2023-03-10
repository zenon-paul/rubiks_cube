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
extern func phase1_move[PHASE1_MOVE];
extern func phase2_move[PHASE2_MOVE];
extern int coorresponding_table_from_phase2_move_to_phase1_move[PHASE2_MOVE];
extern d_state state;
void disp_state(d_state x);
void init_state(d_state* x);
void clear_state(d_state* x);
void make_r(d_state* x);
void make_b(d_state* x);
void make_l(d_state* x);
void make_f(d_state* x);
void make_u(d_state* x);
void make_d(d_state* x);
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
void start_search(d_state start0);
#endif
