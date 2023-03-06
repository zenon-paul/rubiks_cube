#include<stdlib.h>
#include"header.h"
double cube[6][4][3] = {
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
			{EG,0,EG},
			{EG,0,0}
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
int face_set[6][8] = {//中心が足りないので気を付けて前半四つ角後半四つエッヂ
	{1,2,5,6,1,2,5,9},
	{0,3,4,7,0,3,7,11},
	{2,3,6,7,2,3,6,10},
	{0,1,4,5,0,1,4,8},
	{0,1,2,3,4,5,6,7},
	{4,5,6,7,8,9,10,11}
};
int face_posi[6][8];
double corner_seed[8][3] = {//中心が抜けているので注意
	{0,40,0},
	{40,40,0},
	{40,40,40},
	{0,40,40},
	{0,0,0},
	{40,0,0},
	{40,0,40},
	{0,0,40},
};
double edge_seed[12][3] = {
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
double corners[8][6][4][3];
double edges[12][6][4][3];
void init_corner() {
	for (int i = 0; i < 8;i++) {
		for (int j = 0; j < 6;j++) {
			for (int k = 0; k < 4;k++) {
				for (int l = 0; l < 3;l++) {
					corners[i][j][k][l] = corner_seed[i][l] + cube[j][k][l];
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
					edges[i][j][k][l] = edge_seed[i][l] + cube[j][k][l];
				}
			}
		}
	}
}
