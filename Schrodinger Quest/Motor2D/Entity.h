#ifndef _ENTITY_H
#define _ENTITY_H

#include "j1Module.h"

enum class Types
{
	none=0,
	player,
	enemy_ground,
	enemy_air,
	healing_potion,
	coins,
	unknown
};

class Entity :public j1Module
{
public:
	Entity(Types type) {

	}

	// Destructor
	virtual ~Entity() {

	}

	// Called before render is available
	virtual bool Awake(pugi::xml_node&)
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	//Called when loading the game
	virtual bool Load(pugi::xml_node&)
	{
		return true;
	}

	//Called when saving the game
	virtual bool Save(pugi::xml_node&) const
	{
		return true;
	}

public:
	Types entity_type;
	SDL_Rect position_rect;

	//Copy of node
	pugi::xml_node entity_node;
};

#endif // !ENTITY_H
