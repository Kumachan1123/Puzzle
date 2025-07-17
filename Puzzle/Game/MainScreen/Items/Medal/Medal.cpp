/*
*	@file Medal.cpp
*	@brief ���_���N���X
*/
#include "pch.h"
#include "Medal.h"
/*
*	@brief �R���X�g���N�^
*	@details ���_���N���X�̃R���X�g���N�^
*	@param �Ȃ�
*	@return �Ȃ�
*/
Medal::Medal()
	:m_pCommonResources(nullptr) // ���ʃ��\�[�X�ւ̃|�C���^
	, m_itemInfo() // �A�C�e�����
	, m_pModel(nullptr) // ���f���ւ̃|�C���^
	, m_time(0.0f) // �o�ߎ���
{
}
/*
*	@brief �f�X�g���N�^
*	@details ���_���N���X�̃f�X�g���N�^
*	@param �Ȃ�
*	@return �Ȃ�
*/
Medal::~Medal()
{
}
/*
*	@brief ������
*	@details ���_���N���X�̏��������s��
*	@param resources ���ʃ��\�[�X�ւ̃|�C���^
*	@param info �A�C�e�����
*	@return �Ȃ�
*/
void Medal::Initialize(CommonResources* resources, const ItemInfo& info)
{
	// ���ʃ��\�[�X�ւ̃|�C���^��ݒ�
	m_pCommonResources = resources;
	// �A�C�e������ݒ�
	m_itemInfo = info;
}
/*
*	@brief �X�V
*	@details ���_���̍X�V�������s��
*	@param elapsedTime �o�ߎ���
*	@return �Ȃ�
*/
void Medal::Update(float elapsedTime)
{
	// ���Ԃ����Z
	m_time += elapsedTime;
	// ���Ԍo�߂ŉ�]������
	m_rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(m_time * DirectX::XM_PI * 2.0f / 5.0f, 0.0f, 0.0f);
}

void Medal::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	using namespace DirectX::SimpleMath;
	// ���f�����ݒ肳��Ă��Ȃ��ꍇ�͉������Ȃ�
	if (m_pModel == nullptr) return;
	// �f�o�C�X�R���e�L�X�g���擾
	auto context = m_pCommonResources->GetDeviceResources()->GetD3DDeviceContext();
	// ���ʂ̃X�e�[�g���擾
	auto states = m_pCommonResources->GetCommonStates();
	// ���[���h�s���ݒ�
	m_worldMatrix = DirectX::SimpleMath::Matrix::CreateScale(m_itemInfo.scale) *
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_rotation) *
		DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	// �����_�����O
	m_pModel->Draw(context, *states, m_worldMatrix, view, proj, false);
}

void Medal::OnGet(MiniCharacter* miniCharacter)
{
}

void Medal::OnUse(MiniCharacter* miniCharacter)
{
}

void Medal::OnDiscard(MiniCharacter* miniCharacter)
{
}
