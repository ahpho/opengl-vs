#include "stdafx.h"
#pragma comment(lib,"glew32.lib")//����Ҫ���ظþ�̬��
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm\glm.hpp>//б�ܺͷ�б�ܶ�����
#include <iostream>

/*
������shader���̡�
��ʼ������������ӵ�����
*/
using namespace std;

/*����shader�����ã���GLSL�ַ�������shader���б���*/
void compileShader(GLint& shader, const GLchar* shaderCode) {
	const GLchar* codeArray[] = { shaderCode };
	glShaderSource(shader, 1, codeArray, NULL);
	glCompileShader(shader);//����shader

							/*�жϱ����Ľ��*/
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		cout << "shader�������" << endl;
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
		cout << "shader����ɹ���" << endl;
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
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), positionData, GL_STATIC_DRAW);//�󶨶�������
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colorData, GL_STATIC_DRAW);//����ɫ����

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
	//  ����������
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glFlush();


}
void link() {
	//�ж�glew�Ƿ��ܳ�ʼ��
	if (glewInit() != GLEW_OK) {
		cout << "glewInit()ʧ�ܣ�" << endl;
		exit(1);
	}
	/*����vertexShader*/
	const GLchar* shaderCode = "#version 400 \n in vec3 VertexPosition;in vec3 VertexColor;out vec3 Color;void main() {Color = VertexColor;gl_Position = vec4(VertexPosition, 1.0);}";
	GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShader == 0) {
		cout << "vertexShader�޷���ȡ��" << endl;
		exit(1);
	}
	compileShader(vertexShader, shaderCode);

	/*����fragmentShader*/
	const GLchar* fragmentCode = "#version 400 \n in vec3 Color;out vec4 FragColor;void main() {FragColor=vec4(Color,1.0);}";
	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShader == 0) {
		cout << "fragmentShader�޷���ȡ��" << endl;
		exit(1);
	}
	compileShader(fragmentShader, fragmentCode);

	/*��ó���programHandle*/
	GLuint programHandle = glCreateProgram();
	if (programHandle == 0)
	{
		cout << "Program�޷���ȡ��" << endl;
		exit(1);

	}
	/*��shader���ӵ�programHandle*/
	glAttachShader(programHandle, vertexShader);
	glAttachShader(programHandle, fragmentShader);
	glBindAttribLocation(programHandle, 0, "VertexPosition");
	glBindAttribLocation(programHandle, 1, "VertexColor");
	glLinkProgram(programHandle);

	/*�ж�����״̬*/
	GLint status;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		cout << "linkʧ�ܣ�" << endl;
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
		cout << "link�ɹ���" << endl;
		glUseProgram(programHandle);//ʹ�øó���
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
	/*link������GLSL��д������*/
	glutDisplayFunc(link);
	glutMainLoop();
	return 0;
}
