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

// 静的メンバ変数の初期化
float Camera:: scale = 1.0f;
Vector2D* Camera::centerPos = nullptr;
Frame* Camera::frame = nullptr;
Vector2D* Camera::shakeScale = nullptr;
Matrix3x3* Camera::viewMatrix = nullptr;
Matrix3x3* Camera::NorDevMatrix = nullptr;
Matrix3x3* Camera::viewPortMatrix = nullptr;
Matrix3x3* Camera::vpvpMatrix = nullptr;

void Camera::Initalize(const Vector2D& initPos) {
	centerPos = new Vector2D(initPos);
	frame = new Frame;
	shakeScale = new Vector2D;

	viewMatrix = new Matrix3x3;

	viewMatrix->MakeTranslate(initPos);
	viewMatrix->Inverse();

	NorDevMatrix = new Matrix3x3;

	NorDevMatrix->Orthographic({1280.0f, 720.0f});

	viewPortMatrix = new Matrix3x3;

	viewPortMatrix->Viewport({0.0f,0.0f},{1280.0f,720.0f});

	vpvpMatrix = new Matrix3x3;

	frame->Restart();

	*shakeScale = { 10.0f, 10.0f };
}

void Camera::Initalize() {
	centerPos = new Vector2D;
	frame = new Frame;
	shakeScale = new Vector2D;

	viewMatrix = new Matrix3x3;
	viewMatrix->MakeTranslate(*centerPos);
	viewMatrix->Inverse();

	NorDevMatrix = new Matrix3x3;

	NorDevMatrix->Orthographic({ 1280.0f, 702.0f });

	viewPortMatrix = new Matrix3x3;

	viewPortMatrix->Viewport({ 0.0f,0.0f }, { 1280.0f, 702.0f });

	vpvpMatrix = new Matrix3x3;

	frame->Restart();
	*centerPos = { static_cast<float>(MapChip::kWindowWidth / 2), static_cast<float>(MapChip::kWindowHeight / 2) };

	*shakeScale = { 10.0f, 10.0f };
}

void Camera::Finalize() {
	delete centerPos;
	delete frame;
	delete shakeScale;
	delete viewMatrix;
	delete NorDevMatrix;
	delete viewPortMatrix;
	delete vpvpMatrix;
}

void Camera::Update(const Vector2D& worldPos, const float& scale, const bool& shake) {
	frame->Start();
	if (frame->frame > ULLONG_MAX) {
		frame->Stop();
		frame->Restart();
	}

	Camera::scale = scale;

	*centerPos = worldPos;

	// もしシェイクフラグがオンなら
	if (shake) {
		Shake();
	}

	viewMatrix->MakeTranslate(*centerPos);
	viewMatrix->Inverse();

	*vpvpMatrix = (*viewMatrix) * (*NorDevMatrix) * (*viewPortMatrix);
}

void Camera::Shake() {
	centerPos->x += static_cast<float>((rand() % static_cast<int>(shakeScale->x))) - shakeScale->x / 2.0f;
	centerPos->y += static_cast<float>((rand() % static_cast<int>(shakeScale->y))) - shakeScale->y / 2.0f;
}

void Camera::DrawQuad(Quad quad, Texture& texture, const int& animationSpd, const bool& animationStop, const unsigned int& color) {
	quad.worldMatrix *= (*vpvpMatrix);

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

void Camera::DrawQuad(class Quad quad, class Texture& texture, float deg, const int& animationSpd, const bool& animationStop, const unsigned int& color) {
	quad.worldMatrix *= (*vpvpMatrix);

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


void Camera::DrawUI(Quad quad, Texture texture, const int& animationSpd, const bool& animationStop) {
	MyMath::CoordinateChange(quad.worldPos);

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


bool Camera::isDraw(Vector2D pos) {
	const float& length = MyMath::PythagoreanTheorem(pos.x - Camera::centerPos->x, pos.y - Camera::centerPos->y);
	const float& cameraLength = MyMath::PythagoreanTheorem(static_cast<float>(MapChip::kWindowWidth / 2), static_cast<float>(MapChip::kWindowHeight / 2));
	if (length < cameraLength / scale + 100.0f) {
		return true;
	}
	else {
		return false;
	}
}