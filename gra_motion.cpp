#include"rubiks_cube_graphic.h"
void simuration(d_state* state, int i) {
	(phase1_move[i])(state);
}
void update_face_posi(d_state state, int face[6][8]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			face[i][j] = state.cp[face_set[i][j]];
		}
		for (int j = 4; j < 8; j++) {
			face[i][j] = state.ep[face_set[i][j]];
		}
	}
}
