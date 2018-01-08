#ifndef CUBOID_H
#define CUBOID_H




#include "windowOGL.h"
#include "glm\glm.hpp"
#include "glx\glext.h"
#include "wglext.h"
#include <vector>
#include "cColours.h"
#include "cTexture.h"
#include "GL\glut.h"
#include <GL/GL.h>
#include <stdlib.h>




class Cuboid : public windowOGL
{

public:
	Cuboid();
	~Cuboid();

	glm::vec3 getPosition();
	void initialise(GLint theTextureID, glm::vec3 thePosition, float length, float height, float depth, GLfloat red, GLfloat green, GLfloat blue);
	void render();
	void loadTextureCoords();

private:
	float m_Length;
	float m_Height;
	glm::vec3 m_Position;

	glm::vec3 m_topLeftFront;
	glm::vec3 m_bottomLeftFront;
	glm::vec3 m_topRightFront;
	glm::vec3 m_bottomRightFront;
	glm::vec3 m_topLeftBack;
	glm::vec3 m_topRightBack;
	glm::vec3 m_bottomLeftBack;
	glm::vec3 m_bottomRightBack;

	glm::vec3 m_Faces[24];
	GLuint m_Indices[36];

	bool coloursDefined = false;

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_colourList;
	GLuint m_VertexBufferObjects[3];
	glm::vec2 m_TextureIndices[24];
	GLuint m_TextureID;

};

#endif