#ifndef __EENEMY_H__
#define __EENEMY_H__

#include"p2Point.h"
#include"p2Log.h"
#include"p2SString.h"
#include"p2List.h"
#include"eCreature.h"
#include "j1Timer.h"
#include "EntityManager.h"
#include"j1Input.h"

enum class Enemy_State
{
	none = 0,
	idle,
	move,
	chase,
	dead
};

struct SDL_Rect;

//Player class
class eEnemy : public eCreature
{

public:

	eEnemy(Types type) :eCreature(type) {
		name.create("enemy");
	}

	// Destructor
	virtual ~eEnemy() {

	}

	bool Awake(pugi::xml_node&);

	// Called before the first frame
	virtual bool Start() {
		return true;
	}

	//// Called each loop iteration
	bool Update(float dt) {
		return true;
	}

	// Called before quitting
	bool CleanUp();

	void MoveAndDraw(float dt, SDL_Rect);

	p2Point<bool> OnCollision(Collider*, SDL_Rect, SDL_Rect*, Direction, p2Point<bool>);
	void AfterCollision(p2Point<bool>, SDL_Rect, p2Point<int>);

	void DoPathFinding(p2Point<float>, p2Point<float>);

public:
	Enemy_State en_state;
	Enemy_State en_state_update;
	bool not_chase_tang_mode;
	bool player_nearby;
	j1Timer timer_idle;

};
#endif // __EENEMY_H__
