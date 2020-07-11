#include "Ship.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "InputComponent.h"
#include "Math.h"
#include "Laser.h"

Ship::Ship() : Actor(), laserCooldown(0.0f)
{
	SpriteComponent* sc = new SpriteComponent(*this, ResourceManager::getTexture("Ship"));
	InputComponent* ic = new InputComponent(*this);
	ic->setMaxForwardSpeed(300.0f);
	ic->setMaxAngularSpeed(Maths::twoPi);
}

void Ship::actorInput(const Uint8* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && laserCooldown <= 0.0f)
	{
		Laser* laser = new Laser();
		laser->setPosition(getPosition());
		laser->setRotation(getRotation());
		laserCooldown = 0.2f;
	}
}

void Ship::updateActor(float dt)
{
	laserCooldown -= dt;
}

