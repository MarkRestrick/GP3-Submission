#ifndef _GAMECONSTANTS_H
#define _GAMECONSTANTS_H

#define GLM_FORCE_RADIANS
//Define the string to appear in the top left corner of the window
#define WINDOW_TITLE "OpenGl Earth & Moon"

struct lightColour4
{
	lightColour4(float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _a = 0.0f) : r(_r), g(_g), b(_b), a(_a) {}

	float r;	// Red
	float g;	// Green
	float b;	// Blue
	float a;	// Alpha
};


// Windows & OpenGL 
#include <stdlib.h>
#include <Windows.h>
#include "GL\glut.h"
#include <iostream>
#include <string>
#include <ctime>

// Image Texture loading library
#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"

// Font
#include "FTGL\ftgl.h"

// Maths functions
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\geometric.hpp"
#include "glm\gtc\quaternion.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtx\quaternion.hpp"

// STL Container & Algorithms
#include <vector>
#include <map>
#include <algorithm>

// Textures
#include "cTexture.h"

extern int drawMode;
extern float rotationAngle;

//camera controls
extern bool camFor;
extern bool camBack;
extern bool camLeft;
extern bool camRight;

extern bool mouseMove;
extern float mouseX;
extern float mouseY;

extern float angle;

extern int mouseXI;
extern int mouseYI;

extern int oldMouseXI;
extern int oldMouseYI;

extern bool camJump;

extern bool camCollisionBelow;

extern bool soundToggle;

extern bool soundToggledThisFrame;

extern bool camToggle;




#endif