#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "GameConstants.h"


class BoxCollider
{
public:
	BoxCollider();
	~BoxCollider();

	void setCollider();

	void scaleCollider();

	void setup(float length, float height, float depth, glm::vec3 position);

	glm::vec3 getPosition()
	{
		return m_Position;
	}

	glm::vec3 getPositionHigh()
	{
		return m_High;
	}

	glm::vec3 getPositionLow()
	{
		return m_Low;
	}

	void setInteraction(bool interaction)
	{
		m_Interaction = interaction;
	}
	

	void setTransform(glm::vec3 position)
	{
		m_Position = position;
	};
	bool checkCollision(glm::vec3 position);

	bool checkCollisionBelow(glm::vec3 position);

	void setCollected(bool wasCollected)
	{
		m_Collected = wasCollected;
	}

	bool getCollected()
	{
		return m_Collected;
	}

	

private:

	glm::vec3 m_Position;
	glm::vec3 m_Scale;

	glm::vec3 m_High;
	glm::vec3 m_Low;

	float m_Radius;
	float m_Length;
	float m_Height;
	float m_Depth;

	bool m_xCollision = false;
	bool m_yCollision = false;
	bool m_zCollision = false;

	bool scaled = false;

	bool m_Interaction = false;
	bool m_Collected = false;
};
#endif