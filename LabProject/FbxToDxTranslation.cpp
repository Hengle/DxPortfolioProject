#include "stdafx.h"
#include "FbxToDxTranslation.h"

D3DXMATRIX* D3DXMatrixReflect_Fixed(__inout D3DXMATRIX *pOut, __in const D3DXPLANE *pPlane) 
{ 
        D3DXPLANE P; 
        D3DXPlaneNormalize(&P,pPlane); 
 
        *pOut = D3DXMATRIX 
        ( 
        -2.0f * P.a * P.a + 1.0f,  -2.0f * P.b * P.a        , -2.0f * P.c * P.a                 ,  0.0f , 
        -2.0f * P.a * P.b       ,  -2.0f * P.b * P.b + 1.0f , -2.0f * P.c * P.b                 ,  0.0f , 
        -2.0f * P.a * P.c       ,  -2.0f * P.b * P.c        , -2.0f * P.c * P.c + 1.0f			,  0.0f , 
        -2.0f * P.a * P.d       ,  -2.0f * P.b * P.d        , -2.0f * P.c * P.d                 ,  1.0f  
        ); 
 
        return pOut; 
}
FbxAMatrix* D3DXMatrixReflect_Fixed(__inout FbxAMatrix *pOut, __in const D3DXPLANE *pPlane) 
{ 
        D3DXPLANE P; 
        D3DXPlaneNormalize(&P,pPlane); 
 
		pOut->mData[0][0] = -2.0f * P.a * P.a + 1.0f;
		pOut->mData[0][1] = -2.0f * P.b * P.a;
		pOut->mData[0][2] =  -2.0f * P.c * P.a ;
		pOut->mData[0][3] =  0.0f;
		pOut->mData[1][0] = -2.0f * P.a * P.b ;
		pOut->mData[1][1] = -2.0f * P.b * P.b + 1.0f;
		pOut->mData[1][2] = -2.0f * P.c * P.b;
		pOut->mData[1][3] = 0.0f;
		pOut->mData[2][0] = -2.0f * P.a * P.c;
		pOut->mData[2][1] = -2.0f * P.b * P.c;
		pOut->mData[2][2] = -2.0f * P.c * P.c + 1.0f;
		pOut->mData[2][3] =  0.0f;
		pOut->mData[3][0] = -2.0f * P.a * P.d;
        pOut->mData[3][1] = -2.0f * P.b * P.d;
		pOut->mData[3][2] = -2.0f * P.c * P.d;
		pOut->mData[3][3] = 1.0f;

 
        return pOut; 
}




FbxAMatrix GetGeometry(FbxNode* pNode)  
{
    const FbxVector4 lT = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
    const FbxVector4 lR = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
    const FbxVector4 lS = pNode->GetGeometricScaling(FbxNode::eSourcePivot);

    return FbxAMatrix(lT, lR, lS);
}

FbxAMatrix GetPoseMatrix(FbxPose* pPose, int pNodeIndex)
{
    FbxAMatrix lPoseMatrix;
    FbxMatrix lMatrix = pPose->GetMatrix(pNodeIndex);

    memcpy((double*)lPoseMatrix, (double*)lMatrix, sizeof(lMatrix.mData));

    return lPoseMatrix;
}

D3DXMATRIX& GetD3DMatrix( FbxAMatrix & SrcFbxMtx )
{
	D3DXMATRIX Dst;
	Dst._11 = (float)SrcFbxMtx.mData[0][0];
	Dst._12 = (float)SrcFbxMtx.mData[0][1];
	Dst._13 = (float)SrcFbxMtx.mData[0][2];
	Dst._14 = (float)SrcFbxMtx.mData[0][3];
	Dst._21 = (float)SrcFbxMtx.mData[1][0];
	Dst._22 = (float)SrcFbxMtx.mData[1][1];
	Dst._23 = (float)SrcFbxMtx.mData[1][2];
	Dst._24 = (float)SrcFbxMtx.mData[1][3];
	Dst._31 = (float)SrcFbxMtx.mData[2][0];
	Dst._32 = (float)SrcFbxMtx.mData[2][1];
	Dst._33 = (float)SrcFbxMtx.mData[2][2];
	Dst._34 = (float)SrcFbxMtx.mData[2][3];
	Dst._41 = (float)SrcFbxMtx.mData[3][0];
	Dst._42 = (float)SrcFbxMtx.mData[3][1];
	Dst._43 = (float)SrcFbxMtx.mData[3][2];
	Dst._44 = (float)SrcFbxMtx.mData[3][3];
	return Dst;
}

FbxAMatrix& GetFbxMatrix( D3DXMATRIX & SrcFbxMtx )
{
	FbxAMatrix Dst;
	Dst.mData[0][0] = (float)SrcFbxMtx._11;
	Dst.mData[0][1] = (float)SrcFbxMtx._12;
	Dst.mData[0][2] = (float)SrcFbxMtx._13;
	Dst.mData[0][3] = (float)SrcFbxMtx._14;
	Dst.mData[1][0] = (float)SrcFbxMtx._21;
	Dst.mData[1][1] = (float)SrcFbxMtx._22;
	Dst.mData[1][2] = (float)SrcFbxMtx._23;
	Dst.mData[1][3] = (float)SrcFbxMtx._24;
	Dst.mData[2][0] = (float)SrcFbxMtx._31;
	Dst.mData[2][1] = (float)SrcFbxMtx._32;
	Dst.mData[2][2] = (float)SrcFbxMtx._33;
	Dst.mData[2][3] = (float)SrcFbxMtx._34;
	Dst.mData[3][0] = (float)SrcFbxMtx._41;
	Dst.mData[3][1] = (float)SrcFbxMtx._42;
	Dst.mData[3][2] = (float)SrcFbxMtx._43;
	Dst.mData[3][3] = (float)SrcFbxMtx._44;
	return Dst;
}

FbxAMatrix GetGlobalPosition(FbxNode* pNode, const FbxTime& pTime, FbxPose* pPose, FbxAMatrix* pParentGlobalPosition)
{
    FbxAMatrix lGlobalPosition;
    bool       lPositionFound = false;

    if (pPose) // ��� ������ 
    {
        int lNodeIndex = pPose->Find(pNode); // ������ ����� �ε����� ã�´�.

        if (lNodeIndex > -1) // �ε����� 0�̻��̸�
        {
            // The bind pose is always a global matrix. ���ε� ����� ������ �۷ι� ��Ʈ�����̴�.
            // If we have a rest pose, we need to check if it is ���� �츮�� �ٸ� ��� ������ ������ �츮�� �۷ι��̳� ���� ������ ����Ǿ��ִ��� Ȯ���Ѵ�.
            // stored in global or local space.
            if (pPose->IsBindPose() || !pPose->IsLocalMatrix(lNodeIndex)) // ���ε� �����̰ų� ���ø�Ʈ������ �ƴҶ�
            {
                lGlobalPosition = GetPoseMatrix(pPose, lNodeIndex); // ������ ��Ʈ������ �����´�.
            }
            else
            {
                // We have a local matrix, we need to convert it to   ���� ��Ʈ������ �ִٸ� �۷ι� ���� ��Ʈ������ ��ȯ�ؾ��Ѵ�.
                // a global space matrix.
                FbxAMatrix lParentGlobalPosition; // �θ�۷ι���ġ

                if (pParentGlobalPosition) // �θ�۷ι���ġ�� �����Ͱ� ������
                {
                    lParentGlobalPosition = *pParentGlobalPosition; // �θ�۷ι���ġ�� �ٷ� �־���
                }
                else
                {
                    if (pNode->GetParent()) // ����� �θ� �ִ��� Ȯ��
                    {
                        lParentGlobalPosition = GetGlobalPosition(pNode->GetParent(), pTime, pPose); // ���� �θ��� �������� �޾ƿ�
                    }
                }

                FbxAMatrix lLocalPosition = GetPoseMatrix(pPose, lNodeIndex); // ������ �ε����� ���� ������
                lGlobalPosition = lParentGlobalPosition * lLocalPosition; // �۷ι��� ��Ʈ�� ������ ��
            }

            lPositionFound = true;
        }
    }

    if (!lPositionFound)
    {
        // There is no pose entry for that node, get the current global position instead.  ��忡 ��� ���ٸ� ���� �۷ι� ��ġ�� ��Ź޾ƿ�
        // Ideally this would use parent global position and local position to compute the global position. �۷ι���ġ�� ����ϱ����� �θ�۷ι���ġ�� ������ġ�� ���ȴ�.
        // Unfortunately the equation
        // lGlobalPosition = pParentGlobalPosition * lLocalPosition  
        // does not hold when inheritance type is other than "Parent" (RSrs).
        // To compute the parent rotation and scaling is tricky in the RrSs and Rrs cases. RSrs�� Ʈ������ �θ����⸦ ����ϴ°�??
        lGlobalPosition = pNode->EvaluateGlobalTransform(pTime);
    }

    return lGlobalPosition;
}

D3DXMATRIX GetD3DMatrixFromPxMat(PxMat44* pPxMat){
	D3DXMATRIX Dst;
	Dst._11 = pPxMat->column0.x;
	Dst._12 = pPxMat->column0.y;
	Dst._13 = pPxMat->column0.z;
	Dst._14 = pPxMat->column0.w;
	Dst._21 = pPxMat->column1.x;
	Dst._22 = pPxMat->column1.y;
	Dst._23 = pPxMat->column1.z;
	Dst._24 = pPxMat->column1.w;
	Dst._31 = pPxMat->column2.x;
	Dst._32 = pPxMat->column2.y;
	Dst._33 = pPxMat->column2.z;
	Dst._34 = pPxMat->column2.w;
	Dst._41 = pPxMat->column3.x;
	Dst._42 = pPxMat->column3.y;
	Dst._43 = pPxMat->column3.z;
	Dst._44 = pPxMat->column3.w;

	return Dst;

}