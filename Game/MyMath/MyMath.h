#pragma once

class Vector2D;

class MyMath {
private:
	inline MyMath(){}
	inline ~MyMath(){}

public:
	// ワールド座標を変換時の定数
	static const int kCoodinateChangeConstant;

	/*
	ワールド座標をスクリーン座標に返還
	*/
	static void CoordinateChange(const Vector2D& worldPos, Vector2D& screenPos);

	/*
	ワールド座標をスクリーン座標に返還
	*/
	static void CoordinateChange(Vector2D& worldPos);
	/*
	ワールド座標をスクリーン座標に返還
	*/
	static void CoordinateChange(Vector2D& worldPos, const int coordinateChangeConstant);

	/*
	ワールド座標をスクリーン座標に返還
	*/
	static void CoordinateChange(int& worldPos);


	// 三平方の定理
	static float PythagoreanTheorem(const float& x, const float& y);

	// 正規化
	// 第一引数が正規化される
	static float Normalize(const float& x, const float& y);

	static Vector2D Normalize(Vector2D vec);

	/*
	矩形の当たり判定
	
	第一引数：矩形の左上座標
	第二引数：矩形のサイズ
	第三引数：矩形の左上座標2
	第四引数：矩形のサイズ2

	戻り値：あたってる：１
	　　　  あたってない：０
	*/
	static bool CollisionRectangle(Vector2D LeftTop1, Vector2D size1, Vector2D LeftTop2, Vector2D size2);

	/*
	矩形の当たり判定

	第一引数：矩形の左上座標
	第二引数：矩形のサイズ
	第三引数：矩形の左上座標2
	第四引数：矩形のサイズ2

	戻り値：あたってる：１
	　　　  あたってない：０
	*/
	static bool CollisionRectangle(int LeftTopX1, int LeftTopY1, int sizeX1, int sizeY1, int LeftTopX2, int LeftTopY2, int sizeX2, int sizeY2);

	/*
	入れ替え

	第一引数と第二引数を入れ替える
	*/
	template <class T>
	static inline void Tmp(T& x, T& y) {
		T tmp;
		tmp = x;
		x = y;
		y = tmp;
	}


	/*
	バブルソート

	第一引数：データ
	第二引数：データの要素数
	第三引数：true小さい順、false大きい順
	*/
	static void BubbleSort(int* data, int arr, bool order);

	/*
	内積
	*/
	static float Dot(float x1, float y1, float x2, float y2);

	/*
	内積
	*/
	static float Dot(Vector2D vec1, Vector2D vec2);

	/*
	外積
	*/

	/// <summary>
	/// 度数法から弧度法に変換
	/// </summary>
	/// <param name="deg">変換したいdeg</param>
	/// <returns>変換後の角度</returns>
	static float ToRad(const float& deg);

	/// <summary>
	/// 弧度法から度数法に変換
	/// </summary>
	/// <param name="rad">変換したいrad</param>
	/// <returns>変換後の角度</returns>
	static float ToDeg(const float& rad);

	/// <summary>
	/// 特定の角度の範囲かどうか
	/// </summary>
	/// <param name="deg">範囲に入ってるかどうかの角度</param>
	/// <param name="maxDeg">特定の角度の最大値</param>
	/// <param name="minDeg">特定の角度の最小値</param>
	/// <returns>特定の角度の範囲ならture</returns>
	static bool isAngle(float deg, float maxDeg, float minDeg);

	/// <summary>
	/// 特定の場所からの角度を求める
	/// </summary>
	/// <param name="pos">求めたいポジション</param>
	/// <param name="origin">どこからの角度かのポジション</param>
	/// <returns>角度(deg)</returns>
	static float GetAngle(Vector2D pos, Vector2D origin);

	/// <summary>
	/// 引数に入れたものを交換する
	/// </summary>
	/// <param name="num">交換したいもの1</param>
	/// <param name="num2">交換したいもの2</param>
	template<typename T>
	inline static void Swap(T& num, T& num2) {
		T tmp = num;
		num = num2;
		num2 = tmp;
	}

	static float Clamp(float num, float max, float min);

	inline static unsigned int GetRGB(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);
};