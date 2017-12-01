#pragma once

#include <unordered_map>
#include <vector>

class Entity;
class EntityManager;

class WorldManager {
public:
	WorldManager(EntityManager* entity_manager);
	~WorldManager();

	void update(int frame_time);
	void addEntity(int t, Entity* entity, int y);
private:
	EntityManager* entity_manager_;
	int timer_;
	std::unordered_map<int, std::vector<Entity*>> entities_;
};