#pragma once

#include "Game/Object/Object.h"

class Enemy : public Object {
public:
	Enemy() = delete;
	Enemy(Camera* camera, class Player* player, Vector2D pos);

private:
	Player* player;

	Vector2D moveVec;

	float spd;

	static bool isAlive;

public:
	void Update() override;
	void Draw() override;
};