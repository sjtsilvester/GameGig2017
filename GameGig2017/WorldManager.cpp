#include "WorldManager.h"
#include "EntityManager.h"
#include "Entity.h"


WorldManager::WorldManager(EntityManager* entity_manager):
	entity_manager_(entity_manager),
	timer_(0){
}

WorldManager::~WorldManager() {
	/*for (auto& mapit : entities_) {
		for (auto& it : mapit.second) {
			delete &it;
		}
	}*/ //fix this if you don't want memory leak on reloading levels
}

void WorldManager::update(int frame_time) {
	auto result = entities_.find(timer_);
	
	if (result != entities_.end()) {
		for (auto& it : result->second) {
			entity_manager_->add(it);
		}
	}
	timer_ += frame_time;
}

void WorldManager::addEntity(int t, Entity* entity, int y) {
	entity->setPosition(sfld::Vector2f(1024 + 50, y));
	auto result = entities_.find(timer_);
	if (result == entities_.end()) {
		entities_.insert(std::make_pair(t, std::vector<Entity*>()));
	}
	entities_.at(t).push_back(entity);
}