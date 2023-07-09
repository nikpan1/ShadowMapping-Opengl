#include "PointLight.h"

PointLight::PointLight() : Light()
{
	position = glm::vec3(0.f, 0.f, 0.f);
	constant = 1.f;
	linear = 0.f;
	exponent = 0.f;

}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
	GLfloat aIntensity, GLfloat dIntensity,
	GLfloat x, GLfloat y, GLfloat z,
	GLfloat con, GLfloat lin, GLfloat exp)
	: Light(red, green, blue, aIntensity, dIntensity)
{
	position = glm::vec3(x, y, z);
	
	constant = con;
	linear = lin;
	exponent = exp;

}

PointLight::~PointLight()
{
}

void PointLight::Use(GLuint ambientIntensityLoc, GLuint ambientColorLoc, 
						GLuint diffuseIntensityLoc, GLuint positionLocation, 
						GLfloat conLoc, GLfloat linLoc, GLfloat expLoc)
{
	glUniform3f(ambientColorLoc, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLoc, ambientIntensity);

	glUniform1f(diffuseIntensityLoc, diffuseIntensity);
	
	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(conLoc, constant);
	glUniform1f(linLoc, linear);
	glUniform1f(expLoc, exponent);
}
