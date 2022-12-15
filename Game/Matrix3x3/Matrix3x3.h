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

	Matrix3x3 operator*(const Matrix3x3& Matrix1) const;
	const Matrix3x3& operator=(const Matrix3x3& Matrix1);
	const Matrix3x3& operator*=(const Matrix3x3& Matrix1);

	// ��]�s��
	void MakeRotate(float degree);

	// ���s�ړ��s��
	void MakeTranslate(const Vector2D& vec);
	void MakeTranslate(const float& vecX, const float& vecY);

	// �X�J���[�{�s��
	void MakeScalar(const Vector2D& vec);
	void MakeScalar(const float& vecX, const float& vecY);

	// �A�t�B���ϊ�
	void Affin(const Vector2D& size, float degree, const Vector2D& trancelate);

	// �t�s��
	void Inverse();

	// �]�u�s��
	void Transepose();

	// ���ˉe�s��
	void Orthographic(const Vector2D& leftTop, const Vector2D& rightUnder);
	void Orthographic(const Vector2D& size);

	/// <summary>
	/// �r���[�|�[�g�s��
	/// </summary>
	/// <param name="pos">�J�����̍���̍��W</param>
	/// <param name="size">�傫��</param>
	void Viewport(const Vector2D& pos, const Vector2D& size);

};