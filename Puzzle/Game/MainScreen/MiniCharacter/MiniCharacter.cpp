#include <pch.h>
#include "MiniCharacter.h"




// �C���J�E���^�[
int MiniCharacter::s_nodeCount = 0;
// ���i�J�E���^�[
int MiniCharacter::s_partsNumber = 0;

MiniCharacter::MiniCharacter(IComponent* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:m_parent(parent)
	, m_nodeNumber(MiniCharacter::GetNodeCountAfterCountUp())
	, m_partNumber(MiniCharacter::GetPartsNumber())
	, m_partID(MiniCharacter::MINICHARACTER)
	, m_pCommonResources(nullptr)
	, m_enteredTilePtr(nullptr)
	, m_hasEnteredTile(false)
	, m_isMoving(true)
	, m_fallTimer(0.0f)
	, m_fallTimerActive(false)
	, m_hasFallen(false)
	, m_initialPosition(initialPosition)
	, m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle))
	, m_currentPosition{}
	, m_currentVelocity{}
	, m_currentAngle{}
	, m_prevTileName("Start")
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
	// SimpleMath�̖��O��Ԃ��g�����߂�using�錾��ǉ�
	using namespace DirectX::SimpleMath;
	// ���ʃ��\�[�X�����݂��邱�Ƃ��m�F����
	assert(resources);
	// ���ʃ��\�[�X��ݒ肷��
	m_pCommonResources = resources;
	// ���f����ǂݍ���
	m_initialPosition = GetParent()->GetCSVMap()->GetStart().pos;
	UpdateSpeedByStartTile();
	Attach(std::make_unique<Sheep>(this, Vector3(0.0f, 3.5f, 0.0f), 0.0f));
}

void MiniCharacter::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	// ----- �^�C���ɂ��i�s�����̎������� -----
	std::string currentTileName = GetParent()->GetCSVMap()->GetTileData(m_currentPosition).tileInfo.modelName;
	bool isAtTileCenter = IsAtTileCenter(m_currentPosition, GetParent()->GetCSVMap()->GetTileData(m_currentPosition).pos);
	if (currentTileName != m_prevTileName)
	{
		const auto& prevTile = GetParent()->GetCSVMap()->GetTileData(m_prevPosition);
		if (prevTile.tileBasePtr) prevTile.tileBasePtr->OnExit(this);
		const auto& currentTile = GetParent()->GetCSVMap()->GetTileData(m_currentPosition);
		if (currentTile.tileBasePtr ||
			(m_prevTileName == "" && currentTileName != ""))
		{
			currentTile.tileBasePtr->OnEnter(this);
			m_prevTileName = currentTileName;
			m_prevPosition = m_currentPosition;
		}
	}
	if (isAtTileCenter)
	{
		const auto& currentTile = GetParent()->GetCSVMap()->GetTileData(m_currentPosition);
		if (currentTile.tileBasePtr) currentTile.tileBasePtr->OnCenterReached(this);
	}
	else if (currentTileName == "")
	{
		m_isMoving = false;
		if (!m_fallTimerActive)
		{
			m_fallTimerActive = true;
			m_fallTimer = 0.0f;
		}
	}
	// �����^�C�}�[����
	if (m_fallTimerActive && !m_hasFallen)
	{
		m_fallTimer += elapsedTime;
		if (m_fallTimer >= 3.0f)
		{
			m_currentVelocity = Vector3::Zero;
			m_isMoving = false;
			m_hasFallen = true;
		}
	}
	// �����J�E���^�[���ɋ󔒃^�C�����畜�A������A���Z�b�g
	if (m_fallTimerActive && !m_hasFallen && currentTileName != "")
	{
		m_fallTimerActive = false;
		m_fallTimer = 0.0f;
		m_isMoving = true;
		m_hasFallen = false;
	}
	const float gravity = -9.8f;
	if (m_hasFallen)
	{
		m_currentVelocity.y += gravity * elapsedTime;
		m_MiniCharacterVelocity += m_currentVelocity * elapsedTime;
	}
	else if (m_isMoving)
	{
		m_MiniCharacterVelocity += m_currentVelocity * elapsedTime / 4;
	}
	m_currentPosition = currentPosition + m_initialPosition + m_MiniCharacterVelocity;

	// ====== ��������u�h�ꉉ�o�v�ǉ� ======

	// �h��N�H�[�^�j�I���i�f�t�H���g�͉�]�Ȃ��j
	Quaternion shakeQuat = Quaternion::Identity;
	if (m_fallTimerActive && !m_hasFallen)
	{
		float shakeAmount = 0.18f; // �h��̋���
		float shakeSpeed = 7.0f;   // �h��̑���
		float time = m_fallTimer;

		float progress = std::min(time / 3.0f, 1.0f);
		float amp = shakeAmount * (0.5f + 1.0f * progress);

		float xSwing = sinf(time * shakeSpeed) * amp * (0.8f + 0.4f * sinf(time * 2.0f));
		float zSwing = cosf(time * shakeSpeed * 0.7f) * amp * (0.7f + 0.6f * cosf(time * 3.1f));

		shakeQuat = Quaternion::CreateFromYawPitchRoll(0.0f, xSwing, zSwing);
	}

	// �ڕW��]���v�Z�i���x�x�N�g������j
	Quaternion targetQuat;
	if (m_currentVelocity.LengthSquared() > 0.0f)
	{
		float yaw = atan2f(m_currentVelocity.x, m_currentVelocity.z);
		targetQuat = Quaternion::CreateFromYawPitchRoll(yaw, 0.0f, 0.0f);
	}
	else
	{
		targetQuat = Quaternion::Identity;
	}
	float rotateSpeed = 0.05f;
	m_rotationMiniCharacterAngle = Quaternion::Slerp(m_rotationMiniCharacterAngle, targetQuat, rotateSpeed);

	// ====== �h�������������]��K�p ======
	m_currentAngle = currentAngle * m_initialAngle * m_rotationMiniCharacterAngle * shakeQuat;

	// �C�����i���X�V����i�e��m_currentAngle�����̂܂ܓn�����ƂőS�̂��ꏏ�ɗh���j
	for (auto& MiniCharacterPart : m_pMiniCharacterParts)
	{
		MiniCharacterPart->Update(elapsedTime, m_currentPosition, m_currentAngle);
	}
}
void MiniCharacter::Attach(std::unique_ptr<IComponent> MiniCharacterPart)
{
	MiniCharacterPart->Initialize(m_pCommonResources);
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
	// ---�f�o�b�O�\��---
	const auto debugString = m_pCommonResources->GetDebugString();
	// ���W�\��
	debugString->AddString("MiniCharacter Position: (%f, %f, %f)",
		m_currentPosition.x, m_currentPosition.y, m_currentPosition.z);
	// ���x�\��
	debugString->AddString("MiniCharacter Velocity: (%f, %f, %f)",
		m_currentVelocity.x, m_currentVelocity.y, m_currentVelocity.z);
	// �ł��߂��^�C���̖��O��\��
	debugString->AddString("MiniCharacter Tile: %s",
		GetParent()->GetCSVMap()->GetTileData(m_currentPosition).tileInfo.modelName.c_str());
}

void MiniCharacter::Finalize()
{
}

/*
*	@brief �v���C���[�̊J�n�^�C���ɂ���đ��x���X�V����
*	@details �X�^�[�g�n�_�̑O�㍶�E�̃^�C���𒲂ׂāA�v���C���[�̑��x���X�V����B
*	@param �Ȃ�
*	@return �Ȃ�
*/
void MiniCharacter::UpdateSpeedByStartTile()
{
	// SimpleMath�̖��O��Ԃ��g�����߂�using�錾��ǉ�
	using namespace DirectX::SimpleMath;
	// �s�����l
	int startRow = -1;
	// �񏉊��l
	int startCol = -1;

	// �X�^�[�g�ʒu��T��
	for (int row = 0; row < GetParent()->GetCSVMap()->GetMaxRow(); ++row)
	{
		for (int col = 0; col < GetParent()->GetCSVMap()->GetMaxCol(); ++col)
		{
			const auto& tile = GetParent()->GetCSVMap()->GetTileData(row, col);
			if (tile.tileInfo.modelName == "Start") {
				startRow = row;
				startCol = col;
				break;
			}
		}
		if (startRow != -1) break;
	}
	// �㉺���E�̕������
	struct Dir { int dRow, dCol; };
	const Dir dirs[4] =
	{
		{ -1,  0 }, // ��
		{  1,  0 }, // ��
		{  0, -1 }, // ��
		{  0,  1 }, // �E
	};
	// �Ή����鑬�x�x�N�g��
	const Vector3 velocities[4] =
	{
		{0, 0, -1}, // ��i�O�i�j
		{0, 0,  1}, // ���i��i�j
		{-1, 0, 0}, // ��
		{ 1, 0, 0}, // �E
	};

	for (int i = 0; i < 4; ++i)
	{
		int nRow = startRow + dirs[i].dRow;
		int nCol = startCol + dirs[i].dCol;
		if (nRow >= 0 && nRow < GetParent()->GetCSVMap()->GetMaxCol() &&
			nCol >= 0 && nCol < GetParent()->GetCSVMap()->GetMaxRow())
		{
			const auto& neighbor = GetParent()->GetCSVMap()->GetTileData(nRow, nCol);
			const std::string& model = neighbor.tileInfo.modelName;

			if ((i <= 1 && model == "DefaultStraightVertical") || // �㉺
				(i >= 2 && model == "DefaultStraightHorizontal")) // ���E
			{
				m_currentVelocity = velocities[i];
				break;
			}
		}
	}
}
/*
*	@brief �^�C���̒��S�ɂ��邩�ǂ����𔻒肷��
*	@details �v���C���[�̈ʒu���^�C���̒��S�ɋ߂����ǂ����𔻒肷��B
*	@param charPos �v���C���[�̈ʒu
*	@param tileCenter �^�C���̒��S�ʒu
*	@param epsilon ����̋��e�덷
*	@return �^�C���̒��S�ɂ���ꍇ��true�A�����łȂ��ꍇ��false
*/
bool MiniCharacter::IsAtTileCenter(const DirectX::SimpleMath::Vector3& charPos, const DirectX::SimpleMath::Vector3& tileCenter, float epsilon) const
{
	// �^�C���̒��S�ƃv���C���[�̈ʒu�̋������v�Z
	float distance = (charPos - tileCenter).Length();
	return distance < epsilon;
}

