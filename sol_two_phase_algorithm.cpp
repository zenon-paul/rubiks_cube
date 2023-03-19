#include"rubiks_cube_solver.h"
#include<stdio.h>
#include <time.h>
static int path1[VECTOR_LEN] = { 0 };
static int path2[VECTOR_LEN] = { 0 };
static int mnum1 = 0;
static int mnum2 = 0;
static int min_mnum1 = 0;
static int min_mnum2 = 0;
static int min_motion_count = 0;
static int is_time_out = 0;
static int time_limit = TIMELIMIT;
static time_t start_time;
static int coorresponding_table_from_phase2_move_to_phase1_move[PHASE2_MOVE] = { 12,13,14,15,16,17,4,5,10,11 };
static void phase2_solver(d_phase2_state start);
static int is_phase1_move_available(int premove, int currmove) {
	if (premove == PHASE1_MOVE) {
		return 1;
	}
	else if (currmove % NUM_FACE == premove % NUM_FACE) {
		return 0;
	}
	else if ((premove % NUM_FACE) % 2 == 1) {
		if (currmove % NUM_FACE == (premove - 1) % NUM_FACE) {
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
static int phase1_ida_star(d_state s_from1,d_phase1_state from1, int current, int count, int depth) {
	int f = 1;
	time_t now_time;
	now_time = time(NULL);

	if ((now_time - start_time)>time_limit) {
		is_time_out = 1;
		return 1;
	}

	if (((depth - count) < get_co_e_con_prune_table(from1.index_co, from1.index_e_con)) || ((depth - count) < get_eo_e_con_prune_table(from1.index_eo, from1.index_e_con))) {
		return 1;
	}

	if (is_solved_phase1(from1)) {

		d_phase2_state state2;
		state2.index_cp = cp_to_index(s_from1.cp);
		state2.index_ud_ep = ud_ep_to_index(s_from1.ep);
		state2.index_e_ep = e_ep_to_index(s_from1.ep);
		phase2_solver(state2);

		if (mnum1 + mnum2 < min_motion_count) {
			min_mnum1 = mnum1;
			min_mnum2 = mnum2;
			min_motion_count = mnum1 + mnum2;
			int count = 0;
			for (int i = 0; i < mnum2;i++) {
				get_motion_list_address()[count] = coorresponding_table_from_phase2_move_to_phase1_move[path2[i]];
				count++;
			}
			for (int i = mnum1-1; i >= 0;i--) {
				get_motion_list_address()[count] = path1[i];
				count++;
			}
		}
		mnum2 = 0;
	}
	
	for (int i = 0; i < PHASE1_MOVE; i++) {
		if (is_phase1_move_available(current, i)) {
			path1[mnum1] = i;
			mnum1++;

			d_state s_to1;
			d_phase1_state to1;

			copy_state(s_from1,&s_to1);
			phase1_motion(&s_to1,i);
			move1(from1, &to1, i);
			f = phase1_ida_star(s_to1,to1, i, count + 1, depth);
			mnum1--;

			if (is_time_out) {
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
	if (((depth - count) < get_cp_e_ep_prune_table(from2.index_cp,from2.index_e_ep)) || ((depth - count) < get_ud_ep_e_ep_prune_table(from2.index_ud_ep,from2.index_e_ep))) {
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
static void phase1_solver(d_state s,d_phase1_state start) {
	int depth = 0;
	while (phase1_ida_star(s,start, PHASE1_MOVE, 0, depth)) {
		depth++;
	}
}
static void phase2_solver(d_phase2_state start) {
	int depth = 0;
	while (phase2_ida_star(start, PHASE2_MOVE, 0, depth)) {
		depth++;
	}
}
static void revert_to__initial_state() {
	is_time_out = 0;
	min_motion_count = 0;
	min_mnum1 = 0;
	min_mnum2 = 0;
	mnum1 = 0;
	mnum2 = 0;
}
static void set_timer() {
	start_time = time(NULL);
}
void init_timer(int second) {
	time_limit = second;
}
void search(d_state start) {
	printf(">serche start\n");
	disp_state(*get_state_value_address());

	min_motion_count = VECTOR_LEN;

	d_phase1_state state1;
	
	state1.index_co = co_to_index(start.co);
	state1.index_eo = eo_to_index(start.eo);
	state1.index_e_con = e_con_to_index(start.ep);

	set_timer();

	phase1_solver(start,state1);

	*get_motion_count_address() = min_motion_count;

	revert_to__initial_state();


	printf("[");
	for (int i = *get_motion_count_address() - 1; i >= 0; i--) {
		printf("%s ", from_index_to_motion[get_motion_list_address()[i]]);
	}
	printf("motion_count(%d)\n", *get_motion_count_address());
} 
