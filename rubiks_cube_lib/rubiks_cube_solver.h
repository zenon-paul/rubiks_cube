
/**
*This is a header file for solving rubik's puzzle.
**/

#ifndef RUBIK_CUBE_SOLVER_INCLUDE
#define RUBIK_CUBE_SOLVER_INCLUDE

#include"rubiks_cube_definition.h"

/**
* These are maximum values of index that represent cube's state.
*/
#define NUM_CO 2187
#define NUM_EO 2048
#define NUM_E_CON 495
#define NUM_CP 40320
#define NUM_UD_EP 40320
#define NUM_E_EP 24

/**
* This is type of value that has rubik's cube's state as numbers from 0 to each maximum values.
*/
typedef struct phase1_data {
	int index_co;
	int index_eo;
	int index_e_con;
}d_phase1_state;
typedef struct phase2_data {
	int index_cp;
	int index_ud_ep;
	int index_e_ep;
}d_phase2_state;

/**
* These functions gets index of state after you operate the rubik's cube.
* These return index.
*/
int get_co_move_table(int co, int mv);
int get_eo_move_table(int eo, int mv);
int get_e_con_move_table(int e_con, int mv);
int get_cp_move_table(int cp, int mv);
int get_ud_ep_move_table(int ud_ep, int mv);
int get_e_ep_move_table(int e_ep, int mv);
int get_co_e_con_prune_table(int co, int e_com);
int get_eo_e_con_prune_table(int eo, int e_con);
int get_cp_e_ep_prune_table(int cp, int e_ep);
int get_ud_ep_e_ep_prune_table(int ud_ep, int e_ep);

/**
* These functions make tables of index of state after you operate the rubik's cube.
*/
void make_co_move_table(int co, int mv, int val);
void make_eo_move_table(int eo, int mv, int val);
void make_e_con_move_table(int e_con, int mv, int val);
void make_cp_move_table(int cp, int mv, int val);
void make_ud_ep_move_table(int ud_ep, int mv, int val);
void make_e_ep_move_table(int e_ep, int mv, int val);

/**
* These functions make tables of numbers motion that you need to solve the rubik's cube
* from current state.
*/
void make_co_e_con_prune_table(int co, int e_con, int val);
void make_eo_e_con_prune_table(int eo, int e_con, int val);
void make_cp_e_ep_prune_table(int cp, int e_ep, int val);
void make_ud_ep_e_ep_prune_table(int ud_ep, int e_ep, int val);

/**
* These translate index to state and state to index.
* These functions return index.
*/
int co_to_index(int co[NUM_CORNER]);
void index_to_co(int co[NUM_CORNER], int index);
int eo_to_index(int eo[NUM_EDGE]);
void index_to_eo(int eo[NUM_EDGE], int index);
int e_con_to_index(int e_ep[NUM_EDGE]);
void index_to_e_con(int e_ep[NUM_EDGE], int index);
int cp_to_index(int cp[NUM_CORNER]);
void index_to_cp(int cp[NUM_CORNER], int index);
int ud_ep_to_index(int ep[NUM_EDGE]);
void index_to_ud_ep(int ep[NUM_EDGE], int index);
int e_ep_to_index(int ep[NUM_EDGE]);
void index_to_e_ep(int ep[NUM_EDGE], int index);

/**
* These functions operates rubik's cube and reflects the change cube's state of index.
*/
void move1(d_phase1_state from1, d_phase1_state* to1, int move);
void move2(d_phase2_state from2, d_phase2_state* to2, int move);

/**
* These functions make tables.
* You need to make transfer table and prune table before start search.
*/
void init_transfer_table();
void init_prune_table();

/**
* This function set timer.
* The longer time you set ,the smaller number of motion you cost.
* This is becouse that the algorithm can get more sample of solution
* that may smaller solution than any solutions that it has found.
*/
void init_timer(int second);

/**
* This function starts search.
*/
void search(d_state start0);
#endif
