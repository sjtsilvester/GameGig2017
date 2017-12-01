Skip to content
Features
Business
Explore
Marketplace
Pricing
This repository
Search
Sign in or Sign up
Watch 2  Star 0  Fork 0 sjtsilvester / GameGig2017
Code  Issues 0  Pull requests 0  Projects 0  Insights
Branch : master Find file Copy pathGameGig2017 / GameGig2017 / PongBehaviour.cpp
	c520404  5 minutes ago
	@ttb29 ttb29 Added paintSprite() method in PongBehaviour
	2 contributors @ttb29 @sjtsilvester
	RawBlameHistory
	67 lines(53 sloc)  1.08 KB
#include "stdafx.h"
#include "Collision.h"
#include "ResourceManager.h"
#include "PongBehaviour.h"
#include "Entity.h"



	PongBehaviour::PongBehaviour(ResourceManager<sf::Texture, std::string>* rm)
{
	resourceManager = rm;
	speed = 0.2;
	setVelocity(sfld::Vector2f(0, speed));

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
	else
	{
		takeDamage(10);
	}
}

void PongBehaviour::update(int frame_time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		setVelocity(sfld::Vector2f(0, speed));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		setVelocity(sfld::Vector2f(0.0, -speed));
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