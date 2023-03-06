#include"header.h"
d_state r;
d_state b;
d_state l;
d_state f;
d_state u;
d_state d;
func move[MOVE] = { R,L,F,B,U,D,R_,L_,F_,B_,U_,D_,R2,L2,F2,B2,U2,D2 };
void simuration(d_state* state,int i) {
	(move[i])(state);
}
void update_face_posi(d_state state,int face[6][8]) {
	for (int i = 0; i < 6;i++) {
		for (int j = 0; j < 4;j++) {
			face[i][j] = state.cp[face_set[i][j]];
		}
		for (int j = 4; j < 8;j++) {
			face[i][j] = state.ep[face_set[i][j]];
		}
	}
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
void make_r(d_state* x) {////
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

	x->eo[0] = 0;
	x->eo[1] = 0;
	x->eo[2] = 0;
	x->eo[3] = 0;
	x->eo[4] = 0;
	x->eo[5] = 0;
	x->eo[6] = 0;
	x->eo[7] = 0;
	x->eo[8] = 0;
	x->eo[9] = 0;
	x->eo[10] = 0;
	x->eo[11] = 0;

}
void make_b(d_state* x) {////
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
void make_l(d_state* x) {////
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

	x->eo[0] = 0;
	x->eo[1] = 0;
	x->eo[2] = 0;
	x->eo[3] = 0;
	x->eo[4] = 0;
	x->eo[5] = 0;
	x->eo[6] = 0;
	x->eo[7] = 0;
	x->eo[8] = 0;
	x->eo[9] = 0;
	x->eo[10] = 0;
	x->eo[11] = 0;
}
void make_f(d_state* x) {////
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
void make_u(d_state* x) {////
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

	x->co[0] = 0;
	x->co[1] = 0;
	x->co[2] = 0;
	x->co[3] = 0;
	x->co[4] = 0;
	x->co[5] = 0;
	x->co[6] = 0;
	x->co[7] = 0;

	x->eo[0] = 0;
	x->eo[1] = 0;
	x->eo[2] = 0;
	x->eo[3] = 0;
	x->eo[4] = 0;
	x->eo[5] = 0;
	x->eo[6] = 0;
	x->eo[7] = 0;
	x->eo[8] = 0;
	x->eo[9] = 0;
	x->eo[10] = 0;
	x->eo[11] = 0;
}
void make_d(d_state* x) {////
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

	x->co[0] = 0;
	x->co[1] = 0;
	x->co[2] = 0;
	x->co[3] = 0;
	x->co[4] = 0;
	x->co[5] = 0;
	x->co[6] = 0;
	x->co[7] = 0;

	x->eo[0] = 0;
	x->eo[1] = 0;
	x->eo[2] = 0;
	x->eo[3] = 0;
	x->eo[4] = 0;
	x->eo[5] = 0;
	x->eo[6] = 0;
	x->eo[7] = 0;
	x->eo[8] = 0;
	x->eo[9] = 0;
	x->eo[10] = 0;
	x->eo[11] = 0;
}
void make() {
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
