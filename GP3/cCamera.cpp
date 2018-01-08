/*
==========================================================================
ccCamera.h
==========================================================================
*/

#include "cCamera.h"
#include <math.h>






cCamera::cCamera()
{
	m_viewPort = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ProjectionMatrix = glm::mat4(1.0);
	m_camViewMatrix = glm::mat4(1.0);

	m_cameraLookAt = glm::vec3(cos(m_CameraRot.y), 0, sin(m_CameraRot.y));
}


cCamera::cCamera(int screenWidth, int screenHeight)
{
	m_viewPort = glm::vec4(0, 0, screenWidth, screenHeight);
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ProjectionMatrix = glm::mat4(1.0);
	m_camViewMatrix = glm::mat4(1.0);
}

cCamera::~cCamera()
{
	
}



void cCamera::setTheViewPort(int x, int y, int width, int height)
{
	m_viewPort = glm::vec4(x, y, width, height);
	glViewport(x, y, width, height);
}

const glm::vec4 cCamera::getTheViewPort()
{
	return m_viewPort;
}

void cCamera::setTheProjectionMatrix(float fov, float aspectRatio, float nearCP, float farCP)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearCP, farCP);
}

void cCamera::setTheCameraPos(glm::vec3 pos)
{
	m_cameraPos = pos;
}

glm::vec3 cCamera::getTheCameraPos()
{
	return m_cameraPos;
}

void cCamera::setTheCameraUpVector(glm::vec3 camPosUpVec)
{
	m_cameraUpVector = camPosUpVec;
}

glm::vec3 cCamera::getTheCameraUpVector()
{
	return m_cameraUpVector;
}

void cCamera::setTheCameraLookAt(glm::vec3 camLookAt)
{
	m_cameraLookAt = camLookAt;
}

glm::vec3 cCamera::getTheCameraLookAt()
{
	return m_cameraLookAt;
}

void cCamera::setTheCameraDirection()
{
	m_cameraDirection = glm::normalize(m_cameraPos - m_cameraLookAt);
}

glm::vec3 cCamera::getTheCameraDirection()
{
	return m_cameraDirection;
}

void cCamera::setTheCameraStrafe()
{
	m_cameraStrafe = glm::normalize(glm::cross(m_cameraUpVector, m_cameraDirection));
}

glm::vec3 cCamera::getTheCameraStrafe()
{
	return m_cameraStrafe;
}

void cCamera::setTheCameraRot(glm::vec3 camRotation)
{
	m_CameraRot = camRotation;
}

glm::vec3 cCamera::getTheCameraRot()
{
	return m_CameraRot;
}

glm::vec3 cCamera::getProjectedPosition(string direction)
{
	if (direction == "forward")
	{
		//m_cameraPos += glm::vec3(0, 0, 20);
		return m_cameraPos += glm::vec3(-sin(m_CameraRot.y - glm::radians(90.0f)), 0.0f, cos(m_CameraRot.y - glm::radians(90.0f)));
	}
	else if (direction == "back")
	{
		//m_cameraPos += glm::vec3(0, 0, 20);
		return m_cameraPos -= glm::vec3(-sin(m_CameraRot.y - glm::radians(90.0f)), 0.0f, cos(m_CameraRot.y - glm::radians(90.0f)));
	}
	else if (direction == "right")
	{
		//m_cameraPos += glm::vec3(0, 0, 20);
		return m_cameraPos += glm::vec3(-sin(m_CameraRot.y), 0.0f, cos(m_CameraRot.y));
	}
	else
	{
		return m_cameraPos -= glm::vec3(-sin(m_CameraRot.y), 0.0f, cos(m_CameraRot.y));
	}
}

void cCamera::mouseRotation()
{
	
	m_CameraRot += glm::vec3(glm::radians(mouseY / 2), glm::radians(mouseX / 2), 0.0f);

	if (m_CameraRot.x < glm::radians(-80.0f))
	{
		m_CameraRot += glm::vec3( glm::radians(-mouseY / 2), 0.0f, 0.0f);
	}

	if (m_CameraRot.x > glm::radians(80.0f))
	{
		m_CameraRot += glm::vec3(glm::radians(-mouseY / 2), 0.0f, 0.0f);
	}
	
	m_cameraLookAt = glm::vec3(cos(m_CameraRot.y), -tan(m_CameraRot.x), sin(m_CameraRot.y));
	
	

	
	
}

void cCamera::jump()
{
	if (m_Grounded)
	{
		m_Grounded = false;
		m_Force = 2.0f;
		m_Jump = true;
	}
}

void cCamera::setTheCameraAspectRatio(GLfloat width, GLfloat height)
{
	m_AspectRatio = width/height;
}

GLfloat cCamera::getTheCameraAspectRatio()
{
	return m_AspectRatio;
}

glm::mat4 cCamera::getTheProjectionMatrix()
{
	return m_ProjectionMatrix;
}

glm::mat4 cCamera::getTheViewMatrix()
{
	return m_camViewMatrix;
}

glm::mat4 cCamera::getTheViewMatrix2()
{
	return m_camViewMatrix2;
}

void cCamera::setCamViewMatrix()
{
	m_camViewMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraLookAt, m_cameraUpVector);
	m_camViewMatrix2 = glm::lookAt(glm::vec3(100, 50, 100), glm::vec3(100, 0, 50), m_cameraUpVector);
}

glm::mat4 cCamera::getCamViewMatrix()
{
	return m_camViewMatrix;
}

void cCamera::update()
{
	//setTheCameraDirection();
	//setTheCameraStrafe();
	//setTheCameraUpVector(glm::cross(m_cameraDirection, m_cameraStrafe));
	//mouseRotation();

	if (m_Grounded)
	{
		m_Force = 0.0f;
		m_Jump = false;
	}

	//If we're on the ground and not currently jumping
	if (m_cameraPos.y <= 0.0f && !m_Jump)
	{
		m_Grounded = true;
		
		m_cameraPos.y = 0.0f;
	}

	//If we reached the apex of the jump
	if (m_Force < 0.1 && m_Jump) 
	{
		m_Jump = false;
	}

	/*
	//If not jumping and not grounded, apply gravity physics
	if (!m_Jump && !m_Grounded)
	{
		m_cameraPos -= (0.0f, m_Force, 0.0f);
		m_Force += 0.1f;

		//Limit fall speed
		if (m_Force < -24.0f)
		{
			m_Force -= 0.1f;
		}
	}
	*/

	//If not grounded
	if (!m_Grounded)
	{
		m_cameraPos += glm::vec3(0.0f, m_Force, 0.0f);
		m_Force -= 0.1;

		//Limit fall speed
		if (m_Force < -24.0f)
		{
			m_Force == -24.0f;
		}

		move("forward"); //While jumping move the camera forward
	}

	//Fix any rounding if grounded and not jumping
	if (m_Grounded && !m_Jump)
	{
		m_Force = 0.0f;
	}

	setTheProjectionMatrix(45.0f, getTheCameraAspectRatio(), 0.1f, 1000.0f);
	setCamViewMatrix();
}

void cCamera::move(string direction)
{
	
	if (direction == "forward")
	{
		//m_cameraPos += glm::vec3(0, 0, 20);
		m_cameraPos += glm::vec3(-sin(m_CameraRot.y - glm::radians(90.0f)), 0.0f, cos(m_CameraRot.y - glm::radians(90.0f)));
	}
	else if (direction == "back")
	{
		//m_cameraPos += glm::vec3(0, 0, 20);
		m_cameraPos -= glm::vec3(-sin(m_CameraRot.y - glm::radians(90.0f)), 0.0f, cos(m_CameraRot.y - glm::radians(90.0f)));
	}
	else if (direction == "right")
	{
		//m_cameraPos += glm::vec3(0, 0, 20);
		m_cameraPos += glm::vec3(-sin(m_CameraRot.y), 0.0f, cos(m_CameraRot.y));
	}
	else
	{
		m_cameraPos -= glm::vec3(-sin(m_CameraRot.y), 0.0f, cos(m_CameraRot.y));
	}


	//m_cameraLookAt = glm::vec3(cos(m_CameraRot.y), -tan(m_CameraRot.x), sin(m_CameraRot.y));
	
}


