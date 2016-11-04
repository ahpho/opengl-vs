#include "stdafx.h"

// OpenGL-Demo.cpp : Defines the entry point for the console application.
// Created by 曹艳丰
//2016-06-09
//#pragma comment(lib,"glew32.lib")//不用

#pragma comment(lib,"GLTools.lib")

//#include <glew.h>//不用
#include <GLTools.h>
#include <GLShaderManager.h>
#include <GL\freeglut.h>
GLBatch triangleBatch;
GLShaderManager shaderManager;
///////////////////////////////////////////////////////////////////////////////  
// Window has changed size, or has just been created. In either case, we need  
// to use the window dimensions to set the viewport and the projection matrix.  
void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
}


///////////////////////////////////////////////////////////////////////////////  
// This function does any needed initialization on the rendering context.   
// This is the first opportunity to do any OpenGL related tasks.  
void SetupRC()
{
	// Blue background  
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	shaderManager.InitializeStockShaders();

	// Load up a triangle  
	GLfloat vVerts[] = { -0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f };

	triangleBatch.Begin(GL_TRIANGLES, 3);
	triangleBatch.CopyVertexData3f(vVerts);
	triangleBatch.End();
}



///////////////////////////////////////////////////////////////////////////////  
// Called to draw scene  
void RenderScene(void)
{
	// Clear the window with current clearing color  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
	triangleBatch.Draw();

	// Perform the buffer swap to display back buffer  
	glutSwapBuffers();
}


///////////////////////////////////////////////////////////////////////////////  
// Main entry point for GLUT based programs  
int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Triangle");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	SetupRC();

	glutMainLoop();
	return 0;
}
