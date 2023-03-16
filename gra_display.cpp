
#include"rubiks_cube_graphic.h"
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
static int input = 18;
static int mode = 0;
static char key_set[19] = { 'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','x'};
//static int moves[60] = { 0 };
//d_state state;
static int corresponding_table_from_move_to_degree_and_direction[2][19] = {
	{ 0,0, 2,2, 1,1,    0, 0,2, 2,1,1,   0,0,2,2,1,1     ,0},
	{1,-1,-1,1,1,-1,    -1,1,1,-1,-1,1 , -2,2,-2,2,-2,2  ,0}
};
static void floor_value_of_coordinate(int face) {
	for (int i = 0; i < 4;i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 3; l++) {
					corners[face_posi[face % 6][i]][j].face[k][l] = round(corners[face_posi[face % 6][i]][j].face[k][l] / 10) * 10;
				}
			}
		}
	}
	for (int i = 0 + 4; i < 4 + 4; i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 3; l++) {
					edges[face_posi[face % 6][i]][j].face[k][l] = round(edges[face_posi[face % 6][i]][j].face[k][l] / 10) * 10;
				}
			}
		}
	}
	for (int i = 0; i < 6;i++) {
		for (int j = 0; j < 4;j++) {
			for (int k = 0; k < 3;k++) {
				axises[face % 6][i].face[j][k] = round(axises[face % 6][i].face[j][k] / 10) * 10;
			}
		}
	}
}
static void update_face_position(d_state x, int face[6][8]) {
	
	int face_set[6][8] = {
	{1,2,5,6,1,2,5,9},
	{0,3,4,7,0,3,7,11},
	{2,3,6,7,2,3,6,10},
	{0,1,4,5,0,1,4,8},
	{0,1,2,3,4,5,6,7},
	{4,5,6,7,8,9,10,11}
	};
	
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			face[i][j] = x.cp[face_set[i][j]];
		}
		for (int j = 4; j < 8; j++) {
			face[i][j] = x.ep[face_set[i][j]];
		}
	}
}
static void x_rotate(double degree, double xyz[3]) {
	degree /= 2;
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
	degree /= 2;
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
	degree /= 2;
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
				(xyzrotate[xyzmode])(corresponding_table_from_move_to_degree_and_direction[1][input], corners[face_posi[face % 6][i]][j].face[k]);
			}
		}
	}
	for (int i = 0 + 4; i < 4 + 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				(xyzrotate[xyzmode])(corresponding_table_from_move_to_degree_and_direction[1][input], edges[face_posi[face % 6][i]][j].face[k]);
			}
		}
	}
	for (int j = 0; j < 6; j++) {
		for (int k = 0; k < 4; k++) {
			(xyzrotate[xyzmode])(corresponding_table_from_move_to_degree_and_direction[1][input], axises[input % 6][j].face[k]);
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
			phase1_motion(get_state_value_address(),input);
			//simuration(get_state_value_address(), input);
			update_face_position(*get_state_value_address(), face_posi);
			floor_value_of_coordinate(input);
			input = 18;
			if (motion_count == -1) {
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
			phase1_motion(get_state_value_address(), input);
			//simuration(get_state_value_address(), input);
			update_face_position(*get_state_value_address(), face_posi);
			floor_value_of_coordinate(input);
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
	if ((mode == 1) && (input == 18)) {
		input = motion_list[motion_count];
		motion_count--;
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
	if ((input == 18) && (mode == 0)) {
		for (int i = 0; i < 19;i++) {
			if (k == key_set[i]) {
				if (i == 18) {
					search(*get_state_value_address());
					printf("[");
					for (int i = motion_count - 1; i >= 0; i--) {
						printf("%d ", motion_list[i]);
					}
					printf("(%d)\n", motion_count);
					if (motion_count > 0) {
						motion_count--;
						mode = 1;
					}
				}
				else {
					input = i;
				}
				break;
			}
		}
	}
}
void reset() {
	init_state(get_state_value_address());
	init_corner();
	init_edge();
	init_axises();
	//init_cube_color();
	//init_face_position(face_posi);
	init_motion_list();
}
void key_setting(int i,char x) {
	if ((0<=i)&&(i<=18)) {
		key_set[i] = x;
	}
}
void graphic(int argc, char** argv) {
	reset();
	printf("q: R/ w: L/ e: F/ r: B/ t: U/ y: D/ u: R_/ i: L_/ o: F_/ p: B_/ a: U_/ s: D_/ d: R2/ f: L2/ g: F2/ h: B2/ j: U2/ k: D2/ x:start_search\n");
	glutInit(&argc, argv);
	glutInitWindowSize(WID, HIG);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("test test");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	init();
	glutMainLoop();
}
