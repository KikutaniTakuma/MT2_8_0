#pragma once

class Complex {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Complex();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="re">����</param>
	/// <param name="im">����</param>
	Complex(const float& re, const float& im);

	/// <summary>
	/// �R�s�[�R���X�g���N�^
	/// </summary>
	/// <param name="tmp">���f��</param>
	Complex(const Complex& tmp);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	inline ~Complex(){}

	/// <summary>
	/// ���Z�q�̃I�[�o�[���[�h
	/// </summary>
	/// <param name="num">�����������f��</param>
	/// <returns>����������</returns>
	Complex operator+(const Complex& num);

	/// <summary>
	/// ���Z�q�̃I�[�o�[���[�h
	/// </summary>
	/// <param name="num">�|���������f��</param>
	/// <returns>�|��������</returns>
	Complex operator*(const Complex& num);

	/// <summary>
	/// ���Z�q�̃I�[�o�[���[�h
	/// </summary>
	/// <param name="num">������������f��</param>
	/// <returns>*this</returns>
	const Complex& operator=(const Complex& num);

	/// <summary>
	/// ���Z�q�̃I�[�o�[���[�h
	/// </summary>
	/// <param name="num">��������Z���������f��</param>
	/// <returns>�����đ����������</returns>
	const Complex& operator+=(const Complex& num);

	/// <summary>
	/// ���Z�q�̃I�[�o�[���[�h
	/// </summary>
	/// <param name="num">������Ċ|���Z���������f��</param>
	/// <returns>�|���đ����������</returns>
	const Complex& operator*=(const Complex& num);

	/// <summary>
	/// ����
	/// </summary>
	float real;

	/// <summary>
	/// ����
	/// </summary>
	float imag;
};