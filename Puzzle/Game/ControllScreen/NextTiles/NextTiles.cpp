/*
*	@file NextTiles.cpp
*	@brief ���̃^�C���N���X
*/
#include <pch.h>
#include "NextTiles.h"
#include <random>
/*
*	@brief �R���X�g���N�^
*	@details ���̃^�C���N���X�̃R���X�g���N�^
*	@param �Ȃ�
*	@return �Ȃ�
*/
NextTiles::NextTiles()
	: m_pCommonResources(nullptr) // ���ʃ��\�[�X�ւ̃|�C���^
	, m_viewPortControll() // �r���[�|�[�g�̐���
	, m_pDR(nullptr) // �f�o�C�X���\�[�X
	, m_hit(false) // UI�Ƀq�b�g�������ǂ���
	, m_time(0.0f) // �o�ߎ���
	, m_windowHeight(0) // �E�B���h�E�̍���
	, m_windowWidth(0) // �E�B���h�E�̕�
	, m_menuIndex(0) // ���ݑI������Ă��郁�j���[�̃C���f�b�N�X
{
}
/*
*	@brief �f�X�g���N�^
*	@details ���̃^�C���N���X�̃f�X�g���N�^(�����ł͉������Ȃ�)
*	@param �Ȃ�
*	@return �Ȃ�
*/
NextTiles::~NextTiles()
{
	// �������Ȃ�
}
/*
*	@brief ������
*	@details ���̃^�C���N���X�̏��������s��
*	@param resources ���ʃ��\�[�X�ւ̃|�C���^
*	@param width �E�B���h�E�̕�
*	@param height �E�B���h�E�̍���
*	@return �Ȃ�
*/
void NextTiles::Initialize(CommonResources* resources, int width, int height)
{
	// ���O��Ԃ̃G�C���A�X
	using namespace DirectX::SimpleMath;
	// ���ʃ��\�[�X���Z�b�g
	m_pCommonResources = resources;
	// �f�o�C�X���\�[�X�擾
	m_pDR = m_pCommonResources->GetDeviceResources();
	// �E�B���h�E��
	m_windowWidth = (int)(width * .3f);
	// �E�B���h�E����
	m_windowHeight = height;
	// UI�ǉ�
	Add("NextTilesBack"
		, Vector2(290.0f, 300.0f)
		, Vector2(0.6f, 0.6f)
		, KumachiLib::ANCHOR::MIDDLE_CENTER
		, UIType::NON_SELECT);
	// �g���^�C����錾
	// ���i(��)
	m_tilesDictionary.push_back("StraightHorizontal");
	// ���i(�c)
	m_tilesDictionary.push_back("StraightVertical");
	// �\��
	m_tilesDictionary.push_back("Cross");
	// �E���J�[�u
	m_tilesDictionary.push_back("RightDown");
	// �����J�[�u
	m_tilesDictionary.push_back("LeftDown");
	// �E��J�[�u
	m_tilesDictionary.push_back("RightUp");
	// ����J�[�u
	m_tilesDictionary.push_back("LeftUp");
}
/*
*	@brief �X�V
*	@details ���̃^�C���N���X�̍X�V���s��
*	@param elapsedTime �o�ߎ���
*	@return �Ȃ�
*/
void NextTiles::Update(const float elapsedTime)
{
	using namespace DirectX::SimpleMath;
	// �}�E�X�̏�Ԃ��擾
	auto& mouseState = m_pCommonResources->GetInputManager()->GetMouseState();
	m_hit = false;
	m_menuIndex = -1;
	//// �E�B���h�E�n���h�����擾
	//const HWND hwnd = m_pCommonResources->GetDeviceResources()->GetWindow();
	//// �E�B���h�E�T�C�Y�擾
	//RECT rect;
	//// �N���C�A���g�̈�T�C�Y���擾
	//GetClientRect(hwnd, &rect);
	//// �E�B���h�E�̕��i�s�N�Z���P�ʁj
	//float renderWidth = static_cast<float>(rect.right);
	//// �E�B���h�E�̍����i�s�N�Z���P�ʁj
	//float renderHeight = static_cast<float>(rect.bottom);
	//// �r���[�|�[�g�ݒ� 
	//D3D11_VIEWPORT viewportRight = {};
	//// �r���[�|�[�g�̍���X���W�i��ʕ���70%�ʒu�j
	//viewportRight.TopLeftX = renderWidth * 0.7f;
	//// �r���[�|�[�g�̍���Y���W�i�ŏ㕔�j
	//viewportRight.TopLeftY = 0;
	//// �r���[�|�[�g�̕��i��ʕ���30%�j
	//viewportRight.Width = renderWidth * 0.3f;
	//// �r���[�|�[�g�̍����i��ʍ����S�́j
	//viewportRight.Height = renderHeight;
	//// �ŏ��[�x
	//viewportRight.MinDepth = 0.0f;
	//// �ő�[�x
	//viewportRight.MaxDepth = 1.0f;
	//// �r���[�|�[�g���������o�ϐ��ɕۑ�
	//m_viewPortControll = viewportRight;
	//// �r���[�|�[�g����X
	//float vp_left = m_viewPortControll.TopLeftX;
	//// �r���[�|�[�g����Y
	//float vp_top = m_viewPortControll.TopLeftY;
	//// �r���[�|�[�g��
	//float vp_width = m_viewPortControll.Width;
	//// �r���[�|�[�g����
	//float vp_height = m_viewPortControll.Height;

	//// UI�̘_���𑜓x 
	//// �_���𑜓x�̕�
	//constexpr float logicalWidth = 1920.0f;
	//// �_���𑜓x�̍���
	//constexpr float logicalHeight = 1080.0f;
	//// �}�E�X���W��_���𑜓x��ɃX�P�[�����O
	//// �_���𑜓x��̃}�E�XX���W
	//float mouseX_UI = mouseState.x * (logicalWidth / renderWidth);
	//// �_���𑜓x��̃}�E�XY���W
	//float mouseY_UI = mouseState.y * (logicalHeight / renderHeight);
	//// �r���[�|�[�g�̘_���𑜓x��ł̍��W�E�T�C�Y���v�Z
	//// �_���𑜓x��̃r���[�|�[�g����X
	//float vp_left_UI = vp_left * (logicalWidth / renderWidth);
	//// �_���𑜓x��̃r���[�|�[�g����Y
	//float vp_top_UI = vp_top * (logicalHeight / renderHeight);
	//// �_���𑜓x��̃r���[�|�[�g��
	//float vp_width_UI = vp_width * (logicalWidth / renderWidth);
	//// �_���𑜓x��̃r���[�|�[�g����
	//float vp_height_UI = vp_height * (logicalHeight / renderHeight);
	//// �}�E�X���W���r���[�|�[�g�����[�J�����W�ɕϊ�
	//Vector2 mousePos = Vector2(mouseX_UI - vp_left_UI, mouseY_UI - vp_top_UI);
	// UI�v�f���ƂɃq�b�g������s��
	for (int i = 0; i < m_pUI.size(); i++)
	{
		// �}�E�X���r���[�|�[�g�O�Ȃ�X�L�b�v
		if (m_pMouse->GetPosition().x < 0 || m_pMouse->GetPosition().y < 0 || m_pMouse->GetPosition().x >= m_pMouse->GetVpWidthUI() || m_pMouse->GetPosition().y >= m_pMouse->GetVpHeightUI())
			continue;
		// �q�b�g����iUI�v�f���Ɓj
		if (m_pUI[i]->IsHit(m_pMouse->GetPosition()) && mouseState.leftButton)
		{
			m_hit = true;         // �����蔻��t���O
			m_menuIndex = i;      // ��������UI�̃C���f�b�N�X
			const auto debugString = m_pCommonResources->GetDebugString();
			debugString->AddString("hitNextTile:%i", m_menuIndex);
			break;
		}
	}
	// �o�ߎ��Ԃ����Z
	m_time += elapsedTime;
	// 10�b���Ƃ�UI��ǉ�����
	if (m_time >= 10.0f)
	{
		// UI��ǉ�
		AddNextTiles();
		// ���Ԃ����Z�b�g
		m_time = 0.0f;
	}
	// �S�w�iUI�̌o�ߎ��Ԃ��X�V
	for (int i = 0; i < m_pBackUI.size(); i++)
	{
		// �w�iUI�̎��Ԃ��X�V
		m_pBackUI[i]->SetTime(m_pBackUI[i]->GetTime() + elapsedTime);
	}
	// �SUI�v�f�̌o�ߎ��Ԃ��X�V
	for (int i = 0; i < m_pUI.size(); i++)
	{
		// UI�v�f�̎��Ԃ��X�V
		m_pUI[i]->SetTime(m_pUI[i]->GetTime() + elapsedTime);
	}
	// �I�𒆂�UI������Ȃ���W��ύX����
	if (m_menuIndex >= 0 && mouseState.leftButton)m_pUI[m_menuIndex]->SetPosition(m_pMouse->GetPosition());
}
/*
*	@brief �`��
*	@details ���̃^�C���N���X�̕`����s��
*	@param �Ȃ�
*	@return �Ȃ�
*/
void NextTiles::Render()
{
	// �w�iUI�̐������J��Ԃ�
	for (unsigned int i = 0; i < m_pBackUI.size(); i++)
	{
		// �w�iUI�̕`��
		m_pBackUI[i]->Render();
	}
	// UI�̐������J��Ԃ�
	for (unsigned int i = 0; i < m_pUI.size(); i++)
	{
		// �I���\UI�̕`��
		m_pUI[i]->Render();
	}
}
/*
*	@brief UI�ǉ�
*	@details ���̃^�C���N���X��UI��ǉ�����
*	@param key �e�N�X�`���̃L�[
*	@param position �ʒu
*	@param scale �X�P�[��
*	@param anchor �A���J�[
*	@param type UI�̎��
*	@return �Ȃ�
*/
void NextTiles::Add(const std::string& key, const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& scale, KumachiLib::ANCHOR anchor, UIType type)
{
	// UI�I�u�W�F�N�g�̐���
	std::unique_ptr<Canvas> userInterface = std::make_unique<Canvas>(m_pCommonResources);
	// �w��摜��UI�쐬
	userInterface->Create(m_pDR, key, position, scale, anchor);
	// �E�B���h�E�T�C�Y��ݒ�
	userInterface->SetWindowSize(m_windowWidth, m_windowHeight);
	// �A�C�e����V�����ǉ�		
	if (type == UIType::SELECT)m_pUI.push_back(std::move(userInterface));
	else m_pBackUI.push_back(std::move(userInterface));
}

/*
*	@brief ����I��UI��ǉ�����
*	@details �X�V����10�b�Ɉ��UI��ǉ�����
*	@param �Ȃ�
*	@return �Ȃ�
*/
void NextTiles::AddNextTiles()
{
	// ���O��Ԃ̃G�C���A�X
	using namespace DirectX::SimpleMath;
	// UI�̐���5�ȏ�Ȃ�ǉ����Ȃ�
	if (m_pUI.size() == 5)return;
	// �����̐ݒ�
	std::random_device seed;
	// �����Z���k�E�c�C�X�^�@
	std::default_random_engine engine(seed());
	// �����_���Ȕ͈͂�ݒ�
	std::uniform_int_distribution<int> rand(0, (int)m_tilesDictionary.size() - 1);
	// �����_���ȃC���f�b�N�X���擾
	int randomIndex = rand(engine);
	// Y���W�𒲐�
	float positionY = 480.0f - (float(m_pUI.size()) * 90.0f);
	// UI�ǉ�
	Add(m_tilesDictionary[randomIndex]
		, Vector2(290.0f, positionY)
		, Vector2(0.6f, 0.6f)
		, KumachiLib::ANCHOR::MIDDLE_CENTER
		, UIType::SELECT);

}

