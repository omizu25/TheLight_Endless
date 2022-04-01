//**************************************************
// 
// Hackathon ( rectangle.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "fanangle.h"
#include "color.h"
#include "texture.h"
#include "utility.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_FANANGLE = 1024;	// ��`�̍ő吔
const int	NUM_VERTEX = 100;		// ���_�̐�
const int	NUM_POLYGON = NUM_VERTEX - 2;		// �|���S���̐�

typedef struct
{
	LPDIRECT3DTEXTURE9		pTexture;	// �e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9	pVtxBuff;	// ���_�o�b�t�@
	int						nMaxBuff;	// �\�����钸�_�o�b�t�@�̍ő�l
	bool					bUse;		// �g�p���Ă��邩�ǂ���
	bool					bDraw;		// �`�悷�邩�ǂ���
	bool					bAdd;		// ���Z�������邩�ǂ���
}MyFanangle;
}// namespace�͂����܂�

 //==================================================
 // �X�^�e�B�b�N�ϐ�
 //==================================================
namespace
{
MyFanangle	s_aFanangle[MAX_FANANGLE];	// ��`�̏��
}// namespace�͂����܂�

 //--------------------------------------------------
 // ������
 //--------------------------------------------------
void InitFanangle(void)
{
	// �������̃N���A
	memset(s_aFanangle, 0, sizeof(s_aFanangle));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitFanangle(void)
{
	for (int i = 0; i < MAX_FANANGLE; i++)
	{
		MyFanangle *pFanangle = &s_aFanangle[i];

		if (pFanangle->pVtxBuff != NULL)
		{// ���_�o�b�t�@�̉��
			pFanangle->pVtxBuff->Release();
			pFanangle->pVtxBuff = NULL;
		}
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawFanangle(void)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < MAX_FANANGLE; i++)
	{
		MyFanangle *pFanangle = &s_aFanangle[i];

		if (!pFanangle->bUse || !pFanangle->bDraw)
		{// �g�p���Ă��Ȃ��A�`�悷�邵�Ȃ�
			continue;
		}

		/*�� �g�p���Ă���A�`�悷�� ��*/

		if (pFanangle->bAdd)
		{// ���Z��������
		 // �����_�[�X�e�[�g�̐ݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, pFanangle->pVtxBuff, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pFanangle->pTexture);

		// �|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLEFAN,			// �v���~�e�B�u�̎��
			0,							// �`�悷��ŏ��̒��_�C���f�b�N�X
			pFanangle->nMaxBuff);		// �v���~�e�B�u(�|���S��)��

										// �e�N�X�`���̉���
		pDevice->SetTexture(0, NULL);

		if (pFanangle->bAdd)
		{// ���Z��������
		 // �����_�[�X�e�[�g�����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
int SetFanangle(TEXTURE texture)
{
	// �ݒ� [ �e�N�X�`������ ]
	return SetFanangleWithTex(GetTexture(texture));
}

//--------------------------------------------------
// �ݒ� [ �e�N�X�`������ ]
//--------------------------------------------------
int SetFanangleWithTex(LPDIRECT3DTEXTURE9 pTexture)
{
	for (int i = 0; i < MAX_FANANGLE; i++)
	{
		MyFanangle *pFanangle = &s_aFanangle[i];

		if (pFanangle->bUse)
		{// �g�p���Ă���
			continue;
		}

		/*�� �g�p���Ă��Ȃ� ��*/

		pFanangle->pTexture = pTexture;
		pFanangle->nMaxBuff = NUM_POLYGON;
		pFanangle->bUse = true;
		pFanangle->bDraw = true;
		pFanangle->bAdd = false;

		// ���_�o�b�t�@�̐���
		GetDevice()->CreateVertexBuffer(
			sizeof(VERTEX_2D) * NUM_VERTEX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&pFanangle->pVtxBuff,
			NULL);

		VERTEX_2D *pVtx = NULL;		// ���_���ւ̃|�C���^

		// ���_�������b�N���A���_���ւ̃|�C���^���擾
		pFanangle->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�o�b�t�@���A�����b�N����
		pFanangle->pVtxBuff->Unlock();

		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		float fLength = 0.0f;

		// �ʒu�̐ݒ�
		SetPosFanangle(i, pos, fLength,true);

		//�F�̐ݒ�
		SetColorFanangle(i, GetColor(COLOR_WHITE));

		D3DXVECTOR2 texU = D3DXVECTOR2(0.0f, 1.0f);
		D3DXVECTOR2 texV = D3DXVECTOR2(0.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		SetTexFanangle(i);

		return i;
	}

	assert(false);
	return -1;
}

//--------------------------------------------------
// �g�p����߂�
//--------------------------------------------------
void StopUseFanangle(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	pFanangle->bUse = false;

	if (pFanangle->pVtxBuff != NULL)
	{// ���_�o�b�t�@�̉��
		pFanangle->pVtxBuff->Release();
		pFanangle->pVtxBuff = NULL;
	}
}

//--------------------------------------------------
// �ʒu�̐ݒ�
//--------------------------------------------------
void SetPosFanangle(int nIdx, const D3DXVECTOR3 &pos, const float &fLength, bool bSide)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	VERTEX_2D *pVtx = NULL;		// ���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffFanangle(nIdx);

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = pos;
	DEBUG_PRINT("%f	%f\n", pVtx[0].pos.x, pVtx[0].pos.y);

	for (int i = 1; i < NUM_VERTEX; i++)
	{
		float fRot = (D3DX_PI * 2.0f / NUM_POLYGON) * (i - 1);

		// �p�x�̐��K��
		NormalizeAngle(&fRot);

		if (bSide)
		{
			// ���_���W�̐ݒ�
			pVtx[i].pos.x = pos.x + cosf(fRot) * fLength;
			pVtx[i].pos.y = pos.y + sinf(fRot) * fLength;
			pVtx[i].pos.z = pos.z;
		
		}
		else
		{
			// ���_���W�̐ݒ�
			pVtx[i].pos.x = pos.x + cosf(fRot) * fLength;
			pVtx[i].pos.y = pos.y + sinf(fRot) * fLength;
			pVtx[i].pos.z = pos.z;
		}

		DEBUG_PRINT("%f	%f\n", pVtx[i].pos.x, pVtx[i].pos.y);
	}

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// ��]����ʒu�̐ݒ�
//--------------------------------------------------
void SetRotationPosFanangle(int nIdx, const D3DXVECTOR3 &pos, float fRot, float fLength, bool bSide)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	VERTEX_2D *pVtx = NULL;		// ���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffFanangle(nIdx);

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = pos;
	DEBUG_PRINT("%f	%f\n", pVtx[0].pos.x, pVtx[0].pos.y);

	for (int i = 1; i < NUM_VERTEX; i++)
	{
		float fRotData = ((D3DX_PI * 2.0f / NUM_POLYGON) * (i - 1)) - fRot;

		// �p�x�̐��K��
		NormalizeAngle(&fRotData);

		if (bSide)
		{
			// ���_���W�̐ݒ�
			pVtx[i].pos.x = pos.x + cosf(fRotData) * fLength;
			pVtx[i].pos.y = pos.y + sinf(fRotData) * fLength;
			pVtx[i].pos.z = pos.z;

		}
		else
		{
			// ���_���W�̐ݒ�
			pVtx[i].pos.x = pos.x + sinf(fRotData) * fLength;
			pVtx[i].pos.y = pos.y + cosf(fRotData) * fLength;
			pVtx[i].pos.z = pos.z;
		}

		DEBUG_PRINT("%f	%f\n", pVtx[i].pos.x, pVtx[i].pos.y);
	}

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------
void SetColorFanangle(int nIdx, const D3DXCOLOR &color)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	VERTEX_2D *pVtx = NULL;		// ���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffFanangle(nIdx);

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	for (int i = 0; i < NUM_VERTEX; i++)
	{
		float fRot = (D3DX_PI * 2.0f / NUM_POLYGON) * (i - 1);

		// �p�x�̐��K��
		NormalizeAngle(&fRot);

		// ���_�J���[�̐ݒ�
		pVtx[i].col = color;
	}

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// �F�̐ݒ�
//--------------------------------------------------
void SetColorCenterFanangle(int nIdx, const D3DXCOLOR & color)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	VERTEX_2D *pVtx = NULL;		// ���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffFanangle(nIdx);

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = color;

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// �e�N�X�`�����W�̐ݒ�
//--------------------------------------------------
void SetTexFanangle(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	VERTEX_2D *pVtx = NULL;		// ���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffFanangle(nIdx);

	// ���_�������b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < NUM_VERTEX; i++)
	{
		// ���_�J���[�̐ݒ�
		pVtx[i].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// �`�悷�邩�ǂ���
//--------------------------------------------------
void SetDrawFanangle(int nIdx, bool bDraw)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pFanangle->bDraw = bDraw;
}

//--------------------------------------------------
// ���Z�������邩�ǂ���
//--------------------------------------------------
void SetAddFanangle(int nIdx, bool bAdd)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pFanangle->bAdd = bAdd;
}

//--------------------------------------------------
// �e�N�X�`���̕ύX
//--------------------------------------------------
void ChangeTextureFanangle(int nIdx, TEXTURE texture)
{
	// �e�N�X�`���̕ύX [ �e�N�X�`������ ]
	ChangeTextureFanangleWithTex(nIdx, GetTexture(texture));
}

//--------------------------------------------------
// �e�N�X�`���̕ύX [ �e�N�X�`������ ]
//--------------------------------------------------
void ChangeTextureFanangleWithTex(int nIdx, LPDIRECT3DTEXTURE9 pTexture)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// �g�p���Ă��Ȃ�
		return;
	}

	/*�� �g�p���Ă��� ��*/

	pFanangle->pTexture = pTexture;
}

//--------------------------------------------------
// ���_�o�b�t�@���擾
//--------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 GetVtxBuffFanangle(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	if (!pFanangle->bUse)
	{// �g�p���Ă��Ȃ�
		return NULL;
	}

	/*�� �g�p���Ă��� ��*/

	return s_aFanangle[nIdx].pVtxBuff;
}

//--------------------------------------------------
// �`�悷��~�̗ʂ�ݒ�
//--------------------------------------------------
void AddDrawFanangle(int nIdx, int nVolume)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];

	pFanangle->nMaxBuff += nVolume;

	if (pFanangle->nMaxBuff > NUM_POLYGON)
	{
		pFanangle->nMaxBuff = NUM_POLYGON;
	}
	else if (pFanangle->nMaxBuff < 0)
	{
		pFanangle->nMaxBuff = 0;
	}
}

void ResetDrawFanangle(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_FANANGLE);

	MyFanangle *pFanangle = &s_aFanangle[nIdx];
	
	pFanangle->nMaxBuff = NUM_POLYGON;
}
