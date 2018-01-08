#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
	
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::setCollider()
{
	m_High = glm::vec3((m_Position.x + m_Length/2), (m_Position.y + m_Height/2), (m_Position.z + m_Depth/2));
	//m_Low = m_Position - glm::vec3(-m_Radius, -m_Radius, -m_Radius);
	m_Low = glm::vec3((m_Position.x - m_Length/2), (m_Position.y - m_Height/2), (m_Position.z - m_Depth/2));
}

void BoxCollider::scaleCollider()
{
	m_High.x *= m_Scale.x;
	m_Low.x *= m_Scale.x;
	m_High.y *= m_Scale.y;
	m_Low.y *= m_Scale.y;
	m_High.z *= m_Scale.z;
	m_Low.z *= m_Scale.z;

	//cout << m_Position.x + m_High.x << " " << m_Position.x + m_Low.x << " " << m_Position.y + m_High.y << " " << m_Position.y + m_Low.y << " " << m_Position.z + m_High.z << " " << m_Position.z + m_Low.z << "\n";
}

void BoxCollider::setup(float length, float height, float depth, glm::vec3 position)
{
	m_Position = position;
	m_Length = length;
	m_Height = height;
	m_Depth = depth;
	setCollider();
}

bool BoxCollider::checkCollision(glm::vec3 position)
{
	//If this was a collectable object that was already collected, don't do collision checking
	if (m_Collected)
	{
		return false;
	}
	//setCollider();
	/*
	if (!scaled)
	{
		scaleCollider();
		scaled = true;
	}
	*/

	m_xCollision = false;
	m_yCollision = false;
	m_zCollision = false;

	/*
	if (position.x < m_Position.x + m_High.x && position.x >  m_Position.x + m_Low.x)
	{
		m_xCollision = true;
	}

	if (position.y <  m_Position.y + m_High.y && position.y >  m_Position.y + m_Low.y)
	{
		m_yCollision = true;
	}

	if (position.z <  m_Position.z + m_High.z && position.z >  m_Position.z + m_Low.z)
	{
		m_zCollision = true;
	}
	*/

	if (position.x < m_High.x && position.x >  m_Low.x)
	{
		m_xCollision = true;
	}

	if (position.y <  m_High.y && position.y >  m_Low.y)
	{
		m_yCollision = true;
	}

	if (position.z < m_High.z && position.z > m_Low.z)
	{
		m_zCollision = true;
	}

	if (m_xCollision == true && m_yCollision == true && m_zCollision == true)
	{
		return true;
	}

	return false;
}

bool BoxCollider::checkCollisionBelow(glm::vec3 position)
{
	//If there is a collision
	if (checkCollision(position))
	{
		//Check if our current position is very close to the top of the object we're colliding with
		if ((position.y - m_High.y) >= 0.1 && (position.y - m_High.y) >= -0.1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/*
	m_xCollision = false;
	m_yCollision = false;
	m_zCollision = false;

	/*
	if (position.x < m_Position.x + m_High.x && position.x >  m_Position.x + m_Low.x)
	{
	m_xCollision = true;
	}

	if (position.y <  m_Position.y + m_High.y && position.y >  m_Position.y + m_Low.y)
	{
	m_yCollision = true;
	}

	if (position.z <  m_Position.z + m_High.z && position.z >  m_Position.z + m_Low.z)
	{
	m_zCollision = true;
	}
	*/

	/*
	if (position.x < m_High.x && position.x >  m_Low.x)
	{
		m_xCollision = true;
	}

	if (position.y <  m_High.y && position.y >  m_Low.y)
	{
		m_yCollision = true;
	}

	if (position.z < m_High.z && position.z > m_Low.z)
	{
		m_zCollision = true;
	}

	if (m_xCollision == true && m_yCollision == true && m_zCollision == true)
	{
		return true;
	}

	return false;
	*/
}

