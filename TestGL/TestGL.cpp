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
/**绘制 函数，这里是空的*/
static void display() {
}
/**更换屏幕颜色设定矩阵模式
选择正摄投影的范围*/
static void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);//窗口的左下角是原点
}
/* Program entry point */

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);//相对屏幕的左上角
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//正在使用单个帧缓存，颜色模式//为RGB,这是默认的颜色模式
	glutCreateWindow("Draw Curves");
	init();
	if (glewInit() == GLEW_OK) {
		cout << "glew初始化成功！" << endl;
	}
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMainLoop();
}