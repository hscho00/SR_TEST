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
    m_vAxis[(int)CameraAx::Z] = m_LookAt - m_Pos;   // ���� �ٶ󺸴� ��ġ���� ī�޶��� ��ġ������ ������ ����
    D3DXVec3Normalize(&m_vAxis[(int)CameraAx::Z], &m_vAxis[(int)CameraAx::Z]);

    // ī�޶�� �ٶ󺸴� ���� ������ �Ÿ� ���͸� ���� �� �̸� ����ȭ �ϸ� ī�޶��� z�࿡ ���� ���� ����
    // Look�� Pos�� �׻� ������ �� �ۿ� �����Ƿ�, �̸� �������� Z���� ����
    // �� Z���� ������ ��鿡 ������ ��ħ

    D3DXVec3Cross(&m_vAxis[(int)CameraAx::X], &m_vAxis[(int)CameraAx::Y], &m_vAxis[(int)CameraAx::Z]);
    D3DXVec3Normalize(&m_vAxis[(int)CameraAx::X], &m_vAxis[(int)CameraAx::X]);

    // Z���� ���ϸ�, X���� Z��� Y���� ������ ���� ���س� ������ ��
    // ���ʿ��� Y���� ���� ���ص� ���°� �ƴϹǷ�, �ӽ÷� ������ (0, 1, 0) ���͸� �ӽ� Y������ ��� X���� ���

    D3DXVec3Cross(
        &m_vAxis[(int)CameraAx::Y],
        &m_vAxis[(int)CameraAx::Z],
        &m_vAxis[(int)CameraAx::X]);

    D3DXVec3Normalize(
        &m_vAxis[(int)CameraAx::Y],
        &m_vAxis[(int)CameraAx::Y]
    );

    // X��� Z���� �̿��� �ӽ� ���̾��� Y���� ����
} // ī�޶� ���ؿ��� x,y,z ���� ����

void Camera::CalculateView()
{
    D3DXMatrixIdentity(&m_Transform[(int)CameraCt::VIEW]);

    for (int i = 0; i < (int)CameraAx::END; i++)
    {
        memcpy(&m_Transform[(int)CameraCt::VIEW](i, 0), &m_vAxis[i], sizeof(_vector3));
    }
    
    D3DXMatrixTranspose(&m_Transform[(int)CameraCt::VIEW], &m_Transform[(int)CameraCt::VIEW]);

    // ����� ����� ���� x,y,z,�� ���� ���ʷ� �����Ǿ�� �ϴµ� memcpy�� ���ؼ� ������� ���� ������ ���
    // ���� ������ ���� �����ǹǷ�, ��ġ ����� ���ؼ� ���η� ����

    _float DotX = -D3DXVec3Dot(&m_Pos, &m_vAxis[(int)CameraAx::X]);
    _float DotY = -D3DXVec3Dot(&m_Pos, &m_vAxis[(int)CameraAx::Y]);
    _float DotZ = -D3DXVec3Dot(&m_Pos, &m_vAxis[(int)CameraAx::Z]);

    // ī�޶��� ��� �������κ����� ī�޶� ��ü������ ���͸� ����
    // ������ ����� acosf �� ���ؼ� �������� ��ȯ
    // �� ��� ���� ����̽����� ������ ��ġ�� ��ȯ�ϴµ� ���

    m_Transform[(int)CameraCt::VIEW] = _matrix
    (
        m_vAxis[(int)CameraAx::X].x, m_vAxis[(int)CameraAx::Y].x, m_vAxis[(int)CameraAx::Z].x, 0.f,
        m_vAxis[(int)CameraAx::X].y, m_vAxis[(int)CameraAx::Y].y, m_vAxis[(int)CameraAx::Z].y, 0.f,
        m_vAxis[(int)CameraAx::X].z, m_vAxis[(int)CameraAx::Y].z, m_vAxis[(int)CameraAx::Z].z, 0.f,
        DotX, DotY, DotZ, 1.f
    );

    // ���� �����
    // _11 ~ _33 ������ ī���޶��� ��
    // _41 ~ _43 ������ ������ ���
}

void Camera::CalculateProj()
{
}


