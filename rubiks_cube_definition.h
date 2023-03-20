/**
* This is a header file for definition rubik's cube.
**/


#ifndef RUBIKS_CUBE_DEFINITION_INCLUDE
#define RUBIKS_CUBE_DEFINITION_INCLUDE


/**
* The numbers of motion that is available in phase1 or phase2. 
*/
#define PHASE1_MOVE 18
#define PHASE2_MOVE 10

/**
* The numbers of oparation the rubik's cube.
*/
#define MOVE 18

/**
* The numbers of corners , edges , feces , corners that one square has ,
* squares that one face of rubik's cube has and squares that one rubik's cube has.
*/
#define NUM_CORNER 8
#define NUM_EDGE 12
#define NUM_FACE 6
#define NUM_FOUR_CORNER 4
#define NUM_SQUARES_IN_ONE_FACE 9
#define NUM_ALL_SQUARES 54

/**
* This values are used to make value of type "d_state" from csv file. 
*/
#define R_CENTER 4
#define L_CENTER 13
#define F_CENTER 22
#define B_CENTER 31
#define U_CENTER 40
#define D_CENTER 49

/**
* The values of size for arrays.
*/
#define QUERY_SIZE 120
#define FILENAME 32
#define BUFFER_SIZE 64
#define INPUT_FILE_SIZE 120

/**
* This is initial value of time limit of phase1.
*/
#define TIMELIMIT 5

/**
* This is type of value that has rubik's cube's state. 
*/
typedef struct s_data {
	int cp[NUM_CORNER];
	int co[NUM_CORNER];
	int ep[NUM_EDGE];
	int eo[NUM_EDGE];
}d_state;

/**
* This is type of value that has pointer of function that operate rubik's cube.
*/
typedef void(*func)(d_state*);

/**
* This finction displays state of rubik's cube.
*/
void disp_state(d_state cube_state);

/**
* This finction makes state of solved rubik's cube.
*/
void make_solved_state(d_state* cube_state);

/**
* This finction makes state of rubik's cube zero.
*/
void clear_state(d_state* cube_state);

/**
* This finction makes motion data of rubik's cube.
*/
void init_motion();

/**
* These are finction operate rubik's cube.
*/
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

/**
* This function starts to search a way to solve the rubik's cube.
*/
void search(d_state start);

/**
* This function gets address of value that has rubik's cube's state.
* This returns address of the value.
*/
d_state* get_state_value_address();

/**
* This function registers pointer of the rubik's cube's state.
*/
void init_cube_state(d_state* cube_state);

/**
* This function gets address of list that has the way of solution for rubik's cube.
* This returns address of the list.
*/
int* get_motion_list_address();

/**
* This function registers pointer of the rubik's cube's solutin list.
*/
void init_motion_list(int* list);

/**
* This function gets address of list that has number of motions that you cost to solve the rubik's cube.
* This returns address of the value.
*/
int* get_motion_count_address();

/**
* This function registers pointer of value that has number of motion.
*/
void init_motion_count(int* count);

/**
* This function starts phase1 search.
*/
void phase1_motion(d_state* cube_state, int index);

/**
* This function starts phase2 search.
*/
void phase2_motion(d_state* cube_state, int index);

/**
* This function copies value of rubik's cube state.
*/
void copy_state(d_state from, d_state* to);

/**
* This function operates rubik's cube and reflects the change cube's state.
*/
void shuffle(d_state* cube_state, char query[INPUT_FILE_SIZE][3], int size);

/**
* This function resds csv file and makes rubik's cube's state.
* This returns 1 when it sucseeds and returns 0 when it fails.
*/
int read_csv_file(d_state* input,const char file_name[FILENAME]);

/**
* This function reads text file and makes rubik's cube's state.
* This returns 1 whene it sucseeds and returns 0 whene it fails.
*/
int read_text_file(d_state* input, const char file_name[FILENAME]);

/**
* This function gets text motion name.
* This returns address of array that you specify as second argument.
*/
char* get_motion_name_from_index(int index,char* name,int length);

/**
* This function gets the index of opposite motion of argument.
* This returns index of motion.
*/
int get_reverse_motion(int index);
#endif
