#include "MapChip.h"
#include <Novice.h>
#include "Game/Texture/Texture.h"
#include "Game/Vector2D/Vector2D.h"
#include "Game/MyMath/MyMath.h"
#include "Game/Quad/Quad.h"
#include "Game/Camera/Camera.h"

#include "Game/IOcsv/IOcsv.h"

std::vector<int> MapChip::data;
const int MapChip::kMapSize = 32;
const int MapChip::kWindowWidth = 1280;
const int MapChip::kWindowHeight = 704;
const int MapChip::kStageNumberWidth = 1;
const int MapChip::kStageNumberHeight = 1;
const int MapChip::kMapWidth = (kWindowWidth / kMapSize) * kStageNumberWidth;
const int MapChip::kMapHeight = (kWindowHeight / kMapSize) * kStageNumberHeight;


void MapChip::Initilize() {
	MapChip::data.resize(MapChip::kMapHeight * MapChip::kMapWidth);

	IOcsv::Input("./Data/MapChipData.csv", MapChip::data);
}

void MapChip::Finalize() {
}

void MapChip::Reset() {
	IOcsv::Input("./Data/MapChipData.csv", MapChip::data);
}


bool  MapChip::Collision(const Vector2D& pos) {
	if (GetType(pos) == (int)MapChip::Type::BLOCK) {
		return true;
	}
	else if(GetType(pos) == (int)MapChip::Type::NONE) {
		return false;
	}
	else {
		return false;
	}
}

int  MapChip::GetType(Vector2D worldPos) {
	MyMath::CoordinateChange(worldPos, MapChip::kWindowHeight * MapChip::kStageNumberHeight);

	int y = (int)worldPos.y / MapChip::kMapSize;
	int x = (int)worldPos.x / MapChip::kMapSize;

	MyMath::CoordinateChange(worldPos, MapChip::kWindowHeight * MapChip::kStageNumberHeight);

	if (x >= MapChip::kMapWidth || y >= MapChip::kMapHeight || x < 0 || y < 0) {
		return (int)MapChip::Type::NONE;
	}
	else {
		return data[y * MapChip::kMapWidth + x];
	}
}

Vector2D  MapChip::GetPos(Vector2D worldPos) {
	Vector2D mapChipPos;
	mapChipPos.x = (float)(static_cast<int>(worldPos.x) / kMapSize) * kMapSize;
	mapChipPos.y = (float)(static_cast<int>(worldPos.y - 1.0f) / kMapSize) * kMapSize;
	return mapChipPos;
}


void MapChip::Draw(Texture& texture) {
	int x = 0;
	int y = 0;
	Quad quad( {0.0f,0.0f}, { kMapSize, kMapSize } );

	for (y = MapChip::kMapHeight - 1; y >= 0; y--) {
		for (x = 0; x < MapChip::kMapWidth; x++) {
			quad.worldPos = { static_cast<float>((x * kMapSize) + kMapSize / 2), static_cast<float>((y * kMapSize) + kMapSize / 2) };
			MyMath::CoordinateChange(quad.worldPos);
			quad.worldMatrix.MakeTranslate(quad.worldPos);

			if (!Camera::isDraw(quad.worldPos))
			{
				continue;
			}

			switch (data[y * MapChip::kMapWidth + x]) {
			case (int)MapChip::Type::NONE:
				Camera::DrawQuad(quad, texture, 0, false, BLACK);

				break;
			case (int)MapChip::Type::BLOCK:
				Camera::DrawQuad(quad, texture, 0, false, WHITE);

				break;

			default:
				Camera::DrawQuad(quad, texture, 0, false, BLACK);

				break;
			}
		}
	}
}


void MapChip::LoadMap(const char* fileName) {
	IOcsv::Input(fileName, MapChip::data);
}


int MapChip::getData(const int& x, const int& y) {
	return data[y * MapChip::kMapWidth + x];
}

void MapChip::setData(int num, const int& x, const int& y) {
	if (num >= (int)Type::kMaxNum) { num = 0; }

	data[y * MapChip::kMapWidth + x] = num;
}