#pragma once

class Vector2D;
class Matrix3x3;

class Camera {
private:
	inline Camera(){}
	inline ~Camera(){}

public:
	static void Initalize(const Vector2D& initPos);

	static void Initalize();

	static void Finalize();

	static void Update(const Vector2D& worldPos, const float& scale = 1.0f, const bool& shake = false);

	/// <summary>
	/// DrawQuad
	/// </summary>
	/// <param name="quad"></param>
	/// <param name="texture"></param>
	/// <param name="animationSpd">数字を大きくするほど遅くなる</param>
	/// <param name="animationStop">trueならアニメーションさせない</param>
	/// <param name="color">特に指定しない場合WHITEになる</param>
	static void DrawQuad(class Quad quad, class Texture& texture, const int& animationSpd, const bool& animationStop, const unsigned int& color = 0xffffffff);

	/// <summary>
	/// DrawQuad
	/// </summary>
	/// <param name="quad"></param>
	/// <param name="texture"></param>
	/// <param name="deg">角度(度数法)。表示上のみ回転させる</param>
	/// <param name="animationSpd">数字を大きくするほど遅くなる</param>
	/// <param name="animationStop">trueならアニメーションさせない</param>
	/// <param name="color">特に指定しない場合WHITEになる</param>
	static void DrawQuad(class Quad quad, class Texture& texture, float deg, const int& animationSpd, const bool& animationStop, const unsigned int& color = 0xffffffff);
	
	/// <summary>
	/// DrawUI
	/// <para>カメラがどこにいようが表示する</para>
	/// </summary>
	/// <param name="quad"></param>
	/// <param name="texture"></param>
	/// <param name="animationSpd">数字を大きくするほど遅くなる</param>
	/// <param name="animationStop">trueならアニメーションさせない</param>
	static void DrawUI(class Quad quad, class Texture texture, const int& animationSpd, const bool& animationStop);

	// カメラ内に映ってるかどうか
	// 戻り値：
	// ture:映ってる
	// false:映ってない
	static bool isDraw(Vector2D pos);

private:
	static void Shake();

private:
	// カメラ座標(真ん中)
	static Vector2D* centerPos;

	// どのくらいの大きさで表示するか(デフォルトは1.0f)
	static float scale;

	// シェイクの大きさ
	static Vector2D* shakeScale;

	static Matrix3x3* viewMatrix;

	static Matrix3x3* NorDevMatrix;

	static Matrix3x3* viewPortMatrix;

	static Matrix3x3* vpvpMatrix;

public:
	// フレーム
	static class Frame* frame;
};