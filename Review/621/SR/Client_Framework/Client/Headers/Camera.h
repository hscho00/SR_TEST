#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Base.h"

typedef struct _tatProj
{
	float fWidth;
	float fHeight;

	float fFovy;
	float fNear;
	float fFar;
} PROJ, *PPROJ;

class Camera
{
	DECLARE_SINGLETON(Camera)

private:
	explicit Camera();
	virtual ~Camera();

public:
	static Camera*	Create(
		const _vector3& vPos,
		const _vector3& vLookAt,
		const PROJ&	Proj);
	virtual void	Free();

public:
	enum class CameraAx
	{
		X,
		Y,
		Z,
		END
	};

	enum class CameraCt
	{
		VIEW,
		PROJ,
		END
	};

	enum class CameraType
	{
		LANDOBJECT,
		AIRCARFT
	};

public:
	void Ready_Camera(
		const _vector3& vPos,
		const _vector3& vLookAt,
		const PROJ& Proj);
	_uint Release();

public:
	void CalculateAxis();
	void CalculateView();
	void CalculateProj();

private:
	CameraType	m_CameraType;
	
	// View
	_vector3	m_vAxis[(_int)CameraAx::END];	// ���� ����
	_vector3	m_Pos;		//	ī�޶��� ��ġ
	_vector3	m_LookAt;	//	ī�޶� �ٶ󺸴� ��ġ

	//proj
	PROJ		m_Proj;

	////TransForm
	_matrix		m_Transform[(_int)CameraCt::END];

	BOOL		m_bMove;
	BOOL		m_bRot;

};

#endif

