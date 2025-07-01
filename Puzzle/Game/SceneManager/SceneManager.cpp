/*
	@file	SceneManager.cpp
	@brief	�V�[���}�l�[�W���N���X
*/
#include "pch.h"
#include "SceneManager.h"
#include "Game/Screen/Screen.h"
#include "Game/CommonResources/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>


//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
SceneManager::SceneManager()
	:
	m_currentScene{},
	m_commonResources{},
	m_stageNumber{ 0 },
	m_nowSceneID{ IScene::SceneID::NONE }
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
SceneManager::~SceneManager()
{
	Finalize();
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void SceneManager::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	ChangeScene(IScene::SceneID::LAB);
}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void SceneManager::Update(float elapsedTime)
{
	m_currentScene->Update(elapsedTime);

	// �����p�ϐ��F���̃V�[��
	const IScene::SceneID nextSceneID = m_currentScene->GetNextSceneID();

	// �V�[����ύX���Ȃ��Ƃ�
	if (nextSceneID == IScene::SceneID::NONE) return;

	// �V�[����ύX����Ƃ�
	ChangeScene(nextSceneID);
}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void SceneManager::Render()
{
	m_currentScene->Render();
}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void SceneManager::Finalize()
{
	ReleaseScene();
}

//---------------------------------------------------------
// �V�[����ύX����
//---------------------------------------------------------
void SceneManager::ChangeScene(IScene::SceneID sceneID)
{
	// DeleteScene();
	CreateScene(sceneID);
}

//---------------------------------------------------------
// �V�[�����쐬����
//---------------------------------------------------------
void SceneManager::CreateScene(IScene::SceneID sceneID)
{
	assert(m_currentScene == nullptr);

	switch (sceneID)
	{
	case IScene::SceneID::LAB:
		m_currentScene = std::make_unique<Scene>(sceneID);
		break;
		/*case IScene::SceneID::TITLE:
			m_currentScene = std::make_unique<TitleScene>(sceneID);
			break;
		case IScene::SceneID::SETTING:
			m_currentScene = std::make_unique<SettingScene>(sceneID);
			break;
		case IScene::SceneID::STAGESELECT:
			m_currentScene = std::make_unique<StageSelectScene>(sceneID);
			break;
		case IScene::SceneID::PLAY:
			m_currentScene = std::make_unique<PlayScene>(sceneID);

			break;
		case IScene::SceneID::CLEAR:
		case IScene::SceneID::GAMEOVER:

			m_currentScene = std::make_unique<ResultScene>(sceneID);
			break;*/
	default:
		assert(!"SceneManager::CreateScene::�V�[���������݂��܂���I");
		// no break
	}


	m_currentScene->Initialize(m_commonResources);
	SetSceneID(sceneID);
}

void SceneManager::ReleaseScene()
{
	m_currentScene.reset();
}

