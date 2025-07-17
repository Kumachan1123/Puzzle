/*
*	@file ItemBase.h
*	@brief �A�C�e���̃x�[�X�N���X
*/
#pragma once

// �O���錾
class MiniCharacter;

// �A�C�e���x�[�X�N���X
class ItemBase
{
	// public�֐�
public:
	// �f�X�g���N�^
	virtual ~ItemBase() = default;
	// ������
	virtual void Initialize() = 0;
	// �X�V
	virtual void Update(float elapsedTime) = 0;
	// �`��
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) = 0;
	// �A�C�e�����擾�����Ƃ��̏���
	virtual void OnGet(MiniCharacter* miniCharacter) = 0;
	// �A�C�e�����g�p�����Ƃ��̏���
	virtual void OnUse(MiniCharacter* miniCharacter) = 0;
	// �A�C�e����j�������Ƃ��̏���
	virtual void OnDiscard(MiniCharacter* miniCharacter) = 0;
};