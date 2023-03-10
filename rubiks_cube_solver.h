#ifndef RUBIK_CUBE_SOLVER_INCLUDE
#define RUBIK_CUBE_SOLVER_INCLUDE
/**
*This is a header file for solving rubik's puzzle.
*
*
**/

#include"rubiks_cube_definition.h"

#define QLIM 40
#define NUM_CORNER 8
#define NUM_EDGE 12
#define NUM_CO 2187
#define NUM_EO 2048
#define NUM_E_CON 495
#define NUM_CP 40320
#define NUM_UD_EP 40320
#define NUM_E_EP 24

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

extern func phase1_move[PHASE1_MOVE];
extern func phase2_move[PHASE2_MOVE];
extern int co_move_table[NUM_CO][PHASE1_MOVE];
extern int eo_move_table[NUM_EO][PHASE1_MOVE];
extern int e_con_move_table[NUM_E_CON][PHASE1_MOVE];
extern int cp_move_table[NUM_CP][PHASE2_MOVE];
extern int ud_ep_move_table[NUM_UD_EP][PHASE2_MOVE];
extern int e_ep_move_table[NUM_E_EP][PHASE2_MOVE];
extern int co_e_con_prune_table[NUM_CO][NUM_E_CON];
extern int eo_e_con_prune_table[NUM_EO][NUM_E_CON];
extern int cp_e_ep_prune_table[NUM_CP][NUM_E_EP];
extern int ud_ep_e_ep_prune_table[NUM_UD_EP][NUM_E_EP];

int co_to_index(int co[8]);
void index_to_co(int co[8], int index);
int eo_to_index(int eo[12]);
void index_to_eo(int eo[12], int index);
int e_con_to_index(int e_ep[12]);
void index_to_e_con(int e_ep[12], int index);
int cp_to_index(int cp[8]);
void index_to_cp(int cp[8], int index);
int ud_ep_to_index(int ep[12]);
void index_to_ud_ep(int ep[12], int index);
int e_ep_to_index(int ep[12]);
void index_to_e_ep(int ep[12], int index);
void move1(d_phase1_state from1, d_phase1_state* to1, int move);
void move2(d_phase2_state from2, d_phase2_state* to2, int move);
void init_transfer_table();
void init_prune_table();
void shuffle(d_state* x, char q[QLIM][3], int n);
void pre_process_for_start_starch();
void start_search(d_state start0);
#endif
