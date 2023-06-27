#include "Physics.h"

enum class PhysicsType
{
	FORWARD_EULER,
	SYMPLECTIC_EULER,
	VELOCITY_VERLET,
};

Physics::Physics(bool newDragOn)
	:SpriteObject()
	, dragOn(newDragOn)
{
	
	
	
	
}

void Physics::Update(sf::Time frameTime)
{
	
	const float DRAG_MULT = 5.0f;
	const PhysicsType physics = PhysicsType::SYMPLECTIC_EULER;

	switch (physics)
	{
	case PhysicsType::FORWARD_EULER:
	{
		// EXPLICIT EULER (FORWARD EULER)
		SetPosition(GetPosition() + velocity * frameTime.asSeconds());
		velocity = velocity + acceleration * frameTime.asSeconds();

		if (dragOn)
		{

		}


		// Update acceleration
		UpdateAcceleration();
		break;

	case PhysicsType::SYMPLECTIC_EULER:
	{
		//****************************
		// Practical Task: Physics alternatives
		//****************************
		// SEMI-IMPLICIT / SYMPLECTIC_EULER

		velocity = velocity + acceleration * frameTime.asSeconds();

		if (dragOn)
		{
			// drag
			velocity = velocity - velocity * DRAG_MULT * frameTime.asSeconds();
		}


		SetPosition(GetPosition() + velocity * frameTime.asSeconds());

		// Update acceleration
		UpdateAcceleration();
	}
	break;


	case PhysicsType::VELOCITY_VERLET:
	{

		//****************************
		// Practical Task: Physics alternatives
		//****************************
		// VELOCITY VERLET / LEAP FROG

		// Get half frame velocity using
		// previous frame's acceleration
		sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;

		// Get new frame's position using half frame velocity
		SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());

		// Update our current acceleration
		UpdateAcceleration();

		// Get new frame's velocity using half frame velocity and
		// updated acceleration
		velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;
		if (dragOn)
		{
			// drag
			velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();
		}
		
	}
	break;

	default:
		break;
	}
	}
}

void Physics::Draw(sf::RenderTarget& target)
{
	//handled in child
}

void Physics::UpdateAcceleration()
{
	//handled in child
}




