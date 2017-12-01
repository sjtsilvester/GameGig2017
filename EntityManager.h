#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#define TILE_SIZE 32

class Entity;

typedef std::vector<std::unique_ptr<Entity>> EntityList;

class EntityManager {
public:
	EntityManager();
	~EntityManager();

	void update(int frame_time);
	void render(sf::RenderTarget* target);

	void add(Entity* entity);

	EntityList* getEntities();
private:
	EntityList entities_;
	std::vector<Entity*> push_queue_;
};
