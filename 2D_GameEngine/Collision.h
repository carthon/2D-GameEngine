#pragma once
#include <SDL.h>
#include "Vector2D.h"

class Collider;

class Collision {
public:
	//Colision Axis Aling Bouncing Box
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(const Collider& colA, const Collider& colB);
};