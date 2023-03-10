#include"rubiks_cube_solver.h"
#include<stdio.h>
static int is_phase1_move_available(int premove, int currmove) {
	if (premove == PHASE1_MOVE) {
		return 1;
	}
	else if (currmove % 6 == premove % 6) {
		return 0;
	}
	else if ((premove % 6) % 2 == 1) {
		if (currmove % 6 == (premove - 1) % 6) {
			return 0;
		}
		else {
			return 1;
		}
	}
	else {
		return 1;
	}
}
static int is_phase2_move_available(int premove, int currmove) {
	if (premove == PHASE2_MOVE) {
		return 1;
	}
	else if (premove % 2 == 1) {
		if (premove - 1 == currmove) {
			return 0;
		}
		else {
			return 1;
		}
	}
	else if (premove == 9) {
		if ((4 <= currmove) && (currmove <= 9)) {
			return 0;
		}
		else {
			return 1;
		}
	}
	else if (premove == 7) {
		if ((4 <= currmove) && (currmove <= 9)) {
			return 0;
		}
		else {
			return 1;
		}
	}
	else if (premove == 5) {
		if ((4 <= currmove) && (currmove <= 9)) {
			return 0;
		}
		else {
			return 1;
		}
	}
	else if ((4 <= premove) && (4 <= currmove)) {
		if (premove % 2 == currmove % 2) {
			return 0;
		}
		else {
			return 1;
		}
	}
	else {
		return 1;
	}
}
void shuffle(d_state* x, char q[QLIM][3], int n) {
	for (int i = 0; i < n; i++) {
		switch (q[i][0]) {
		case 'R':
			if (q[i][1] == '\0') {
				R(x);
			}
			else if (q[i][1] == '2') {
				R2(x);
			}
			else if (q[i][1] == '_') {
				R_(x);
			}
			else {
				break;
			}
			break;
		case 'B':
			if (q[i][1] == '\0') {
				B(x);
			}
			else if (q[i][1] == '2') {
				B2(x);
			}
			else if (q[i][1] == '_') {
				B_(x);
			}
			else {
				break;
			}
			break;
		case 'L':
			if (q[i][1] == '\0') {
				L(x);
			}
			else if (q[i][1] == '2') {
				L2(x);
			}
			else if (q[i][1] == '_') {
				L_(x);
			}
			else {
				break;
			}
			break;
		case 'F':
			if (q[i][1] == '\0') {
				F(x);
			}
			else if (q[i][1] == '2') {
				F2(x);
			}
			else if (q[i][1] == '_') {
				F_(x);
			}
			else {
				break;
			}
			break;
		case 'U':
			if (q[i][1] == '\0') {
				U(x);
			}
			else if (q[i][1] == '2') {
				U2(x);
			}
			else if (q[i][1] == '_') {
				U_(x);
			}
			else {
				break;
			}
			break;
		case 'D':
			if (q[i][1] == '\0') {
				D(x);
			}
			else if (q[i][1] == '2') {
				D2(x);
			}
			else if (q[i][1] == '_') {
				D_(x);
			}
			else {
				break;
			}
			break;
		default:
			break;

		}
	}
}
static int is_solved_phase1(d_phase1_state x) {
	if ((x.index_co == 0) && (x.index_eo == 0) && (x.index_e_con == 0)) {
		return 1;
	}
	else {
		return 0;
	}
}
static int is_solved_phase2(d_phase2_state x) {
	if ((x.index_cp == 0) && (x.index_ud_ep == 0) && (x.index_e_ep == 0)) {
		return 1;
	}
	else {
		return 0;
	}
}
static int phase1_ida_star(d_phase1_state from1, int current, int count, int depth) {
	int f = 1;
	if (is_solved_phase1(from1)) {
		return 0;
	}
	if (((depth - count) < co_e_con_prune_table[from1.index_co][from1.index_e_con]) || ((depth - count) < eo_e_con_prune_table[from1.index_eo][from1.index_e_con])) {
		return 1;
	}
	for (int i = 0; i < PHASE1_MOVE; i++) {
		if (is_phase1_move_available(current, i)) {
			d_phase1_state to1;
			move1(from1, &to1, i);
			f = phase1_ida_star(to1, i, count + 1, depth);
			path1[mnum1] = i;
			if (f == 0) {
				mnum1++;
				return 0;
			}
		}
	}
	return 1;
}
static int phase2_ida_star(d_phase2_state from2, int current, int count, int depth) {
	int f = 1;
	if (is_solved_phase2(from2)) {
		return 0;
	}
	if (((depth - count) < cp_e_ep_prune_table[from2.index_cp][from2.index_e_ep]) || ((depth - count) < ud_ep_e_ep_prune_table[from2.index_ud_ep][from2.index_e_ep])) {
		return 1;
	}
	for (int i = 0; i < PHASE2_MOVE; i++) {
		if (is_phase2_move_available(current, i)) {
			d_phase2_state to2;
			move2(from2, &to2, i);
			f = phase2_ida_star(to2, i, count + 1, depth);
			path2[mnum2] = i;
			if (f == 0) {
				mnum2++;
				return 0;
			}
		}
	}
	return 1;
}
static void phase1_solver(d_phase1_state start) {
	int depth = 0;
	while (phase1_ida_star(start, PHASE1_MOVE, 0, depth)) {
		depth++;
	}
}
static void phase2_solver(d_phase2_state start) {
	int depth = 0;
	while (phase2_ida_star(start, PHASE2_MOVE, 0, depth)) {
		depth++;
	}
}
void pre_process_for_start_starch() {
	init_move();
	init_transfer_table();
	init_prune_table();
}
void start_search(d_state start0) {
	d_phase1_state state1;
	d_phase2_state state2;
	int qnum = 0;
	char query[QLIM][3] = { 0 };
	state1.index_co = co_to_index(start0.co);
	state1.index_eo = eo_to_index(start0.eo);
	state1.index_e_con = e_con_to_index(start0.ep);
	phase1_solver(state1);
	printf("%d \n",mnum1);
	printf("\n[");
	for (int i = mnum1 - 1; i >= 0; i--) {
		(phase1_move[path1[i]])(&start0);
		printf("%d ", path1[i]);
	}
	printf("\n");
	state2.index_cp = cp_to_index(start0.cp);
	state2.index_ud_ep = ud_ep_to_index(start0.ep);
	state2.index_e_ep = e_ep_to_index(start0.ep);
	phase2_solver(state2);
	printf("%d \n", mnum2);
	printf("\n[");
	for (int i = mnum2 - 1; i >= 0; i--) {
		printf("%d ", path2[i]);
	}
	printf("\n");
} 
