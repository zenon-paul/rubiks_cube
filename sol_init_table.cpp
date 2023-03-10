#include"rubiks_cube_solver.h"
#include<stdio.h>
static void make_co_move_table() {
	for (int i = 0; i < NUM_CO; i++) {
		for (int j = 0; j < PHASE1_MOVE; j++) {
			d_state sample;
			clear_state(&sample);
			index_to_co(sample.co, i);
			(phase1_move[j])(&sample);
			co_move_table[i][j] = co_to_index(sample.co);
		}
	}
}
static void make_eo_move_table() {
	for (int i = 0; i < NUM_EO; i++) {
		for (int j = 0; j < PHASE1_MOVE; j++) {
			d_state sample;
			clear_state(&sample);
			index_to_eo(sample.eo, i);
			(phase1_move[j])(&sample);
			eo_move_table[i][j] = eo_to_index(sample.eo);
		}
	}
}
static void make_e_con_move_table() {
	for (int i = 0; i < NUM_E_CON; i++) {
		for (int j = 0; j < PHASE1_MOVE; j++) {
			d_state sample;
			clear_state(&sample);
			index_to_e_con(sample.ep, i);
			int r = 0;
			int l = 0;
			for (int k = 0; k < 12; k++) {
				if (sample.ep[k]) {
					sample.ep[k] = r;
					r++;
				}
				else {
					sample.ep[k] = 4 + l;
					l++;
				}
			}
			(phase1_move[j])(&sample);
			e_con_move_table[i][j] = e_con_to_index(sample.ep);
		}

	}
}
static void make_cp_move_tanle() {
	for (int i = 0; i < NUM_CP; i++) {
		for (int j = 0; j < PHASE2_MOVE; j++) {
			d_state sample;
			clear_state(&sample);
			index_to_cp(sample.cp, i);
			cp_move_table[i][j] = cp_to_index(sample.cp);
			(phase2_move[j])(&sample);
			cp_move_table[i][j] = cp_to_index(sample.cp);
		}
	}
}
static void make_ud_ep_move_table() {
	for (int i = 0; i < NUM_UD_EP; i++) {
		for (int j = 0; j < PHASE2_MOVE; j++) {
			d_state sample;
			clear_state(&sample);
			index_to_ud_ep(sample.ep, i);
			for (int k = 0; k < 4; k++) {
				sample.ep[k] = k;
			}
			for (int k = 0 + 4; k < 8 + 4; k++) {
				sample.ep[k] += 4;
			}
			(phase2_move[j])(&sample);
			ud_ep_move_table[i][j] = ud_ep_to_index(sample.ep);
		}
	}
}
static void make_e_ep_move_table() {
	for (int i = 0; i < NUM_E_EP; i++) {
		for (int j = 0; j < PHASE2_MOVE; j++) {
			d_state sample;
			clear_state(&sample);
			index_to_e_ep(sample.ep, i);
			for (int k = 0 + 4; k < 8 + 4; k++) {
				sample.ep[k] = k;
			}
			(phase2_move[j])(&sample);
			e_ep_move_table[i][j] = e_ep_to_index(sample.ep);
		}
	}
}
void init_transfer_table() {
	make_co_move_table();
	printf("co_move_finished \n");
	make_eo_move_table();
	printf("eo_move_finished \n");
	make_e_con_move_table();
	printf("e_con_move_finished \n");
	make_cp_move_tanle();
	printf("cp_move_finished \n");
	make_ud_ep_move_table();
	printf("ud_ep_move_finished \n");
	make_e_ep_move_table();
	printf("e_ep_move_finished \n");
}
static void make_phase1_co_e_con_prune_table() {
	for (int i = 0; i < NUM_CO; i++) {
		for (int j = 0; j < NUM_E_CON; j++) {
			co_e_con_prune_table[i][j] = -1;
		}
	}
	co_e_con_prune_table[0][0] = 0;
	int dist = 0;
	int filled_num = 1;
	while (filled_num < NUM_CO * NUM_E_CON) {
		for (int i = 0; i < NUM_CO; i++) {
			for (int j = 0; j < NUM_E_CON; j++) {
				if (co_e_con_prune_table[i][j] == dist) {
					for (int k = 0; k < PHASE1_MOVE; k++) {
						int next_co = co_move_table[i][k];
						int next_e_con = e_con_move_table[j][k];
						if (co_e_con_prune_table[next_co][next_e_con] == -1) {
							co_e_con_prune_table[next_co][next_e_con] = dist + 1;
							filled_num++;
						}
					}
				}
			}
		}
		dist++;
	}
}
static void make_phase1_eo_e_con_prune_table() {
	for (int i = 0; i < NUM_EO; i++) {
		for (int j = 0; j < NUM_E_CON; j++) {
			eo_e_con_prune_table[i][j] = -1;
		}
	}
	eo_e_con_prune_table[0][0] = 0;
	int dist = 0;
	int filled_num = 1;
	while (filled_num < NUM_EO * NUM_E_CON) {
		for (int i = 0; i < NUM_EO; i++) {
			for (int j = 0; j < NUM_E_CON; j++) {
				if (eo_e_con_prune_table[i][j] == dist) {
					for (int k = 0; k < PHASE1_MOVE; k++) {
						int next_eo = eo_move_table[i][k];
						int next_e_con = e_con_move_table[j][k];
						if (eo_e_con_prune_table[next_eo][next_e_con] == -1) {
							eo_e_con_prune_table[next_eo][next_e_con] = dist + 1;
							filled_num++;
						}
					}
				}
			}
		}
		dist++;
	}
}
static void make_phase1_prune_table() {
	make_phase1_co_e_con_prune_table();
	printf("phase1_co_e_con_finished \n");
	make_phase1_eo_e_con_prune_table();
	printf("phase1_eo_e_con_finished \n");
}
static void make_phase2_cp_e_ep_prune_table() {
	for (int i = 0; i < NUM_CP; i++) {
		for (int j = 0; j < NUM_E_EP; j++) {
			cp_e_ep_prune_table[i][j] = -1;
		}
	}
	cp_e_ep_prune_table[0][0] = 0;
	int dist = 0;
	int filled_num = 1;
	while (filled_num < NUM_CP * NUM_E_EP) {
		for (int i = 0; i < NUM_CP; i++) {
			for (int j = 0; j < NUM_E_EP; j++) {
				if (cp_e_ep_prune_table[i][j] == dist) {
					for (int k = 0; k < PHASE2_MOVE; k++) {
						int next_cp = cp_move_table[i][k];
						int next_e_ep = e_ep_move_table[j][k];
						if (cp_e_ep_prune_table[next_cp][next_e_ep] == -1) {
							cp_e_ep_prune_table[next_cp][next_e_ep] = dist + 1;
							filled_num++;
						}
					}
				}
			}
		}
		dist++;
	}
}
static void make_phase2_ud_ep_e_ep_prune_table() {
	for (int i = 0; i < NUM_UD_EP; i++) {
		for (int j = 0; j < NUM_E_EP; j++) {
			ud_ep_e_ep_prune_table[i][j] = -1;
		}
	}
	ud_ep_e_ep_prune_table[0][0] = 0;
	int dist = 0;
	int filled_num = 1;
	while (filled_num < NUM_UD_EP * NUM_E_EP) {
		for (int i = 0; i < NUM_UD_EP; i++) {
			for (int j = 0; j < NUM_E_EP; j++) {
				if (ud_ep_e_ep_prune_table[i][j] == dist) {
					for (int k = 0; k < PHASE2_MOVE; k++) {
						int next_ud_ep = ud_ep_move_table[i][k];
						int next_e_ep = e_ep_move_table[j][k];
						if (ud_ep_e_ep_prune_table[next_ud_ep][next_e_ep] == -1) {
							ud_ep_e_ep_prune_table[next_ud_ep][next_e_ep] = dist + 1;
							filled_num++;
						}
					}
				}
			}
		}
		dist++;
	}
}
static void make_phase2_prune_table() {
	make_phase2_cp_e_ep_prune_table();
	printf("phase2_cp_e_ep_finished \n");
	make_phase2_ud_ep_e_ep_prune_table();
	printf("phase2_ud_ep_e_ep_finished \n");
}
void init_prune_table() {
	make_phase1_prune_table();
	make_phase2_prune_table();
	printf("finished!\n");
}
