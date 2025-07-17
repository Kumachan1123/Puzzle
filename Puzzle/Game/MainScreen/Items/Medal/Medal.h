#pragma once
// ����w�b�_�[�t�@�C��
#include "Game/MainScreen/Items/ItemBase/ItemBase.h"

class Medal : public ItemBase
{
public:
	// �R���X�g���N�^
	Medal() = default;
	// ������
	void Initialize() override;
	// �X�V
	void Update(float elapsedTime) override;
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) override;
	// �A�C�e�����擾�����Ƃ��̏���
	void OnGet(MiniCharacter* miniCharacter) override;
	// �A�C�e�����g�p�����Ƃ��̏���
	void OnUse(MiniCharacter* miniCharacter) override;
	// �A�C�e����j�������Ƃ��̏���
	void OnDiscard(MiniCharacter* miniCharacter) override;

};