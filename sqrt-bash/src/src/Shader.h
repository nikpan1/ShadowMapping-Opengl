#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "directionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "config.h"

class Shader
{
public:
	Shader();
	~Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFile(const char* vertexLocation, const char* fragmentLocation);
	std::string ReadFile(const char* FileLocation);


	void Use();
	void Clear();
	

	void SetDirectionalLights(DirectionalLight* dLight);
	void SetPointLights(PointLight* pLight, unsigned int lightCount);
	void SetSpotLights(SpotLight* sLight, unsigned int lightCount);
	
	void SetTexture(GLuint textureUnit);
	void SetDirectionalShadowMap(GLuint textureUnit);
	void SetDirectionalLightTransform(glm::mat4* ltransform);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColorLocation();

	GLuint GetDiffusionIntensityLocation();
	GLuint GetDirectionLocation();

	GLuint GetSpecularDensityLocation();
	GLuint GetShininessLocation();
	
	GLuint GetEyePosition();

private:
	int pointLightCount;
	int spotLightCount;
	GLuint uniformPointLightCount;
	GLuint uniformSpotLightCount;

	GLuint shaderID, uniformProjection, uniformModel, uniformView,
		uniformEyePosition, uniformSpecularIntensity, uniformShininess;

	GLuint uniformTexture, uniformDirectionalLightTransform, uniformDirectionalShadowMap;

	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		
		GLuint uniformDirection;
	} uniformDirectionalLight;
	

	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		
		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	} uniformPointLight[MAX_POINTS_LIGHTS];


	struct {
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;

		GLuint uniformDirection;
		GLuint uniformEdge;
	} uniformSpotLight[MAX_SPOT_LIGHTS];

	void Compile(const char* vertexCode, const char* fragmentCode);
	void Add(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};
