/*
	@file	Scene.h
	@brief	��ʓI�ȃV�[���N���X
*/
#pragma once
#include <cassert>
#include <DeviceResources.h>
#include "Game/SceneManager/IScene.h"
#include "Game/CommonResources/CommonResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"

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
private:

	// �萔�o�b�t�@�p�̃o�b�t�@�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	// �f�o�b�O�J����
	std::unique_ptr<mylib::DebugCamera> m_debugCamera;

	// �i�q��
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;




	// ����
	float m_time;

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;
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
};
