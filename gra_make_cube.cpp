#include"rubiks_cube_graphic.h"
static double cube[6][4][3] = {
		{
			{0,EG,0},
			{0,EG,EG},
			{EG,EG,EG},
			{EG,EG,0}
		},
		{
			{EG,0,0},
			{EG,EG,0},
			{EG,EG,EG},
			{EG,0,EG}
		},
		{
			{0,0,EG},
			{EG,0,EG},
			{EG,EG,EG},
			{0,EG,EG}
		},
		{
			{0,0,0},
			{0,0,EG},
			{EG, 0, EG},
			{ EG,0,0 }
		},
		{
			{0,0,0},
			{0,EG,0},
			{0,EG,EG},
			{0,0,EG}
		},
		{
			{0,0,0},
			{EG,0,0},
			{EG,EG,0},
			{0,EG,0}
		}
};
/*int face_set[6][8] = {
	{1,2,5,6,1,2,5,9},
	{0,3,4,7,0,3,7,11},
	{2,3,6,7,2,3,6,10},
	{0,1,4,5,0,1,4,8},
	{0,1,2,3,4,5,6,7},
	{4,5,6,7,8,9,10,11}
};*/
int face_posi[6][8] = {
	{1,2,5,6,1,2,5,9},
	{0,3,4,7,0,3,7,11},
	{2,3,6,7,2,3,6,10},
	{0,1,4,5,0,1,4,8},
	{0,1,2,3,4,5,6,7},
	{4,5,6,7,8,9,10,11}
};
static double corner_seed[8][3] = {
	{0,40,0},
	{40,40,0},
	{40,40,40},
	{0,40,40},
	{0,0,0},
	{40,0,0},
	{40,0,40},
	{0,0,40},
};
static double edge_seed[12][3] = {
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
static double axis_seed[6][3] = {
	{40,20,20},
	{0,20,20},
	{20,20,40},
	{20,20,0},
	{20,40,20},
	{20,0,20}
};
d_face corners[8][6];
d_face edges[12][6];
d_face axises[6][6];
void init_corner() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 3; l++) {
					corners[i][j].face[k][l] = corner_seed[i][l] + cube[j][k][l];
				}
			}
		}
	}
}
void init_edge() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 3; l++) {
					edges[i][j].face[k][l] = edge_seed[i][l] + cube[j][k][l];
				}
			}
		}
	}
}
void init_axises() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 3; l++) {
					axises[i][j].face[k][l] = axis_seed[i][l] + cube[j][k][l];
				}
			}
		}
	}
}
void init_cube_color(double colors[6][3]) {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 3; k++) {
				corners[i][j].color[k] = colors[j][k];
			}
		}
	}
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 3; k++) {
				edges[i][j].color[k] = colors[j][k];
			}
		}
	}
}
/*void init_face_position(int posi[6][8]) {
	static int face_set[6][8] = {
	{1,2,5,6,1,2,5,9},
	{0,3,4,7,0,3,7,11},
	{2,3,6,7,2,3,6,10},
	{0,1,4,5,0,1,4,8},
	{0,1,2,3,4,5,6,7},
	{4,5,6,7,8,9,10,11}
	};
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			posi[i][j] = face_set[i][j];
		}
	}
}*/
