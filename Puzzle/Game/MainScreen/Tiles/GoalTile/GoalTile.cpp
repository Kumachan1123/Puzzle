/*
*	@file GoalTile.cpp
*	@brief �S�[���^�C���̏������`����N���X
*/
#include "pch.h"
#include "GoalTile.h"

/*
*	@brief �^�C���ɓ������Ƃ��̏���
*	@details �L�����N�^�[�����̃^�C���ɓ������Ƃ��̏������`����B
*	@param character �^�C���ɓ������L�����N�^�[�ւ̃|�C���^
*	@return �Ȃ�
*/
void GoalTile::OnEnter(MiniCharacter* character)
{
	// ���g�p�x����\��
	UNREFERENCED_PARAMETER(character);
	// 2��ڈȍ~�͉������Ȃ�
	if (character->HasEnteredTile(this)) return;

	// �S�[���ɓ��B�������Ƃ�ʒm

	// �ʉߋL�^
	character->SetEnteredTile(this);
}

/*
*	@brief �^�C������o���Ƃ��̏���
*	@details �L�����N�^�[�����̃^�C������o���Ƃ��̏������`����B
*	@param character �^�C������o���L�����N�^�[�ւ̃|�C���^
*	@return �Ȃ�
*/
void GoalTile::OnExit(MiniCharacter* character)
{
	// ���g�p�x����\��
	UNREFERENCED_PARAMETER(character);
	// �t���O����������
	character->ResetEnteredTiles();
}

void GoalTile::OnCenterReached(MiniCharacter* character)
{
	using namespace DirectX::SimpleMath;
	// ���g�p�x����\��
	UNREFERENCED_PARAMETER(character);
	// �L�����N�^�[�̑��x���[���ɂ���
	character->SetVelocity(Vector3(0.0f, 0.0f, 0.0f));
	// �L�����N�^�[�𓮂����t���O���~�߂�
	character->SetMoving(false);
}
