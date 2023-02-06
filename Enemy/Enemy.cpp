#include "Enemy.hpp"
#include "Game/Player/Player.h"
#include "Game/MyMath/MyMath.h"
#include "Bullet/Bullet.hpp"

bool Enemy::isAlive = true;

Enemy::Enemy(Camera* camera, class Player* player, Vector2D pos):
	Object(camera),
	player(player),
	spd(10.0f)
{
	this->pos.Set(pos, Vector2D(100.0f, 100.0f));
	isAlive = true;
}

void Enemy::Update() {
	if (isAlive) {
 		pos.worldPos.x += spd;
		if (pos.worldPos.x < pos.getSize().x / 2.0f || pos.worldPos.x > 1280.0f - pos.getSize().x / 2.0f) {
			spd *= -1.0f;
		}
	}

	for (auto& i : player->bul) {
		if (i->Collision(pos)) {
			isAlive = false;
			i->flg = false;
		}
	}
}

void Enemy::Draw() {
	if (isAlive) {
		camera->DrawQuad(pos, whiteBox, 0, MyMath::GetRGB(255, 0, 255, 255));
	}
}