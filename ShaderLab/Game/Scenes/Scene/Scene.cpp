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
	, m_gridFloor{}
	, m_projection{}
	, m_time{ 0.0f }
	, m_isChangeScene{}
{
}

Scene::~Scene()
{
}

void Scene::Initialize(CommonResources* resources)
{
	m_commonResources = resources;
	this->CreateCamera();

}

void Scene::Update(float elapsedTime)
{
	// �f�o�b�O�J�����̍X�V
	m_debugCamera->Update(m_commonResources->GetInputManager());
}

void Scene::Render()
{
	// �r���[�s����擾����
	m_view = m_debugCamera->GetViewMatrix();
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
	m_debugCamera->Initialize(rect.right, rect.bottom);
	// �ˉe�s����쐬����
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 100.0f
	);
}