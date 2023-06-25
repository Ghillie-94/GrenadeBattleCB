#include "Physics.h"

enum class PhysicsType
{
	FORWARD_EULER,
	SYMPLECTIC_EULER,
	VELOCITY_VERLET,
};

Physics::Physics()
	:SpriteObject()
	,hasPlayerJumped(false)
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
		//****************************
		// Practical Task: Physics alternatives
		//****************************
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
	const float GRAVITY = 500;
	const float PLAYERACCEL = 1500;
	const float JUMPSPEED = 2500;
	
	//update acceleration
	acceleration.x = 0;
	acceleration.y = GRAVITY;

	//Player movement 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		acceleration.x = -PLAYERACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		acceleration.x = PLAYERACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!hasPlayerJumped)
		{
			acceleration.y = JUMPSPEED;
			hasPlayerJumped = true;
			jumpCooldownClock.restart();
			JumpCooldown();
		}
		
	}
	
}

void Physics::UpdateGrenadeAcceleration()
{
	/*
	const float GRENADEACCEL = 5000;
	const float GRAVITY = 500;
	//update acceleration
	acceleration.x = GRENADEACCEL; //todo add aim vector
	acceleration.y = GRAVITY;
	*/
	//handled in child
}

void Physics::JumpCooldown()
{
	if (hasPlayerJumped)
	{
		jumpCooldownTimer = jumpCooldownClock.getElapsedTime();
		if (jumpCooldownTimer > sf::seconds(1.5f))
		{
			hasPlayerJumped = false;
		}
	}
}
