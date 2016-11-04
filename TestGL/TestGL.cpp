#include "stdafx.h"
#pragma comment(lib,"glew32.lib")//这里要加载该静态包
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm\glm.hpp>//斜杠和反斜杠都可以
#include <iostream>

/*
完整的shader过程。
初始化→编译→链接到程序
*/
using namespace std;

/*传入shader的引用，和GLSL字符串，对shader进行编译*/
void compileShader(GLint& shader, const GLchar* shaderCode) {
	const GLchar* codeArray[] = { shaderCode };
	glShaderSource(shader, 1, codeArray, NULL);
	glCompileShader(shader);//编译shader

							/*判断编译后的结果*/
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		cout << "shader编译错误！" << endl;
		GLint logLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char* log = (char*)malloc(logLen);
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, log);
			cout << log << endl;
			free(log);

		}
		exit(1);
	}
	else
	{
		cout << "shader编译成功！" << endl;
	}
}
void render(GLuint programHandle) {
	float positionData[] = {
		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		0.0f, 0.8f, 0.0f
	};
	float colorData[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	GLuint vboHandle[2];
	glGenBuffers(2, vboHandle);
	GLuint positionbufferHandle = vboHandle[0];
	GLuint colorBufferHandle = vboHandle[1];
	glBindBuffer(GL_ARRAY_BUFFER, positionbufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);//绑定顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);//绑定颜色数据

	GLuint vaoHandle;
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, positionbufferHandle);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
	glBindVertexArray(vaoHandle);
	//  绘制三角形
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glFlush();


}
void link() {
	//判断glew是否能初始化
	if (glewInit() != GLEW_OK) {
		cout << "glewInit()失败！" << endl;
		exit(1);
	}
	/*编译vertexShader*/
	const GLchar* shaderCode = "#version 400 \n in vec3 VertexPosition;in vec3 VertexColor;out vec3 Color;void main() {Color = VertexColor;gl_Position = vec4(VertexPosition, 1.0);}";
	GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShader == 0) {
		cout << "vertexShader无法获取！" << endl;
		exit(1);
	}
	compileShader(vertexShader, shaderCode);

	/*编译fragmentShader*/
	const GLchar* fragmentCode = "#version 400 \n in vec3 Color;out vec4 FragColor;void main() {FragColor=vec4(Color,1.0);}";
	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShader == 0) {
		cout << "fragmentShader无法获取！" << endl;
		exit(1);
	}
	compileShader(fragmentShader, fragmentCode);

	/*获得程序programHandle*/
	GLuint programHandle = glCreateProgram();
	if (programHandle == 0)
	{
		cout << "Program无法获取！" << endl;
		exit(1);

	}
	/*将shader链接到programHandle*/
	glAttachShader(programHandle, vertexShader);
	glAttachShader(programHandle, fragmentShader);
	glBindAttribLocation(programHandle, 0, "VertexPosition");
	glBindAttribLocation(programHandle, 1, "VertexColor");
	glLinkProgram(programHandle);

	/*判断链接状态*/
	GLint status;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		cout << "link失败！" << endl;
		GLint logLen;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char* log = (char*)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(programHandle, logLen, &written, log);
			cout << log << endl;
			free(log);

		}
		exit(1);
	}
	else {
		cout << "link成功！" << endl;
		glUseProgram(programHandle);//使用该程序
		render(programHandle);
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);;
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(900, 600);
	glutCreateWindow("First GLUT Sample");
	/*link函数是GLSL编写的主体*/
	glutDisplayFunc(link);
	glutMainLoop();
	return 0;
}
