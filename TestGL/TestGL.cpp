#include "stdafx.h"

// OpenGL-Demo.cpp : Defines the entry point for the console application.
//
#pragma comment(lib,"glew32.lib")
#include <glew.h>
#include <freeglut.h>
#include <iostream>
using namespace std;
/* GLUT callback Handlers */

static void resize(GLint width, GLint height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)width, 0.0, (GLdouble)height);
	glClear(GL_COLOR_BUFFER_BIT);
}
/**���� �����������ǿյ�*/
static void display() {
}
/**������Ļ��ɫ�趨����ģʽ
ѡ������ͶӰ�ķ�Χ*/
static void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);//���ڵ����½���ԭ��
}
/* Program entry point */

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);//�����Ļ�����Ͻ�
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//����ʹ�õ���֡���棬��ɫģʽ//ΪRGB,����Ĭ�ϵ���ɫģʽ
	glutCreateWindow("Draw Curves");
	init();
	if (glewInit() == GLEW_OK) {
		cout << "glew��ʼ���ɹ���" << endl;
	}
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMainLoop();
}