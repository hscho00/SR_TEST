#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Base.h"

class Camera
{
public:
	Camera();
	~Camera();

public:
	enum class CameraType
	{
		LANDOBJECT,
		AIRCARFT
	};

public:
	void strafe(float units);	// ���� / ������
	void fly(float units);		// ���� / �Ʒ���
	void walk(float units);		// ���� / ����

	void pitch(float angle);	// ���� ���ͷ� ȸ��
	void yaw(float angle);		// ���� ���ͷ� ȸ��
	void roll(float angle);		// ���� ���ͷ� ȸ��

public:
	void getViewMatrix(_matrix* v);
	void getPosition(_vector3* pos);
	void getRight(_vector3* right);
	void getUp(_vector3* up);
	void getLook(_vector3* look);

public:
	void setCameraType(CameraType cameraType);
	void setPosition(_vector3* pos);

private:
	CameraType	m_CameraType;
	_vector3	m_Right;
	_vector3	m_Up;
	_vector3	m_Look;
	_vector3	m_Pos;

};

#endif

