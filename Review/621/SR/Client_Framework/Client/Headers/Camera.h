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
	void strafe(float units);	// 왼쪽 / 오른쪽
	void fly(float units);		// 위쪽 / 아래쪽
	void walk(float units);		// 앞쪽 / 뒤쪽

	void pitch(float angle);	// 우향 벡터로 회전
	void yaw(float angle);		// 상향 벡터로 회전
	void roll(float angle);		// 전방 벡터로 회전

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

