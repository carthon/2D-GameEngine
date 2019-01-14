#pragma once
#include "ECS.h"
#include "Components.h"

class Projectile : public Component {
private:
	Transform *transform;
	int range = 0, speed = 0, distance = 0;
	Vector2D velocity;
public:
	Projectile(int range, int speed, Vector2D velocity) : range(range), speed(speed), velocity(velocity) {}
	~Projectile(){}

	void Init() override {
		transform = &entity->GetComponent<Transform>();
		transform->velocity = velocity;
	}
	void Update() override {
		distance += speed;
		if (distance > range) {
			std::cout << "Out of range!" << std::endl;
			entity->Destroy();
		}
		else if (
			transform->position.x > Engine::camera.x + Engine::camera.w ||
			transform->position.x < Engine::camera.x ||
			transform->position.y > Engine::camera.y + Engine::camera.h ||
			transform->position.y < Engine::camera.y
			) {
			std::cout << "Out of bounce!" << std::endl;
			entity->Destroy();
		}
	}
};