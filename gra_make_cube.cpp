#include"rubiks_cube_graphic.h"
#include<stdio.h>
#include<stdlib.h>
static double cube[NUM_FACE][NUM_FOUR_CORNER][3] = {
		{
			{EG,0,0},
			{EG,EG,0},
			{EG,EG,EG},
			{EG,0,EG}
		},
		{
			{0,0,0},
			{0,EG,0},
			{0,EG,EG},
			{0,0,EG}
		},
		{
			{0,0,EG},
			{EG,0,EG},
			{EG,EG,EG},
			{0,EG,EG}
		},
		{
			{0,0,0},
			{EG,0,0},
			{EG,EG,0},
			{0,EG,0}
		},
		{
			{0,EG,0},
			{0,EG,EG},
			{EG,EG,EG},
			{EG,EG,0}
		},
		{
			{0,0,0},
			{0,0,EG},
			{EG, 0, EG},
			{ EG,0,0 }
		}
};
static double corner_seed[NUM_CORNER][3] = {
	{0,40,0},
	{40,40,0},
	{40,40,40},
	{0,40,40},
	{0,0,0},
	{40,0,0},
	{40,0,40},
	{0,0,40},
};
static double edge_seed[NUM_EDGE][3] = {
	{0,20,0},
	{40,20,0},
	{40,20,40},
	{0,20,40},
	{20,40,0},
	{40,40,20},
	{20,40,40},
	{0,40,20},
	{20,0,0,},
	{40,0,20},
	{20,0,40},
	{0,0,20},
};
static double axis_seed[NUM_FACE][3] = {
	{40,20,20},
	{0,20,20},
	{20,20,40},
	{20,20,0},
	{20,40,20},
	{20,0,20}
};
static int corner_front_faces[NUM_CORNER][3] = {
	{1,3,4},
	{3,0,4},
	{0,2,4},
	{2,1,4},
	{3,1,5},
	{0,3,5},
	{2,0,5},
	{1,2,5}
};
static int edge_front_faces[NUM_EDGE][2] = {
	{1,3},
	{0,3},
	{0,2},
	{1,2},
	{3,4},
	{0,4},
	{2,4},
	{1,4},
	{3,5},
	{0,5},
	{2,5},
	{1,5}
};
int face_posi[NUM_FACE][8] = {
	{1,2,5,6,1,2,5,9},
	{0,3,4,7,0,3,7,11},
	{2,3,6,7,2,3,6,10},
	{0,1,4,5,0,1,4,8},
	{0,1,2,3,4,5,6,7},
	{4,5,6,7,8,9,10,11}
};
d_face corners[NUM_CORNER][NUM_FACE];
d_face edges[NUM_EDGE][NUM_FACE];
d_face axises[NUM_FACE][NUM_FACE];
static void init_cube_color(double colors[NUM_FACE][3]) {

	for (int i = 0; i < NUM_FACE; i++)
	{
		for (int j = 0; j < NUM_FACE; j++)
		{
			for (int k = 0; k < 3; k++) {
				axises[i][j].color[k] = colors[j][k];
			}
		}
	}

	d_state* x = get_state_value_address();

	disp_state(*x);

	for (int i = 0; i < NUM_CORNER; i++) {
		int p = 0;
		while (x->cp[p] != i) {
			p++;
		}
		if (x->co[p] == 1) {
			for (int k = 0; k < 3; k++) {
				corners[i][corner_front_faces[p][0]].color[k] = colors[corner_front_faces[i][2]][k];
			}
			for (int k = 0; k < 3; k++) {
				corners[i][corner_front_faces[p][1]].color[k] = colors[corner_front_faces[i][0]][k];
			}
			for (int k = 0; k < 3; k++) {
				corners[i][corner_front_faces[p][2]].color[k] = colors[corner_front_faces[i][1]][k];
			}
		}

		else if (x->co[p] == 2) {
			for (int k = 0; k < 3; k++) {
				corners[i][corner_front_faces[p][1]].color[k] = colors[corner_front_faces[i][2]][k];
			}
			for (int k = 0; k < 3; k++) {
				corners[i][corner_front_faces[p][2]].color[k] = colors[corner_front_faces[i][0]][k];
			}
			for (int k = 0; k < 3; k++) {
				corners[i][corner_front_faces[p][0]].color[k] = colors[corner_front_faces[i][1]][k];
			}
		}
		else {
			for (int k = 0; k < 3; k++) {
				corners[i][corner_front_faces[p][0]].color[k] = colors[corner_front_faces[i][0]][k];

			}
			for (int k = 0; k < 3; k++) {
				corners[i][corner_front_faces[p][1]].color[k] = colors[corner_front_faces[i][1]][k];
			}
			for (int k = 0; k < 3; k++) {
				corners[i][corner_front_faces[p][2]].color[k] = colors[corner_front_faces[i][2]][k];
			}
		}
	}

	for (int i = 0; i < NUM_EDGE; i++) {
		int p = 0;
		while (x->ep[p] != i) {
			p++;
		}
		printf("pppppppppp(%d)\n", p);
		printf("clock(%d)\n", edge_front_faces[p][0]);
		printf("anti(%d)\n", edge_front_faces[p][1]);
		if (x->eo[p] == 1) {
			for (int k = 0; k < 3; k++) {
				edges[i][edge_front_faces[p][0]].color[k] = colors[edge_front_faces[i][1]][k];
			}
			for (int k = 0; k < 3; k++) {
				edges[i][edge_front_faces[p][1]].color[k] = colors[edge_front_faces[i][0]][k];
			}
		}
		else {
			if (i == 1) {
				printf(" 0->0:%d->%d  1->1:%d->%d\n", edge_front_faces[i][0], edge_front_faces[p][0], edge_front_faces[i][1], edge_front_faces[p][1]);
			}
			for (int k = 0; k < 3; k++) {
				edges[i][edge_front_faces[p][0]].color[k] = colors[edge_front_faces[i][0]][k];
			}
			for (int k = 0; k < 3; k++) {
				edges[i][edge_front_faces[p][1]].color[k] = colors[edge_front_faces[i][1]][k];
			}
		}
	}


	for (int i = 0; i < NUM_FACE; i++) {
		for (int j = 0; j < NUM_FACE; j++) {
			if (i != j) {
				for (int k = 0; k < 3; k++) {
					axises[i][j].color[k] = 0.0;
				}
			}
		}
	}



}
void update_cube_group(d_state x, int face[NUM_FACE][8]) {

	int face_set[NUM_FACE][8] = {
	{1,2,5,6,1,2,5,9},
	{0,3,4,7,0,3,7,11},
	{2,3,6,7,2,3,6,10},
	{0,1,4,5,0,1,4,8},
	{0,1,2,3,4,5,6,7},
	{4,5,6,7,8,9,10,11}
	};
	for (int i = 0; i < NUM_FACE; i++) {
		for (int j = 0; j < NUM_FOUR_CORNER; j++) {
			face[i][j] = x.cp[face_set[i][j]];
		}
		for (int j = 4; j < 4 + NUM_FOUR_CORNER; j++) {
			face[i][j] = x.ep[face_set[i][j]];
		}
	}
	printf(">update face_posi\n");
	for (int i = 0; i < NUM_FACE; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%d ", face_posi[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void init_corner(d_state* cube_state) {
	
	for (int i = 0; i < NUM_CORNER; i++) {
		int p = 0;
		while (cube_state->cp[p] != i) {
			p++;
		}

		for (int j = 0; j < NUM_FACE; j++) {
			for (int k = 0; k < NUM_FOUR_CORNER; k++) {
				for (int l = 0; l < 3; l++) {
					corners[i][j].face[k][l] = corner_seed[p][l] + cube[j][k][l];
				}
			}
		}
	}
}
void init_edge(d_state* cube_state) {

	for (int i = 0; i < NUM_EDGE; i++) {
		int p = 0;
		while (cube_state->ep[p] != i) {
			p++;
		}
		for (int j = 0; j < NUM_FACE; j++) {
			for (int k = 0; k < NUM_FOUR_CORNER; k++) {
				for (int l = 0; l < 3; l++) {
					edges[i][j].face[k][l] = edge_seed[p][l] + cube[j][k][l];
				}
			}
		}
	}
}
void init_axises() {
	for (int i = 0; i < NUM_FACE; i++) {
		for (int j = 0; j < NUM_FACE; j++) {
			for (int k = 0; k < NUM_FOUR_CORNER; k++) {
				for (int l = 0; l < 3; l++) {
					axises[i][j].face[k][l] = axis_seed[i][l] + cube[j][k][l];
				}
			}
		}
	}
}
void init_shuffled_cube(d_state x,double fc[NUM_FACE][3]) {
	init_cube_color(fc);
	update_cube_group(x,face_posi);
}
