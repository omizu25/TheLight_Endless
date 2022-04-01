//**************************************************
//
// Hackathon ( answer.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "answer.h"
#include "rectangle.h"
#include "texture.h"
#include "color.h"
#include "mode.h"
#include "light.h"
#include "player.h"
#include "game.h"
#include "bg.h"
#include "sound.h"
#include "ui.h"
#include "score.h"

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_TIME = 120;	// �^�C���̍ő�l
}// namespace�͂����܂�

 //==================================================
 // �X�^�e�B�b�N�ϐ�
 //==================================================
namespace
{
bool	s_bAnswer;	// �����Ă邩�ǂ���
int		s_nTime;	// �^�C��
}// namespace�͂����܂�

 //--------------------------------------------------
 // ������
 //--------------------------------------------------
void InitAnswer(void)
{
	s_nTime = 0;
	s_bAnswer = true;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitAnswer(void)
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateAnswer(void)
{
	//if (!s_bAnswer)
	//{// �s����
	//	s_nTime++;

	//	if (s_nTime >= MAX_TIME)
	//	{// ���Ԃ�����
	//		s_nTime = 0;
	//		s_bAnswer = true;

	//		// ���[�h�̕ύX
	//		ChangeMode(MODE_RESULT);
	//	}
	//}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawAnswer(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetAnswer(int nNowLight)
{
	if (GetColorLight(nNowLight) == GetColorPlayer(nNowLight))
	{// ����
		s_bAnswer = true;

		// ����
		AnswerLight();

		// �X�R�A�̉��Z
		AddScore(1);
	}
	else
	{// �s����
		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_MISS);

		// ����
		AnswerLight();

		if (GetScore() > 0)
		{// �X�R�A������
			// �X�R�A�̉��Z
			AddScore(-1);
		}
	}
}

//--------------------------------------------------
// �擾
// �Ԓl  : bool / �����ɂȂ������ǂ���
//--------------------------------------------------
bool GetAnswer(void)
{
	return s_bAnswer;
}