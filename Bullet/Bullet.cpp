#include "Bullet.hpp"
#include "Game/MyMath/MyMath.h"

Bullet::Bullet(Camera* camera, float spd, unsigned int color):
	Object(camera),
	flg(false),
	atk(0),
	spd(spd),
	color(color),
	size({32.0f,32.0f})
{
	pos.Set(Vector2D(), size);
}

Bullet::Bullet(Camera* camera) :
	Object(camera),
	flg(false),
	atk(0),
	spd(0),
	color(MyMath::GetRGB(255, 0, 0, 255)),
	size({ 32.0f,32.0f })
{
	pos.Set(Vector2D(), size);
}

void Bullet::Update() {
	if (flg) {
		pos.worldPos.y += spd;
	}

	if (!camera->isDraw(pos.worldPos, 0)) {
		flg = false;
	}
}

void Bullet::Draw() {
	if (flg) {
		camera->DrawQuad(pos, whiteBox, 0, color);
	}
}


bool Bullet::Collision(const Bullet& bul) const {
	return pos.Collision(bul.pos);
}

bool  Bullet::Collision(const Quad& pos) const {
	return this->pos.Collision(pos);
}

Bullet::operator bool() const {
	return flg;
}

float Bullet::getSpd() const {
	return spd;
}

void Bullet::setSpd(float num) {
	if (!flg) {
		spd = num;
	}
}

void Bullet::setPos(Vector2D pos) {
	if (!flg) {
		this->pos.worldPos = pos;
	}
}