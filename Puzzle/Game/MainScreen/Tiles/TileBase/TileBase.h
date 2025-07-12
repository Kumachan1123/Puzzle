#pragma once
//// ����w�b�_�[�t�@�C��
//#include "Game/MainScreen/MiniCharacter/MiniCharacter.h"
class MiniCharacter;
// �^�C���x�[�X�N���X
class TileBase
{
public:
	// public�֐�
	virtual ~TileBase() = default;
	// �^�C���ɓ������Ƃ��̏���
	virtual void OnEnter(MiniCharacter* miniCharacter) = 0;
	// �^�C������o���Ƃ��̏���
	virtual void OnExit(MiniCharacter* miniCharacter) = 0;
	// �^�C���̒��S�ɗ������̏���
	virtual void OnCenterReached(MiniCharacter* miniCharacter) = 0;

};