#include "stdafx.h"
#include "Collision.h"
#include "ResourceManager.h"
#include "PongBehaviour.h"



PongBehaviour::PongBehaviour(ResourceManager<sf::Texture, std::string>* rm)
{
	resourceManager = *rm;
}


PongBehaviour::~PongBehaviour()
{

}

void PongBehaviour::collided(Entity* other, MTV v)
{
	if (other->getType() == "bullet")
	{
		sfld::Vector2f velocity = other->getVelocity();
		velocity.x = -1 * velocity.x;
		other->setVelocity(velocity);
	}
	else
	{
		takeDamage(10);
	}
}

void PongBehaviour::update(int frame_time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		setVelocity(sfld::Vector2f(0.0, 0.0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		setVelocity(sfld::Vector2f(0.0, 0.0));
	}
}

void PongBehaviour::render(sf::RenderTarget* target)
{
	target->draw(*getSprite());
}

sf::Sprite* PongBehaviour::getSprite()
{
	return &sprite;
}
