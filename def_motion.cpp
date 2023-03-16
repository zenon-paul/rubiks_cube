#include"rubiks_cube_definition.h"
#include<stdio.h>
int path1[VECTOR_LEN][GENERATION] = { 0 };
int path2[VECTOR_LEN][GENERATION] = { 0 };
int mnum1[GENERATION] = { 0 };
int mnum2[GENERATION] = { 0 };
int motion_count = 0;
int motion_list[VECTOR_LEN] = { 0 };
static func phase1_move[PHASE1_MOVE] = { R,L,F,B,U,D,R_,L_,F_,B_,U_,D_,R2,L2,F2,B2,U2,D2 };
static func phase2_move[PHASE2_MOVE] = { R2,L2,F2,B2,U2,D2,U,D,U_,D_ };
int coorresponding_table_from_phase2_move_to_phase1_move[PHASE2_MOVE] = { 12,13,14,15,16,17,4,5,10,11 };
static d_state r;
static d_state b;
static d_state l;
static d_state f;
static d_state u;
static d_state d;
static d_state state;
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
void disp_state(d_state x) {
	for (int i = 0; i < 8; i++) {
		printf("%d ", x.cp[i]);
	}
	printf("\n");
	for (int i = 0; i < 8; i++) {
		printf("%d ", x.co[i]);
	}
	printf("\n");
	for (int i = 0; i < 12; i++) {
		printf("%d ", x.ep[i]);
	}
	printf("\n");
	for (int i = 0; i < 12; i++) {
		printf("%d ", x.eo[i]);
	}
	printf("\n");
}
void init_state(d_state* x) {
	for (int i = 0; i < 8; i++) {
		x->cp[i] = i;
		x->co[i] = 0;
	}
	for (int i = 0; i < 12; i++) {
		x->ep[i] = i;
		x->eo[i] = 0;
	}
}
void clear_state(d_state* x) {
	for (int i = 0; i < 8; i++) {
		x->cp[i] = 0;
		x->co[i] = 0;
	}
	for (int i = 0; i < 12; i++) {
		x->ep[i] = 0;
		x->eo[i] = 0;
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
void init_move() {
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
	return &state;
}
void phase1_motion(d_state* x,int i) {
	(phase1_move[i])(x);
}
void phase2_motion(d_state* x, int i) {
	(phase2_move[i])(x);
}
void init_motion_list() {
	motion_count = 0;
	for (int i = 0; i < GENERATION;i++) {
		mnum1[i] = 0;
		mnum2[i] = 0;
	}
	for (int i = 0; i < VECTOR_LEN; i++) {
		for (int j = 0; j < GENERATION;j++) {
			path1[i][j] = 0;
			path2[i][j] = 0;
		}
	}
}
static void init_corner_index_table() {
	for (int i = 0; i < NUM_CORNER; i++) {
		int index = 0;
		int cardinal_num = 1;
		int j = 0;
		for (int k = 0; k < NUM_FACE; k++) {
			if (corner_identification_table[i][j] / NUM_3_SQUARED == k) {
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
			if (edge_identification_table[i][j] / NUM_3_SQUARED == k) {
				if (i == 3) {
					printf(" KKK%d", k);
				}
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
static int is_input_valid(char rest[54], char face[NUM_FACE]) {
	int face_count[NUM_FACE] = { 0 };
	for (int i = 0; i < 54; i++) {
		for (int j = 0; j < NUM_FACE; j++) {
			if (rest[i] == face[j]) {
				face_count[j]++;
				break;
			}
		}
	}
	for (int i = 0; i < 6;i++) {
		printf("%d ",face_count[i]);
	}
	printf("\n");
	for (int i = 0; i < NUM_FACE; i++) {
		if (face_count[i] != NUM_3_SQUARED) {
			printf("(%c)",face[i]);
			return 0;
		}
	}
	return 1;
}
int read_csv_file() {
	FILE* fp = NULL;
	errno_t no;
	char s[NUM_3_SQUARED][VECTOR_LEN];
	char rest[VECTOR_LEN] = { 0 };
	d_state* input = get_state_value_address();

	init_corner_index_table();
	init_edge_index_table();

	no = fopen_s(&fp, "Book0.csv", "r");
	if (no != 0) {
		printf("failed\n");
		return 0;
	}
	for (int i = 0; fgets(s[i], VECTOR_LEN, fp) != NULL; i++) {
		printf("+++%s", s[i]);
	}
	printf("\n");

	fclose(fp);

	int k = 36;
	printf("U\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; s[i][j] != '\0'; j++) {
			if (('a' <= s[i][j]) && (s[i][j] <= 'z')) {
				rest[k] = s[i][j];
				k++;
			}
		}
	}

	printf("L\n");
	k = 9;
	for (int i = 3; i < 6; i++) {
		int j = 0;
		for (int l = 0; l < 6; l++) {
			if (('a' <= s[i][j + l]) && (s[i][j + l] <= 'z')) {
				rest[k] = s[i][j + l];
				k++;
			}
		}
		j += 18;
	}

	printf("F\n");
	k = 18;
	for (int i = 3; i < 6; i++) {
		int j = 6;
		for (int l = 0; l < 6; l++) {
			if (('a' <= s[i][j + l]) && (s[i][j + l] <= 'z')) {
				rest[k] = s[i][j + l];
				k++;
			}
		}
		j += 18;
	}

	printf("R\n");
	k = 0;
	for (int i = 3; i < 6; i++) {
		int j = 12;
		for (int l = 0; l < 6; l++) {
			if (('a' <= s[i][j + l]) && (s[i][j + l] <= 'z')) {
				rest[k] = s[i][j + l];
				k++;
			}
		}
		j += 18;
	}

	printf("B\n");
	k = 27;
	for (int i = 3; i < 6; i++) {
		int j = 18;
		for (int l = 0; l < 6; l++) {
			if (('a' <= s[i][j + l]) && (s[i][j + l] <= 'z')) {
				rest[k] = s[i][j + l];
				k++;
			}
		}
		j += 18;
	}

	printf("D\n");
	k = 45;
	for (int i = 6; i < 9; i++) {
		for (int j = 0; s[i][j] != '\0'; j++) {
			if (('a' <= s[i][j]) && (s[i][j] <= 'z')) {
				rest[k] = s[i][j];
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
		printf("入力が正しくありません\n");
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
		if (rest[edge_identification_table[i][1]] == center_color_value[edge_identification_table[input->ep[i]][1] / NUM_3_SQUARED]) {
			input->eo[i] = 0;
		}
		else {
			input->eo[i] = 1;
		}
	}

	for (int i = 0; i < 8; i++) {
		printf("%d ", input->cp[i]);
	}
	printf("\n");
	for (int i = 0; i < 8; i++) {
		printf("%d ", input->co[i]);
	}
	printf("\n");
	for (int i = 0; i < 12; i++) {
		printf("%d ", input->ep[i]);
	}
	printf("\n");
	for (int i = 0; i < 12; i++) {
		printf("%d ", input->eo[i]);
	}
	printf("\n");
	return 1;
}

