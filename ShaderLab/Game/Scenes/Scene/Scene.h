/*
	@file	Scene.h
	@brief	��ʓI�ȃV�[���N���X
*/
#pragma once
#include <cassert>
#include <DeviceResources.h>

#include <Libraries/MyLib/DebugCamera.h>
#include <Libraries/MyLib/DebugString.h>
#include <Libraries/MyLib/GridFloor.h>
#include <Libraries/MyLib/InputManager.h>
#include <Libraries/MyLib/MemoryLeakDetector.h>

// ����w�b�_�[�t�@�C��
#include "Game/SceneManager/IScene.h"
#include "Game/CommonResources/CommonResources.h"
#include "Game/Camera/FixedCamera/FixedCamera.h"
#include "Game/MainScreen/CSVMap/CSVMap.h"
#include "Game/ControllScreen/UIBack/UIBack.h"
#include "Game/ControllScreen/Panel/Panel.h"
#include "Game/Mouse/Mouse.h"
#include "Game/ControllScreen/NextTiles/NextTiles.h"
// �O���錾
class CommonResources;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}

// ��ʓI�ȃV�[���N���X
class Scene : public IScene
{
public:
	Scene(IScene::SceneID sceneID);
	~Scene()override;
	void Initialize(CommonResources* resources) override;
	void Update(float elapsedTime)override;
	void Render()override;
	void Finalize()override;
	SceneID GetNextSceneID() const override;
private:
	// �J�����Ɋւ���ݒ������
	void CreateCamera();
	// �e��r���[�|�[�g��ݒ肷��
	void CreateViewports();
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// �f�o�b�O�J����
	std::unique_ptr<mylib::DebugCamera> m_debugCamera;
	// �Œ�J����
	std::unique_ptr<FixedCamera> m_pFixedCamera;
	// CSV�}�b�v
	std::unique_ptr<CSVMap> m_pCSVMap;
	// �����ʂ̔w�i
	std::unique_ptr<UIBack> m_pUIBack;
	// �p�l��
	std::unique_ptr<Panel> m_pPanel;
	// ���̃^�C��
	std::unique_ptr<NextTiles> m_pNextTiles;
	// �}�E�X
	std::unique_ptr<MyMouse> m_pMouse;
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projectionGame;
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projectionControll;
	// ���݂̃V�[��ID
	IScene::SceneID m_nowSceneID;
	// �Q�[����ʗp�r���[�|�[�g�@
	D3D11_VIEWPORT m_viewPortGame;
	// ����p�r���[�|�[�g
	D3D11_VIEWPORT m_viewPortControll;
	// ����
	float m_time;
	// �V�[���`�F���W�t���O
	bool m_isChangeScene;

};
