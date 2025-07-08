#include "pch.h"
#include "MiniCharacterHand.h"
#include "Game/MainScreen/MiniCharacter/MiniCharacterBody/MiniCharacterBody.h"
#include "KumachiLib/Easing/Easing.h"

MiniCharacterHand::MiniCharacterHand(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:m_pParent(parent)
	, m_nodeNumber(MiniCharacter::GetNodeCountAfterCountUp())
	, m_partNumber(MiniCharacter::GetPartsNumber())
	, m_partID(MiniCharacter::HEAD)
	, m_pCommonResources(nullptr)
	, m_pModel(nullptr)
	, m_time(0.0f)
	, m_initialPosition(initialPosition)
	, m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle))
	, m_currentPosition{}
	, m_currentAngle{}
	, m_rotationMiniCharacterAngle{}
	, m_mass{}
	, m_MiniCharacterVelocity{}
{
	//m_pMiniCharacter = dynamic_cast<MiniCharacter*>(parent->GetParent()->GetParent());
}

MiniCharacterHand::~MiniCharacterHand()
{
	Finalize();
}

void MiniCharacterHand::Initialize(CommonResources* commonResources)
{
	using namespace DirectX;
	assert(commonResources);
	m_pCommonResources = commonResources;
	// ���f����ǂݍ���
	m_pModel = m_pCommonResources->GetModelManager()->GetModel("PlayerHand");
}

void MiniCharacterHand::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	m_time += elapsedTime;
	// ���݂̈ʒu���X�V����
	m_currentPosition = currentPosition + m_initialPosition;
	//m_currentPosition.x += Easing::Reflect(Easing::EaseInSine, m_time) / 4; // �C�[�W���O���g����X���W��ω�������
	m_currentPosition.y += Easing::Reflect(Easing::EaseInSine, m_time) / 8; // �C�[�W���O���g����Y���W��ω�������
	// ���݂̉�]�p���X�V����
	m_currentAngle = m_rotationMiniCharacterAngle * m_initialAngle * currentAngle;
}

void MiniCharacterHand::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	using namespace DirectX::SimpleMath;
	auto context = m_pCommonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_pCommonResources->GetCommonStates();
	// ���[���h�s��𐶐�����
	m_worldMatrix = Matrix::CreateScale(1) *
		Matrix::CreateFromQuaternion(m_currentAngle) *
		Matrix::CreateTranslation(m_currentPosition);
	m_pModel->Draw(context, *states, m_worldMatrix, view, proj, false);
}

void MiniCharacterHand::Finalize()
{
}
