#include "Mesh.h"


Mesh::Mesh() {
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
}

void Mesh::Create(GLfloat* vertices, unsigned int* indices, 
					unsigned int numOfVertices, unsigned int numOfIndices) {
	unsigned int attribPointerSize = 3; // @TODO remove it 
	indexCount = numOfIndices;
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, 
		indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices,
		vertices, GL_STATIC_DRAW);


	// points
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
	glEnableVertexAttribArray(0);
	
	//textures
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 
		reinterpret_cast<const void*>(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 
		reinterpret_cast<const void*>(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);


	// unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


void Mesh::Render() {
	// bind
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	// unbind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Mesh::Clear() {
	if (!IBO) {
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}
	
	if (!VBO) {
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (!VAO) {
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}

Mesh::~Mesh() {
	Mesh::Clear();
}
