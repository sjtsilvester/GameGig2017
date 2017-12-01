#pragma once
#include "Behaviour.h"

class GameState;
class Entity;

class ShooterBehaviour : public Behaviour {
public:
	ShooterBehaviour(ResourceManager<sf::Texture, std::string>* rm, Entity* player, GameState* gameState);
	void collided(Entity* other, MTV v);
	void update(int frameTime);
	void render(sf::RenderTarget* target);
	void sfmlEvent(sf::Event evt);
	sf::Sprite *getSprite();
private:
	ResourceManager<sf::Texture, std::string>* rm_;
	sf::Sprite sprite;
	GameState* gameState_;
	Entity* player_;
	int timer;
	int r;
	int shoottimer;
};
