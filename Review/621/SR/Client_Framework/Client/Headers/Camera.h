#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Base.h"

class Camera
{
	DECLARE_SINGLETON(Camera)

private:
	explicit Camera();
	virtual ~Camera();

public:
	static Camera*	Create(
		_lpd3dd9 pDevice,
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
		_lpd3dd9 pDevice,
		const _vector3& vPos,
		const _vector3& vLookAt,
		const PROJ& Proj);
	_uint Release();

public:
	_uint UpdateCamera();

public:
	const _matrix& Get_Transform(CameraCt _CameraCt) { return m_Transform[(_int)_CameraCt]; }

public:
	void CalculateAxis();		// 우향 벡터 계산
	void CalculateView();		// 뷰 행렬 
	void CalculateProj();		// 투영 행렬

	BOOL CalculateMove();		// 카메라의 이동
	BOOL CalculateRot();		// 카메라의 회전

private:
	_lpd3dd9	m_pDevice;
	CameraType	m_CameraType;
	
	// View
	_vector3	m_vAxis[(_int)CameraAx::END];	// 우향 벡터
	_vector3	m_Pos;		//	카메라의 위치
	_vector3	m_LookAt;	//	카메라가 바라보는 위치

	//proj
	PROJ		m_Proj;

	////TransForm
	_matrix		m_Transform[(_int)CameraCt::END];

	BOOL		m_bMove;
	BOOL		m_bRot;

	//Stat
	_float		m_MoveSpeed = 0.03f;
	_vector3	m_Angle = _vector3(0.f, 0.f, 0.f);

};

#endif

