#include"rubiks_cube_solver.h"
static int co_move_table[NUM_CO][PHASE1_MOVE];
static int eo_move_table[NUM_EO][PHASE1_MOVE];
static int e_con_move_table[NUM_E_CON][PHASE1_MOVE];
static int cp_move_table[NUM_CP][PHASE2_MOVE];
static int ud_ep_move_table[NUM_UD_EP][PHASE2_MOVE];
static int e_ep_move_table[NUM_E_EP][PHASE2_MOVE];
static int co_e_con_prune_table[NUM_CO][NUM_E_CON];
static int eo_e_con_prune_table[NUM_EO][NUM_E_CON];
static int cp_e_ep_prune_table[NUM_CP][NUM_E_EP];
static int ud_ep_e_ep_prune_table[NUM_UD_EP][NUM_E_EP];
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
int get_co_move_table(int co,int mv) {
	return co_move_table[co][mv];
}
int get_eo_move_table(int eo,int mv) {
	return eo_move_table[eo][mv];
}
int get_e_con_move_table(int e_con,int mv) {
	return e_con_move_table[e_con][mv];
}
int get_cp_move_table(int cp,int mv) {
	return cp_move_table[cp][mv];
}
int get_ud_ep_move_table(int ud_ep,int mv) {
	return ud_ep_move_table[ud_ep][mv];
}
int get_e_ep_move_table(int e_ep,int mv) {
	return e_ep_move_table[e_ep][mv];
}
int get_co_e_con_prune_table(int co,int e_com) {
	return co_e_con_prune_table[co][e_com];
}
int get_eo_e_con_prune_table(int eo,int e_con) {
	return eo_e_con_prune_table[eo][e_con];
}
int get_cp_e_ep_prune_table(int cp,int e_ep) {
	return cp_e_ep_prune_table[cp][e_ep];
}
int get_ud_ep_e_ep_prune_table(int ud_ep,int e_ep) {
	return ud_ep_e_ep_prune_table[ud_ep][e_ep];
}
void make_co_move_table(int co, int mv,int val) {
	co_move_table[co][mv] = val;
}
void make_eo_move_table(int eo, int mv,int val) {
	eo_move_table[eo][mv] = val;
}
void make_e_con_move_table(int e_con, int mv,int val) {
	e_con_move_table[e_con][mv] = val;
}
void make_cp_move_table(int cp, int mv,int val) {
	cp_move_table[cp][mv] = val;
}
void make_ud_ep_move_table(int ud_ep, int mv,int val) {
	ud_ep_move_table[ud_ep][mv] = val;
}
void make_e_ep_move_table(int e_ep, int mv,int val) {
	e_ep_move_table[e_ep][mv] = val;
}
void make_co_e_con_prune_table(int co, int e_con,int val) {
	co_e_con_prune_table[co][e_con] = val;
}
void make_eo_e_con_prune_table(int eo, int e_con,int val) {
	eo_e_con_prune_table[eo][e_con] = val;
}
void make_cp_e_ep_prune_table(int cp, int e_ep,int val) {
	cp_e_ep_prune_table[cp][e_ep] = val;
}
void make_ud_ep_e_ep_prune_table(int ud_ep, int e_ep,int val) {
	ud_ep_e_ep_prune_table[ud_ep][e_ep] = val;
}
