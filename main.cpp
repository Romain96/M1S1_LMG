#define NDEBUG

//////////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>
#include <GL/glew.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL.h>
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

////////////////////////////////////////////////////////////////////////////
// DEFINITIONS
////////////////////////////////////////////////////////////////////////////

void display();
void reshape(int width, int height);
void mouse_callback(int button, int state, int x, int y);
void scroll_callback(int button, int dir, int x, int y);
void processInput(unsigned char key, int x, int y);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// autre
Shader *ourShader;
Model *ourModel;

////////////////////////////////////////////////////////////////////////////
// MAIN
////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	// initialisation de la librairie GLUT
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Model Loader");

	// Initialisation de la librairie GLEW
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
		exit(-1);
	}

	// configure global opengl state
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	ourShader = new Shader("model_loading.vs", "model_loading.fs");

	// load models
	ourModel = new Model("nanosuit/nanosuit.obj");

	// fonctions de callback
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(processInput);
	glutMouseFunc(mouse_callback);
	glutMouseWheelFunc(scroll_callback);

	// boucle principale
	glutMainLoop();

	return 0;
}

////////////////////////////////////////////////////////////////////////////
// DISPLAY LOOP
////////////////////////////////////////////////////////////////////////////
void display()
{
	// per-frame time logic
	// --------------------
	float currentFrame = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// render
	// ------
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// don't forget to enable shader before setting uniforms
	ourShader->use();

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	ourShader->setMat4("projection", projection);
	ourShader->setMat4("view", view);

	// render the loaded model
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
	ourShader->setMat4("model", model);
	ourModel->Draw(*ourShader);

	glutSwapBuffers();
}

////////////////////////////////////////////////////////////////////////////
// KEYBOARD KEY PRESSED EVENT
////////////////////////////////////////////////////////////////////////////
void processInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		camera.ProcessKeyboard(FORWARD, deltaTime);
		break;
	case GLUT_KEY_DOWN:
		camera.ProcessKeyboard(FORWARD, deltaTime);
		break;
	case GLUT_KEY_LEFT:
		camera.ProcessKeyboard(FORWARD, deltaTime);
		break;
	case GLUT_KEY_RIGHT:
		camera.ProcessKeyboard(FORWARD, deltaTime);
		break;
	}
}

////////////////////////////////////////////////////////////////////////////
// MOUSE EVENT
////////////////////////////////////////////////////////////////////////////
void mouse_callback(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		lastX = x;
		lastY = y;
	}

	float xoffset = x - lastX;
	float yoffset = lastY - y; // reversed since y-coordinates go from bottom to top

	lastX = x;
	lastY = y;

	camera.ProcessMouseMovement(xoffset, yoffset, false);
}

////////////////////////////////////////////////////////////////////////////
// MOUSE WHEEL EVENT
////////////////////////////////////////////////////////////////////////////
void scroll_callback(int button, int dir, int x, int y)
{
	camera.ProcessMouseScroll(dir);
	return;
}

////////////////////////////////////////////////////////////////////////////
// MOUSE WHEEL EVENT
////////////////////////////////////////////////////////////////////////////
void reshape(int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}