#include"rubiks_cube_graphic.h"
#include<math.h>
void product(double matrix[3][3], double vector[3]) {
	double result[3] = { 0,0,0 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i] += matrix[i][j] * vector[j];
		}
	}
	vector[0] = result[0];
	vector[1] = result[1];
	vector[2] = result[2];
}
