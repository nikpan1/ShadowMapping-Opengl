#pragma once

#include "Lighting.h"

class PointLight : public Light {

public:

	PointLight();
	~PointLight();

	PointLight(GLfloat red, GLfloat green, GLfloat blue,
				GLfloat aIntensity, GLfloat dIntensity,
				GLfloat x, GLfloat y, GLfloat z,
				GLfloat con, GLfloat lin, GLfloat exp);
	
	void Use(GLuint ambientIntensityLoc, GLuint ambientColorLoc,
				GLuint diffuseIntensityLoc, GLuint positionLoc,
				GLfloat conLoc, GLfloat linLoc, GLfloat exp);


protected:
	glm::vec3 position;
	GLfloat constant, linear, exponent; 

};
