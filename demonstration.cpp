#include"rubiks_cube_solver.h"
#include"rubiks_cube_graphic.h"
#include<stdio.h>
int main(int argc, char** argv) {
	double color[6][3] = {
		{0.0,1.0,0.0},
		{1.0,1.0,0.0},
		{0.0,0.5,1.0},
		{1.0,1.0,1.0},
		{1.0,0.5,0.0},
		{1.0,0.0,0.0}
	};
	int m_c = 0;
	init_motion_count(&m_c);

	int m_l[BUFFER_SIZE] = { 0 };
	init_motion_list(m_l);

	d_state ss;
	init_cube_state(&ss);

	init_motion();
	init_transfer_table();
	init_prune_table();
	make_solved_state(get_state_value_address());

	//read_csv_file(&ss, "jikkemBooknonbom.csv");
	read_text_file(&ss,"jikken.txt");

	//printf(">get data from csv file\n");
	//disp_state(*get_state_value_address());

	init_shuffled_cube(ss, color);
	init_corner(&ss);
	init_edge(&ss);
	init_axises();


	graphic(argc, argv);
}
