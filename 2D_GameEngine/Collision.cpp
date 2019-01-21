#include "Collision.h"
#include "Collider.h"
/*
bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB, float push) {
	Vector2D thisPosition = { rectA.x, rectA.y };
	Vector2D thisHalfSize = { rectA.w / 2, rectA.h / 2 };
	Vector2D otherPosition = { rectB.x, rectB.y };
	Vector2D otherHalfSize = { rectB.w / 2, rectB.h / 2 };

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersecX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersecY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
	float deltaX = otherPosition.x - thisPosition.y;

	if (intersecX < 0.0f && intersecY < 0.0f) {
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersecX > intersecY) {
			if (deltaX > 0.0f) {
				Move(intersecX * (1.0f - push), 0);
				other.Move(-intersecX * push, 0);
			}
			else {
				Move(-intersecX * (1.0f - push), 0);
				other.Move(intersecX * push, 0);
			}
		}
		else {
			if (deltaY > 0.0f) {
				Move(intersecY * (1.0f - push), 0);
				other.Move(-intersecY * push, 0);
			}
			else {
				Move(-intersecY * (1.0f - push), 0);
				other.Move(intersecY * push, 0);
			}
		}
		return true;
	}

	return false;
}
*/
bool Collision::AABB(const Collider& colA, const Collider& colB, float push) {
	Vector2D thisPosition = { static_cast<float>( colA.collider.x), static_cast<float>(colA.collider.y) };
	Vector2D thisHalfSize = { static_cast<float>(colA.collider.w / 2), static_cast<float>(colA.collider.h / 2) };
	Vector2D otherPosition = { static_cast<float>(colB.collider.x), static_cast<float>(colB.collider.y) };
	Vector2D otherHalfSize = { static_cast<float>(colB.collider.w / 2), static_cast<float>(colB.collider.h / 2) };

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersecX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersecY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	Transform *transA = &colA.entity->GetComponent<Transform>();
	Transform *transB = &colB.entity->GetComponent<Transform>();

	if (intersecX < 0.0f && intersecY < 0.0f) {
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersecX > intersecY) {
			if (deltaX > 0.0f) {
				transA->Move(intersecX * (1.0f - push), 0);
				transB->Move(-intersecX * push, 0);
			}
			else {
				transA->Move(-intersecX * (1.0f - push), 0);
				transB->Move(intersecX * push, 0);
			}
		}
		else {
			if (deltaY > 0.0f) {
				transA->Move(intersecY * (1.0f - push), 0);
				transB->Move(-intersecY * push, 0);
			}
			else {
				transA->Move(-intersecY * (1.0f - push), 0);
				transB->Move(intersecY * push, 0);
			}
		}
		std::cout << colA.tag << " hit: " << colB.tag << std::endl;
		return true;
	}
	return false;
}

