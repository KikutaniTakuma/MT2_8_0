#pragma once

class Vector2D;
class Matrix3x3;

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

public:
	class Player* player;

	class Texture* whiteBox;
};