#ifndef RUBIK_CUBE_SOLVER_INCLUDE
#define RUBIK_CUBE_SOLVER_INCLUDE
/**
*This is a header file for solving rubik's puzzle.
*
*
**/

#include"rubiks_cube_definition.h"

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

extern int co_move_table[NUM_CO][PHASE1_MOVE];
extern int eo_move_table[NUM_EO][PHASE1_MOVE];
extern int e_con_move_table[NUM_E_CON][PHASE1_MOVE];
extern int cp_move_table[NUM_CP][PHASE2_MOVE];
extern int ud_ep_move_table[NUM_UD_EP][PHASE2_MOVE];
extern int e_ep_move_table[NUM_E_EP][PHASE2_MOVE];

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
void updata_co_move_table(int co, int mv, int val);
void updata_eo_move_table(int eo, int mv, int val);
void updata_e_con_move_table(int e_con, int mv, int val);
void updata_cp_move_table(int cp, int mv, int val);
void updata_ud_ep_move_table(int ud_ep, int mv, int val);
void updata_e_ep_move_table(int e_ep, int mv, int val);
void updata_co_e_con_prune_table(int co, int e_con, int val);
void updata_eo_e_con_prune_table(int eo, int e_con, int val);
void updata_cp_e_ep_prune_table(int cp, int e_ep, int val);
void updata_ud_ep_e_ep_prune_table(int ud_ep, int e_ep, int val);

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
void move1(d_phase1_state from1, d_phase1_state* to1, int move);
void move2(d_phase2_state from2, d_phase2_state* to2, int move);
void init_transfer_table();
void init_prune_table();
void init_timer(int second);
void search(d_state start0);
#endif
