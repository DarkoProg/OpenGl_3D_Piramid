#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include"Libraries/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float4.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

struct objPos
{
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};


class Camera
{
	public:


		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 objRot = glm::mat4(1.0f);

		int width;
		int height;
		int ProjectionType = 1;
		
		objPos PirPos;
		float rotSpeed = 0.8f;
		float Xrotation = 0.8f;
		float Yrotation = 0.8f;
		float speed = 0.3f;
		float sensetivity = 100.0f;
		
		Camera(int width, int height, glm::vec3 position);
		void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader &shader, const char* uniform);
		void Inputs(GLFWwindow *window, float &scale);
};
#endif
