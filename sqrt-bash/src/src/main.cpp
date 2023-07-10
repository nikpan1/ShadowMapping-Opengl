#define STB_IMAGE_IMPLEMENTATION

#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\mat4x4.hpp>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "glWindow.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"
#include "Model.h"

#include "config.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"

const GLint WIDTH = 1280, HEIGHT = 1024;
const float toRadians = 3.14159265f / 180.f;

Window* mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Shader directionalShadowShader;

Camera* camera;

Texture* brickTexture;
Texture* plainTexture;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINTS_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];
Material shinyMaterial;
Model xwing;

GLfloat deltaTime = 0.f;
GLfloat lastTime = 0.f;

unsigned int pointLightCount = 0, spotLightCount = 0;

static const char* vertexShader = "shaders/shader.vert";
static const char* fragmenShader = "shaders/shader.frag";

GLuint uniformProjection{ 0 }, uniformModel{ 0 }, uniformView{ 0 },
uniformEyePosition{ 0 }, uniformSpecularIntensity{ 0 }, uniformShininess{ 0 };

// temporary here
void calcAvgNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount, 
						unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);
		
		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObject() {
	GLfloat vertices[] = {
	//		position			 texture		  light
	//  x		y		z		  u    v		nx	 ny	   nz
		-1.0f, -1.0f, -0.6f,		 0.f, 0.f,		0.f, 0.f, 0.f,
		0.0f, -1.0f, 1.0f,	     0.5f, 0.f, 	0.f, 0.f, 0.f,
		1.0f, -1.0f, -0.6f,		 1.f, 0.f, 		0.f, 0.f, 0.f,
		0.0f, 1.0f, 0.0f,		 0.5f, 1.f,		0.f, 0.f, 0.f
	};

	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};
	
	calcAvgNormals(indices, 12, vertices, 32, 8, 5);


	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};


	Mesh* obj1 = new Mesh();
	obj1->Create(vertices, indices, 32, 12);
	meshList.push_back(obj1);
	
	Mesh* obj2 = new Mesh();
	obj2->Create(floorVertices, floorIndices, 32, 12);
	meshList.push_back(obj2);

	xwing.LoadModel("Models/x-wing.obj");
}

void CreateShaders() {
	Shader* shader1 = new Shader();
	shader1->CreateFromFile(vertexShader, fragmenShader);
	shaderList.push_back(shader1);

	directionalShadowShader = Shader();
	directionalShadowShader.CreateFromFile("shaders/directional_shadow_map.vert", "shaders/directional_shadow_map.frag");
}

void RenderScene() {
	// it's important to initialize an indetity matrix with constructor
	glm::mat4 model = glm::mat4(1.0f);
	// the order is important	p v m
	model = glm::translate(model, glm::vec3(0.f, -2.f, -2.f));
	model = glm::rotate(model, 100.f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.f, 1.f, 1.f));


	brickTexture->Use();
	shinyMaterial.Use(uniformSpecularIntensity, uniformShininess);

	meshList[0]->Render();
	meshList[1]->Render();

}

void DirectionalShadowMapPass(DirectionalLight* light) {
	directionalShadowShader.Use();
	glViewport(0, 0, light->GetShadowMap()->GetShadowWidth(), 
		light->GetShadowMap()->GetShadowHeight());

	light->GetShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	uniformModel = directionalShadowShader.GetModelLocation();
	auto lightTransform = mainLight.CalculateLightTransform();
	directionalShadowShader.SetDirectionalLightTransform(&lightTransform);

	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void RenderPass(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
	shaderList[0]->Use();

	uniformProjection = shaderList[0]->GetProjectionLocation();
	uniformModel = shaderList[0]->GetModelLocation();
	uniformView = shaderList[0]->GetViewLocation();

	uniformEyePosition = shaderList[0]->GetEyePosition();
	uniformSpecularIntensity = shaderList[0]->GetSpecularDensityLocation();
	uniformShininess = shaderList[0]->GetShininessLocation();

	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniform3f(uniformEyePosition, camera->getCameraPosition().x,
		camera->getCameraPosition().y, camera->getCameraPosition().z);

	shaderList[0]->SetDirectionalLight(&mainLight);
	auto lightTransform = mainLight.CalculateLightTransform();
	directionalShadowShader.SetDirectionalLightTransform(&lightTransform);

	shaderList[0]->SetPointLights(pointLights, pointLightCount);
	shaderList[0]->SetSpotLights(spotLights, spotLightCount);

	mainLight.GetShadowMap()->Read(GL_TEXTURE1);
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

int main() {
	mainWindow = new Window(WIDTH, HEIGHT);
	mainWindow->Init();

	CreateObject();
	CreateShaders();
	
	camera = new Camera(glm::vec3(0.f, 0.f, 1.f), 
						glm::vec3(0.f, 1.f, 0.f), 
						-90.f, 0.f, 2.f, 0.1f);
	
	std::string path = "Textures/plain.png";
	brickTexture = new Texture(path.c_str());
	brickTexture->Load();	

	std::string path2 = "Textures/plain.png";
	plainTexture = new Texture(path2.c_str());
	plainTexture->Load();
	
	shinyMaterial = Material(1.f, 32);
	
	//xwing = Model();
	//xwing.LoadModel("models/uh60.obj");

	mainLight = DirectionalLight(WIDTH, HEIGHT,
								1.f, 1.f, 1.f,
								0.3f, 0.6f,
								2.f, 0.f, -2.f);
	
	pointLights[0] = PointLight(0.f, 0.f, 1.f,
								0.1f, 0.3f,
								-4.f, 0., 0.f,
								0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[1] = PointLight(0.f, 1.f, 0.f,
								0.1f, 1.f,
								-4.f, 2.f, 0.f,
								0.3f, 0.1f, 0.1f);
	pointLightCount++;


	

	spotLights[0] = SpotLight(1.f, 0.f, 0.f,
								0.f, 1.f,
								0.f, 1.f, 0.f,
								0.f, -2.f, 0.f,
								1.f, 0.f, 0.9f,
								40.f);
	spotLightCount++;

	float FOV = 45.f;
	float aspect_ratio = mainWindow->getBufferWidth() / mainWindow->getBufferHeight();
	float  zNear = 0.1f, zFar = 100.f;
	glm::mat4 projection = glm::perspective(FOV, aspect_ratio, zNear, zFar);

	while (!mainWindow->shouldClose()) {
		GLfloat now = glfwGetTime(); // in seconds
		deltaTime = now - lastTime;
		lastTime = now;

		// user input
		glfwPollEvents();
		camera->keyControl(mainWindow->getsKeys(), deltaTime);
		camera->mouseControl(mainWindow->getXChange(), mainWindow->getYChange());
		
		DirectionalShadowMapPass(&mainLight);
		RenderPass(camera->calculateViewMatrix(), projection);
		RenderScene();
		mainWindow->swapBuffers();
	}
	

	// change to smart pointers
	meshList[0]->Clear();
	return 0;
}