/*
 *	@file StraightHorizontalTile.cpp
 *	@brief ���i�i���j�^�C���̏������`����N���X
 */
#include <pch.h>
#include "StraightHorizontalTile.h"
 /*
 *	@brief �^�C���ɓ������Ƃ��̏���
 *	@details �L�����N�^�[�����̃^�C���ɓ������Ƃ��̏������`����B
 *	@param character �^�C���ɓ������L�����N�^�[�ւ̃|�C���^
 *	@return �Ȃ�
 */
void StraightHorizontalTile::OnEnter(MiniCharacter* character)
{
	// 2��ڈȍ~�͉������Ȃ�
	if (character->HasEnteredTile(this)) return;
	// �������ɐi��
	character->SetVelocity(character->GetVelocity());
	// �ʉߋL�^
	character->SetEnteredTile(this);
}
/*
*	@brief �^�C������o���Ƃ��̏���
*	@details �L�����N�^�[�����̃^�C������o���Ƃ��̏������`����B
*	@param character �^�C������o���L�����N�^�[�ւ̃|�C���^
*	@return �Ȃ�
*/
void StraightHorizontalTile::OnExit(MiniCharacter* character)
{
	// �t���O����������
	character->ResetEnteredTiles();
}
