#include"rubiks_cube_solver.h"
#include"rubiks_cube_graphic.h"
int main(int argc, char** argv) {
	double color[6][3] = {
		{0.3,0.4,0.8},
		{0.7,0.8,0.5},
		{0.8,0.2,0.1},
		{0.2,0.6,0.3},
		{0.0,0.5,0.8},
		{0.2,0.6,0.6}
	};
	init_move();
	init_transfer_table();
	init_prune_table();
	init_state(get_state_value_address());
	init_cube_color(color);
	init_corner();
	init_edge();
	init_axises();
	//init_face_position(face_posi);
	init_motion_list();
	graphic(argc, argv);
}
/*
double color[6][3] = {
		{1.0,1.0,1.0},
		{1.0,0.0,0.0},
		{0.0,1.0,0.0},
		{1.0,1.0,0.0},
		{1.0,0.5,0.0},
		{0.0,0.0,1.0}
	};
*/
