/*
*	@file	NextTiles.h
*	@brief	���̃^�C���N���X
*/
#pragma once
// �W�����C�u����
#include <vector>
#include <string>
// DirectX
#include <DeviceResources.h>
#include <SimpleMath.h>
#include <WICTextureLoader.h>
#include <Mouse.h>
// �O�����C�u����
#include <Libraries/MyLib/InputManager.h>
#include <Libraries/MyLib/DebugString.h>
// ����w�b�_�[�t�@�C��
#include "Game/CommonResources/CommonResources.h"
#include "Game/ControllScreen/Canvas/Canvas.h"
#include "Game/Interface/IUI/IUI.h"
#include "Game/Screen/Screen.h"
#include "KumachiLib/BinaryFile/BinaryFile.h"
#include "Game/Mouse/Mouse.h"

// �O���錾
class CommonResources;

// ���̃^�C���N���X
class NextTiles : public IUI
{
public:
	// �A�N�Z�T
	// UI�Ƀq�b�g�������ǂ����擾
	bool GetIsHit()const { return m_hit; }
	// UI�Ƀq�b�g�������ǂ����ݒ�
	void SetIsHit(bool hit) { m_hit = hit; }
	// �}�E�X�|�C���^�[��ݒ�
	void SetMouse(MyMouse* pMouse) { m_pMouse = pMouse; }
	// �r���[�|�[�g��ݒ�
	void SetViewport(const D3D11_VIEWPORT& viewport) { m_viewPortControll = viewport; }
public:
	// public�֐�
	// �R���X�g���N�^
	NextTiles();
	// �f�X�g���N�^
	~NextTiles();
	// ������
	void Initialize(CommonResources* resources, int width, int height) override;
	// �X�V
	void Update(const float elapsedTime) override;
	// �`��
	void Render() override;
	// UI�ǉ�
	void Add(
		const std::string& key,						// �e�N�X�`���̃L�[
		const DirectX::SimpleMath::Vector2& position,	// �ʒu
		const DirectX::SimpleMath::Vector2& scale,	// �X�P�[��
		KumachiLib::ANCHOR anchor,					// �A���J�[
		UIType type) override;						// UI�̎��
private:
	// private�֐�
	// �X�V���ɒ���I��UI��ǉ�����
	void AddNextTiles();
	// �V�����p�l����z�u
	void AddToPanel();
	// ���̈ʒu�Ƀ^�C����߂�
	void ResetTilePosition();

private:
	// private�֐�
	// �f�o�C�X���\�[�X
	DX::DeviceResources* m_pDR;
	// ���ʃ��\�[�X
	CommonResources* m_pCommonResources;
	// �I���\UI
	std::vector<std::unique_ptr<Canvas>> m_pUI;
	// �w�iUI
	std::vector<std::unique_ptr<Canvas>> m_pBackUI;
	// �I�𒆂ł��邱�Ƃ�\������UI
	std::unique_ptr<Canvas> m_pSelectedUI;
	// �}�E�X�̃|�C���^�[
	MyMouse* m_pMouse;
	// �e�I���\UI�̏����ʒu���X�g
	std::vector<DirectX::SimpleMath::Vector2> m_initialPositions;
	// �h���b�O����UI�C���f�b�N�X
	int m_draggingIndex;
	// �E�B���h�E�̕��ƍ���
	int m_windowWidth, m_windowHeight;
	// ����
	float m_time;
	// �q�b�g�t���O
	bool m_hit;
	// �q�b�g�t���O��������UI�̃C���f�b�N�X
	int m_menuIndex;
	// ����p�r���[�|�[�g
	D3D11_VIEWPORT m_viewPortControll;
	// �g���^�C���̎���
	std::vector<std::string> m_tilesDictionary;
};