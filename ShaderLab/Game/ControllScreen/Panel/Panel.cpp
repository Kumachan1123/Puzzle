/*
*	@file Panel.cpp
*	@brief �p�l���N���X
*/
#include <pch.h>
#include "Panel.h"
/*
*	@brief �R���X�g���N�^
*	@details �p�l���N���X�̃R���X�g���N�^
*	@param mapSizeX �}�b�v�̃T�C�YX
*	@param mapSizeY �}�b�v�̃T�C�YY
*	@return �Ȃ�
*/
Panel::Panel(int mapSizeX, int mapSizeY)
	: m_pCommonResources(nullptr) // ���ʃ��\�[�X�ւ̃|�C���^
	, m_pDR(nullptr) // �f�o�C�X���\�[�X
	, m_hit(false) // UI�Ƀq�b�g�������ǂ���
	, m_time(0.0f) // �o�ߎ���
	, m_windowHeight(0) // �E�B���h�E�̍���
	, m_windowWidth(0) // �E�B���h�E�̕�
	, m_mapSizeX(mapSizeX) // �}�b�v�̃T�C�YX
	, m_mapSizeY(mapSizeY) // �}�b�v�̃T�C�YY
{
}
/*
*	@brief �f�X�g���N�^
*	@details �p�l���N���X�̃f�X�g���N�^(�����ł͉������Ȃ�)
*	@param �Ȃ�
*	@return �Ȃ�
*/
Panel::~Panel()
{
	/*do nothing*/
}
/*
*	@brief ������
*	@details �p�l���N���X�̏��������s��
*	@param resources ���ʃ��\�[�X�ւ̃|�C���^
*	@param width �E�B���h�E�̕�
*	@param height �E�B���h�E�̍���
*	@return �Ȃ�
*/
void Panel::Initialize(CommonResources* resources, int width, int height)
{
	// ���O��Ԃ̃G�C���A�X
	using namespace DirectX::SimpleMath;
	// ���ʃ��\�[�X���Z�b�g
	m_pCommonResources = resources;
	// �f�o�C�X���\�[�X�擾
	m_pDR = m_pCommonResources->GetDeviceResources();
	// �E�B���h�E��
	m_windowWidth = width * .3f;
	// �E�B���h�E����
	m_windowHeight = height;
	// �ꖇ������̕�
	const float tileSize = 90.0f;
	// ���[�̈ʒu
	const float startX = Screen::CENTER_X - (tileSize * 2);
	// ��[�̈ʒu
	const float startY = Screen::CENTER_Y - (tileSize * 2);
	// �O���b�h�̃L�[�����肷�邽�߂̃��[�v
	for (int row = 0; row < 5; ++row)
	{
		for (int col = 0; col < 5; ++col)
		{
			// CSV�}�b�v�̃^�C�������擾
			const CSVMap::MapTileData& tileData = m_pCSVMap->GetTileData(row, col);
			// �O���b�h�̃L�[������
			std::string textureKey = ((row + col) % 2 == 0) ? "GridA" : "GridB";
			// �^�C���̎�ނɉ����ăe�N�X�`���L�[��ύX
			textureKey = tileData.tileInfo.modelName.empty() ? textureKey : tileData.tileInfo.modelName;
			// �ʒu�v�Z
			float posX = startX + col * tileSize - 350.0f;
			float posY = startY + row * tileSize + 420.0f;
			// �^�C������ׂ�
			Add(textureKey
				, Vector2(posX, posY)
				, Vector2(0.6f, 0.6f)
				, KumachiLib::ANCHOR::MIDDLE_CENTER
				, UIType::SELECT);
		}
	}
}

void Panel::Update(const float elapsedTime)
{
	using namespace DirectX::SimpleMath;
	// �}�E�X�g���b�J�[���擾����
	auto& mtracker = m_pCommonResources->GetInputManager()->GetMouseTracker();
	// �}�E�X�̌��݂̏�Ԃ��擾����
	auto& mouseState = m_pCommonResources->GetInputManager()->GetMouseState();
	// ���I����Ԃɂ���
	m_hit = false;
	// �}�E�X���W��2D�x�N�g���Ŏ擾����
	Vector2 mousePos = Vector2(static_cast<float>(mouseState.x), static_cast<float>(mouseState.y));
	// UI�̊e�v�f�ɑ΂��ăq�b�g������s��
	for (int i = 0; i < m_pUI.size(); i++)
	{
		// �}�E�X�̍��W��UI�ɏd�Ȃ��Ă��邩�m�F����
		if (m_pUI[i]->IsHit(mousePos))
		{
			// �q�b�g�t���O�𗧂Ă�
			m_hit = true;
			//// �I�����j���[���O��ƈႤ�ꍇ�ASE�Đ��t���O�����Z�b�g
			//if ((int(m_menuIndex)) != i)m_isSEPlay = false;
			//// SE�����Đ��Ȃ�
			//if (!m_isSEPlay)
			//{
			//	// ���ʉ����Đ�����
			//	m_pCommonResources->GetAudioManager()->PlaySound("Select", m_SEVolume);
			//	// SE�Đ��t���O�𗧂Ă�
			//	m_isSEPlay = true;
			//}
			//// ���ݑI������Ă��郁�j���[�̃C���f�b�N�X���X�V����
			//m_menuIndex = i;
			// 1�ł��q�b�g�����瑼�͖�������i�I����1�����j
			break;
		}
	}
	// �o�ߎ��Ԃ����Z����
	m_time += elapsedTime;
	// UI�v�f�̏�Ԃ��X�V���� 
	for (int i = 0; i < m_pUI.size(); i++)
	{
		// �o�ߎ��Ԃ�n���ăA�j���i�s
		m_pUI[i]->SetTime(m_pUI[i]->GetTime() + elapsedTime);
	}
}

void Panel::Render()
{
	// UI�̐������J��Ԃ�
	for (unsigned int i = 0; i < m_pUI.size(); i++)
	{
		// �`��
		m_pUI[i]->Render();
	}
}

void Panel::Add(const std::string& key, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale, KumachiLib::ANCHOR anchor, UIType type)
{
	// UI�I�u�W�F�N�g�̐���
	std::unique_ptr<Canvas> userInterface = std::make_unique<Canvas>(m_pCommonResources);
	// �w��摜��UI�쐬
	userInterface->Create(m_pDR, key, position, scale, anchor);
	// �E�B���h�E�T�C�Y��ݒ�
	userInterface->SetWindowSize(m_windowWidth, m_windowHeight);
	// UI�̎�ނɉ����ď����𕪊�
	if (type == UIType::SELECT)// �I���\�ȃA�C�e���Ȃ�
	{
		// �A�C�e����V�����ǉ�		
		m_pUI.push_back(std::move(userInterface));

	}
}
