#define GL_GLEXT_PROTOTYPES 1

#include "Cuboid.h"


Cuboid::Cuboid()
{
}

Cuboid::~Cuboid()
{
}

glm::vec3 Cuboid::getPosition()
{
	return m_Position;
}

void Cuboid::initialise(GLint theTextureID, glm::vec3 thePosition, float length, float height, float depth, GLfloat red, GLfloat green, GLfloat blue)
{
	m_Length = length;
	m_Height = height;
	m_Position = thePosition;

	
	
	
	GLfloat halfSideLength = length * 0.5f;
	GLfloat halfSideHeight = height * 0.5f;
	GLfloat halfSideDepth = depth *0.5f;
	GLfloat vertices[] =
	{
		//front face
		thePosition.x - halfSideLength, thePosition.y + halfSideHeight, thePosition.z + halfSideDepth, // topleft
		thePosition.x + halfSideLength, thePosition.y + halfSideHeight, thePosition.z + halfSideDepth, // topright
		thePosition.x + halfSideLength, thePosition.y - halfSideHeight, thePosition.z + halfSideDepth, // bottomright
		thePosition.x - halfSideLength, thePosition.y - halfSideHeight, thePosition.z + halfSideDepth, // bottomleft

		//back face
		thePosition.x - halfSideLength, thePosition.y + halfSideHeight, thePosition.z - halfSideDepth, // topleft
		thePosition.x + halfSideLength, thePosition.y + halfSideHeight, thePosition.z - halfSideDepth, // topright
		thePosition.x + halfSideLength, thePosition.y - halfSideHeight, thePosition.z - halfSideDepth, // bottomright
		thePosition.x - halfSideLength, thePosition.y - halfSideHeight, thePosition.z - halfSideDepth, // bottomleft

		//left face
		thePosition.x - halfSideLength, thePosition.y + halfSideHeight, thePosition.z + halfSideDepth, // topleft
		thePosition.x - halfSideLength, thePosition.y + halfSideHeight, thePosition.z - halfSideDepth, // topright
		thePosition.x - halfSideLength, thePosition.y - halfSideHeight, thePosition.z - halfSideDepth, // bottomright
		thePosition.x - halfSideLength, thePosition.y - halfSideHeight, thePosition.z + halfSideDepth, // bottomleft

		//right face
		thePosition.x + halfSideLength, thePosition.y + halfSideHeight, thePosition.z + halfSideDepth, // topleft
		thePosition.x + halfSideLength, thePosition.y + halfSideHeight, thePosition.z - halfSideDepth, // topright
		thePosition.x + halfSideLength, thePosition.y - halfSideHeight, thePosition.z - halfSideDepth, // bottomright
		thePosition.x + halfSideLength, thePosition.y - halfSideHeight, thePosition.z + halfSideDepth, // bottomleft

		//top face
		thePosition.x - halfSideLength, thePosition.y + halfSideHeight, thePosition.z + halfSideDepth, // topleft
		thePosition.x - halfSideLength, thePosition.y + halfSideHeight, thePosition.z - halfSideDepth, // topright
		thePosition.x + halfSideLength, thePosition.y + halfSideHeight, thePosition.z - halfSideDepth, // bottomright
		thePosition.x + halfSideLength, thePosition.y + halfSideHeight, thePosition.z + halfSideDepth, // bottomleft

		//bottom face
		thePosition.x - halfSideLength, thePosition.y - halfSideHeight, thePosition.z + halfSideDepth, // topleft
		thePosition.x - halfSideLength, thePosition.y - halfSideHeight, thePosition.z - halfSideDepth, // topright
		thePosition.x + halfSideLength, thePosition.y - halfSideHeight, thePosition.z - halfSideDepth, // bottomright
		thePosition.x + halfSideLength, thePosition.y - halfSideHeight, thePosition.z + halfSideDepth, // bottomleft

	};

	GLfloat cubeColour[] =
	{
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue,
		red, green, blue
	};


	/*
	if (!coloursDefined)
	{
		coloursDefined = true;
		
		for (int i = 1; i <= 68; i + 3)
		{
			int tempX = ((rand() / (RAND_MAX))/10) + green;
			if (tempX < 0)
			{
				tempX = 0;
			}
			if (tempX > 1)
			{
				tempX = 1;
			}
			cubeColour[i] = tempX;
		}
		
	}
	*/
	

	//glEnable(GL_TEXTURE_2D);


	glDisable(GL_LIGHTING);
	
	//glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//glBindTexture(GL_TEXTURE_2D, theTextureID);
	//glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, &cubeColour);
	//glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glDrawArrays(GL_QUADS, 0, 24);
	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glDisableClientState(GL_TEXTURE_2D);

	/*
	// Assign variables that will be used to store the unique object ID’s that will be used to refer to the two buffers. 
	/*
	glGenBuffers = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	

	glGenBuffers(2, &m_VertexBufferObjects[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[0]); //Bind the vertex buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW); //Send the data to OpenGL 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexBufferObjects[1]); //Bind the vertex buffer 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * sizeof(m_Indices), &m_Indices[0], GL_STATIC_DRAW); //Send the data to OpenGL 

																											  // Lab 2/3
																											  // Create and Bind VBO for Texture
																											  //Bind the Texture coordinate array, and set the Texture coordinate pointer to point at it
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_TextureIndices), &m_TextureIndices[0], GL_STATIC_DRAW); //Send the data to OpenGL

	glBindTexture(GL_TEXTURE_2D, theTextureID);

	// Lab 2/3
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[2]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	//Bind the vertex array and set the vertex pointer to point at it 
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glTranslatef(m_Position.x, m_Position.y, m_Position.z);
	//glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
	*/
	
	

	
}

void Cuboid::render()
{
	/*
	//glRotatef(rotAngle, 0.0f, 1.0f, 0.0f); 
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); // Lab 2/3

	glVertexPointer(3, GL_FLOAT, 0, 0);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY); // Lab 2/3

	glDisable(GL_TEXTURE_2D);
	*/
}

void Cuboid::loadTextureCoords()
{
	m_TextureIndices[0] = glm::vec2(0.0f, 0.0f);
	m_TextureIndices[1] = glm::vec2(1.0f, 0.0f);
	m_TextureIndices[2] = glm::vec2(1.0f, 1.0f);
	m_TextureIndices[3] = glm::vec2(0.0f, 1.0f);

	m_TextureIndices[4] = glm::vec2(1.0f, 0.0f);
	m_TextureIndices[5] = glm::vec2(0.0f, 0.0f);
	m_TextureIndices[6] = glm::vec2(0.0f, 1.0f);
	m_TextureIndices[7] = glm::vec2(0.0f, 0.0f);

	m_TextureIndices[8] = glm::vec2(0.0f, 1.0f);
	m_TextureIndices[9] = glm::vec2(0.0f, 0.33f);
	m_TextureIndices[10] = glm::vec2(1.0f, 0.0f);
	m_TextureIndices[11] = glm::vec2(1.0f, 1.0f);

	m_TextureIndices[12] = glm::vec2(1.0f, 1.0f);
	m_TextureIndices[13] = glm::vec2(0.0f, 1.0f);
	m_TextureIndices[14] = glm::vec2(0.0f, 0.0f);
	m_TextureIndices[15] = glm::vec2(1.0f, 0.0f);

	m_TextureIndices[16] = glm::vec2(1.0f, 0.0f);
	m_TextureIndices[17] = glm::vec2(1.0f, 1.0f);
	m_TextureIndices[18] = glm::vec2(0.0f, 1.0f);
	m_TextureIndices[19] = glm::vec2(0.0f, 0.0f);

	m_TextureIndices[20] = glm::vec2(0.0f, 0.0f);
	m_TextureIndices[21] = glm::vec2(1.0f, 0.0f);
	m_TextureIndices[22] = glm::vec2(1.0f, 1.0f);
	m_TextureIndices[23] = glm::vec2(0.0f, 1.0f);
}
