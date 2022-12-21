#pragma once

class Vector2D;

class Matrix3x3 {
public:
	Matrix3x3();
	Matrix3x3(const Matrix3x3& matrix);
	inline ~Matrix3x3() {}

private:
	static const int HEIGHT = 3;
	static const int WIDTH = 3;

public:
	float m[HEIGHT][WIDTH];

public:
	Matrix3x3 operator*(const Matrix3x3& Matrix1) const;
	const Matrix3x3& operator=(const Matrix3x3& Matrix1);
	const Matrix3x3& operator*=(const Matrix3x3& Matrix1);

public:
	// 回転行列
	void Rotate(float degree);

	// 平行移動行列
	void Translate(const Vector2D& vec);
	void Translate(const float& vecX, const float& vecY);

	// スカラー倍行列
	void Scalar(const Vector2D& vec);
	void Scalar(const float& vecX, const float& vecY);

	// アフィン変換
	void Affin(const Vector2D& size, float degree, const Vector2D& trancelate);

	// 逆行列
	void Inverse();

	// 転置行列
	void Transepose();

	// 正射影行列
	void Orthographic(const Vector2D& leftTop, const Vector2D& rightUnder);
	void Orthographic(const Vector2D& size);

	/// <summary>
	/// ビューポート行列
	/// </summary>
	/// <param name="pos">カメラの左上の座標</param>
	/// <param name="size">大きさ</param>
	void Viewport(const Vector2D& pos, const Vector2D& size);
};