#pragma once
#include "Game/Object/Object.h"
#include <vector>

class Player : public Object {
public:
	struct State {
		float hp;
		float attck;
		float spd;
	};

	enum Dirextion {
		LEFT = 0,
		RIGHT,
	};

public:
	Player() = delete;
	Player(Camera* camera);
	~Player();

private:
	Vector2D tentativPos;
	Vector2D moveVec;

	float spd;

	class Effect* landing;

	unsigned short deadZone;

public:
	std::vector<class Bullet*> bul;
	std::vector<class Bullet*>::iterator curBul;

public:
	void Update() override;

	void Draw() override;

	void Reset() override;

private:
	void Move();

	void Collision();

public:
	// getter
	Vector2D getWorldPos() const;
};