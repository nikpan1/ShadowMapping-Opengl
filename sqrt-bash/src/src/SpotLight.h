#pragma once

#include "PointLight.h"

class SpotLight : public PointLight {

public:
	SpotLight();
	~SpotLight();



	SpotLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat xDir, GLfloat yDir, GLfloat zDir,
		GLfloat con, GLfloat lin, GLfloat exp,
		GLfloat edg);

	void Use(GLuint ambientIntensityLoc, GLuint ambientColorLoc,
		GLuint diffuseIntensityLoc, GLuint positionLoc, GLuint directionLox,
		GLfloat conLoc, GLfloat linLoc, GLfloat expLoc, GLfloat edgeLoc);


private:
	glm::vec3 direction;
	GLfloat edge;
	GLfloat procEdge;	// procedge = cos(ToRadians(edge)s


};