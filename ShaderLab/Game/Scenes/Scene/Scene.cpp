/*
	@file	Scene.cpp
	@brief	��ʓI�ȃV�[���N���X
*/
#include "pch.h"
#include "Scene.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;




Scene::Scene(IScene::SceneID sceneID)
	: m_commonResources{}
	, m_debugCamera{}
	, m_projectionGame{}
	, m_projectionControll{}
	, m_time{ 0.0f }
	, m_isChangeScene{}
	, m_viewPortGame{}
	, m_viewPortControll{}
	, m_nowSceneID{ sceneID }// ���݂̃V�[��ID

{
}

Scene::~Scene()
{
}

void Scene::Initialize(CommonResources* resources)
{
	m_commonResources = resources;
	CreateCamera();
	const auto deviceResources = m_commonResources->GetDeviceResources();
	// �e��r���[�|�[�g���쐬����
	CreateViewports();
	// �}�b�v����
	m_pCSVMap = std::make_unique<CSVMap>(m_commonResources);
	// CSV�}�b�v��ǂݍ���
	m_pCSVMap->LoadMap("Resources/Map/test.csv");
	// �����ʂ̔w�i���쐬����
	m_pUIBack = std::make_unique<UIBack>(m_commonResources);
	// �����ʂ̔w�i������������
	m_pUIBack->Create(deviceResources);
	// �p�l�����쐬����
	m_pPanel = std::make_unique<Panel>(m_pCSVMap->GetMaxCol(), m_pCSVMap->GetMaxRow());
	// �p�l���Ƀ}�b�v����n��
	m_pPanel->SetCSVMap(m_pCSVMap.get());
	// �p�l��������������
	m_pPanel->Initialize(m_commonResources, deviceResources->GetOutputSize().right, deviceResources->GetOutputSize().bottom);
}

void Scene::Update(float elapsedTime)
{
	m_time += elapsedTime;
	// �f�o�b�O�J�����̍X�V
	m_debugCamera->Update(m_commonResources->GetInputManager());
	// �����ʂ̔w�i�̍X�V
	m_pUIBack->Update(elapsedTime);
	// �p�l���̍X�V
	m_pPanel->Update(elapsedTime);
}
void Scene::Render()
{
	const auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	RECT rect = m_commonResources->GetDeviceResources()->GetOutputSize();

	// --- ����: �Q�[����ʗp�r���[�|�[�g ---
	context->RSSetViewports(1, &m_viewPortGame);

	// �����ŃQ�[����ʂ�`��
	// �r���[�s����擾
	m_view = m_debugCamera->GetViewMatrix();
	// CSV�}�b�v�̕`��
	m_pCSVMap->Render(m_view, m_projectionGame);
	// --- �E��: �����ʗp�r���[�|�[�g ---
	context->RSSetViewports(1, &m_viewPortControll);
	// �����ʂ̔w�i��`��
	m_pUIBack->Render();
	// �p�l����`��
	m_pPanel->Render();


	// --- �f�o�b�O���i��j ---
	// �r���[�|�[�g�����̐ݒ�ɖ߂�
	const auto& viewPort = m_commonResources->GetDeviceResources()->GetScreenViewport();
	context->RSSetViewports(1, &viewPort);

	const auto debugString = m_commonResources->GetDebugString();
	debugString->AddString("Use ViewPort.");
}

void Scene::Finalize()
{
}

IScene::SceneID Scene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::LAB;// �Q�[���I�[�o�[�V�[����
	}
	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;// �������Ȃ�
}

//---------------------------------------------------------
// �J�����A�r���[�s��A�ˉe�s����쐬����
//---------------------------------------------------------
void Scene::CreateCamera()
{
	// �f�o�b�O�J�������쐬����
	RECT rect = m_commonResources->GetDeviceResources()->GetOutputSize();
	m_debugCamera = std::make_unique<mylib::DebugCamera>();
	m_debugCamera->Initialize(rect.right * 0.7f, rect.bottom);
	// �ˉe�s����쐬����
	m_projectionGame = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right * 0.7f) / static_cast<float>(rect.bottom),
		0.1f, 100.0f
	);
	m_projectionControll = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right * 0.3f) / static_cast<float>(rect.bottom),
		0.1f, 100.0f
	);
}

void Scene::CreateViewports()
{
	RECT rect = m_commonResources->GetDeviceResources()->GetOutputSize();
	// --- ����: �Q�[����ʗp�r���[�|�[�g ---
	D3D11_VIEWPORT viewportLeft = {};
	viewportLeft.TopLeftX = 0;
	viewportLeft.TopLeftY = 0;
	viewportLeft.Width = (FLOAT)rect.right * 0.7f; // ��: ��7��
	viewportLeft.Height = (FLOAT)rect.bottom;
	viewportLeft.MinDepth = 0.0f;
	viewportLeft.MaxDepth = 1.0f;
	m_viewPortGame = viewportLeft;

	// --- �E��: �����ʗp�r���[�|�[�g ---
	D3D11_VIEWPORT viewportRight = {};
	viewportRight.TopLeftX = (FLOAT)rect.right * 0.7f;
	viewportRight.TopLeftY = 0;
	viewportRight.Width = (FLOAT)rect.right * 0.3f; // ��: �E3��
	viewportRight.Height = (FLOAT)rect.bottom;
	viewportRight.MinDepth = 0.0f;
	viewportRight.MaxDepth = 1.0f;
	m_viewPortControll = viewportRight;
}
