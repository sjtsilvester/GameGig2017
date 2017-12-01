#include "stdafx.h"
#include "Collision.h"
#include "ResourceManager.h"
#include "PongBehaviour.h"
#include "Entity.h"

PongBehaviour::PongBehaviour(ResourceManager<sf::Texture, std::string>* rm)
{
	resourceManager = rm;
	setVelocity(sfld::Vector2f(0, 0.3));

	// initialise sprite
	paintSprite();
	sprite.setOrigin(16, 16);
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
	else if (other->getType() == "ghost") {
		takeDamage(10);
	}
	else if (other->getType() == "vulnerable ghost") {
		other->takeDamage(1000);
	}
	else if (other->getType() == "goomba") {
		takeDamage(10);
	}
	else if (other->getType() == "static") {
		takeDamage(10);
		other->takeDamage(1000);
	}
}

void PongBehaviour::update(int frame_time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		setVelocity(sfld::Vector2f(0, -0.3));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		setVelocity(sfld::Vector2f(0.0, 0.3));
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

void PongBehaviour::paintSprite()
{
	sprite.setTexture(resourceManager->get("pong"));
}

void PongBehaviour::sfmlEvent(sf::Event e)
{
}