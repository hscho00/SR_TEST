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
    _lpd3dd9 pDevice,
    const _vector3& vPos,
    const _vector3& vLookAt,
    const PROJ& Proj)
{

    m_pInstance->Ready_Camera(pDevice, vPos, vLookAt, Proj);
    
    //View
    return m_pInstance;
}

void Camera::Free()
{
}

void Camera::Ready_Camera(_lpd3dd9 pDevice, const _vector3& vPos, const _vector3& vLookAt, const PROJ& Proj)
{
    m_pDevice = pDevice;
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
    Free();
    delete this;
    return 0;
}

_uint Camera::UpdateCamera()
{
    m_bMove = CalculateMove();
    m_bRot = CalculateRot();

    if (m_bMove || m_bRot)
    {
        CalculateView();
    }
    
    m_bMove = FALSE;
    m_bRot = FALSE;

    D3DXMATRIX matView;

    matView = Camera::Get_Instance()->Get_Transform(Camera::CameraCt::VIEW);
    if (FAILED(m_pDevice->SetTransform(D3DTS_VIEW, &matView)))
        return E_FAIL;
    
    return _uint();
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
    float Aspect = m_Proj.fWidth / m_Proj.fHeight;
    // ������ â�� ���μ��� ����

    float h = 1 / tanf(m_Proj.fFovy / 2.f);
    float w = h / Aspect;

    // �þ߰��� ���� ������ ������ ����ϹǷ�, h�� ��ü
    // ���� ������ �⺻������ ���簢���� ������ ���߿��� �ֱ� ������,
    // ���� ���꿡 �߰������� ������ â�� ���� ������ ������ �ݿ����־�� ��

    float a = m_Proj.fFar / (m_Proj.fFar - m_Proj.fNear);
    float b = -m_Proj.fNear * a;

    m_Transform[(_int)CameraCt::PROJ] = _matrix
    {
        w,  0,  0,  0,
        0,  h,  0,  0,
        0,  0,  a,  1,
        0,  0,  b,  0
    };

    
}

BOOL Camera::CalculateMove()
{
    BOOL MoveCheck = FALSE;

    _vector3 vMove = _vector3(0.f, 0.f, 0.f);    // �̵��� ����

    if (GetAsyncKeyState('W') & 0x8000)
    {
        vMove.z += m_MoveSpeed;
        MoveCheck = TRUE;
    }
    if (GetAsyncKeyState('S') & 0x8000)
    {
        vMove.z -= m_MoveSpeed;
        MoveCheck = TRUE;
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
        vMove.x -= m_MoveSpeed;
        MoveCheck = TRUE;
    }
    if (GetAsyncKeyState('D') & 0x8000)
    {
        vMove.x += m_MoveSpeed;
        MoveCheck = TRUE;
    }
    if (GetAsyncKeyState('Q') & 0x8000)
    {
        m_Pos += m_vAxis[(_int)CameraAx::Z]*0.03f;
        MoveCheck = TRUE;
    }
    if (GetAsyncKeyState('E') & 0x8000)
    {
        m_Pos -= m_vAxis[(_int)CameraAx::Z] * 0.03f;
        MoveCheck = TRUE;
    }

    m_Pos += vMove;
    m_LookAt += vMove;

    return MoveCheck;
}

BOOL Camera::CalculateRot()
{
    BOOL m_bRight = FALSE;
    BOOL m_bUp = FALSE;

    _matrix     matRot;         // ȸ������� ���� ����
    _vector3    vDist;          // Look�� eye�� ���̸� ���� ���� 
        
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        m_Angle.y += 0.0001f;
        m_bRight = TRUE;
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        m_Angle.y -= 0.0001f;
        m_bRight = TRUE;
    }

    if (m_bRight)
    {
        D3DXMatrixRotationY(&matRot, m_Angle.y);
        memcpy(&matRot._41, &m_LookAt, sizeof(_vector3));
        vDist = m_Pos - m_LookAt;

        for (int i = 0; i < (_int)CameraAx::END; i++)
        {
            D3DXVec3TransformNormal(&m_vAxis[i], &m_vAxis[i], &matRot);
            D3DXVec3Normalize(&m_vAxis[i], &m_vAxis[i]);
        }

        D3DXVec3TransformCoord(&m_Pos, &vDist, &matRot);

    }



    return (m_bRight | m_bUp);
}


