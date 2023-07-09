#pragma once

#include <GL/glew.h>

class Material {
public:
	Material();
	Material(GLfloat sIntensity, GLfloat shine);
	~Material();

	void Use(GLuint speculatIntensityLoc, GLuint shininessLoc);

private:
	GLfloat specularIntensity; // how much will the material absorb the light
	GLfloat shininess;		// how smooth is the material, bigger -> smoother

};
