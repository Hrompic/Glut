#include <GL/glut.h>
//#include <SFML/Graphics.hpp>
#include <stdio.h>

#ifdef ANDROID
#include <android/log.h>
#endif

#include <GLES2/gl2.h>
#include <GL/freeglut_ext.h>
GLint prog;
GLint attr2d;

#ifdef ANDROID
#define LOGI(...)  ((void)__android_log_print(ANDROID_LOG_INFO, "My glut", __VA_ARGS__))

#else
#define LOGI(...) printf(__VA_ARGS__)
#endif

void render()
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glClearColor(0,1,0,1);
	glUseProgram(prog);
	glEnableVertexAttribArray(attr2d);
	GLfloat triangle[] = 
	{
	 0.0,  0.8,
    -0.8, -0.8,
     0.8, -0.8,
	};
	glVertexAttribPointer(attr2d, 2,
					GL_FLOAT, GL_FALSE,
					0, triangle);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(attr2d);
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
	LOGI("vShader %d, %d\n", vs, comp);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	char *fsrc=
	"#version 100\n"
	"void main(void){"
	" gl_FragColor.x = 0.0;"
	" gl_FragColor[1] = 0.0;"
	" gl_FragColor[2] = 1.0;"
	"}";
	glShaderSource(fs, 1, &fsrc, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &comp);
	LOGI("fShader %d, %d\n", fs, comp );
	char* l =  (char*)glGetString(GL_VERSION);
	LOGI("%s",l);	
	prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);
	glGetProgramiv(prog, GL_LINK_STATUS, &link);
	LOGI("Program:%d, %d\n", prog, link);
	char* attr = "cord2d";
	attr2d = glGetAttribLocation(prog, attr);
	LOGI("Attrib: %d\n",attr2d);

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
