#include "AutomatedBehaviours.hpp"

AutomatedBehaviours::AutomatedBehaviours(GameObject* parent)
	: Component(parent)
{
	// Ensure Object has transform
	if (m_parent->GetComponent<Transform>() == nullptr)
		m_parent->AddComponent<Transform>();
	
	m_transform = parent->GetComponent<Transform>();

	// Ensure Object has a Ray Caster
	if (m_parent->GetComponent<RayCaster>() == nullptr)
		m_parent->AddComponent<RayCaster>();
	
	m_rayCaster = parent->GetComponent<RayCaster>();
}

void AutomatedBehaviours::accelerate()
{
	if (TopSpeed > 0 && Acceleration < TopSpeed)
		Acceleration += AccelerationRate;

	if (TopSpeed < 0 && Acceleration > TopSpeed)
		Acceleration -= AccelerationRate;

	m_transform->translatePostMultiply(glm::normalize(Heading) * Acceleration);
}

void AutomatedBehaviours::decelerate()
{
	if (Acceleration > 0)
		Acceleration -= AccelerationRate * 3;

	if (Acceleration < 0)
		Acceleration += AccelerationRate * 3;

	m_transform->translatePostMultiply(glm::normalize(Heading) * Acceleration);
}

void AutomatedBehaviours::seek(glm::vec3 targetPosition)
{
	glm::vec3 targetHeading = (targetPosition - m_transform->getPosition());

	if(frontFeelerHit != -1)
	{
		decelerate();
		Angle += RotationSpeed;
		m_transform->rotate(-RotationSpeed, glm::vec3(0, 1, 0));			// turn right
	}
	else if(feelerRightHit != -1)
	{
		Angle -= RotationSpeed;
		m_transform->rotate(RotationSpeed, glm::vec3(0, 1, 0));			// turn left
	}
	else if(feelerLeftHit != -1)
	{
		Angle += RotationSpeed;
		m_transform->rotate(-RotationSpeed, glm::vec3(0, 1, 0));			// turn right
	}
	else
	{
		if (angle_XZ(Heading) < angle_XZ(targetHeading))  
		{
			if(angle_XZ(targetHeading) - angle_XZ(Heading) > RotationSpeed)		// greater than rotation speed as a buffer to stop unecesary rotation
			{
				if(angle_XZ(Heading) - angle_XZ(targetHeading) > (glm::pi<float>()))		// if difference is greater than pi, it's quicker to turn the other way
				{
					Angle -= RotationSpeed;
					m_transform->rotate(RotationSpeed, glm::vec3(0, 1, 0));			// turn left
				}
				else
				{
					Angle += RotationSpeed;
					m_transform->rotate(-RotationSpeed, glm::vec3(0, 1, 0));			// turn right
				}
			}
		}
		else
		{
			if(angle_XZ(Heading) - angle_XZ(targetHeading) > RotationSpeed)		// greater than rotation speed as a buffer to stop unecesary rotation
			{
				if (angle_XZ(Heading) - angle_XZ(targetHeading) > (glm::pi<float>()))	// if difference is greater than pi, it's quicker to turn the other way
				{
					Angle += RotationSpeed;
					m_transform->rotate(-RotationSpeed, glm::vec3(0, 1, 0));			// turn right
				}
				else
				{
					Angle -= RotationSpeed;
					m_transform->rotate(RotationSpeed, glm::vec3(0, 1, 0));			// turn left
				}
			}
		}
	}

	updateHeading();
	updateFeelers();
}

void AutomatedBehaviours::wander()
{
	float ringDistance = 10;
	float ringRadius = 5;

	glm::vec3 ringLocation = m_transform->getPosition() + glm::normalize(Heading) * ringDistance;

	//rotate
	//theta = Point2D::randomNumber(0, 6.28);  //6.28 = 2pi
	//std::cout << glm::linearRand(m_wanderAngle - 1, m_wanderAngle + 1) << "\n";
	m_wanderAngle = glm::linearRand(m_wanderAngle - 1, m_wanderAngle + 1);  //defines the jitter
	if (m_wanderAngle > glm::pi<float>())
		--m_wanderAngle;
	if (m_wanderAngle < -glm::pi<float>())
		++m_wanderAngle;

	glm::vec3 seekTarget = ringLocation + glm::normalize(Heading) * ringRadius;


	//test
	glm::vec3 temp1 = seekTarget - ringLocation;
	auto temp2 = glm::vec3(0);
	temp2.x = temp1.x * cos(m_wanderAngle) - temp1.z * sin(m_wanderAngle);
	temp2.z = temp1.x * sin(m_wanderAngle) + temp1.z * cos(m_wanderAngle);

	seekTarget = temp2 + ringLocation;

	seek(seekTarget);
}

void AutomatedBehaviours::updateFeelers()
{
	frontFeelerHit = -1;
	feelerLeftHit = -1;
	feelerRightHit = -1;

	glm::vec3 temp1 = Heading;
	temp1.y = 0;
	auto temp2 = glm::vec3(0);

	temp2.x = temp1.x * cos(0.39) - temp1.z * sin(0.39);        // 0.39 rad = 22.5 deg
	temp2.z = temp1.x * sin(0.39) + temp1.z * cos(0.39);

	feelerRight = temp2;

	temp2.x = temp1.x * cos(-0.39) - temp1.z * sin(-0.39);        // 0.39 rad = 22.5 deg
	temp2.z = temp1.x * sin(-0.39) + temp1.z * cos(-0.39);

	feelerLeft = temp2;

	glm::vec3 test = m_transform->getPosition();
	test.y++;

	frontFeelerHit = m_rayCaster->CastRay(test, glm::normalize(Heading), 10);
	feelerLeftHit = m_rayCaster->CastRay(test, glm::normalize(feelerLeft), 5);
	feelerRightHit = m_rayCaster->CastRay(test, glm::normalize(feelerRight), 5);
}

void AutomatedBehaviours::updateHeading()
{
	if (Angle > glm::pi<float>())
		Angle = -glm::pi<float>();
	if (Angle < -glm::pi<float>())
		Angle = glm::pi<float>();

	Heading = glm::vec3(cos(Angle), 0, sin(Angle));
}


// UTILITY FUNCTION SHOULD GO IN SEPERATE CLASS //

float AutomatedBehaviours::angle_XZ(const glm::vec3 vector)
{
		return(atan2f(vector.z, vector.x));
}