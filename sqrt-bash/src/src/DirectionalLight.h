#pragma once

#include "Lighting.h"


class DirectionalLight : public Light {

public:
	DirectionalLight();
	~DirectionalLight();

	DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight,
					GLfloat red, GLfloat green, GLfloat blue, 
						GLfloat aIntensity,  GLfloat dIntensity,
						GLfloat x, GLfloat y, GLfloat z);
	
	glm::mat4 CalculateLightTransform();
	
	void Use(GLuint ambientIntensityLoc, GLfloat ambienColorLoc, 
				GLfloat diffuseIntensityLoc, GLfloat directionLocation);

private:
	glm::vec3 direction;

};
