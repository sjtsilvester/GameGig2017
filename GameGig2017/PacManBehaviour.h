#pragma once
#include "stdafx.h"
#include "Collision.h"
#include "ResourceManager.h"


class PacManBehaviour {
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
		void update(double frame_time);
		void render(sf::RenderTarget* target); //Usage: target->draw(sprite)

		void paintSprite(sf::Texture texture);
		sf::Sprite* getSprite();


};