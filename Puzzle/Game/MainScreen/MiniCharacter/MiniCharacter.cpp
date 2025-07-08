#include <pch.h>
#include "MiniCharacter.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


// �C���J�E���^�[
int MiniCharacter::s_nodeCount = 0;
// ���i�J�E���^�[
int MiniCharacter::s_partsNumber = 0;

MiniCharacter::MiniCharacter(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:m_parent(parent)
	, m_nodeNumber(MiniCharacter::GetNodeCountAfterCountUp())
	, m_partNumber(MiniCharacter::GetPartsNumber())
	, m_partID(MiniCharacter::MINICHARACTER)
	, m_commonResources(nullptr)
	, m_initialPosition(initialPosition)
	, m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle))
	, m_currentPosition{}
	, m_currentAngle{}
	, m_rotationMiniCharacterAngle{}
	, m_mass{}
	, m_MiniCharacterVelocity{}

{
}

MiniCharacter::~MiniCharacter()
{
	Finalize();
}

void MiniCharacter::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;
	Attach(std::make_unique<MiniCharacterBody>(this, Vector3(0.0f, 1.8f, 0.0f), 0.0f));
}

void MiniCharacter::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	// ���݂̈ʒu���X�V����
	m_currentPosition = currentPosition + m_initialPosition + m_MiniCharacterVelocity;
	// ���݂̉�]�p���X�V����
	m_currentAngle = currentAngle * m_initialAngle * m_rotationMiniCharacterAngle;

	// �C�����i���X�V����
	for (auto& MiniCharacterPart : m_pMiniCharacterParts)
	{
		// �C�����i���X�V����
		MiniCharacterPart->Update(elapsedTime, m_currentPosition, m_currentAngle);
	}
}

void MiniCharacter::Attach(std::unique_ptr<IComponent> MiniCharacterPart)
{
	MiniCharacterPart->Initialize(m_commonResources);
	m_pMiniCharacterParts.push_back(std::move(MiniCharacterPart));
}

void MiniCharacter::Detach(std::unique_ptr<IComponent> MiniCharacterPart)
{
}

void MiniCharacter::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	// �C�����i��`�悷��
	for (auto& MiniCharacterPart : m_pMiniCharacterParts)
	{
		MiniCharacterPart->Render(view, proj);
	}
}

void MiniCharacter::Finalize()
{
}


//void MiniCharacter::LoadModel()
//{
//	auto device = m_pCommonResources->GetDeviceResources()->GetD3DDevice();
//
//	// ���f����ǂݍ��ޏ���
//	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
//	fx->SetDirectory(L"Resources/models/PMiniCharacter");
//	//�e�N�X�`���p�X��ݒ肷��
//	wcscpy_s(m_modelPath, L"Resources/models/PMiniCharacter/MiniCharacter_Body.cmo");
//
//	// ���f����ǂݍ���
//	m_pModel = Model::CreateFromCMO(device, m_modelPath, *fx);
//	//m_face = Model::CreateFromCMO(device, L"Resources/models/enemy/Boss_Face_Attack.cmo", *fx);
//}
