//============================================================================
// Name        : Module4Resubmit.cpp
// Author      : Danielle Hoopes
// Version     :2

// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <Gl/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;

GLint WindowWidth = 800, WindowHeight = 600;

GLuint VBO, VAO, EBO; //Global variables for Buffer Object etc.

GLuint ProgramId;

#define WINDOW_TITLE "Danielle Hoopes"

#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version "\n" #Source
#endif

void UResizeWindow(int, int);
void URenderGraphics(void);
void applyDepthSettings(void);
void UCreateVBO(void);
void UCreateShaders(void);

const GLchar * VertexShader = GLSL(330,

	layout(location=0) vec4 vertex_Position; //incoming data

	layout(location=1) vec4 colorFrom VBO;

	out vec4 mobileColor; //Attrib pointer 0
	//out vec4 colorFromVShader;

	//uniform mat4 primitiveTransform; //transform for shape

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

	 void main()
	 {
	        	 //gl_Position = primitiveTransform * vertex_Position; //move object on y-axis .5
	        	 gl_Position = projection * view * model * vec4(position, 1.0f); //move object on y-axis .5
	        	 //colorFromVShader = colorFromVBO;
	        	 mobileColor = color;
	 }

);
const GLchar * FragmentShader = GLSL(440,

		in vec3 mobileColor;
        out vec4 gpuColor;

         void main(){
        	// gl_FragColor= vec4(1.0, 0.5, 0.0, 1.0);
        	gpuColor= vec4(mobileColor, 1.0);
         }
);


//Main
int main(int argc, char* argv[])
{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowSize(WindowWidth, WindowHeight);
		glutCreateWindow(WINDOW_TITLE);


		glutReshapeFunc(UResizeWindow);

		glewExperimental = GL_TRUE;

		if(glewInit() != GLEW_OK)
		{
			cout << "Failed to initialize glew!" << endl;
			return -1;
		}

		UCreateVBO();
		UCreateShaders();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glEnable(GL_DEPTH_TEST);

		glutDisplayFunc(URenderGraphics);

		applyDepthSettings();

		glutMainLoop();

		glDeleteVertexArrays(1, &VAO);//cleanup
		glDeleteBuffers(1, &VBO);//cleanup
		glDeleteBuffers(1, &EBO);//cleanup


		return 0;
}

void UResizeWindow(int w, int h)
{
	WindowWidth = w;
	WindowHeight = h;
	glViewport(0, 0, WindowWidth, WindowHeight);
}


void URenderGraphics(void)
{
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);         //specify rendering mode

	 glBindVertexArray(VAO); //activate vertex array to render the vertices that render our shape

	 glm::mat4 model;
	 model = glm::translate(model,glm::vec3(0.0f, 0.0f, 0.0));
	 model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f)); //rotate shape x-axis by 1.0f
	 model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f)); //scale shape


	 glm::mat4 view; //camera
	 view = glm::translate(view,glm::vec3(0.0f, 0.0f, -5.0) ); //move camera back by 5 (z)

	 glm::mat4 projection;
	 projection = glm::perspective(45.0f, (GLfloat)WindowWidth / (GLfloat)WindowHeight, 0.1f, 100.0f);
	 //projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);


	 GLint modelLoc = glGetUniformLocation(ProgramId, "model");
	 GLint viewLoc = glGetUniformLocation(ProgramId, "view");
	 GLint projLoc = glGetUniformLocation(ProgramId, "projection");

	 glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	 glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	 glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	 //apply projection matrix
	 /*

	 glm::mat4 newTransform; //references 4 x 4 matrix

	 newTransform = glm::translate(newTransform, glm::vec3(0.0f, 0.5f, 0.0)); //make square move up y-axis
	 newTransform = glm::rotate(newTransform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //rotate shape
	 //newTransform = glm::scale(newTransform, glm::vec3(0.5f, 0.5f, 0.5f)); //rotate shape

	 GLuint transformInfo = glGetUniformLocation(ProgramId, "primitiveTransform"); //id for shader, name of variable shader
	 glUniformMatrix4fv(transformInfo, 1, GL_FALSE, glm::value_ptr(newTransform));
*/

	 GLuint totalVertices = 36;

	 glDrawElements(GL_TRIANGLES, totalVertices, GL_UNSIGNED_INT, 0);

	 glutPostRedisplay();

	 glBindVertexArray(0);

	 glutSwapBuffers();

}

void applyDepthSettings() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);
   glShadeModel(GL_SMOOTH);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void UCreateVBO(void)
{
	//specify coords for creating square
	// Positon and Color data
		GLfloat vertices[] = {
	// Vertex Positions    // Colors
			-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // Top Right Vertex 0
			1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Bottom Right Vertex 1
			1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // Bottom Left Vertex 2
			-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,    // Top Left Vertex 3
			0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

			0.5f, -0.5f, -1.0f, 0.5f, 0.5f, 1.0f,  // 4 br  right
			0.5f, 0.5f, -1.0f, 1.0f, 1.0f, 0.5f,  //  5 tl  right
			-0.5f, 0.5f, -1.0f, 0.2f, 0.2f, 0.5f,  //  6 tl  top
			-0.5f, -0.5f, -1.0f, 1.0f, 0.0f, 1.0f  //  7 bl back

		   	   	   	   	   	   };
		// Index data to share position data
		   GLuint indices[] = {
				   	   	   	   	   0, 1, 3,  // Triangle 1
								   1, 2, 3,   // Triangle 2
								   0, 1, 4,  // Triangle 3
								   0, 4, 5,  // Triangle 4
								   0, 5, 6, // Triangle 5
								   0, 3, 6,  // Triangle 6
								   4, 5, 6, // Triangle 7
								   4, 6, 7, // Triangle 8
								   2, 3, 6, // Triangle 9
								   2, 6, 7, // Triangle 10
								   1, 4, 7, // Triangle 11
								   1, 2, 7 // Triangle 12
		   	   	   	   	   	   };

	//generate id's for buffer object
	glGenVertexArrays(1, &VAO); //generate for Vertex Array Object
	glGenBuffers(1, &VBO);      //generate for Vertex Buffer Object
	glGenBuffers(1, &EBO);      //generate for Buffer Object

	glBindVertexArray(VAO);      //activate text array object

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //activating VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pass in size of array from line 128

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //specify indices and Element Buffer Object
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //pass in size of array from line 138

    GLint vertexStride = 6 * sizeof(GLfloat); //24 bytes determines vertex stride

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexStride, (GLvoid*)0);//send data to shader (accepts 6 arguments)GL_FALSE=not using normalization
    glEnableVertexAttribArray(0);//enable vertex attribute pointer, starting position of x,y,z

    GLint colorStride = 6 * sizeof(GLfloat); //24 bytes determines vertex stride
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, colorStride, (GLvoid*)(3 * sizeof(GLfloat)));//send data to shader (accepts 6 arguments)GL_FALSE=not using normalization
    glEnableVertexAttribArray(1);//specify color starting point

    glBindVertexArray(0);  //deactivate vertex array object (VBO)

}

void UCreateShaders(void)
{
	 ProgramId = glCreateProgram();

	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShaderId, 1, &VertexShader, NULL);
	glShaderSource(fragmentShaderId, 1, &FragmentShader, NULL);

	glCompileShader(vertexShaderId);
	glCompileShader(fragmentShaderId);

	glAttachShader(ProgramId, vertexShaderId);
	glAttachShader(ProgramId, fragmentShaderId);

	glLinkProgram(ProgramId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	glUseProgram(ProgramId);

}

