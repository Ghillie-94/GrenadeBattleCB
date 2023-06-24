#include "Physics.h"

enum class PhysicsType
{
	FORWARD_EULER,
	SYMPLECTIC_EULER,
	VELOCITY_VERLET,
};

Physics::Physics()
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

		// drag
		velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();
		velocity.y = velocity.y - velocity.y * DRAG_MULT * frameTime.asSeconds();

		// Update acceleration
		UpdatePlayerAcceleration();
		UpdateGrenadeAcceleration();
	}
	break;

	case PhysicsType::SYMPLECTIC_EULER:
	{
		// SEMI-IMPLICIT / SYMPLECTIC_EULER

		velocity = velocity + acceleration * frameTime.asSeconds();

		// drag
		velocity = velocity - velocity * DRAG_MULT * frameTime.asSeconds();

		SetPosition(GetPosition() + velocity * frameTime.asSeconds());

		// Update acceleration
		UpdatePlayerAcceleration();
		UpdateGrenadeAcceleration();
	}
	break;


	case PhysicsType::VELOCITY_VERLET:
	{
		// VELOCITY VERLET / LEAP FROG

		// Get half frame velocity using
		// previous frame's acceleration
		sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;

		// Get new frame's position using half frame velocity
		SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());

		// Update our current acceleration
		UpdatePlayerAcceleration();
		UpdateGrenadeAcceleration();

		// Get new frame's velocity using half frame velocity and
		// updated acceleration
		velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

		// drag
		velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();
	}
	break;

	default:
		break;
	}

}

void Physics::UpdatePlayerAcceleration()
{
}

void Physics::UpdateGrenadeAcceleration()
{
}
