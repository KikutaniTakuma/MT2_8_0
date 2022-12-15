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
	/// <param name="animationSpd">������傫������قǒx���Ȃ�</param>
	/// <param name="animationStop">true�Ȃ�A�j���[�V���������Ȃ�</param>
	/// <param name="color">���Ɏw�肵�Ȃ��ꍇWHITE�ɂȂ�</param>
	static void DrawQuad(class Quad quad, class Texture& texture, const int& animationSpd, const bool& animationStop, const unsigned int& color = 0xffffffff);

	/// <summary>
	/// DrawQuad
	/// </summary>
	/// <param name="quad"></param>
	/// <param name="texture"></param>
	/// <param name="deg">�p�x(�x���@)�B�\����̂݉�]������</param>
	/// <param name="animationSpd">������傫������قǒx���Ȃ�</param>
	/// <param name="animationStop">true�Ȃ�A�j���[�V���������Ȃ�</param>
	/// <param name="color">���Ɏw�肵�Ȃ��ꍇWHITE�ɂȂ�</param>
	static void DrawQuad(class Quad quad, class Texture& texture, float deg, const int& animationSpd, const bool& animationStop, const unsigned int& color = 0xffffffff);
	
	/// <summary>
	/// DrawUI
	/// <para>�J�������ǂ��ɂ��悤���\������</para>
	/// </summary>
	/// <param name="quad"></param>
	/// <param name="texture"></param>
	/// <param name="animationSpd">������傫������قǒx���Ȃ�</param>
	/// <param name="animationStop">true�Ȃ�A�j���[�V���������Ȃ�</param>
	static void DrawUI(class Quad quad, class Texture texture, const int& animationSpd, const bool& animationStop);

	// �J�������ɉf���Ă邩�ǂ���
	// �߂�l�F
	// ture:�f���Ă�
	// false:�f���ĂȂ�
	static bool isDraw(Vector2D pos);

private:
	static void Shake();

private:
	// �J�������W(�^��)
	static Vector2D* centerPos;

	// �ǂ̂��炢�̑傫���ŕ\�����邩(�f�t�H���g��1.0f)
	static float scale;

	// �V�F�C�N�̑傫��
	static Vector2D* shakeScale;

	static Matrix3x3* viewMatrix;

	static Matrix3x3* NorDevMatrix;

	static Matrix3x3* viewPortMatrix;

	static Matrix3x3* vpvpMatrix;

public:
	// �t���[��
	static class Frame* frame;
};