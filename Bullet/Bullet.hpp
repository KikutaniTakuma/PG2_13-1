#pragma once

#include "Game/Object/Object.h"
class Bullet : public Object {
public:
	Bullet() = delete;
	Bullet(Camera* camera, float spd, unsigned int color);
	Bullet(Camera* camera);

public:
	bool flg;

private:
	int atk;
	float spd;
	unsigned int color;

public:
	Vector2D size;

public:
	void Update() override;
	void Draw() override;

	explicit operator bool() const;

	float getSpd() const;
	void setSpd(float num);

	void setPos(Vector2D pos);

	bool Collision(const Bullet& bul) const;
	bool Collision(const Quad& pos) const;
};