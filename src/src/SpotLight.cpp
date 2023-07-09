#include "SpotLight.h"

SpotLight::SpotLight() : PointLight()
{
	direction = glm::vec3(0.f, -1.f, 0.f);
	edge = 0.f;
	procEdge = cosf(glm::radians(edge));
}

SpotLight::~SpotLight()
{
}

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue, 
	GLfloat aIntensity, GLfloat dIntensity, 
	GLfloat xPos, GLfloat yPos, GLfloat zPos, 
	GLfloat xDir, GLfloat yDir, GLfloat zDir, 
	GLfloat con, GLfloat lin, GLfloat exp, GLfloat edg)
	: PointLight(red, green, blue, aIntensity, dIntensity, xPos, yPos, xPos, con, lin, exp) {

	direction = glm::vec3(xDir, yDir, zDir);
	direction = glm::normalize(direction);
	edge = edg;
	procEdge = cosf(glm::radians(edg));

}

// @TODO Can I use DirectionalLight::Use?
void SpotLight::Use(GLuint ambientIntensityLoc, GLuint ambientColorLoc, GLuint diffuseIntensityLoc, 
	GLuint positionLoc, GLuint directionLoc, GLfloat conLoc, GLfloat linLoc, GLfloat expLoc, GLfloat edgeLoc)
{

	glUniform3f(ambientColorLoc, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLoc, ambientIntensity);

	glUniform1f(diffuseIntensityLoc, diffuseIntensity);

	glUniform3f(positionLoc, position.x, position.y, position.z);
	glUniform1f(conLoc, constant);
	glUniform1f(linLoc, linear);
	glUniform1f(expLoc, exponent);

	glUniform3f(directionLoc, direction.x, direction.y, direction.z);
	glUniform1f(edgeLoc, procEdge);

}
