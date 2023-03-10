#include"rubiks_cube_solver.h"
int co_move_table[NUM_CO][PHASE1_MOVE];
int eo_move_table[NUM_EO][PHASE1_MOVE];
int e_con_move_table[NUM_E_CON][PHASE1_MOVE];
int cp_move_table[NUM_CP][PHASE2_MOVE];
int ud_ep_move_table[NUM_UD_EP][PHASE2_MOVE];
int e_ep_move_table[NUM_E_EP][PHASE2_MOVE];
int co_e_con_prune_table[NUM_CO][NUM_E_CON];
int eo_e_con_prune_table[NUM_EO][NUM_E_CON];
int cp_e_ep_prune_table[NUM_CP][NUM_E_EP];
int ud_ep_e_ep_prune_table[NUM_UD_EP][NUM_E_EP];
void move1(d_phase1_state from1, d_phase1_state* to1, int move) {
	to1->index_co = co_move_table[from1.index_co][move];
	to1->index_eo = eo_move_table[from1.index_eo][move];
	to1->index_e_con = e_con_move_table[from1.index_e_con][move];
}
void move2(d_phase2_state from2, d_phase2_state* to2, int move) {
	to2->index_cp = cp_move_table[from2.index_cp][move];
	to2->index_ud_ep = ud_ep_move_table[from2.index_ud_ep][move];
	to2->index_e_ep = e_ep_move_table[from2.index_e_ep][move];
}
