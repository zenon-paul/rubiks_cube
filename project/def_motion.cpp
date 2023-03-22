#include"rubiks_cube_definition.h"
#include<stdio.h>

static char comment = '#';
static int* motion_count;
static int* motion_list;
static int reverse_motion[PHASE1_MOVE] = {6,7,8,9,10,11,0,1,2,3,4,5,12,13,14,15,16,17};
static char from_index_to_motion[PHASE1_MOVE][3] = { "R","L","F","B","U","D","R_","L_","F_","B_","U_","D_","R2","L2","F2","B2","U2","D2"};
static func phase1_move[PHASE1_MOVE] = { R,L,F,B,U,D,R_,L_,F_,B_,U_,D_,R2,L2,F2,B2,U2,D2 };
static func phase2_move[PHASE2_MOVE] = { R2,L2,F2,B2,U2,D2,U,D,U_,D_ };
static d_state r;
static d_state b;
static d_state l;
static d_state f;
static d_state u;
static d_state d;
static d_state* state;
static int corner_identification_table[NUM_CORNER][3] = {
	{9,29,36},
	{2,27,38},
	{0,20,44},
	{11,18,42},
	{15,35,51},
	{8,33,53},
	{6,26,47},
	{17,24,45}
};
static int edge_identification_table[NUM_EDGE][2] = {
	{12,32},
	{5,30},
	{3,23},
	{14,21},
	{28,37},
	{1,41},
	{19,43},
	{10,39},
	{34,52},
	{7,50},
	{25,46},
	{16,48}
};
static int corner_index_table[65] = { 0 };
static int edge_index_table[65] = { 0 };
static int center_color_index[128] = { 0 };
static char center_color_value[6] = { 0 };
void disp_state(d_state cube_state) {
	for (int i = 0; i < 8; i++) {
		printf("%d ", cube_state.cp[i]);
	}
	printf("\n");
	for (int i = 0; i < 8; i++) {
		printf("%d ", cube_state.co[i]);
	}
	printf("\n");
	for (int i = 0; i < 12; i++) {
		printf("%d ", cube_state.ep[i]);
	}
	printf("\n");
	for (int i = 0; i < 12; i++) {
		printf("%d ", cube_state.eo[i]);
	}
	printf("\n");
}
void make_solved_state(d_state* cube_state) {
	for (int i = 0; i < 8; i++) {
		cube_state->cp[i] = i;
		cube_state->co[i] = 0;
	}
	for (int i = 0; i < 12; i++) {
		cube_state->ep[i] = i;
		cube_state->eo[i] = 0;
	}
}
void clear_state(d_state* cube_state) {
	for (int i = 0; i < 8; i++) {
		cube_state->cp[i] = 0;
		cube_state->co[i] = 0;
	}
	for (int i = 0; i < 12; i++) {
		cube_state->ep[i] = 0;
		cube_state->eo[i] = 0;
	}
}
static void make_r(d_state* x) {////
	x->cp[0] = 0;
	x->cp[1] = 2;
	x->cp[2] = 6;
	x->cp[3] = 3;
	x->cp[4] = 4;
	x->cp[5] = 1;
	x->cp[6] = 5;
	x->cp[7] = 7;

	x->ep[0] = 0;
	x->ep[1] = 5;
	x->ep[2] = 9;
	x->ep[3] = 3;
	x->ep[4] = 4;
	x->ep[5] = 2;
	x->ep[6] = 6;
	x->ep[7] = 7;
	x->ep[8] = 8;
	x->ep[9] = 1;
	x->ep[10] = 10;
	x->ep[11] = 11;

	x->co[0] = 0;
	x->co[1] = 1;
	x->co[2] = 2;
	x->co[3] = 0;
	x->co[4] = 0;
	x->co[5] = 2;
	x->co[6] = 1;
	x->co[7] = 0;

	for (int i = 0; i < 12; i++) {
		x->eo[i] = 0;
	}
}
static void make_b(d_state* x) {////
	x->cp[0] = 1;
	x->cp[1] = 5;
	x->cp[2] = 2;
	x->cp[3] = 3;
	x->cp[4] = 0;
	x->cp[5] = 4;
	x->cp[6] = 6;
	x->cp[7] = 7;

	x->ep[0] = 4;
	x->ep[1] = 8;
	x->ep[2] = 2;
	x->ep[3] = 3;
	x->ep[4] = 1;
	x->ep[5] = 5;
	x->ep[6] = 6;
	x->ep[7] = 7;
	x->ep[8] = 0;
	x->ep[9] = 9;
	x->ep[10] = 10;
	x->ep[11] = 11;

	x->co[0] = 1;
	x->co[1] = 2;
	x->co[2] = 0;
	x->co[3] = 0;
	x->co[4] = 2;
	x->co[5] = 1;
	x->co[6] = 0;
	x->co[7] = 0;

	x->eo[0] = 1;
	x->eo[1] = 1;
	x->eo[2] = 0;
	x->eo[3] = 0;
	x->eo[4] = 1;
	x->eo[5] = 0;
	x->eo[6] = 0;
	x->eo[7] = 0;
	x->eo[8] = 1;
	x->eo[9] = 0;
	x->eo[10] = 0;
	x->eo[11] = 0;
}
static void make_l(d_state* x) {////
	x->cp[0] = 4;
	x->cp[1] = 1;
	x->cp[2] = 2;
	x->cp[3] = 0;
	x->cp[4] = 7;
	x->cp[5] = 5;
	x->cp[6] = 6;
	x->cp[7] = 3;

	x->ep[0] = 11;
	x->ep[1] = 1;
	x->ep[2] = 2;
	x->ep[3] = 7;
	x->ep[4] = 4;
	x->ep[5] = 5;
	x->ep[6] = 6;
	x->ep[7] = 0;
	x->ep[8] = 8;
	x->ep[9] = 9;
	x->ep[10] = 10;
	x->ep[11] = 3;

	x->co[0] = 2;
	x->co[1] = 0;
	x->co[2] = 0;
	x->co[3] = 1;
	x->co[4] = 1;
	x->co[5] = 0;
	x->co[6] = 0;
	x->co[7] = 2;

	for (int i = 0; i < 12; i++) {
		x->eo[i] = 0;
	}
}
static void make_f(d_state* x) {////
	x->cp[0] = 0;
	x->cp[1] = 1;
	x->cp[2] = 3;
	x->cp[3] = 7;
	x->cp[4] = 4;
	x->cp[5] = 5;
	x->cp[6] = 2;
	x->cp[7] = 6;

	x->ep[0] = 0;
	x->ep[1] = 1;
	x->ep[2] = 6;
	x->ep[3] = 10;
	x->ep[4] = 4;
	x->ep[5] = 5;
	x->ep[6] = 3;
	x->ep[7] = 7;
	x->ep[8] = 8;
	x->ep[9] = 9;
	x->ep[10] = 2;
	x->ep[11] = 11;

	x->co[0] = 0;
	x->co[1] = 0;
	x->co[2] = 1;
	x->co[3] = 2;
	x->co[4] = 0;
	x->co[5] = 0;
	x->co[6] = 2;
	x->co[7] = 1;

	x->eo[0] = 0;
	x->eo[1] = 0;
	x->eo[2] = 1;
	x->eo[3] = 1;
	x->eo[4] = 0;
	x->eo[5] = 0;
	x->eo[6] = 1;
	x->eo[7] = 0;
	x->eo[8] = 0;
	x->eo[9] = 0;
	x->eo[10] = 1;
	x->eo[11] = 0;
}
static void make_u(d_state* x) {////
	x->cp[0] = 3;
	x->cp[1] = 0;
	x->cp[2] = 1;
	x->cp[3] = 2;
	x->cp[4] = 4;
	x->cp[5] = 5;
	x->cp[6] = 6;
	x->cp[7] = 7;

	x->ep[0] = 0;
	x->ep[1] = 1;
	x->ep[2] = 2;
	x->ep[3] = 3;
	x->ep[4] = 7;
	x->ep[5] = 4;
	x->ep[6] = 5;
	x->ep[7] = 6;
	x->ep[8] = 8;
	x->ep[9] = 9;
	x->ep[10] = 10;
	x->ep[11] = 11;

	for (int i = 0; i < 8; i++) {
		x->co[i] = 0;
	}
	for (int i = 0; i < 12; i++) {
		x->eo[i] = 0;
	}
}
static void make_d(d_state* x) {////
	x->cp[0] = 0;
	x->cp[1] = 1;
	x->cp[2] = 2;
	x->cp[3] = 3;
	x->cp[4] = 5;
	x->cp[5] = 6;
	x->cp[6] = 7;
	x->cp[7] = 4;

	x->ep[0] = 0;
	x->ep[1] = 1;
	x->ep[2] = 2;
	x->ep[3] = 3;
	x->ep[4] = 4;
	x->ep[5] = 5;
	x->ep[6] = 6;
	x->ep[7] = 7;
	x->ep[8] = 9;
	x->ep[9] = 10;
	x->ep[10] = 11;
	x->ep[11] = 8;

	for (int i = 0; i < 8;i++) {
		x->co[i] = 0;
	}
	for (int i = 0; i < 12;i++) {
		x->eo[i] = 0;
	}

}
void init_motion() {
	make_r(&r);
	make_b(&b);
	make_l(&l);
	make_f(&f);
	make_u(&u);
	make_d(&d);
}
void R(d_state* x) {
	int c_memo[8] = { 0 };
	int e_memo[12] = { 0 };
	for (int i = 0; i < 8; i++) {
		c_memo[i] = x->cp[r.cp[i]];
	}
	for (int i = 0; i < 8; i++) {
		x->cp[i] = c_memo[i];
	}
	for (int i = 0; i < 8; i++) {
		c_memo[i] = x->co[r.cp[i]];
	}
	for (int i = 0; i < 8; i++) {
		x->co[i] = (c_memo[i] + r.co[i]) % 3;
	}

	for (int i = 0; i < 12; i++) {
		e_memo[i] = x->ep[r.ep[i]];
	}
	for (int i = 0; i < 12; i++) {
		x->ep[i] = e_memo[i];
	}
	for (int i = 0; i < 12; i++) {
		e_memo[i] = x->eo[r.ep[i]];
	}
	for (int i = 0; i < 12; i++) {
		x->eo[i] = (e_memo[i] + r.eo[i]) % 2;
	}
}
void B(d_state* x) {
	int c_memo[8] = { 0 };
	int e_memo[12] = { 0 };
	for (int i = 0; i < 8; i++) {
		c_memo[i] = x->cp[b.cp[i]];
	}
	for (int i = 0; i < 8; i++) {
		x->cp[i] = c_memo[i];
	}
	for (int i = 0; i < 8; i++) {
		c_memo[i] = x->co[b.cp[i]];
	}
	for (int i = 0; i < 8; i++) {
		x->co[i] = (c_memo[i] + b.co[i]) % 3;
	}

	for (int i = 0; i < 12; i++) {
		e_memo[i] = x->ep[b.ep[i]];
	}
	for (int i = 0; i < 12; i++) {
		x->ep[i] = e_memo[i];
	}
	for (int i = 0; i < 12; i++) {
		e_memo[i] = x->eo[b.ep[i]];
	}
	for (int i = 0; i < 12; i++) {
		x->eo[i] = (e_memo[i] + b.eo[i]) % 2;
	}
}
void L(d_state* x) {
	int c_memo[8] = { 0 };
	int e_memo[12] = { 0 };
	for (int i = 0; i < 8; i++) {
		c_memo[i] = x->cp[l.cp[i]];
	}
	for (int i = 0; i < 8; i++) {
		x->cp[i] = c_memo[i];
	}
	for (int i = 0; i < 8; i++) {
		c_memo[i] = x->co[l.cp[i]];
	}
	for (int i = 0; i < 8; i++) {
		x->co[i] = (c_memo[i] + l.co[i]) % 3;
	}

	for (int i = 0; i < 12; i++) {
		e_memo[i] = x->ep[l.ep[i]];
	}
	for (int i = 0; i < 12; i++) {
		x->ep[i] = e_memo[i];
	}
	for (int i = 0; i < 12; i++) {
		e_memo[i] = x->eo[l.ep[i]];
	}
	for (int i = 0; i < 12; i++) {
		x->eo[i] = (e_memo[i] + l.eo[i]) % 2;
	}
}
void F(d_state* x) {
	int c_memo[8] = { 0 };
	int e_memo[12] = { 0 };
	for (int i = 0; i < 8; i++) {
		c_memo[i] = x->cp[f.cp[i]];
	}
	for (int i = 0; i < 8; i++) {
		x->cp[i] = c_memo[i];
	}
	for (int i = 0; i < 8; i++) {
		c_memo[i] = x->co[f.cp[i]];
	}
	for (int i = 0; i < 8; i++) {
		x->co[i] = (c_memo[i] + f.co[i]) % 3;
	}

	for (int i = 0; i < 12; i++) {
		e_memo[i] = x->ep[f.ep[i]];
	}
	for (int i = 0; i < 12; i++) {
		x->ep[i] = e_memo[i];
	}
	for (int i = 0; i < 12; i++) {
		e_memo[i] = x->eo[f.ep[i]];
	}
	for (int i = 0; i < 12; i++) {
		x->eo[i] = (e_memo[i] + f.eo[i]) % 2;
	}
}
void U(d_state* x) {
	int c_memo[8] = { 0 };
	int e_memo[12] = { 0 };
	for (int i = 0; i < 8; i++) {
		c_memo[i] = x->cp[u.cp[i]];
	}
	for (int i = 0; i < 8; i++) {
		x->cp[i] = c_memo[i];
	}
	for (int i = 0; i < 8; i++) {
		c_memo[i] = x->co[u.cp[i]];
	}
	for (int i = 0; i < 8; i++) {
		x->co[i] = (c_memo[i] + u.co[i]) % 3;
	}

	for (int i = 0; i < 12; i++) {
		e_memo[i] = x->ep[u.ep[i]];
	}
	for (int i = 0; i < 12; i++) {
		x->ep[i] = e_memo[i];
	}
	for (int i = 0; i < 12; i++) {
		e_memo[i] = x->eo[u.ep[i]];
	}
	for (int i = 0; i < 12; i++) {
		x->eo[i] = (e_memo[i] + u.eo[i]) % 2;
	}
}
void D(d_state* x) {
	int c_memo[8] = { 0 };
	int e_memo[12] = { 0 };
	for (int i = 0; i < 8; i++) {
		c_memo[i] = x->cp[d.cp[i]];
	}
	for (int i = 0; i < 8; i++) {
		x->cp[i] = c_memo[i];
	}
	for (int i = 0; i < 8; i++) {
		c_memo[i] = x->co[d.cp[i]];
	}
	for (int i = 0; i < 8; i++) {
		x->co[i] = (c_memo[i] + d.co[i]) % 3;
	}

	for (int i = 0; i < 12; i++) {
		e_memo[i] = x->ep[d.ep[i]];
	}
	for (int i = 0; i < 12; i++) {
		x->ep[i] = e_memo[i];
	}
	for (int i = 0; i < 12; i++) {
		e_memo[i] = x->eo[d.ep[i]];
	}
	for (int i = 0; i < 12; i++) {
		x->eo[i] = (e_memo[i] + d.eo[i]) % 2;
	}
}
void R2(d_state* x) {
	R(x);
	R(x);
}
void B2(d_state* x) {
	B(x);
	B(x);
}
void L2(d_state* x) {
	L(x);
	L(x);
}
void F2(d_state* x) {
	F(x);
	F(x);
}
void U2(d_state* x) {
	U(x);
	U(x);
}
void D2(d_state* x) {
	D(x);
	D(x);
}
void R_(d_state* x) {
	R(x);
	R(x);
	R(x);
}
void B_(d_state* x) {
	B(x);
	B(x);
	B(x);
}
void L_(d_state* x) {
	L(x);
	L(x);
	L(x);
}
void F_(d_state* x) {
	F(x);
	F(x);
	F(x);
}
void U_(d_state* x) {
	U(x);
	U(x);
	U(x);
}
void D_(d_state* x) {
	D(x);
	D(x);
	D(x);
}
d_state* get_state_value_address() {
	return state;
}
void init_cube_state(d_state* cube_state) {
	state = cube_state;
}
int* get_motion_list_address() {
	return motion_list;
}
void init_motion_list(int* list) {
	motion_list = list;
}
int* get_motion_count_address() {
	return motion_count;
}
void init_motion_count(int * count) {
	motion_count = count;
	*motion_count = 0;
}
void phase1_motion(d_state* cube_state,int index) {
	(phase1_move[index])(cube_state);
}
void phase2_motion(d_state* cube_state, int index) {
	(phase2_move[index])(cube_state);
}
static void init_corner_index_table() {
	for (int i = 0; i < NUM_CORNER; i++) {
		int index = 0;
		int cardinal_num = 1;
		int j = 0;
		for (int k = 0; k < NUM_FACE; k++) {
			if (corner_identification_table[i][j] / NUM_SQUARES_IN_ONE_FACE == k) {
				index += cardinal_num;
				j++;
			}
			cardinal_num *= 2;
			if (j == 3) {
				break;
			}
		}
		corner_index_table[index] = i;
	}
}
static void init_edge_index_table() {
	for (int i = 0; i < NUM_EDGE; i++) {
		int index = 0;
		int cardinal_num = 1;
		int j = 0;
		for (int k = 0; k < NUM_FACE; k++) {
			if (edge_identification_table[i][j] / NUM_SQUARES_IN_ONE_FACE == k) {
				index += cardinal_num;
				j++;
			}
			cardinal_num *= 2;
			if (j == 2) {
				break;
			}
		}
		edge_index_table[index] = i;
	}
}
static int is_input_valid(char rest[NUM_ALL_SQUARES], char face[NUM_FACE]) {
	int face_count[NUM_FACE] = { 0 };
	for (int i = 0; i < NUM_ALL_SQUARES; i++) {
		for (int j = 0; j < NUM_FACE; j++) {
			if (rest[i] == face[j]) {
				face_count[j]++;
				break;
			}
		}
	}
	for (int i = 0; i < NUM_FACE; i++) {
		if (face_count[i] != NUM_SQUARES_IN_ONE_FACE) {
			return 0;
		}
	}
	return 1;
}
static void delete_comment(char from[][INPUT_FILE_SIZE], char to[][INPUT_FILE_SIZE],int row) {
	int end = 0;
	for (int i = 0; i < row;i++) {
		if (from[i][0] != '#') {
			int j;
			for (j = 0; from[i][j] != '\0'; j++) {
				to[end][j] = from[i][j];
			}
			to[end][j] = '\0';
			end++;
		}
	}
}
static int is_charactor_available_for_mode(char x) {
	if ((x == 'R')||(x == 'L')||(x == 'F')||(x == 'B')||(x == 'U')||(x == 'D')) {
		return 1;
	}
	else {
		return 0;
	}
}
static int is_charactor_available_for_type(char x) {
	if (x == '2') {
		return 1;
	}
	else if (x == '_') {
		return 1;
	}
	else {
		return 0;
	}
}
void copy_state(d_state from, d_state* to) {
	for (int i = 0; i < NUM_CORNER; i++) {
		to->cp[i] = from.cp[i];
		to->co[i] = from.co[i];
	}
	for (int i = 0; i < NUM_EDGE; i++) {
		to->ep[i] = from.ep[i];
		to->eo[i] = from.eo[i];
	}
}
void shuffle(d_state* cube_state, char query[INPUT_FILE_SIZE][3], int size) {
	for (int i = 0; i < size; i++) {
		switch (query[i][0]) {
		case 'R':
			if (query[i][1] == '\0') {
				R(cube_state);
			}
			else if (query[i][1] == '2') {
				R2(cube_state);
			}
			else if (query[i][1] == '_') {
				R_(cube_state);
			}
			else {
				break;
			}
			break;
		case 'B':
			if (query[i][1] == '\0') {
				B(cube_state);
			}
			else if (query[i][1] == '2') {
				B2(cube_state);
			}
			else if (query[i][1] == '_') {
				B_(cube_state);
			}
			else {
				break;
			}
			break;
		case 'L':
			if (query[i][1] == '\0') {
				L(cube_state);
			}
			else if (query[i][1] == '2') {
				L2(cube_state);
			}
			else if (query[i][1] == '_') {
				L_(cube_state);
			}
			else {
				break;
			}
			break;
		case 'F':
			if (query[i][1] == '\0') {
				F(cube_state);
			}
			else if (query[i][1] == '2') {
				F2(cube_state);
			}
			else if (query[i][1] == '_') {
				F_(cube_state);
			}
			else {
				break;
			}
			break;
		case 'U':
			if (query[i][1] == '\0') {
				U(cube_state);
			}
			else if (query[i][1] == '2') {
				U2(cube_state);
			}
			else if (query[i][1] == '_') {
				U_(cube_state);
			}
			else {
				break;
			}
			break;
		case 'D':
			if (query[i][1] == '\0') {
				D(cube_state);
			}
			else if (query[i][1] == '2') {
				D2(cube_state);
			}
			else if (query[i][1] == '_') {
				D_(cube_state);
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
int read_csv_file(d_state* input,const char file_name[FILENAME]) {
	
	FILE* fp = NULL;
	errno_t no;

	char srest[BUFFER_SIZE][INPUT_FILE_SIZE];
	char string[NUM_SQUARES_IN_ONE_FACE][INPUT_FILE_SIZE];
	char rest[NUM_ALL_SQUARES] = { 0 };
	int row_count = 0;

	init_corner_index_table();
	init_edge_index_table();

	no = fopen_s(&fp, file_name , "r");
	if (no != 0) {
		printf("failed\n");
		return 0;
	}
	for (int i = 0; fgets(srest[i],INPUT_FILE_SIZE, fp) != NULL; i++) {
		//printf("%s", srest[i]);
		row_count++;
	}
	//printf("\n");

	fclose(fp);

	delete_comment(srest,string,row_count);

	int k = 36;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; string[i][j] != '\0'; j++) {
			if (('a' <= string[i][j]) && (string[i][j] <= 'z')) {
				rest[k] = string[i][j];
				k++;
			}
		}
	}

	k = 9;
	for (int i = 3; i < 6; i++) {
		int j = 0;
		for (int l = 0; l < 6; l++) {
			if (('a' <= string[i][j + l]) && (string[i][j + l] <= 'z')) {
				rest[k] = string[i][j + l];
				k++;
			}
		}
		j += 18;
	}

	k = 18;
	for (int i = 3; i < 6; i++) {
		int j = 6;
		for (int l = 0; l < 6; l++) {
			if (('a' <= string[i][j + l]) && (string[i][j + l] <= 'z')) {
				rest[k] = string[i][j + l];
				k++;
			}
		}
		j += 18;
	}

	k = 0;
	for (int i = 3; i < 6; i++) {
		int j = 12;
		for (int l = 0; l < 6; l++) {
			if (('a' <= string[i][j + l]) && (string[i][j + l] <= 'z')) {
				rest[k] = string[i][j + l];
				k++;
			}
		}
		j += 18;
	}

	k = 27;
	for (int i = 3; i < 6; i++) {
		int j = 18;
		for (int l = 0; l < 6; l++) {
			if (('a' <= string[i][j + l]) && (string[i][j + l] <= 'z')) {
				rest[k] = string[i][j + l];
				k++;
			}
		}
		j += 18;
	}

	k = 45;
	for (int i = 6; i < 9; i++) {
		for (int j = 0; string[i][j] != '\0'; j++) {
			if (('a' <= string[i][j]) && (string[i][j] <= 'z')) {
				rest[k] = string[i][j];
				k++;
			}
		}
	}

	center_color_index[rest[R_CENTER]] = 0;
	center_color_index[rest[L_CENTER]] = 1;
	center_color_index[rest[F_CENTER]] = 2;
	center_color_index[rest[B_CENTER]] = 3;
	center_color_index[rest[U_CENTER]] = 4;
	center_color_index[rest[D_CENTER]] = 5;

	center_color_value[0] = rest[R_CENTER];
	center_color_value[1] = rest[L_CENTER];
	center_color_value[2] = rest[F_CENTER];
	center_color_value[3] = rest[B_CENTER];
	center_color_value[4] = rest[U_CENTER];
	center_color_value[5] = rest[D_CENTER];

	if (is_input_valid(rest, center_color_value) == 0) {
		printf("input is invalid\n");
		return 0;
	}


	for (int i = 0; i < NUM_CORNER; i++) {
		int index = 0;
		for (int j = 0; j < 3; j++) {
			index += (1 << center_color_index[rest[corner_identification_table[i][j]]]);
		}
		input->cp[i] = corner_index_table[index];
	}
	for (int i = 0; i < NUM_EDGE; i++) {
		int index = 0;
		for (int j = 0; j < 2; j++) {
			index += (1 << center_color_index[rest[edge_identification_table[i][j]]]);
		}
		input->ep[i] = edge_index_table[index];
	}

	for (int i = 0; i < 4; i++) {
		if ((rest[U_CENTER] == rest[corner_identification_table[i][2]]) || (rest[D_CENTER] == rest[corner_identification_table[i][2]])) {
			input->co[i] = 0;
		}
		else if ((i % 2 == 0) && ((rest[U_CENTER] == rest[corner_identification_table[i][0]]) || (rest[D_CENTER] == rest[corner_identification_table[i][0]]))) {
			input->co[i] = 1;
		}
		else if ((i % 2 == 1) && ((rest[U_CENTER] == rest[corner_identification_table[i][1]]) || (rest[D_CENTER] == rest[corner_identification_table[i][1]]))) {
			input->co[i] = 1;
		}
		else {
			input->co[i] = 2;
		}
	}

	for (int i = 4; i < NUM_CORNER; i++) {
		if ((rest[U_CENTER] == rest[corner_identification_table[i][2]]) || (rest[D_CENTER] == rest[corner_identification_table[i][2]])) {
			input->co[i] = 0;
		}
		else if ((i % 2 == 0) && ((rest[U_CENTER] == rest[corner_identification_table[i][1]]) || (rest[D_CENTER] == rest[corner_identification_table[i][1]]))) {
			input->co[i] = 1;
		}
		else if ((i % 2 == 1) && ((rest[U_CENTER] == rest[corner_identification_table[i][0]]) || (rest[D_CENTER] == rest[corner_identification_table[i][0]]))) {
			input->co[i] = 1;
		}
		else {
			input->co[i] = 2;
		}
	}


	for (int i = 0; i < NUM_EDGE; i++) {
		if (rest[edge_identification_table[i][1]] == center_color_value[edge_identification_table[input->ep[i]][1] / NUM_SQUARES_IN_ONE_FACE]) {
			input->eo[i] = 0;
		}
		else {
			input->eo[i] = 1;
		}
	}
	return 1;
}
int read_text_file(d_state* input,const char file_name[FILENAME]) {

	FILE* fp = NULL;
	errno_t no;

	char srest[BUFFER_SIZE][INPUT_FILE_SIZE];
	char string[BUFFER_SIZE][INPUT_FILE_SIZE];
	char query[QUERY_SIZE][3];
	int row_count = 0;


	no = fopen_s(&fp, file_name, "r");
	if (no != 0) {
		printf("failed\n");
		return 0;
	}
	for (int i = 0; fgets(srest[i],INPUT_FILE_SIZE,fp) != NULL;i++) {
		//printf("[%s\n",string[i]);
		row_count++;
	}

	fclose(fp);

	delete_comment(srest, string, row_count);
	
	for (int i = 0; i < row_count;i++) {
		int count = 0;
		for (int curre = 0; (string[i][curre] != '\0')&&(i<INPUT_FILE_SIZE-1);curre++) {
			if (is_charactor_available_for_mode(string[i][curre])) {
				int k = 0; 
				while ( (is_charactor_available_for_type(string[i][curre+k])||is_charactor_available_for_mode(string[i][curre + k])) && (k<2) ) {
					query[count][k] = string[i][curre + k];
					k++;
				}
				query[count][k] = '\0';
				curre = k+ curre -1;
				count++;
			}
		}
		shuffle(input,query,count);
	}
	return 1;
}
char* get_motion_name_from_index(int index,char* name,int length) {
	int i;
	for (i = 0; (from_index_to_motion[index][i])&&(i<(length-1)) != '\0';i++) {
		name[i] = from_index_to_motion[index][i];
	}
	name[i] = '\0';
	return name;
}
int get_reverse_motion(int index) {
	return reverse_motion[index];
}


