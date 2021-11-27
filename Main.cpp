
#include <cstdio>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <glm/matrix.hpp>
#include<iostream>
#include"Libraries/include/glad/glad.h"
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;


// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES   
	-0.2f, -0.2f,  -0.2f,   
	0.2f, -0.2f, -0.2f,     
	0.2f, 0.2f, -0.2f,     
	-0.2f, 0.2f,  -0.2f,  
	-0.2f, -0.2f,  0.2f, 
	 0.2f, -0.2f, 0.2f, 
	 0.2f, 0.2f, 0.2f, 
	 -0.2f, 0.2f,  0.2f,
};

glm::vec3 color1 = glm::vec3(0.70f, 0.50f, 0.32f);
glm::vec3 color2 = glm::vec3(0.50f, 0.25f, 0.32f);
glm::vec3 color3 = glm::vec3(0.00f, 0.30f, 0.70f);
glm::vec3 color4 = glm::vec3(0.40f, 1.00f, 0.10f);
glm::vec3 color5 = glm::vec3(0.25f, 0.46f, 0.80f);
glm::vec3 colorF = glm::vec3(0.90f, 0.20f, 0.70f);

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, 
	0, 3, 2, 
	0, 1, 5,
	0, 4, 5,
	0, 3, 7,
	0, 4, 7,
	6, 7, 3,
	6, 2, 3,
	6, 5, 4,
	6, 7, 4,
	6, 2, 1,
	6, 5, 1
};



int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "3DPiramida", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the Vport of OpenGL in the Window
	// In this case the Vport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	//VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();



	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	float scale = 1.0f;
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	const glm::mat4 startMatrix = glm::mat4(1.0f);

	const glm::mat4 Tfloor = glm::translate(startMatrix, glm::vec3(0.0f, -0.2, 0.0f));
	const glm::mat4 Rfloor = camera.objRot;
	const glm::mat4 Sfloor = glm::scale(startMatrix, glm::vec3(100.0f, 0.1f, 100.0f));
	const glm::mat4 Mfloor = Tfloor * Rfloor * Sfloor;

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		camera.Inputs(window, scale);
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		VAO1.Bind();

	
		glm::mat4 Mk = startMatrix; 
		int MfloorLoc = glGetUniformLocation(shaderProgram.ID, "M");
		glUniformMatrix4fv(MfloorLoc, 1, GL_FALSE, value_ptr(Mfloor));
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "PV");
		int MkLoc = glGetUniformLocation(shaderProgram.ID, "Mk");
		glUniformMatrix4fv(MkLoc, 1, GL_FALSE, value_ptr(Mk));
		int colLoc = glGetUniformLocation(shaderProgram.ID, "col");
		glUniform3fv(colLoc, 1, glm::value_ptr(colorF));
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		glm::mat4 T = glm::translate(startMatrix, glm::vec3(camera.PirPos.x, camera.PirPos.y, camera.PirPos.z));
		glm::mat4 R = camera.objRot;
		glm::mat4 S = glm::scale(startMatrix, glm::vec3(scale, scale, scale));

		glm::mat4 M = T*R*S;
		int MLoc = glGetUniformLocation(shaderProgram.ID, "M");
		glUniformMatrix4fv(MLoc, 1, GL_FALSE, value_ptr(M));
		//glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		Mk = glm::translate(startMatrix, glm::vec3(0.0f, 0.4f, 0.0f));

		colLoc = glGetUniformLocation(shaderProgram.ID, "col");
		glUniform3fv(colLoc, 1, glm::value_ptr(color1));
		MkLoc = glGetUniformLocation(shaderProgram.ID, "Mk");
		glUniformMatrix4fv(MkLoc, 1, GL_FALSE, value_ptr(Mk));
		//VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);


		Mk = glm::translate(startMatrix, glm::vec3(0.4f, 0.0f, 0.0f));

		colLoc = glGetUniformLocation(shaderProgram.ID, "col");
		glUniform3fv(colLoc, 1, glm::value_ptr(color2));
		MkLoc = glGetUniformLocation(shaderProgram.ID, "Mk");
		glUniformMatrix4fv(MkLoc, 1, GL_FALSE, value_ptr(Mk));
		//VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);


		Mk = glm::translate(startMatrix, glm::vec3(-0.4f, 0.0f, 0.0f));


		colLoc = glGetUniformLocation(shaderProgram.ID, "col");
		glUniform3fv(colLoc, 1, glm::value_ptr(color3));
		MkLoc = glGetUniformLocation(shaderProgram.ID, "Mk");
		glUniformMatrix4fv(MkLoc, 1, GL_FALSE, value_ptr(Mk));
		//VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);


		Mk = glm::translate(startMatrix, glm::vec3(0.0f, 0.0f, 0.4f));


		colLoc = glGetUniformLocation(shaderProgram.ID, "col");
		glUniform3fv(colLoc, 1, glm::value_ptr(color4));
		MkLoc = glGetUniformLocation(shaderProgram.ID, "Mk");
		glUniformMatrix4fv(MkLoc, 1, GL_FALSE, value_ptr(Mk));
		//VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);



		Mk = glm::translate(startMatrix, glm::vec3(0.0f, 0.0f, -0.4f));

		colLoc = glGetUniformLocation(shaderProgram.ID, "col");
		glUniform3fv(colLoc, 1, glm::value_ptr(color5));
		MkLoc = glGetUniformLocation(shaderProgram.ID, "Mk");
		glUniformMatrix4fv(MkLoc, 1, GL_FALSE, value_ptr(Mk));
		//VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
		

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
