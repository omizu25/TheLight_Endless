//**************************************************
//
// Hackathon ( light.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h" 
#include "fade.h"
#include "input.h"
#include "select.h"
#include "mode.h"
#include "rectangle.h"
#include "light.h"
#include "color.h"
#include "sound.h"
#include "texture.h"
#include "utility.h"
#include "game.h"
#include "effect.h"
#include "player.h"
#include "time.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_LIGHT = 16;		// ���C�g�̍ő吔
const int	MAX_TIME = 90;		// �^�C���̍ő�l
const int	REPEAT_TIME = 30;	// �^�C���̌J��Ԃ�
const float	LIGHT_SIZE = 50.0f;	// ���C�g�̃T�C�Y

typedef enum
{
	LIGHT_RED = 0,	// ��
	LIGHT_GREEN,	// ��
	LIGHT_BLUE,		// ��
	LIGHT_YELLOW,	// ���F
	LIGHT_MAX,
}LIGHT;
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int		s_nIdxSelect;			// ���j���[�̔z��̃C���f�b�N�X
int		s_nIdxFrame;			// �g�̔z��̃C���f�b�N�X
int		s_nTime;				// �^�C��
int		s_nIdxColor[MAX_LIGHT];	// �F�̔ԍ�
TEXTURE	s_aTexture[LIGHT_MAX];	// �e�N�X�`��
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitLight(void)
{
	s_aTexture[LIGHT_RED] = TEXTURE_Red;
	s_aTexture[LIGHT_GREEN] = TEXTURE_Green;
	s_aTexture[LIGHT_BLUE] = TEXTURE_Bule;
	s_aTexture[LIGHT_YELLOW] = TEXTURE_Yellow;

	{// �g
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = 0.0f;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.35f;
		select.fBottom = SCREEN_HEIGHT * 0.35f;
		select.fWidth = LIGHT_SIZE * 1.5f;
		select.fHeight = LIGHT_SIZE * 1.5f;
		select.bSort = false;

		for (int i = 0; i < MAX_LIGHT; i++)
		{
			select.texture[i] = TEXTURE_Hackathon_Ring;
		}

		// �Z���N�g�̐ݒ�
		s_nIdxFrame = SetSelect(select);
	}

	{// ���j���[
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = 0.0f;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.35f;
		select.fBottom = SCREEN_HEIGHT * 0.35f;
		select.fWidth = LIGHT_SIZE;
		select.fHeight = LIGHT_SIZE;
		select.bSort = false;

		for (int i = 0; i < MAX_LIGHT; i++)
		{
			select.texture[i] = TEXTURE_effect_000;
		}

		// �Z���N�g�̐ݒ�
		s_nIdxSelect = SetSelect(select);
	}

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// ��`�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxFrame, i, false);
	}

	// ��`�̕`�悷�邩�ǂ���
	SetDrawSelect(s_nIdxFrame, 0, true);

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		s_nIdxColor[i] = IntRandam(LIGHT_MAX, 0);

		// �Z���N�g�̃e�N�X�`���̐ݒ�
		ChangeTextuteSelect(s_nIdxSelect, i, s_aTexture[s_nIdxColor[i]]);
	}

	// ���}���u
	s_nIdxColor[0] = IntRandam(LIGHT_MAX, 0);

	// �Z���N�g�̃e�N�X�`���̐ݒ�
	ChangeTextuteSelect(s_nIdxSelect, 0, s_aTexture[s_nIdxColor[0]]);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitLight(void)
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateLight(void)
{
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawLight(void)
{
}

//--------------------------------------------------
// �F�̎擾
//--------------------------------------------------
int GetColorLight(int nNowLight)
{
	assert(nNowLight >= 0 && nNowLight < MAX_LIGHT);

	return s_nIdxColor[nNowLight];
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CorrectAnswerLight(void)
{
	for (int i = 0; i < MAX_LIGHT - 1; i++)
	{
		s_nIdxColor[i] = s_nIdxColor[i + 1];
	}

	s_nIdxColor[MAX_LIGHT - 1] = IntRandam(LIGHT_MAX, 0);

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// �Z���N�g�̃e�N�X�`���̐ݒ�
		ChangeTextuteSelect(s_nIdxSelect, i, s_aTexture[s_nIdxColor[i]]);
	}
}