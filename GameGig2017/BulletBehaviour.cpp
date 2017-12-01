#include "stdafx.h"
#include "Collision.h"
#include "ResourceManager.h"
#include "BulletBehaviour.h"
#include "Entity.h"

BulletBehaviour::BulletBehaviour(ResourceManager<sf::Texture, std::string>* rm, Entity* p)
{
	player = p;
	resourceManager = rm;
	setVelocity(sfld::Vector2f(-0.5, 0.0));

	// initialise sprite 1024 x 768
	paintSprite();
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}


BulletBehaviour::~BulletBehaviour()
{
}

void BulletBehaviour::collided(Entity* other, MTV v)
{
	if ((other == player && other->getType() != "pong")
		|| other->getType() == "goomba" || other->getType() == "ghost" || other->getType() == "shooter"
		|| other->getType() == "bullet") {
		other->takeDamage(10);
		takeDamage(1000);
	}
	else if( other->getType() != "pong"){
		takeDamage(1000);
	}
}

void BulletBehaviour::update(int frame_time)
{
	sfld::Vector2f direction = getVelocity().normalise();
	sprite.setRotation(sfld::maths::toDegrees(atan2(direction.y, direction.x)));
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
