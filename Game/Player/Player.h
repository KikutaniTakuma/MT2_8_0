#pragma once
class Vector2D;
class Matrix3x3;

class Player {
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
	Player();
	~Player();

private:
	

	Vector2D* tentativPos;
	Vector2D* size;
	Vector2D* moveVec;
	class Quad* pos;

	float spd;

	bool flgJump;
	bool flgJumpSecond;

	float jumpValue;
	float jumpSeconsdValue;

	bool flgGravity;
	float gravity;

	class Effect* landing;

	unsigned short deadZone;

	// èdóÕÇ»ÇµÇ©Ç«Ç§Ç©
	bool flgZeroGravity;

public:
	void Update();

	void Draw(class Texture& tex);

	void Reset();

private:
	void Move();

	void Jump();

	void Collision();

public:
	// getter
	Vector2D getWorldPos() const;
	float getWorldPosX() const;
	float getWorldPosY() const;
	float getSize()const;

	// setter
	void setWorldPos(Vector2D pos);
	void setWorldPosX(const float& num);
	void setWorldPosY(const float& num);
};