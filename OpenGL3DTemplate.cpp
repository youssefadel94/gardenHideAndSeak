#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)
float y = 0.2;
float xt = 0.4;
float zt = 0.4;
float fs = 0.04;
float yc = 0.02;
float pstop = 0.046;
class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 1.0, float eyeY = 1.0f, float eyeZ = 1.0, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
			);
	}
};

Camera camera;

void drawWall(double thickness) {
	glPushMatrix();
	glTranslated(0.4, 0.5 * thickness, 0.4);
	glScaled(0.8, thickness, 0.8);
	glutSolidCube(1);
	glPopMatrix();
}
void drawFence() {
	float l = 0.013;
	float ll = fs;
	float lll = fs + 0.013;
	for (int i = 0; i < 20; i++) {
		glPushMatrix();
		glTranslated(0, 0.07, l);
		glScaled(0.01, 0.2, 0.01);
		glutSolidCube(1);
		glPopMatrix();
		l = l + fs;
	}
	l = 0;
	for (int j = 0; j < 20; j++) {
		glPushMatrix();
		glTranslated(ll, 0.07, l);
		glScaled(0.01, 0.2, 0.01);
		glutSolidCube(1);
		glPopMatrix();
		ll = ll + fs;
	}
	ll = ll - fs;
	for (int jj = 0; jj < 20; jj++) {
		glPushMatrix();
		glTranslated(ll, 0.07, lll);
		glScaled(0.01, 0.2, 0.01);
		glutSolidCube(1);
		glPopMatrix();
		lll = lll + fs;
	}




}
void drawTableLeg(double thick, double len) {
	glPushMatrix();
	glTranslated(0, len / 2, 0);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawPergola(double topWid, double topThick, double legThick, double legLen) {

	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topThick);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, legLen, pstop);
	glScaled(topWid, topThick, topThick);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, legLen, pstop * 2);
	glScaled(topWid, topThick, topThick);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, legLen, -pstop);
	glScaled(topWid, topThick, topThick);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, legLen, pstop*-2);
	glScaled(topWid, topThick, topThick);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, legLen, 0);
	glRotated(90, 0, 1, 0);
	glScaled(topWid, topThick, topThick);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(pstop, legLen, 0);
	glRotated(90, 0, 1, 0);
	glScaled(topWid, topThick, topThick);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(pstop * 2, legLen, 0);
	glRotated(90, 0, 1, 0);
	glScaled(topWid, topThick, topThick);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(pstop*-1, legLen, 0);
	glRotated(90, 0, 1, 0);
	glScaled(topWid, topThick, topThick);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(pstop * -2, legLen, 0);
	glRotated(90, 0, 1, 0);
	glScaled(topWid, topThick, topThick);
	glutSolidCube(1.0);
	glPopMatrix();

	double dist = 0.95 * topWid / 2.0 - legThick / 2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	drawTableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glTranslated(-2 * dist, 0, 2 * dist);
	drawTableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
}
void drawJackPart() {
	glPushMatrix();
	glScaled(0.2, 0.2, 1.0);
	glutSolidSphere(1, 15, 15);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, 0, 1.2);
	glutSolidSphere(0.2, 15, 15);
	glTranslated(0, 0, -2.4);
	glutSolidSphere(0.2, 15, 15);
	glPopMatrix();
}
void drawJack() {
	glPushMatrix();
	drawJackPart();
	glRotated(90.0, 0, 1, 0);
	drawJackPart();
	glRotated(90.0, 1, 0, 0);
	drawJackPart();
	glPopMatrix();
}
void drawChair(double topWid, double topThick, double legThick, double legLen) {
	glPushMatrix();
	glTranslated(0, legLen, 0);
	glScaled(topWid, topThick, topWid);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, legLen*1.5, -topWid / 2);
	glRotated(90, 1, 0, 0);
	glScaled(topWid, topThick, topWid);
	glutSolidCube(1.0);
	glPopMatrix();

	double dist = 0.95 * topWid / 2.0 - legThick / 2.0;
	glPushMatrix();
	glTranslated(dist, 0, dist);
	drawTableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glTranslated(-2 * dist, 0, 2 * dist);
	drawTableLeg(legThick, legLen);
	glTranslated(0, 0, -2 * dist);
	drawTableLeg(legThick, legLen);
	glPopMatrix();
}

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}
void tree(float xt, float zt) {
	glPushMatrix();
	glTranslated(xt, y, zt);
	glScaled(0.01, 0.2, 0.01);
	glColor3f(0.2, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(xt, y + 0.01, zt + 0.007);
	glRotated(45, 1, 0, 0);
	glScaled(0.001, 0.04, 0.01);
	glColor3f(0.2, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(xt, y + 0.01, zt - 0.007);
	glRotated(-45, 1, 0, 0);
	glScaled(0.001, 0.04, 0.01);
	glColor3f(0.2, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(xt, y + 0.1, zt);
	glRotated(90, 1, 0, 0);
	glColor3f(0, 0.7, 0.2);
	glutSolidSphere(0.07, 4, 16);
	glPopMatrix();

}
void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setupCamera();
	setupLights();
	glPushMatrix();
	glColor3f(0.2, 0, 0);

	drawFence();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0.7, 0.2);
	drawWall(0.02);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0, 0.1, 0);
	glutSolidSphere(0.01, 3, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0, -0.1, 0);
	tree(0.4, 0.75);
	tree(0.2, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.4, yc, 0.15);
	glColor3f(0.3, 0, 1);
	drawChair(0.07, 0.0001, 0.005, 0.07);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0.5, yc, 0.15);
	glColor3f(0.1, 1, 1);
	drawChair(0.07, 0.0001, 0.005, 0.07);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.5, 0, 0.4);
	glColor3f(0.3, 0.1, 0.1);
	drawPergola(0.2, 0.01, 0.007, 0.3);
	glPopMatrix();
	glFlush();

}

void Keyboard(unsigned char key, int x, int y) {
	float d = 0.01;
	float aa = 1.0;
	if (key == 'y') {
		y = y + 0.2;
	}
	if (key == 'h')
		y = y - 0.2;

	switch (key) {

	case 'w':
		camera.moveY(d);
		break;
	case 's':
		camera.moveY(-d);
		break;
	case 'a':
		camera.moveX(d);
		break;
	case 'd':
		camera.moveX(-d);
		break;
	case 'q':
		camera.moveZ(d);
		break;
	case 'e':
		camera.moveZ(-d);
		break;

	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	glutPostRedisplay();
}
void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Lab 5");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}
