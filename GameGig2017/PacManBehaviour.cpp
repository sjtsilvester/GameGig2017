#include "stdafx.h"
#include "Collision.h"
#include "ResourceManager.h"



Behaviour(ResourceManager<sf::Texture, std::string>* rm); //You will want to save rm to a private variable. To get a texture: rm->get("texture name"); We will load textures later.
      asdf
void collided(Entity* other, MTV v);


void update(int frame_time);

void render(sf::RenderTarget* target); //Usage: target->draw(sprite)

sf::Sprite* getSprite();

void setVelocity(sfld::Vector2f velocity);

sfld::Vector2f getVelocity();