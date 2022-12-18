#pragma once

#include "Game/Vector2D/Vector2D.h"

class Matrix3x3;
class Camera;

class World {
public:
	World();
	World(int screenSizeX, int screenSizeY);
	~World();

private:
	void Input();
	void Reset();
	void Update();
	void Draw();

public:
	void MainLoop();

private:
	Camera* camera;

	class Player* player;

	class Texture* whiteBox;
};