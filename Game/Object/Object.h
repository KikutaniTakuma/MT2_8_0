#pragma once
#include "Game/Camera/Camera.h"

class Object {
public:
	Object(class Camera* camera);

protected:
	const Camera* camera;

public:
	virtual void Update() = 0;

	virtual void Draw(class Texture& tex) = 0;

	virtual void Reset() = 0;
};