//------------------------------------------------------- ----------------------
// File: Mesh.h
//-----------------------------------------------------------------------------

#pragma once
#include "Vertex.h"
#include "Timer.h"


typedef struct tagAABB
{
//�ٿ�� �ڽ��� �ּ����� �ִ����� ��Ÿ���� �����̴�.
	D3DXVECTOR3 m_d3dxvMinimum;
	D3DXVECTOR3 m_d3dxvMaximum;

//�� ���� �ٿ�� �ڽ��� ���Ѵ�.
	void Union(D3DXVECTOR3& d3dxvMinimum, D3DXVECTOR3& d3dxvMaximum);
//�ٿ�� �ڽ��� 8���� �������� ��ķ� ��ȯ�ϰ� �ּ����� �ִ����� �ٽ� ����Ѵ�.
	void Transform(D3DXMATRIX *pd3dxmtxTransform);
} AABB;




/////////////////////////////////////////////////////////////////////////////////////////////////
//
class CMesh
{
public:
    CMesh(ID3D11Device *pd3dDevice);
    virtual ~CMesh();

	int								m_nReferences;
	void AddRef();
	void Release();

	D3D11_PRIMITIVE_TOPOLOGY		m_d3dPrimitiveTopology;

	ID3D11Buffer					*m_pd3dVertexBuffer;
	UINT							m_nVertices;
	UINT							m_nStride;
	UINT							m_nOffset;

	ID3D11Buffer					*m_pd3dIndexBuffer;
	UINT							m_nIndices;
	UINT							m_nStartIndex;
	int								m_nBaseVertex;

	ID3D11RasterizerState			*m_pd3dRasterizerState;

	AABB m_bcBoundingCube;

	virtual void SetRasterizerState(ID3D11Device *pd3dDevice);
	virtual void Render(ID3D11DeviceContext *pd3dImmediateDeviceContext);
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//
class CCubeMesh : public CMesh
{
public:
    CCubeMesh(ID3D11Device *pd3dDevice, float fWidth=2.0f, float fHeight=2.0f, float fDepth=2.0f, D3DXCOLOR d3dxColor=D3DXCOLOR(1.0f,1.0f,0.0f,0.0f));
    virtual ~CCubeMesh();

	virtual void SetRasterizerState(ID3D11Device *pd3dDevice);
	virtual void Render(ID3D11DeviceContext *pd3dImmediateDeviceContext);
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//


class CMeshIlluminated : public CMesh
{
public:
    CMeshIlluminated(ID3D11Device *pd3dDevice);
    virtual ~CMeshIlluminated();

public:
//������ ���Ե� �ﰢ���� �������͸� ����ϴ� �Լ��̴�.
	D3DXVECTOR3 CalculateTriAngleNormal(BYTE *pVertices, USHORT nIndex0, USHORT nIndex1, USHORT nIndex2);
	void SetTriAngleListVertexNormal(BYTE *pVertices);
//������ ���������� ����� ����ϴ� �Լ��̴�.
	void SetAverageVertexNormal(BYTE *pVertices, WORD *pIndices, int nPrimitives, int nOffset, bool bStrip);
	void CalculateVertexNormal(BYTE *pVertices, WORD *pIndices);

	virtual void Render(ID3D11DeviceContext *pd3dImmediateDeviceContext);
};
class CCubeMeshIlluminated : public CMeshIlluminated
{
public:
	CCubeMeshIlluminated(ID3D11Device *pd3dDevice, float fWidth=2.0f, float fHeight=2.0f, float fDepth=2.0f);
	virtual ~CCubeMeshIlluminated();

	virtual void SetRasterizerState(ID3D11Device *pd3dDevice);
	virtual void Render(ID3D11DeviceContext *pd3dImmediateDeviceContext);
};

class CTexturedCubeMesh : public CMesh
{
public:
	CTexturedCubeMesh(ID3D11Device *pd3dDevice, float fWidth, float fHeight, float fDepth);
	virtual ~CTexturedCubeMesh();

	virtual void SetRasterizerState(ID3D11Device *pd3dDevice);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);
};
class CCubeMeshIlluminatedTextured : public CMeshIlluminated
{
public:
    CCubeMeshIlluminatedTextured(ID3D11Device *pd3dDevice, float fWidth=2.0f,       float fHeight=2.0f, float fDepth=2.0f);
    virtual ~CCubeMeshIlluminatedTextured();

    virtual void SetRasterizerState(ID3D11Device *pd3dDevice);
    virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);
};
