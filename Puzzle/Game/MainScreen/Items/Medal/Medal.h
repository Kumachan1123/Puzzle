/*
*	@file Medal.h
*	@brief ���_���N���X
*/
#pragma once
// ����w�b�_�[�t�@�C��
#include "Game/CommonResources/CommonResources.h"
#include "Game/MainScreen/Items/ItemBase/ItemBase.h"
#include "Game/MainScreen/MiniCharacter/MiniCharacter.h"
// �O���錾
class CommonResources;

// ���_���N���X
class Medal : public ItemBase
{
public:
	// �A�N�Z�T
	// �A�C�e���̈ʒu���擾����
	const DirectX::SimpleMath::Vector3& GetPosition() const override { return m_position; }
	// �A�C�e���̈ʒu��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3& pos) override { m_position = pos; }
	// �A�C�e���̃��f�����擾����
	DirectX::Model* GetModel() const override { return m_pModel; }
	// �A�C�e���̃��f����ݒ肷��
	void SetModel(DirectX::Model* model) override { m_pModel = model; }
	// �A�C�e���̃��[���h�s����擾����
	const DirectX::SimpleMath::Matrix& GetWorldMatrix() const override { return m_worldMatrix; }
	// �A�C�e���̃��[���h�s���ݒ肷��
	void SetWorldMatrix(const DirectX::SimpleMath::Matrix& world) override { m_worldMatrix = world; }

public:
	// public�֐�
	// �R���X�g���N�^
	Medal();
	// �f�X�g���N�^
	~Medal() override;
	// ������
	void Initialize(CommonResources* resources, const ItemInfo& info) override;
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
private:
	// private�ϐ�
	// ���ʃ��\�[�X�ւ̃|�C���^
	CommonResources* m_pCommonResources;
	// ���_���̃��f��
	DirectX::Model* m_pModel;
	// ���_���̏��
	ItemInfo m_itemInfo;
	// ���_���̈ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// ���_���̃X�P�[��
	DirectX::SimpleMath::Vector3 m_scale;
	// ���_���̉�]
	DirectX::SimpleMath::Quaternion m_rotation;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// ����
	float m_time;
};