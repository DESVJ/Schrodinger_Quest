#ifndef __j1RENDER_H__
#define __j1RENDER_H__

#include "p2Point.h"
#include "j1Module.h"

class j1Render : public j1Module
{
public:

	j1Render();

	// Destructor
	virtual ~j1Render();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Load / Save
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	// Blit
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	bool Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, bool flip = false, fPoint speed = { 1.0f, 1.0f }, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX, bool get_scale = true) const;
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool use_camera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true, bool use_scale = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;
	void BlitBackgroud(SDL_Texture* texture);
	void BlitInsideQuad(SDL_Texture* texture, SDL_Rect sprite, SDL_Rect quad);

	// Set background color
	void SetBackgroundColor(SDL_Color color);

	//Set map limits by TMX file
	void SetMapLimitsWithTMX();

public:

	SDL_Renderer* renderer = nullptr;
	SDL_Rect		camera;
	SDL_Rect		viewport;
	SDL_Color		background;

	p2SString vsync;

	//Camera follow rect
	SDL_Rect followMinRect = {0, 0, 50, 50};

	//Camera limits
	int limitPosX, limitNegX, limitPosY, limitNegY;

	//Move camera to a point inside map limits
	void MoveCameraToPointInsideLimits(p2Point<int> point);

};

#endif // __j1RENDER_H__