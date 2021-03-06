﻿//------------------------------------------------------- ----------------------
// File: Mesh.h
//-----------------------------------------------------------------------------

#pragma once
#include "Vertex.h"
#include "Timer.h"
#include "AABB.h"
#include "Animation.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
//基本的なメッシュです。
class CMesh
{
public:
	CMesh(ID3D11Device *pd3dDevice);
	virtual ~CMesh();

	void AddRef();
	void Release();

	virtual void SetRasterizerState(ID3D11Device *pd3dDevice);
	virtual void Render(ID3D11DeviceContext *pd3dDeviceContext);
	virtual void RenderInstanced(ID3D11DeviceContext *pd3dDeviceContext, int nInstances, int nStartInstance);
	virtual void AppendVertexBuffer(int nBuffers, ID3D11Buffer **pd3dBuffer, UINT *nStride, UINT *nOffset);

	ID3D11Buffer* CreateVertexBuffer(ID3D11Device *pd3dDevice, int nObjects, UINT nBufferStride, void *pBufferData);
	GET_SET_FUNC_IMPL(AABB, BoundingCube, m_bcBoundingCube);

protected:

	int								m_nReferences;

	D3D11_PRIMITIVE_TOPOLOGY		m_d3dPrimitiveTopology;
	ID3D11RasterizerState			*m_pd3dRasterizerState;

	UINT							m_nVertices;
	UINT							m_nIndices;

	UINT							*m_nStride;
	UINT							*m_nOffset;

	ID3D11Buffer					**m_ppd3dVertexBuffers;
	UINT							m_nVertexBuffers;

	ID3D11Buffer					*m_pd3dIndexBuffer;

	AABB							m_bcBoundingCube;


};

/////////////////////////////////////////////////////////////////////////////////////////////////
//テクスチャを持っているメッシュです。
class CMeshTextured : public CMesh
{
public:
	CMeshTextured(ID3D11Device *pd3dDevice);
	virtual ~CMeshTextured();

protected:
	ID3D11Buffer					*m_pd3dTexCoordBuffer;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//ライティングの影響を受けるメッシュです。
class CMeshIlluminated : public CMesh
{
public:
	CMeshIlluminated(ID3D11Device *pd3dDevice);
	virtual ~CMeshIlluminated();
	//頂点が含まれている三角形の法線ベクトルを計算する関数
	D3DXVECTOR3 CalculateTriAngleNormal(BYTE *pVertices, UINT nIndex0, UINT nIndex1, UINT nIndex2);
	void SetTriAngleListVertexNormal(BYTE *pVertices);
	//頂点の法線ベクトルの平均を計算する関数
	void SetAverageVertexNormal(BYTE *pVertices, UINT *pIndices, int nPrimitives, int nOffset, bool bStrip);
	void CalculateVertexNormal(BYTE *pVertices, UINT *pIndices);
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//ライティングの影響を受けるキューブメッシュです。
class CCubeMeshIlluminated : public CMeshIlluminated
{
public:
	CCubeMeshIlluminated(ID3D11Device *pd3dDevice, float fWidth = 2.0f, float fHeight = 2.0f, float fDepth = 2.0f);
	virtual ~CCubeMeshIlluminated();
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//テクスチャを持っており、ライティングの影響も受けるキューブメッシュです。
class CCubeMeshIlluminatedTextured : public CMeshIlluminated
{
public:
	CCubeMeshIlluminatedTextured(ID3D11Device *pd3dDevice, float fWidth = 2.0f, float fHeight = 2.0f, float fDepth = 2.0f, float fRepeatUV = 1.0f);
	virtual ~CCubeMeshIlluminatedTextured();
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//スカイボックスメッシュです。
class CSkyBoxMesh : public CMeshTextured
{
public:
	CSkyBoxMesh(ID3D11Device *pd3dDevice, float fWidth = 20.0f, float fHeight = 20.0f, float fDepth = 20.0f);
	virtual ~CSkyBoxMesh();
};

/////////////////////////////////////////////////////////////////////////////////////////////////
//テクスチャを持っており、光の影響を受けるFBXモデルのメッシュです。

class CFbxMeshIlluminatedTextured : public CMesh
{
public:
	CFbxMeshIlluminatedTextured(ID3D11Device *pd3dDevice, FbxManager *pFbxSdkManager, string filename, float fScaleMultiplier = 1.0f, bool _bHasAnimation = false);
	virtual ~CFbxMeshIlluminatedTextured();

	virtual void SetRasterizerState(ID3D11Device *pd3dDevice);

	void SetBoneNameIndex(FbxNode *pNode, vector<string> *pBoneName);
	void SetBoneAtVertices(FbxNode *pNode, unordered_map<int, vector<pair<UINT, float>>> *pClusterIndexVector, vector<string> *pBoneName);
	void SetVertices(FbxNode *pNode, vector<CBoneWeightVertex> *pVertexVector, unordered_map<int, vector<pair<UINT, float>>> *pClusterIndexVector);

	
private:
	bool						m_bHasAnimation;
};