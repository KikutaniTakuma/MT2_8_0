#pragma once

class Texture;
class Vector2D;

#include <vector>

class MapChip {
public:
	enum class Type {
		NONE, // 0
		BLOCK, // 1

		kMaxNum
	};

private:
	inline MapChip() {}
	inline ~MapChip() {}

public:
	static const int kMapSize;
	static const int kWindowWidth;
	static const int kWindowHeight;
	static const int kStageNumberWidth;
	static const int kStageNumberHeight;
	static const int kMapWidth;
	static const int kMapHeight;
	static std::vector<int> data;

private:
	static const class Camera* camera;

public:
	static void Initilize();

	static void SetCamera(class Camera* cameraPointa);

	static void Finalize();

	static bool Collision(const Vector2D& pos);

	// マップチップの踏んでいる場所
	static int GetType(Vector2D worldPos);

	// マップチップの座標
	static Vector2D GetPos(Vector2D worldPos);

	// MapChipの表示処理
	static void Draw(Texture& texture);

	// ホットリロード
	static void Reset();

	/// <summary>
	/// 特定のマップチップ読み込み
	/// </summary>
	/// <param name="fileName">読み込みたいファイルパス</param>
	static void LoadMap(const char* fileName);

	// getter
	static int getData(const int& x, const int& y);

	// setter
	static void setData(int num, const int& x, const int& y);
};