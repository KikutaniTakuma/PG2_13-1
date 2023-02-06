#pragma once

#include <vector>
#include <Novice.h>

class World {
public:
	World();
	~World();

private:
	void Input();
	void Reset();
	void Update();
	void Draw();

public:
	void MainLoop();

private:
	class Camera* camera;

	WindowMode winMode;

	std::vector<class Object*> object;
};