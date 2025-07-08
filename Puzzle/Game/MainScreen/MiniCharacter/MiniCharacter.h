#pragma once
// �W�����C�u����
#include <cassert>
// DirectX
#include <SimpleMath.h>
#include <Model.h>
#include <Effects.h>
#include <memory>
#include <DeviceResources.h>
// �O�����C�u����
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
// ����w�b�_�[�t�@�C��
#include "Game/CommonResources/CommonResources.h"
#include "Game/Scenes/Scene/Scene.h"
#include "Game/MainScreen/MiniCharacter/Interface/IComposite.h"
#include "Game/MainScreen/MiniCharacter/MiniCharacterBody/MiniCharacterBody.h"
// �O���錾
class CommonResources;

class MiniCharacter : public IComposite
{
public:
	// ���iID
	enum PartID : int
	{
		MINICHARACTER = -1,
		BODY = 0,
		HEAD = 1,
		ARM_LEFT = 2,
		ARM_RIGHT = 3,
	};
public:
	// �A�N�Z�T
	// �m�[�h�ԍ����擾����
	int GetNodeNumber() const { return m_nodeNumber; }
	// ���iID���擾����
	int GetPartID() const { return  m_partID; }
	// ���i�ԍ����擾����
	int GetPartNumber() const { return m_partNumber; }
	// �e���擾����
	IComponent* GetParent() const { return m_parent; }
	// ���݂̈ʒu���擾����
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_currentPosition; }
	// ���݂̈ʒu��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3& currretPosition) { m_currentPosition = currretPosition; }
	// ���݂̉�]�p���擾����
	DirectX::SimpleMath::Quaternion GetAngle() const { return m_currentAngle; }
	// ���݂̉�]�p��ݒ肷��
	void SetAngle(const DirectX::SimpleMath::Quaternion& currentAngle) { m_currentAngle = currentAngle; }
	// ���ʂ��擾����
	float GetMass() const { return m_mass; }
	// ���ʂ�ݒ肷��
	void SetMass(const float& mass) { m_mass = mass; }
	// ���f�����擾����
	DirectX::Model* GetModel() { return nullptr; }
	// ���[���h�s����擾����
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }
public:
	// �R���X�g���N�^
	MiniCharacter(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// �f�X�g���N�^
	~MiniCharacter();
	// ����������
	void Initialize(CommonResources* commonResources);
	// �X�V����
	void Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle);
	// ���i��ǉ�����
	void Attach(std::unique_ptr<IComponent> MiniCharacterPart);
	// ���i���폜����
	void Detach(std::unique_ptr<IComponent> MiniCharacterPart);
	// �`�悷��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	// �㏈�����s��
	void Finalize();
public:
	// �m�[�h�J�E���g�A�b�v������m�[�h�J�E���g���擾����
	static int GetNodeCountAfterCountUp() { return ++s_nodeCount; }
	// �m�[�h�J�E���g���擾����
	static int GetNodeCount() { return s_nodeCount; }
	// ���i�ԍ������Z�b�g����(-1����J�n����)
	static void ResetPartsNumber() { s_partsNumber = -1; }
	// ���i�ԍ����擾����
	static int GetPartsNumber() { return s_partsNumber; }
	// ���i�ԍ����₷
	static void IncrementPartsNumber() { s_partsNumber++; }
private:
	// �C���J�E���g
	static int s_nodeCount;
	// �C�����i�J�E���g
	static int s_partsNumber;
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// �e
	IComponent* m_parent;
	// �m�[�h�ԍ�
	int m_nodeNumber;
	// ���i�ԍ�
	int m_partNumber;
	// ���iID
	int m_partID;
	// �����ʒu
	DirectX::SimpleMath::Vector3 m_initialPosition;
	// ������]�p
	DirectX::SimpleMath::Quaternion m_initialAngle;
	// ���݂̈ʒu
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// ���݂̉�]�p
	DirectX::SimpleMath::Quaternion m_currentAngle;
	// �v���C���[��]�p
	DirectX::SimpleMath::Quaternion m_rotationMiniCharacterAngle;
	// �v���C���[���x
	DirectX::SimpleMath::Vector3 m_MiniCharacterVelocity;
	// ����
	float m_mass;
	// ���i�z��
	std::vector<std::unique_ptr<IComponent>> m_pMiniCharacterParts;
	//	���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
};