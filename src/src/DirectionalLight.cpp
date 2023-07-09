#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
									GLfloat aIntensity, GLfloat dIntensity,
									GLfloat x, GLfloat y, GLfloat z)
					: Light(red, green, blue, aIntensity, dIntensity)
{
	direction = glm::vec3(x, y, z);
}

void DirectionalLight::Use(GLuint ambientIntensityLoc, GLfloat ambientColorLoc, 
							GLfloat diffuseIntensityLoc, GLfloat directionLocation)
{
	glUniform3f(ambientColorLoc, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLoc, ambientIntensity);

	glUniform1f(diffuseIntensityLoc, diffuseIntensity);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
}

DirectionalLight::~DirectionalLight()
{
}
