#include <stdio.h>
#include <math.h>
#include <gl/glut.h>
#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600
#define PI 3.14159
void display(void);
int stack[20], k = 0, total = 0, a[20][20], n,s1,f1,maxflow[20][20],br[20][20],aa[20];

typedef struct
{
	int x, y;
} point;

point points[20];

void fordvalue(int k) {
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			br[i][j] = 0;
	int min;
	min = a[stack[0]][stack[1]] - maxflow[stack[0]][stack[1]];
	for (i = 1; i<k; i++)
		if (min>(a[stack[i - 1]][stack[i]]- maxflow[stack[i-1]][stack[i]])) 
			min = (a[stack[i - 1]][stack[i]] - maxflow[stack[i - 1]][stack[i]]);
	for (i = 1; i < k; i++) {
		maxflow[stack[i - 1]][stack[i]] += min;
		br[stack[i - 1]][stack[i]] = 1;
	}
	printf("\nmin=%d\n", min);
	total += min;
	display();
	Sleep(2000);
}
void fordfulk(int s, int f) {
	int i,j;
	stack[k++] = s; aa[s] = 1;
	for (i = n-1; i>=0; i--) {
		if (s == f) { fordvalue(k); return; }
		else if (a[s][i]>0 && aa[i]==0) {
			fordfulk(i, f);
			k--; aa[i] = 0;
		}
	}
}

void random()
{
	int i, k;

	for (int k = 0; k < n; k++)
	{
		int ri = rand() % WINDOW_WIDTH;
		ri -= WINDOW_WIDTH / 2;
		points[k].x = ri;

		ri = rand() % WINDOW_HEIGHT;
		ri -= WINDOW_HEIGHT / 2;
		points[k].y = ri;

	}

}


void drawCircle(GLfloat x, GLfloat y, GLfloat radius, GLfloat x1, GLfloat y1, GLfloat z1)
{
	int i;
	int triangleAmount = 1000;
	GLfloat twicePi = 2.0f * PI;
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor4f(x1, y1, z1, 1.0);
	for (i = 0; i <= triangleAmount; i++)
	{
		glVertex2f(x, y);
		glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
	}
	glEnd();
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}

void onResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawstring(GLfloat x, GLfloat y, char *string)
{
	char *c;
	glRasterPos2f(x, y);
	glColor3f(0, 0, 0);
	for (c = string; *c != '\0'; *c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

void printcost()
{
	char buffer[10],p[2]="/",buf[10];
	int k, i,z;
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			if (a[k][i] == 0) {
				continue;
			}
			else
			{
				int x = (points[i].x + points[k].x) / 2;
				int y = (points[i].y + points[k].y) / 2;

				_itoa_s(maxflow[k][i], buffer, 10);
				z = (maxflow[k][i] > 9) ? x - 25 : x - 15;
				drawstring(z, y + 10, buffer);
				drawstring(x-5, y + 10, p);
				_itoa_s(a[k][i], buf, 10);
				drawstring(x, y + 10, buf);
			}
		}
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1);
	glLineWidth(2);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if (a[i][j] != 0 ) {
				glBegin(GL_LINES);
				if(br[i][j]==0) glColor3f(0, 0, 0);
				else glColor3f(0, 0, 1);
				int x = points[i].x;
				int y = points[i].y;
				int x2 = points[j].x;
				int y2 = points[j].y;
				glVertex2i(x, y);
				glVertex2i(x2, y2);
				glEnd();
			}
	for (int i = 0; i < n; i++) {
		if(i==s1) drawCircle(points[i].x, points[i].y, 10,0,1,0);
		else if(i==f1) drawCircle(points[i].x, points[i].y, 10,1,0,0);
		else drawCircle(points[i].x, points[i].y, 10,0.7,0.7,0.7);
		char buffer[20];
		_itoa_s(i, buffer, 10);
		drawstring(points[i].x, points[i].y + 10, buffer);
	}
	printcost();
	drawCircle(500,300 , 10, 0, 1, 0);
	char qw[20] = "-> Starting Node";
	drawstring(520,295, qw);
	char wq[20] = "-> Ending Node";
	drawCircle(500, 250, 10, 1, 0, 0);
	drawstring(520, 245, wq);
	glFlush();
}

void frontscreen(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	char vvce[50] = "Vidyavardhaka College of Engineering";
	drawstring(-WINDOW_HEIGHT / 2.79, WINDOW_WIDTH / 2, vvce);
	glColor3f(0.7, 0, 1);
	char dept[50] = "DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING ";
	drawstring((-WINDOW_HEIGHT / 2.79)-80, (WINDOW_WIDTH / 2)-50, dept);
	glColor3f(1, 0.5, 0);
	char miniproj[50] = "A MINI PROJECT ON : ";
	drawstring((-WINDOW_HEIGHT / 2.79) - 80, (WINDOW_WIDTH / 2) - 200, miniproj);
	glColor3f(1, 0, 0);
	char title[50] = "Ford-Fulkerson Maximum Flow In a Graph";
	drawstring((-WINDOW_HEIGHT / 2.79)+120, (WINDOW_WIDTH / 2) - 200, title);
	glColor3f(1, 0.5, 0);
	char by[10] = "BY:";
	drawstring(250,-200, by);
	glColor3f(0.5, 0, 0.5);
	char pr[30] = "R Prajwal (4VV15CS080)";
	drawstring(300, -200, pr);
	glColor3f(0.5, 0, 0.5);
	char rah[30] = "Rahul R (4VV15CS084)";
	drawstring(300, -230,rah);
	/*glColor3f(1, 0.5, 0);
	drawstring(68, 50, "GUIDES:");
	glColor3f(0.5, 0.2, 0.2);
	drawstring(63, 40, "GUIDE NAME FIRST");
	drawstring(63, 34,"GUIDE NAME SECOND");*/
	glColor3f(1, 0.1, 1);
	char start[20] = "PRESS 's' TO START";
	drawstring(-100, -300, start);
	glFlush();
}


void keyCB(unsigned char key, int x, int y)
{
	int i, j;
	char p[30] = "MaxFlow in the Graph : ",buf[10];
	if (key == 'q') exit(0);
	if (key == 'f') {
		total = 0; k = 0;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				maxflow[i][j] = 0;
		fordfulk(s1,f1);
		int i, j;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				br[i][j] = 0;
		//display();
		glColor3f(0, 0, 0);
		drawstring(-650,-320 ,p);
		_itoa_s(total, buf, 10);
		glColor3f(0, 0, 0);
		drawstring(-450, -320, buf);
		glFlush();
	}
	if (key == 's') {
		random();
		display();

	}
}

int main(int argc, char** argv)
{
	int i, j, s, f;
	printf("Enter the number of vertices : ");
	scanf_s("%d", &n);
	printf("Enter the matrix : \n");
	for (i = 0; i<n; i++)
		for (j = 0; j < n; j++)
			scanf_s("%d", &a[i][j]);
	printf("Enter the starting node : ");
	scanf_s("%d", &s);
	printf("Enter the ending node : ");
	scanf_s("%d", &f);
	f1 = f; s1 = s;
	for (i = 0; i < 10; i++) { stack[i] = 0; aa[i] = 0; }
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Open GL");
	init();
	glutDisplayFunc(frontscreen);
	glutReshapeFunc(onResize);
	glutKeyboardFunc(keyCB);
	glutPostRedisplay();
	glutMainLoop();
	return 0;
}
