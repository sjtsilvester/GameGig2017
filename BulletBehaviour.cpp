#include "stdafx.h"
#include "Collision.h"
#include "ResourceManager.h"
#include "BulletBehaviour.h"
#include "Entity.h"

BulletBehaviour::BulletBehaviour(ResourceManager<sf::Texture, std::string>* rm)
{
	resourceManager = rm;
	setVelocity(sfld::Vector2f(-0.5, 0.0));

	// initialise sprite 1024 x 768
	paintSprite();
	sprite.setOrigin(512, 384);
}


BulletBehaviour::~BulletBehaviour()
{
}

void BulletBehaviour::collided(Entity* other, MTV v)
{
	if (other->getType() == "pong")
	{
		setVelocity(sfld::Vector2f(0.5, 0.0));
	}
	else
	{
		other->takeDamage(10);
		//takeDamage(4000000000);
	}
}

void BulletBehaviour::update(int frame_time)
{
}

void BulletBehaviour::render(sf::RenderTarget* target)
{
	target->draw(*getSprite());
}

sf::Sprite* BulletBehaviour::getSprite()
{
	return &sprite;
}

void BulletBehaviour::paintSprite()
{
	sprite.setTexture(resourceManager->get("bullet"));
}

void BulletBehaviour::sfmlEvent(sf::Event e)
{
}

void BulletBehaviour::setVelocity(sfld::Vector2f velo)
{
	velocity_ = velo;
}
