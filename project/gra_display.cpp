#include"rubiks_cube_graphic.h"
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

/**
* MODE ----- cubes are stationary.
* other ----- cubes are rotating.
*/
static int input = MOVE;

/**
* 0 ----- you can type and oparate the rubik's cube.
* 1 -----you can't type(play mode).
* -1 -----you can type only to move to the next step of solution or to go back one step of solution (step mode).
*/
static int mode = 0;    
static int count_down_motion = 0;
static char key_set[PHASE1_MOVE + 4] = { 'q','w','e','r','t','y','u','i','o','p','a','s','d','f','g','h','j','k','x','z','c','v'};
static int rotation_speed = 2;
static int corresponding_table_from_move_to_degree_and_direction[2][PHASE1_MOVE+1] = {
	{0,0,2,2,1,1,0, 0,2,2,1,1,0,0,2,2,1,1,0},
	{1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,-2,2,-2,2,-2,2,0}
};
static void floor_value_of_coordinate(int face) {
	for (int i = 0; i < NUM_FOUR_CORNER;i++) {
		for (int j = 0; j < NUM_FACE; j++) {
			for (int k = 0; k < NUM_FOUR_CORNER; k++) {
				for (int l = 0; l < 3; l++) {
					corners[face_posi[face % NUM_FACE][i]][j].face[k][l] = round(corners[face_posi[face % NUM_FACE][i]][j].face[k][l] / 10) * 10;
				}
			}
		}
	}
	for (int i = 4; i < 4 + NUM_FOUR_CORNER; i++) {
		for (int j = 0; j < NUM_FACE; j++) {
			for (int k = 0; k < NUM_FOUR_CORNER; k++) {
				for (int l = 0; l < 3; l++) {
					edges[face_posi[face % NUM_FACE][i]][j].face[k][l] = round(edges[face_posi[face % NUM_FACE][i]][j].face[k][l] / 10) * 10;
				}
			}
		}
	}
	for (int i = 0; i < NUM_FACE;i++) {
		for (int j = 0; j < NUM_FOUR_CORNER;j++) {
			for (int k = 0; k < 3;k++) {
				axises[face % NUM_FACE][i].face[j][k] = round(axises[face % NUM_FACE][i].face[j][k] / 10) * 10;
			}
		}
	}
}
static void x_rotate(double degree, double xyz[3]) {
	degree /= rotation_speed;
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
	degree /= rotation_speed;
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
	degree /= rotation_speed;
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
	if (input == PHASE1_MOVE) {
		return;
	}
	for (int i = 0; i < NUM_FOUR_CORNER; i++)
	{
		for (int j = 0; j < NUM_FACE; j++)
		{
			for (int k = 0; k < NUM_FOUR_CORNER; k++)
			{
				(xyzrotate[xyzmode])(corresponding_table_from_move_to_degree_and_direction[1][input], corners[face_posi[face % NUM_FACE][i]][j].face[k]);
			}
		}
	}
	for (int i = 0 + 4; i < 4 + NUM_FOUR_CORNER; i++)
	{
		for (int j = 0; j < NUM_FACE; j++)
		{
			for (int k = 0; k < NUM_FOUR_CORNER; k++)
			{
				(xyzrotate[xyzmode])(corresponding_table_from_move_to_degree_and_direction[1][input], edges[face_posi[face % NUM_FACE][i]][j].face[k]);
			}
		}
	}
	for (int j = 0; j < NUM_FACE; j++) {
		for (int k = 0; k < NUM_FOUR_CORNER; k++) {
			(xyzrotate[xyzmode])(corresponding_table_from_move_to_degree_and_direction[1][input], axises[input % NUM_FACE][j].face[k]);
		}
	}
}
int set_rotaion_speed(int speed) {
	if (speed != 0) {
		rotation_speed = speed;
		return 1;
	}
	else {
		printf("0 is invalid\n");
		return 0;
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
			glColor3dv(axises[i][j].color);
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
	static int count = 0;
	static double angle = 0;
	static int right_abgle = 90 * rotation_speed;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(120.0, 80.0, 80.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//glRotated(angle, -0.2, 0.1, 0.5);

	disp_xyzaxis();
	disp_cube();
	glFlush();

	if (angle >= 360) {
		angle = 0;
	}
	else {
		angle += 0.04;
	}

	if (mode != 0) {
		if (count >= right_abgle) {
			count = 0;
			phase1_motion(get_state_value_address(),input);
			//printf(">answer input\n");
			//disp_state(*get_state_value_address());
			update_cube_group(*get_state_value_address(), face_posi);
			floor_value_of_coordinate(input);
			input = PHASE1_MOVE;

			if (count_down_motion == -1) {
				mode = 0;
				//printf(">solved\n");
				//disp_state(*get_state_value_address());
			}
		}
		else {
			rotate(input, corresponding_table_from_move_to_degree_and_direction[0][input]);
			if (input != PHASE1_MOVE) {
				count++;
			}
		}
	}
	else {
		if (count >= right_abgle) {
			count = 0;
			phase1_motion(get_state_value_address(), input);
			//printf(">input is done\n");
			//disp_state(*get_state_value_address());
			update_cube_group(*get_state_value_address(), face_posi);
			floor_value_of_coordinate(input);
			input = PHASE1_MOVE;
		}
		else {
			rotate(input, corresponding_table_from_move_to_degree_and_direction[0][input]);
			if (input != PHASE1_MOVE) {
				count++;
			}
		}
	}

	glDisable(GL_NORMALIZE);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}
static void idle() {
	if ((mode == 1) && (input == PHASE1_MOVE )) {
		input = get_motion_list_address()[count_down_motion];
		count_down_motion--;
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
	if ((input == PHASE1_MOVE) && (mode == 0)) {
		for (int i = 0; i < PHASE1_MOVE+3;i++) {
			if (k == key_set[i]) {
				if (i == PHASE1_MOVE) {
					search(*get_state_value_address());
				}
				else if (i == (PHASE1_MOVE + 1)) {
					count_down_motion = *get_motion_count_address() - 1;
					if (count_down_motion > 0) {
						mode = 1;
					}
				}
				else if (i == (PHASE1_MOVE + 2)) {
					count_down_motion = *get_motion_count_address() - 1;
					if (count_down_motion > 0) {
						mode = -1;
					}
				}
				else {
					//printf(">keyboard input\n");
					//disp_state(*get_state_value_address());
					input = i;
				}
				break;
			}
		}
	}
	else if ((input == PHASE1_MOVE) && (mode == -1)) {
		if (k == key_set[PHASE1_MOVE + 2]) {
			input = get_motion_list_address()[count_down_motion];
			count_down_motion--;
		}
		else if ((k == key_set[PHASE1_MOVE + 3])&&(count_down_motion < *get_motion_count_address()-1)) {
			input = get_reverse_motion(get_motion_list_address()[count_down_motion + 1]);
			count_down_motion++;
		}
	}
}
void key_setting() {
	for (int i = 0; i < PHASE1_MOVE;i++) {
		char name[3];
		get_motion_name_from_index(i, name, 3);
		printf(" %s: %c | ",name,key_set[i]);
	}
	printf(" start search %c | view mode %c | step mode/one step forward %c | go back one step %c \n",key_set[18],key_set[19],key_set[20],key_set[21]);
}
int set_keyboard(int index,char key) {
	if ((0<=index)&&(index<=PHASE1_MOVE)) {
		key_set[index] = key;
		return 1;
	}
	else {
		return 0;
	}
}
void graphic(int argc, char** argv) {
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
