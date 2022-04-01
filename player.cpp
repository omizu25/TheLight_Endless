//**************************************************
//
// Hackathon ( player.cpp )
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
#include "answer.h"
#include "time.h"
#include "bg.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_LIGHT = 16;		// ���C�g�̍ő吔
const float	LIGHT_SIZE = 50.0f;	// ���C�g�̃T�C�Y

typedef enum
{
	LIGHT_COLOR_RED = 0,	// ��
	LIGHT_COLOR_GREEN,		// ��
	LIGHT_COLOR_BLUE,		// ��
	LIGHT_COLOR_YELLOW,		// ���F
	LIGHT_COLOR_MAX,
}LIGHT_COLOR;
}// namespace�͂����܂�

 //==================================================
 // �X�^�e�B�b�N�ϐ�
 //==================================================
namespace
{
COLOR	s_aColor[LIGHT_COLOR_MAX];		// ���C�g�̐F
int		s_nIdxSelect;					// ���j���[�̔z��̃C���f�b�N�X
int		s_nIdxFrame;					// �g�̔z��̃C���f�b�N�X
int		s_nIdxColor[MAX_LIGHT];			// �F�̔ԍ�
TEXTURE	s_aTexture[LIGHT_COLOR_MAX];	// �e�N�X�`��
}// namespace�͂����܂�

 //==================================================
 // �X�^�e�B�b�N�֐��v���g�^�C�v�錾
 //==================================================
namespace
{
void ResetDrawPlayer(void);
}// namespace�͂����܂�

 //--------------------------------------------------
 // ������
 //--------------------------------------------------
void InitPlayer(void)
{
	s_aColor[LIGHT_COLOR_RED] = COLOR_RED;
	s_aColor[LIGHT_COLOR_GREEN] = COLOR_GREEN;
	s_aColor[LIGHT_COLOR_BLUE] = COLOR_BLUE;
	s_aColor[LIGHT_COLOR_YELLOW] = COLOR_YELLOW;
	s_aTexture[LIGHT_COLOR_RED] = TEXTURE_Red;
	s_aTexture[LIGHT_COLOR_GREEN] = TEXTURE_Green;
	s_aTexture[LIGHT_COLOR_BLUE] = TEXTURE_Bule;
	s_aTexture[LIGHT_COLOR_YELLOW] = TEXTURE_Yellow;

	{// �g
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = 0.0f;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.5f;
		select.fBottom = SCREEN_HEIGHT * 0.5f;
		select.fWidth = LIGHT_SIZE;
		select.fHeight = LIGHT_SIZE;
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
		select.fTop = SCREEN_HEIGHT * 0.5f;
		select.fBottom = SCREEN_HEIGHT * 0.5f;
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

	// �`��̃��Z�b�g
	ResetDrawPlayer();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitPlayer(void)
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdatePlayer(void)
{
	if (GetFade() != FADE_NONE)
	{
		return;
	}

	if (!GetAnswer())
	{// �s����
		return;
	}

	if (GetLightKeyTrigger(LIGHT_KEY_RED))
	{// ��
		PlaySound(SOUND_LABEL_SE_SELECT);
		s_nIdxColor[0] = LIGHT_COLOR_RED;

		// �Z���N�g�̃e�N�X�`���̐ݒ�
		ChangeTextuteSelect(s_nIdxSelect, 0, s_aTexture[LIGHT_COLOR_RED]);

		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxSelect, 0, true);

		// �������킹
		SetAnswer(0);

		// ��`�̐F�̐ݒ�
		SetColorRectangle(GetIdxBG(0), GetColor(COLOR_RED));

		// �g�̐ݒ�
		SetFramePlayer(0);

		// �G�t�F�N�g�̐ݒ�
		SetEffect(GetPosSelect(s_nIdxSelect, 0), EFFECT_TYPE_000, GetColor(s_aColor[s_nIdxColor[0]]));
	}
	else if (GetLightKeyTrigger(LIGHT_KEY_GREEN))
	{// ��
		PlaySound(SOUND_LABEL_SE_SELECT);
		s_nIdxColor[0] = LIGHT_COLOR_GREEN;

		// �Z���N�g�̃e�N�X�`���̐ݒ�
		ChangeTextuteSelect(s_nIdxSelect, 0, s_aTexture[LIGHT_COLOR_GREEN]);

		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxSelect, 0, true);

		// �������킹
		SetAnswer(0);

		// ��`�̐F�̐ݒ�
		SetColorRectangle(GetIdxBG(0), GetColor(COLOR_GREEN));

		// �g�̐ݒ�
		SetFramePlayer(0);

		// �G�t�F�N�g�̐ݒ�
		SetEffect(GetPosSelect(s_nIdxSelect, 0), EFFECT_TYPE_000, GetColor(s_aColor[s_nIdxColor[0]]));
	}
	else if (GetLightKeyTrigger(LIGHT_KEY_BLUE))
	{// ��
		PlaySound(SOUND_LABEL_SE_SELECT);
		s_nIdxColor[0] = LIGHT_COLOR_BLUE;

		// �Z���N�g�̃e�N�X�`���̐ݒ�
		ChangeTextuteSelect(s_nIdxSelect, 0, s_aTexture[LIGHT_COLOR_BLUE]);

		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxSelect, 0, true);

		// �������킹
		SetAnswer(0);

		// ��`�̐F�̐ݒ�
		SetColorRectangle(GetIdxBG(0), GetColor(COLOR_BLUE));

		// �g�̐ݒ�
		SetFramePlayer(0);

		// �G�t�F�N�g�̐ݒ�
		SetEffect(GetPosSelect(s_nIdxSelect, 0), EFFECT_TYPE_000, GetColor(s_aColor[s_nIdxColor[0]]));
	}
	else if (GetLightKeyTrigger(LIGHT_KEY_YELLOW))
	{// ���F
		PlaySound(SOUND_LABEL_SE_SELECT);
		s_nIdxColor[0] = LIGHT_COLOR_YELLOW;

		// �Z���N�g�̃e�N�X�`���̐ݒ�
		ChangeTextuteSelect(s_nIdxSelect, 0, s_aTexture[LIGHT_COLOR_YELLOW]);

		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxSelect, 0, true);

		// �������킹
		SetAnswer(0);

		// ��`�̐F�̐ݒ�
		SetColorRectangle(GetIdxBG(0), GetColor(COLOR_YELLOW));

		// �g�̐ݒ�
		SetFramePlayer(0);

		// �G�t�F�N�g�̐ݒ�
		SetEffect(GetPosSelect(s_nIdxSelect, 0), EFFECT_TYPE_000, GetColor(s_aColor[s_nIdxColor[0]]));
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawPlayer(void)
{
}

//--------------------------------------------------
// �F�̎擾
//--------------------------------------------------
int GetColorPlayer(int nNowLight)
{
	assert(nNowLight >= 0 && nNowLight <= MAX_LIGHT);

	return s_nIdxColor[nNowLight];
}

//--------------------------------------------------
// �g�̐ݒ�
//--------------------------------------------------
void SetFramePlayer(int nNowLight)
{
	assert(nNowLight >= 0 && nNowLight <= MAX_LIGHT);

	if (GetAnswer())
	{// �ő�l
		return;
	}

	// �Z���N�g�̕`�悷�邩�ǂ���
	SetDrawSelect(s_nIdxFrame, nNowLight, true);
}

namespace
{
//--------------------------------------------------
// �`��̃��Z�b�g
//--------------------------------------------------
void ResetDrawPlayer(void)
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxSelect, i, false);
	}

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxFrame, i, false);
	}

	// �Z���N�g�̕`�悷�邩�ǂ���
	SetDrawSelect(s_nIdxFrame, 0, true);
}
}// namespace�͂����܂�