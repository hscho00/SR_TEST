#include "stdafx.h"
#include "..\Headers\Camera.h"

IMPLEMENT_SINGLETON(Camera)

Camera::Camera()
{
}

Camera::~Camera()
{
}

Camera* Camera::Create(
    const _vector3& vPos,
    const _vector3& vLookAt,
    const PROJ& Proj)
{

    m_pInstance->Ready_Camera(vPos, vLookAt, Proj);
    
    //View
    return m_pInstance;
}

void Camera::Free()
{
}

void Camera::Ready_Camera(const _vector3& vPos, const _vector3& vLookAt, const PROJ& Proj)
{
    //view
    m_Pos = vPos;
    m_LookAt = vLookAt;

    // Proj
    m_Proj = Proj;

    m_vAxis[(int)CameraAx::Y] = _vector3(0.f, 1.f, 0.f);

    for (int i = 0; i < (int)CameraCt::END; ++i)
    {
        D3DXMatrixIdentity(&m_Transform[i]);
    }

    CalculateAxis();
    CalculateView();
    CalculateProj();

    m_bMove = FALSE;
    m_bRot = FALSE;

}

_uint Camera::Release()
{
    return 0;
}

void Camera::CalculateAxis()
{
    m_vAxis[(int)CameraAx::Z] = m_LookAt - m_Pos;   // 깊이 바라보는 위치에서 카메라의 위치까지의 내적을 구함
    D3DXVec3Normalize(&m_vAxis[(int)CameraAx::Z], &m_vAxis[(int)CameraAx::Z]);

    // 카메라와 바라보는 지점 사이의 거리 벡터를 구한 뒤 이를 정규화 하면 카메라의 z축에 대한 방향 벡터
    // Look과 Pos는 항상 존재할 수 밖에 없으므로, 이를 기준으로 Z축을 설정
    // 이 Z축이 나머지 축들에 영향을 미침

    D3DXVec3Cross(&m_vAxis[(int)CameraAx::X], &m_vAxis[(int)CameraAx::Y], &m_vAxis[(int)CameraAx::Z]);
    D3DXVec3Normalize(&m_vAxis[(int)CameraAx::X], &m_vAxis[(int)CameraAx::X]);

    // Z축을 구하면, X축은 Z축과 Y축의 외적을 통해 구해낸 수직인 축
    // 최초에는 Y축을 따로 구해둔 상태가 아니므로, 임시로 설정한 (0, 1, 0) 벡터를 임시 Y축으로 삼아 X축을 계산

    D3DXVec3Cross(
        &m_vAxis[(int)CameraAx::Y],
        &m_vAxis[(int)CameraAx::Z],
        &m_vAxis[(int)CameraAx::X]);

    D3DXVec3Normalize(
        &m_vAxis[(int)CameraAx::Y],
        &m_vAxis[(int)CameraAx::Y]
    );

    // X축과 Z축을 이용해 임시 값이었던 Y축을 연산
} // 카메라 기준에서 x,y,z 축을 연산

void Camera::CalculateView()
{
    D3DXMatrixIdentity(&m_Transform[(int)CameraCt::VIEW]);

    for (int i = 0; i < (int)CameraAx::END; i++)
    {
        memcpy(&m_Transform[(int)CameraCt::VIEW](i, 0), &m_vAxis[i], sizeof(_vector3));
    }
    
    D3DXMatrixTranspose(&m_Transform[(int)CameraCt::VIEW], &m_Transform[(int)CameraCt::VIEW]);

    // 연산된 결과의 축은 x,y,z,가 세로 차례로 구성되어야 하는데 memcpy를 통해서 순서대로 값을 대입한 경우
    // 가로 순서로 축이 구성되므로, 전치 행렬을 통해서 세로로 정렬

    _float DotX = -D3DXVec3Dot(&m_Pos, &m_vAxis[(int)CameraAx::X]);
    _float DotY = -D3DXVec3Dot(&m_Pos, &m_vAxis[(int)CameraAx::Y]);
    _float DotZ = -D3DXVec3Dot(&m_Pos, &m_vAxis[(int)CameraAx::Z]);

    // 카메라의 축과 원점으로부터의 카메라 객체까지의 벡터를 내적
    // 내적의 결과는 acosf 를 통해서 라디안으로 변환
    // 이 결과 값은 디바이스에서 정점의 위치를 변환하는데 사용

    m_Transform[(int)CameraCt::VIEW] = _matrix
    (
        m_vAxis[(int)CameraAx::X].x, m_vAxis[(int)CameraAx::Y].x, m_vAxis[(int)CameraAx::Z].x, 0.f,
        m_vAxis[(int)CameraAx::X].y, m_vAxis[(int)CameraAx::Y].y, m_vAxis[(int)CameraAx::Z].y, 0.f,
        m_vAxis[(int)CameraAx::X].z, m_vAxis[(int)CameraAx::Y].z, m_vAxis[(int)CameraAx::Z].z, 0.f,
        DotX, DotY, DotZ, 1.f
    );

    // 실제 뷰행렬
    // _11 ~ _33 까지는 카과메라의 축
    // _41 ~ _43 까지는 내저의 결과
}

void Camera::CalculateProj()
{
}


