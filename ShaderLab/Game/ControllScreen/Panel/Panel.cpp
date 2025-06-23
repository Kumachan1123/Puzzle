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
	, m_pCSVMap(nullptr) // CSV�}�b�v�ւ̃|�C���^
	, m_hit(false) // UI�Ƀq�b�g�������ǂ���
	, m_time(0.0f) // �o�ߎ���
	, m_windowHeight(0) // �E�B���h�E�̍���
	, m_windowWidth(0) // �E�B���h�E�̕�
	, m_menuIndex(0) // ���ݑI������Ă��郁�j���[�̃C���f�b�N�X
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
	// �}�E�X�̏�Ԃ��擾
	auto& mouseState = m_pCommonResources->GetInputManager()->GetMouseState();
	m_hit = false;
	// �E�B���h�E�n���h�����擾
	const HWND hwnd = m_pCommonResources->GetDeviceResources()->GetWindow();
	// �E�B���h�E�T�C�Y�擾
	RECT rect;
	// �N���C�A���g�̈�T�C�Y���擾
	GetClientRect(hwnd, &rect);
	// �E�B���h�E�̕��i�s�N�Z���P�ʁj
	float renderWidth = static_cast<float>(rect.right);
	// �E�B���h�E�̍����i�s�N�Z���P�ʁj
	float renderHeight = static_cast<float>(rect.bottom);
	// �r���[�|�[�g�ݒ� 
	D3D11_VIEWPORT viewportRight = {};
	// �r���[�|�[�g�̍���X���W�i��ʕ���70%�ʒu�j
	viewportRight.TopLeftX = renderWidth * 0.7f;
	// �r���[�|�[�g�̍���Y���W�i�ŏ㕔�j
	viewportRight.TopLeftY = 0;
	// �r���[�|�[�g�̕��i��ʕ���30%�j
	viewportRight.Width = renderWidth * 0.3f;
	// �r���[�|�[�g�̍����i��ʍ����S�́j
	viewportRight.Height = renderHeight;
	// �ŏ��[�x
	viewportRight.MinDepth = 0.0f;
	// �ő�[�x
	viewportRight.MaxDepth = 1.0f;
	// �r���[�|�[�g���������o�ϐ��ɕۑ�
	m_viewPortControll = viewportRight;
	// �r���[�|�[�g����X
	float vp_left = m_viewPortControll.TopLeftX;
	// �r���[�|�[�g����Y
	float vp_top = m_viewPortControll.TopLeftY;
	// �r���[�|�[�g��
	float vp_width = m_viewPortControll.Width;
	// �r���[�|�[�g����
	float vp_height = m_viewPortControll.Height;

	// UI�̘_���𑜓x 
	// �_���𑜓x�̕�
	constexpr float logicalWidth = 1920.0f;
	// �_���𑜓x�̍���
	constexpr float logicalHeight = 1080.0f;
	// �}�E�X���W��_���𑜓x��ɃX�P�[�����O
	// �_���𑜓x��̃}�E�XX���W
	float mouseX_UI = mouseState.x * (logicalWidth / renderWidth);
	// �_���𑜓x��̃}�E�XY���W
	float mouseY_UI = mouseState.y * (logicalHeight / renderHeight);
	// �r���[�|�[�g�̘_���𑜓x��ł̍��W�E�T�C�Y���v�Z
	// �_���𑜓x��̃r���[�|�[�g����X
	float vp_left_UI = vp_left * (logicalWidth / renderWidth);
	// �_���𑜓x��̃r���[�|�[�g����Y
	float vp_top_UI = vp_top * (logicalHeight / renderHeight);
	// �_���𑜓x��̃r���[�|�[�g��
	float vp_width_UI = vp_width * (logicalWidth / renderWidth);
	// �_���𑜓x��̃r���[�|�[�g����
	float vp_height_UI = vp_height * (logicalHeight / renderHeight);
	// �}�E�X���W���r���[�|�[�g�����[�J�����W�ɕϊ�
	Vector2 mousePos = Vector2(mouseX_UI - vp_left_UI, mouseY_UI - vp_top_UI);
	// �f�o�b�O�\��
	const auto debugString = m_pCommonResources->GetDebugString();
	debugString->AddString("isInside: %s",
		(mouseX_UI >= vp_left_UI) && (mouseX_UI < vp_left_UI + vp_width_UI)
		&& (mouseY_UI >= vp_top_UI) && (mouseY_UI < vp_top_UI + vp_height_UI)
		? "true" : "false"); // �}�E�X���r���[�|�[�g���ɂ��邩
	debugString->AddString("Inside ViewPort Mouse Position: (%f, %f)", mousePos.x, mousePos.y); // �r���[�|�[�g���}�E�X���W

	// 6. UI�v�f���ƂɃq�b�g������s��
	for (int i = 0; i < m_pUI.size(); i++)
	{
		// �}�E�X���r���[�|�[�g�O�Ȃ�X�L�b�v
		if (mousePos.x < 0 || mousePos.y < 0 || mousePos.x >= vp_width_UI || mousePos.y >= vp_height_UI)
			continue;

		// �q�b�g����iUI�v�f���Ɓj
		if (m_pUI[i]->IsHit(mousePos))
		{
			m_hit = true;         // �����蔻��t���O
			m_menuIndex = i;      // ��������UI�̃C���f�b�N�X
			break;
		}
	}

	// �o�ߎ��Ԃ����Z
	m_time += elapsedTime;

	// �SUI�v�f�̌o�ߎ��Ԃ��X�V
	for (int i = 0; i < m_pUI.size(); i++)
	{
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
	const auto& mouseState = m_pCommonResources->GetInputManager()->GetMouseState();
	const auto debugString = m_pCommonResources->GetDebugString();
	debugString->AddString("hitPanel:%i", m_menuIndex);
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
