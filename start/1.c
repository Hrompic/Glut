#include <GL/glut.h>
#include <GL/freeglut_ext.h>
//#include <SFML/Graphics.hpp>
#include <stdio.h>
GLint prog;

void render()
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glClearColor(0,1,0,1);
    
    glutSwapBuffers();
}
int init()
{
	GLint comp=0, link=0;
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	char *vsrc = 
	"#version 100\n"
	"attribute vec2 cord2d;"
	"void main(void) {"
	"gl_Position = vec4(cord2d, 0.0, 1.0);"
	"}";
	glShaderSource(vs, 1, &vsrc, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &comp);
	fprintf(stderr, "Shader %d, %d\n", vs, comp );
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	char *fsrc=
	"#version 100\n"
	"void main(void) { "
	" gl_FragColor[0] = 0.0; "
	" gl_FragColor[1] = 0.0; "
	" gl_FragColor[2] = 1.0; "
	"}";
	glShaderSource(fs, 1, &fsrc, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &comp);
	fprintf(stderr, "Shader %d, %d\n", fs, comp );
	

}
int main(int argc, char **argv)
{
	glutInitContextVersion(2, 1);
	glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_RGBA| GLUT_DEPTH| GLUT_DOUBLE);
    glutCreateWindow("Wimdow");
	init();
    glutDisplayFunc(render);
    glutMainLoop();	
}
