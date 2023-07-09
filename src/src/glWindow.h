#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

class Window {
public:
	Window();
	Window(int windowWidth, int windowHeight);
	~Window();
	
	int Init();
	GLint getBufferWidth();
	GLint getBufferHeight();
	
	bool shouldClose();
	
	bool* getsKeys() { return keys; };	// temporary @TODO change the Keys getter
	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers();
private:
	GLFWwindow* mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;
	
	bool keys[1024];

	GLfloat lastX, lastY;
	GLfloat xChange, yChange;
	bool mouseFirstMoved;

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};
