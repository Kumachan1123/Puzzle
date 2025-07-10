/*
*	@file TileFactory.cpp
*	@brief �^�C���𐶐����邽�߂̃t�@�N�g���[�N���X
*/
#include "pch.h"
#include "TileFactory.h"
/*
*	@brief �^�C�����Ɋ�Â��ă^�C���𐶐�����
*	@details �^�C�����ɉ����āA�Ή�����^�C���I�u�W�F�N�g�𐶐�����B
*	@param name �^�C���̖��O
*	@return �������ꂽ�^�C���I�u�W�F�N�g�̃��j�[�N�|�C���^
*/
std::unique_ptr<TileBase> TileFactory::CreateTileByName(const std::string& name)
{
	// �^�C�����ɉ����ă^�C���𐶐�
	// ���i�i�c�j�^�C��
	if (name == "DefaultStraightVertical" || name == "StraightVertical")
		return std::make_unique<StraightVerticalTile>();
	// ���i�i���j�^�C��
	if (name == "DefaultStraightHorizontal" || name == "StraightHorizontal")
		return std::make_unique<StraightHorizontalTile>();
	// ����^�C��
	if (name == "LeftUp")
		return std::make_unique<LeftUpTile>();
	// �����^�C��
	if (name == "LeftDown")
		return std::make_unique<LeftDownTile>();
	// �E��^�C��
	if (name == "RightUp")
		return std::make_unique<RightUpTile>();
	// �E���^�C��
	if (name == "RightDown")
		return std::make_unique<RightDownTile>();
	// �X�^�[�g�^�C��
	if (name == "Start")
		return std::make_unique<StartTile>();
	// �S�[���^�C��
	if (name == "Goal")
		return std::make_unique<GoalTile>();

	return nullptr;
}
