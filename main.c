#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include"header.h"//今は一つの回転方向だけ
int width = WID;
int hight = HIG;
double angle = 0;
int count = 0;
int p = 0;//キーボード操作で変更
int a = 1;
int s = 3;
int move_memo = 0;
extern double cube[6][4][3];
typedef (*rfunc)(int);
typedef (*xyzfunc)(double,double*);
rfunc rotate[18] = {r_r,l_r,f_r,b_r,u_r,d_r,r__r,l__r,f__r,b__r,u__r,d__r,
	r2_r,l2_r,f2_r,b2_r,u2_r,d2_r};
xyzfunc xyzrotate[3] = {xrotate,yrotate,zrotate};
d_state state;
void clear() {
	for (int i = 0; i < 6;i++) {
		for (int j = 0; j < 4;j++) {
			for (int z = 0; z < 3;z++) {
				cube[i][j][z] = round(cube[i][j][z]/10)*10;
			}
		}
	}
}
void xrotate(double degree,double xyz[3]) {
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
	product(r_m,xyz);
	xyz[0] += X_AXIS;
	xyz[1] += Y_AXIS;
	xyz[2] += Z_AXIS;
}
void yrotate(double degree, double xyz[3]) {
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
void zrotate(double degree, double xyz[3]) {
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
void rotate(int f,int xyzmode){
	for(int i = 0;i<4;i++)
		{
			for(int j = 0;j<6;j++)
			{
				for(int k = 0;k<4;k++)
				{
					(xyzrotate[xyzmode])(p,corners[face_set[f][i]][j].face[k]);
				}
			}
		}
		for(int i = 0;i<4;i++)
		{
			for(int j = 0;j<6;j++)
			{
				for(ini k = 0;k<4;k++)
				{
					(xyzrotate[xyzmode])(p,edges[face_set[f][i+4]][j].face[k]);
				}
			}
		}
}

void disp_cube() {
	int normal[6][3] = {
		{0,1,0},
		{1,0,0},
		{0,0,1},
		{0,-1,0},
		{-1,0,0},
		{0,0,-1}
	};

	double color[6][3] = {
		{1.0,1.0,1.0},
		{1.0,0.0,0.0},
		{0.0,1.0,0.0},
		{1.0,1.0,0.0},
		{1.0,0.5,0.0},
		{0.0,0.0,1.0}
	};

	/*for (int i = 0; i < 6; i++) {
		glNormal3iv(normal[i]);
		glColor3dv(color[i]);
		glBegin(GL_QUADS);
		for (int j = 0; j < 4; j++) {
			glVertex3dv(cube[i][j]);
		}
	}*/

	
	//for (int i = 0; i < 8; i++) {
		/*for (int j = 0; j < 4;j++) {
			for (int k = 0; k < 6; k++) {
				glNormal3iv(normal[k]);
				glColor3dv(color[k]);
				glBegin(GL_QUADS);
				for (int l = 0; l < 4; l++) {
					glVertex3dv(corners[face_posi[0][j]][k][l]);
				}
			}
		}
		for (int j = 0; j < 4;j++) {
			for (int k = 0; k < 6;k++) {
				glNormal3iv(normal[k]);
				glColor3dv(color[k]);
				glBegin(GL_QUADS);
				for (int l = 0; l < 4; l++) {
					glVertex3dv(edges[face_posi[0][j+4]][k][l]);
				}
			}
		}*/
	//}
	glBegin(GL_QADS);
	for(int i = 0;i<6;i++)
	{
		for(int j = 0;j<8;j++)
		{
			for(int k = 0;k<6;k++)
			{
				glNormal3iv(normal[k]);
				glColor3dv(corners[j][k].color);
				for(int l = 0;l<4;l++)
				{
					glVertex3dv(corners[j][k].face[l]);
				}
			}
		}
		for(int j = 0;j<12;j++)
		{
			for(int k = 0;k<6;k++)
			{
				glNormal3iv(normal[k]);
				glColor3dv(edges[j][k].color);
				for(int l = 0;l<4;l++)
				{
					glVertex3dv(glVertex3dv(edges[j][k].face[l]););
				}
			}
		}
	}
	glEnd();
	glFlush();
}
void axis() {
	glColor3d(0.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex3i(0,0,0);
	glVertex3i(100,0,0);
	glVertex3i(0,0,0);
	glVertex3i(0,100,0);
	glVertex3i(0,0,0);
	glVertex3i(0,0,100);
	glColor3d(1.0,0.0,0.0);
	glVertex3d(0,Y_AXIS,Z_AXIS);
	glVertex3d(100,Y_AXIS,Z_AXIS);
	glEnd();
	glFlush();
}
void disp() {
//
	if (/*p*/0) {
		printf("p:%d coun:%d\n", p, count);

		for (int i = 0; i < 6; i++) {
			printf("[\n");
			for (int j = 0; j < 6; j++) {
				for (int z = 0; z < 3; z++) {
					printf("%3.10lf ", cube[i][j][z]);
				}
				printf("\n");
			}
			printf("[\n");
			printf("\n");
		}
	}
//
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(100.0, 100.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//glRotated(angle, 0.0, 1.0, 0.0);

	axis();
	disp_cube();
	glFlush();

	if (angle >= 360) {
		angle = 0;
	}
	else {
		angle += 0.04;
	}

	if (count >= RA) {
		printf("FFFFFFIIIIIINNNNNNNNSSSSSSHHHHHHHHHHHH\n");
		p = 0;
		count = 0;
		a = 0;
		simuration(&state,move_memo);
		update_face_posi(state,face_posi);
		clear();
	}
	else {
		/*for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 4; j++) {
				zrotate(p, cube[i][j]);
			}
		}*/
		
		
		/*for (int j = 0; j < 4;j++) {
			for (int k = 0; k < 6;k++) {
				for (int l = 0; l < 4;l++) {
					xrotate(p,corners[face_posi[0][j]][k][l]);
				}
			}
		}
		for (int j = 0; j < 4;j++) {
			for (int k = 0; k < 6;k++) {
				for (int l = 0; l < 4;l++) {
					xrotate(p, edges[face_posi[0][j+4]][k][l]);
				}
			}
		}*/
		
		if (p) {
			count++;
		}
	}

	glDisable(GL_NORMALIZE);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
}
void idle() {
	glutPostRedisplay();
}
void init() {
	glClearColor(0.7, 0.7, 0.7, 1.0);
}
void reshape(int w,int h) {
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, (double)w / h, 10.0, 6000.0);
	width = w;
	hight = h;
}
void mouse(int button,int state,int x,int y){
//	if ((button == GLUT_LEFT_BUTTON)&&(state == GLUT_DOWN)) {
		p = 1;
//	}
}
int main(int argc, char** argv) {
	init_state(&state);
	init_corner();
	init_edge();
	init_cube_color();
	glutInit(&argc, argv);
	glutInitWindowSize(width,hight);
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_DEPTH);//GL_だとうまくいかない
	glutCreateWindow("test test");
	glutDisplayFunc(disp);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	init();
	glutMainLoop();

}
