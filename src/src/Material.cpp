#include "Material.h"

Material::Material() {
	shininess = 0;
	specularIntensity = 0;
}

Material::Material(GLfloat sIntensity, GLfloat shine) {
	shininess = shine;
	specularIntensity = sIntensity;
}

Material::~Material() {

}

void Material::Use(GLuint specularIntensityLoc, GLuint shininessLoc) {
	glUniform1f(specularIntensityLoc, specularIntensity);
	glUniform1f(shininessLoc, shininess);
}

