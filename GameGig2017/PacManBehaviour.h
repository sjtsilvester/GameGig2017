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
		bool isFlashing;
		int endFlash;

	public:
		PacManBehaviour(ResourceManager<sf::Texture, std::string>* rm);
		void collided(Entity* other, MTV v);
		void update(int frame_time);
		void render(sf::RenderTarget* target); //Usage: target->draw(sprite)
		void sfmlEvent(sf::Event evt);

		void paintSprite();
		sf::Sprite* getSprite();


};