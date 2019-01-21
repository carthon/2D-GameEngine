#pragma once
#include "Vector2D.h"

class Collider;

class Transform : public Component {
public:
	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	Transform() {
		position.Zero();
	}

	Transform(int sc) {
		position.Zero();
		scale = sc;
	}

	Transform(int height, int width, int sc) {
		position.Zero();
		scale = sc;
		this->height = height;
		this->width = width;
	}

	Transform(float x, float y) {
		position.x = x;
		position.y = y;
	}	
	Transform(float x, float y, int height, int width, int scale) {
		position.x = x;
		position.y = y;
		this->height = height;
		this->width = width;
		this->scale = scale;
	}

	void Init() override {
		velocity.Zero();
	}
	
	void Move(float x, float y) {
		position.x += x;
		position.y += y;

	}

	void Update() override {
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};