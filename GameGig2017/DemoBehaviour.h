#pragma once

#include "Behaviour.h"
#include "ResourceManager.h"

class DemoBehaviour : public Behaviour {
public:
	DemoBehaviour(ResourceManager<sf::Texture, std::string>* rm);
	void collided(Entity* other, MTV v);
	void update(int frame_time);
	void render(sf::RenderTarget* target);
	void sfmlEvent(sf::Event evt);

	sf::Sprite* getSprite();
private:
	ResourceManager<sf::Texture, std::string>* rm_;
	sf::Sprite sprite_;
};