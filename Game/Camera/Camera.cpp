#include "Game/Camera/Camera.h"
#include "Game/Vector2D/Vector2D.h"
#include "Game/Frame/Frame.h"
#include "Game/Texture/Texture.h"
#include "Game/Quad/Quad.h"
#include "Game/MapChip/MapChip.h"
#include "Game/MyMath/MyMath.h"
#include "Game/Matrix3x3/Matrix3x3.h"

#include <Novice.h>

#include <time.h>
#include <stdlib.h>
#include <limits.h>

Camera::Camera() {
	worldPos = { static_cast<float>(MapChip::kWindowWidth) / 2.0f, static_cast<float>(MapChip::kWindowHeight) / 2.0f };
	screenPos = { 0.0f,0.0f };

	drawLeftTop = { static_cast<float>(MapChip::kWindowWidth) / -2.0f, static_cast<float>(MapChip::kWindowHeight) / 2.0f };
	drawRightBottom = { static_cast<float>(MapChip::kWindowWidth) / 2.0f, static_cast<float>(MapChip::kWindowHeight) / -2.0f };

	size = { static_cast<float>(MapChip::kWindowWidth), static_cast<float>(MapChip::kWindowHeight) };
	viewMatrix.MakeTranslate(worldPos);
	viewMatrix.Inverse();

	NorDevMatrix.Orthographic(drawLeftTop, drawRightBottom);

	viewPortMatrix.Viewport({ 0.0f,0.0f }, size);

	frame = new Frame;
	frame->Restart();

	shakeScale = { 10.0f, 10.0f };
}

Camera::~Camera(){
	delete frame;
}

void Camera::Update(const Vector2D& worldPos, const Vector2D& cameraPos, const float& scale, const bool& shake) {
	frame->Start();
	if (frame->frame > ULLONG_MAX) {
		frame->Stop();
		frame->Restart();
	}

	this->scale = scale;

	this->worldPos = worldPos;

	// もしシェイクフラグがオンなら
	if (shake) {
		Shake();
	}

	viewMatrix.MakeTranslate(this->worldPos);
	viewMatrix.Inverse();
	NorDevMatrix.Orthographic(size / this->scale);
	viewPortMatrix.Viewport(cameraPos, size);

	vpvpMatrix = viewMatrix * NorDevMatrix * viewPortMatrix;
}

void Camera::Update(const Vector2D& worldPos, const Vector2D& cameraPos, const Vector2D& drawLeftTop, const Vector2D& drawRightBottom, const bool& shake) {
	frame->Start();
	if (frame->frame > ULLONG_MAX) {
		frame->Stop();
		frame->Restart();
	}

	this->worldPos = worldPos;

	// もしシェイクフラグがオンなら
	if (shake) {
		Shake();
	}
	this->drawLeftTop = drawLeftTop;
	this->drawRightBottom = drawRightBottom;

	viewMatrix.MakeTranslate(this->worldPos);
	viewMatrix.Inverse();
	NorDevMatrix.Orthographic(this->drawLeftTop, this->drawRightBottom);
	viewPortMatrix.Viewport(cameraPos, size);

	vpvpMatrix = viewMatrix * NorDevMatrix * viewPortMatrix;
}


void Camera::Shake() {
	worldPos.x += static_cast<float>((rand() % static_cast<int>(shakeScale.x))) - shakeScale.x / 2.0f;
	worldPos.y += static_cast<float>((rand() % static_cast<int>(shakeScale.y))) - shakeScale.y / 2.0f;
}

void Camera::DrawQuad(Quad quad, Texture& texture, const int& animationSpd, const bool& animationStop, const unsigned int& color) const {
	quad.worldMatrix *= vpvpMatrix;

	if (!animationStop && animationSpd != 0) {
		if (frame->frame % animationSpd == 0) {
			texture.drawPos += texture.width;
			if (texture.drawPos > texture.spriteSize - texture.width) {
				texture.drawPos = 0;
			}
		}
	}

	Novice::DrawQuad(
		static_cast<int>(quad.getMatrixLeftTop().x), static_cast<int>(quad.getMatrixLeftTop().y),
		static_cast<int>(quad.getMatrixRightTop().x), static_cast<int>(quad.getMatrixRightTop().y),
		static_cast<int>(quad.getMatrixLeftUnder().x), static_cast<int>(quad.getMatrixLeftUnder().y),
		static_cast<int>(quad.getMatrixRightUnder().x), static_cast<int>(quad.getMatrixRightUnder().y),
		texture.drawPos, 0, texture.width, texture.height, texture.textureHandle, color
	);
}

void Camera::DrawQuad(class Quad quad, Texture& texture, float deg, const int& animationSpd, const bool& animationStop, const unsigned int& color) const {
	quad.worldMatrix *= vpvpMatrix;

	if (!animationStop && animationSpd != 0) {
		if (frame->frame % animationSpd == 0) {
			texture.drawPos += texture.width;
			if (texture.drawPos > texture.spriteSize - texture.width) {
				texture.drawPos = 0;
			}
		}
	}

	Novice::DrawQuad(
		static_cast<int>(quad.getMatrixLeftTop().x), static_cast<int>(quad.getMatrixLeftTop().y),
		static_cast<int>(quad.getMatrixRightTop().x), static_cast<int>(quad.getMatrixRightTop().y),
		static_cast<int>(quad.getMatrixLeftUnder().x), static_cast<int>(quad.getMatrixLeftUnder().y),
		static_cast<int>(quad.getMatrixRightUnder().x), static_cast<int>(quad.getMatrixRightUnder().y),
		texture.drawPos, 0, texture.width, texture.height, texture.textureHandle, color
	);
}


void Camera::DrawUI(Quad quad, Texture& texture, const int& animationSpd, const bool& animationStop) const {
	Matrix3x3 mat;
	mat.MakeTranslate(worldPos);
	quad.worldMatrix *= mat * vpvpMatrix;

	if (!animationStop && animationSpd != 0) {
		if (frame->frame % animationSpd == 0) {
			texture.drawPos += texture.width;
			if (texture.drawPos > texture.spriteSize - texture.width) {
				texture.drawPos = 0;
			}
		}
	}

	Novice::DrawQuad(
		static_cast<int>(quad.getPosLeftTop().x), static_cast<int>(quad.getPosLeftTop().y),
		static_cast<int>(quad.getPosRightTop().x), static_cast<int>(quad.getPosRightTop().y),
		static_cast<int>(quad.getPosLeftUnder().x), static_cast<int>(quad.getPosLeftUnder().y),
		static_cast<int>(quad.getPosRightUnder().x), static_cast<int>(quad.getPosRightUnder().y),
		texture.drawPos, 0, texture.width, texture.height, texture.textureHandle, WHITE
	);
}


bool Camera::isDraw(Vector2D pos, const float& drawLength) const {
	pos -= worldPos;
	if (pos.x < drawLeftTop.x - drawLength || pos.x > drawRightBottom.x + drawLength ||
		pos.y > drawLeftTop.y + drawLength || pos.y < drawRightBottom.y - drawLength) {
		return false;
	}
	else {
		return true;
	}
}

Vector2D Camera::getPos() const {
	return worldPos;
}