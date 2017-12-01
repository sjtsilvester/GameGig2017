#pragma once
#include "Collision.h"
#include "ResourceManager.h"
#include "Behaviour.h"

class Entity;

class PacManBehaviour : public Behaviour{
	private:
		ResourceManager<sf::Texture, std::string>* resourceManager;
		float speed;
		
		sf::Sprite sprite;
		int flash; 	/*
					works both as a flag and a counter
					lifecycle: set 0 in contructor
								set 1 in collided
								incremented by update
								set back to 0 when it reaches 5 (depending on the desired rate of flashing effect)
					*/
	public:
		PacManBehaviour(ResourceManager<sf::Texture, std::string>* rm);
		void collided(Entity* other, MTV v);
		void update(int frame_time);
		void render(sf::RenderTarget* target); //Usage: target->draw(sprite)
		void sfmlEvent(sf::Event evt);

		void paintSprite();
		sf::Sprite* getSprite();


};