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
#define NUM_FACE 6
#define NUM_FOUR_CORNER 4
#define NUM_3_SQUARED 9
#define TIMELIMIT 5

#define R_CENTER 4
#define L_CENTER 13
#define F_CENTER 22
#define B_CENTER 31
#define U_CENTER 40
#define D_CENTER 49

#define QLIM 40
#define FILENAME 32

typedef struct s_data {
	int cp[NUM_CORNER];
	int co[NUM_CORNER];
	int ep[NUM_EDGE];
	int eo[NUM_EDGE];
}d_state;

typedef void(*func)(d_state*);
extern char from_index_to_motion[PHASE1_MOVE][3];
void disp_state(d_state cube_state);
void init_state(d_state* cube_state);
void clear_state(d_state* cube_state);
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
void init_cube_state(d_state* cube_state);
int* get_motion_list_address();
void init_motion_list(int* list);
int* get_motion_count_address();
void init_motion_count(int* count);
void phase1_motion(d_state* cube_state, int index);
void phase2_motion(d_state* cube_state, int index);
void copy_state(d_state from, d_state* to);
void shuffle(d_state* cube_state, char query[QLIM][3], int size);
int read_csv_file(d_state* input,const char file_name[FILENAME]);
#endif
