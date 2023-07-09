#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera 
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, 
			GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	~Camera();
	
	void keyControl(bool* keys, GLfloat deltaTime);	// @TODO change it to more advanced event system
	void mouseControl(GLfloat xChange, GLfloat yChange);
	glm::mat4 calculateViewMatrix();
	glm::vec3 getCameraPosition();

private:
	glm::vec3 position;
	glm::vec3 front, up, right, worldUp;
	GLfloat yaw, pitch;

	GLfloat movementSpeed, turnSpeed;

	void update();
};