#include"rubiks_cube_graphic.h"
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
static int input = 18;
static int mode = 0;
static int move_count = 0;
static int moves[60] = { 0 };
d_state state;
static int corresponding_table_from_move_to_degree_and_direction[2][19] = {
	{ 0,0, 2,2, 1,1,    0, 0,2, 2,1,1,   0,0,2,2,1,1     ,0},
	{1,-1,-1,1,1,-1,    -1,1,1,-1,-1,1 , -2,2,-2,2,-2,2  ,0}
};
static void foolr_value_of_coordinate() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			for (int z = 0; z < 3; z++) {
				cube[i][j][z] = round(cube[i][j][z] / 10) * 10;
			}
		}
	}
}
static void x_rotate(double degree, double xyz[3]) {
	double r_m[3][3];
	double radian = (degree / 180.0) * PI;
	r_m[0][0] = 1;
	r_m[0][1] = 0;
	r_m[0][2] = 0;
	r_m[1][0] = 0;
	r_m[1][1] = cos(radian);
	r_m[1][2] = sin(radian);
	r_m[2][0] = 0;
	r_m[2][1] = -sin(radian);
	r_m[2][2] = cos(radian);

	xyz[0] -= X_AXIS;
	xyz[1] -= Y_AXIS;
	xyz[2] -= Z_AXIS;
	product(r_m, xyz);
	xyz[0] += X_AXIS;
	xyz[1] += Y_AXIS;
	xyz[2] += Z_AXIS;
}
static void y_rotate(double degree, double xyz[3]) {
	double r_m[3][3];
	double radian = (degree / 180.0) * PI;
	r_m[0][0] = cos(radian);
	r_m[0][1] = 0;
	r_m[0][2] = -sin(radian);
	r_m[1][0] = 0;
	r_m[1][1] = 1;
	r_m[1][2] = 0;
	r_m[2][0] = sin(radian);
	r_m[2][1] = 0;
	r_m[2][2] = cos(radian);

	xyz[0] -= X_AXIS;
	xyz[1] -= Y_AXIS;
	xyz[2] -= Z_AXIS;
	product(r_m, xyz);
	xyz[0] += X_AXIS;
	xyz[1] += Y_AXIS;
	xyz[2] += Z_AXIS;
}
static void z_rotate(double degree, double xyz[3]) {
	double r_m[3][3];
	double radian = (degree / 180.0) * PI;
	r_m[0][0] = cos(radian);
	r_m[0][1] = -sin(radian);
	r_m[0][2] = 0;
	r_m[1][0] = sin(radian);
	r_m[1][1] = cos(radian);
	r_m[1][2] = 0;
	r_m[2][0] = 0;
	r_m[2][1] = 0;
	r_m[2][2] = 1;

	xyz[0] -= X_AXIS;
	xyz[1] -= Y_AXIS;
	xyz[2] -= Z_AXIS;
	product(r_m, xyz);
	xyz[0] += X_AXIS;
	xyz[1] += Y_AXIS;
	xyz[2] += Z_AXIS;
}
static void rotate(int face, int xyzmode) {
	static rfunc xyzrotate[3] = { x_rotate,y_rotate,z_rotate };
	if (input == 18) {
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				(xyzrotate[xyzmode])(corresponding_table_from_move_to_degree_and_direction[1][input], corners[face_posi[face%6][i]][j].face[k]);
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				(xyzrotate[xyzmode])(corresponding_table_from_move_to_degree_and_direction[1][input], edges[face_posi[face%6][i + 4]][j].face[k]);
			}
		}
	}
	for (int j = 0; j < 6; j++) {
		for (int k = 0; k < 4; k++) {
			(xyzrotate[xyzmode])(corresponding_table_from_move_to_degree_and_direction[1][input], axises[input][j].face[k]);
		}
	}
}

static void disp_cube() {
	int normal[6][3] = {
		{0,1,0},
		{1,0,0},
		{0,0,1},
		{0,-1,0},
		{-1,0,0},
		{0,0,-1}
	};
	glBegin(GL_QUADS);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 6; j++) {
			glNormal3iv(normal[j]);
			glColor3dv(corners[i][j].color);
			for (int k = 0; k < 4; k++) {
				glVertex3dv(corners[i][j].face[k]);
			}
		}
	}
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			glNormal3iv(normal[j]);
			glColor3dv(edges[i][j].color);
			for (int k = 0; k < 4; k++) {
				glVertex3dv(edges[i][j].face[k]);
			}
		}
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			glNormal3iv(normal[j]);
			glColor3dv(edges[i][j].color);
			for (int k = 0; k < 4; k++) {
				glVertex3dv(axises[i][j].face[k]);
			}
		}
	}
	glEnd();
	glFlush();
}
static void disp_xyzaxis() {
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(100, 0, 0);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 100, 0);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 100);
	glEnd();
	glFlush();
}
static void display() {
	//printf("input:%d \n", input);
	static int count = 0;
	static double angle = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(120.0, 80.0, 80.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//glRotated(angle, 0.0, 1.0, 0.0);

	disp_xyzaxis();
	disp_cube();
	glFlush();
	
	if (angle >= 360) {
		angle = 0;
	}
	else {
		angle += 0.04;
	}

	if (mode) {
		if (count >= RA) {
			count = 0;
			simuration(&state, input);
			update_face_posi(state, face_posi);
			foolr_value_of_coordinate();
			input = 18;
			if (move_count == -1) {
				mode = 0;
				reset();
			}
		}
		else {
			rotate(input, corresponding_table_from_move_to_degree_and_direction[0][input]);
			if (input != 18) {
				count++;
			}
		}
	}
	else {
		if (count >= RA) {
			count = 0;
			simuration(&state, input);
			update_face_posi(state, face_posi);
			foolr_value_of_coordinate();
			input = 18;
		}
		else {
			rotate(input, corresponding_table_from_move_to_degree_and_direction[0][input]);
			if (input != 18) {
				count++;
			}
		}
	}
	
	glDisable(GL_NORMALIZE);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}
static void idle() {
	if ((mode == 1)&&(input == 18)) {
		input = moves[move_count];
		move_count--;
	}
	glutPostRedisplay();
}
static void init() {
	glClearColor(0.7, 0.7, 0.7, 1.0);
}
static void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, (double)w / h, 10.0, 6000.0);
}
static void keyboard(unsigned char k, int x, int y) {
	if ((input == 18)&&(mode == 0)) {
		switch (k) {
		case 'q':
			input = 0;
			break;
		case 'w':
			input = 1;
			break;
		case 'e':
			input = 2;
			break;
		case 'r':
			input = 3;
			break;
		case 't':
			input = 4;
			break;
		case 'y':
			input = 5;
			break;
		case 'u':
			input = 6;
			break;
		case 'i':
			input = 7;
			break;
		case 'o':
			input = 8;
			break;
		case 'p':
			input = 9;
			break;
		case 'a':
			input = 10;
			break;
		case 's':
			input = 11;
			break;
		case 'd':
			input = 12;
			break;
		case 'f':
			input = 13;
			break;
		case 'g':
			input = 14;
			break;
		case 'h':
			input = 15;
			break;
		case 'j':
			input = 16;
			break;
		case 'k':
			input = 17;
			break;
		case 'x':
			start_search(state);
		for (int i = 0; i < mnum2; i++) {
			moves[move_count] = coorresponding_table_from_phase2_move_to_phase1_move[path2[i]];
			move_count++;
		}
		for (int i = 0; i < mnum1; i++) {
			moves[move_count] = path1[i];
			move_count++;
		}
		printf("[");
		for (int i = move_count - 1; i >= 0; i--) {
			printf("%d ", moves[i]);
		}
		printf("(%d)\n", move_count);
		if (move_count > 0) {
			move_count--;
			mode = 1;
		}
			break;
		default:
			break;
		}
	}
}
void reset() {
	init_state(&state);
	init_corner();
	init_edge();
	init_axises();
	init_cube_color();
	init_face_posi(face_posi);
	move_count = 0;
	mnum1 = 0;
	mnum2 = 0;
	for (int i = 0; i < VECTOR_LEN;i++) {
		moves[i] = 0;
		path1[i] = 0;
		path2[i] = 0;
	}
}
void graphic(int argc,char** argv) {
	init_state(&state);
	init_corner();
	init_edge();
	init_axises();
	init_cube_color();
	printf("q: R/ w: L/ e: F/ r: B/ t: U/ y: D/ u: R_/ i: L_/ o: F_/ p: B_/ a: U_/ s: D_/ d: R2/ f: L2/ g: F2/ h: B2/ j: U2/ k: D2/ x:start_search\n");
	glutInit(&argc, argv);
	glutInitWindowSize(WID,HIG);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("test test");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
}
