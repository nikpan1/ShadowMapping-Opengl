#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	lightProj = glm::ortho(-5.f, 5.f, -5.f, -5.f, 0.1f, 20.f);
}

DirectionalLight::DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight, 
									GLfloat red, GLfloat green, GLfloat blue,
									GLfloat aIntensity, GLfloat dIntensity,
									GLfloat x, GLfloat y, GLfloat z)
					: Light(shadowWidth, shadowHeight, red, green, blue, aIntensity, dIntensity)
{
	direction = glm::vec3(x, y, z);
	lightProj = glm::ortho(-20.f, 20.f, -20.f, 20.f, 0.1f, 20.f);
}

void DirectionalLight::Use(GLuint ambientIntensityLoc, GLfloat ambientColorLoc, 
							GLfloat diffuseIntensityLoc, GLfloat directionLocation)
{
	glUniform3f(ambientColorLoc, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLoc, ambientIntensity);

	glUniform1f(diffuseIntensityLoc, diffuseIntensity);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
}

glm::mat4 DirectionalLight::CalculateLightTransform()
{
	return lightProj * glm::lookAt(-direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

DirectionalLight::~DirectionalLight()
{
}
