/*
*	@file Mouse.h
*	@brief �}�E�X�N���X
*/
#pragma once
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

// �O���錾
class CommonResources;

// �}�E�X�N���X
class MyMouse
{
public:
	// �A�N�Z�T
	// �}�E�X�̈ʒu���擾
	DirectX::SimpleMath::Vector2 GetPosition() const { return m_position; }
	// �}�E�X�̈ʒu��ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector2& position) { m_position = position; }
	// �_���𑜓x��̃r���[�|�[�g����X���擾
	float GetVpLeftUI() const { return m_vp_left_UI; }
	// �_���𑜓x��̃r���[�|�[�g����Y���擾
	float GetVpTopUI() const { return m_vp_top_UI; }
	// �_���𑜓x��̃r���[�|�[�g�����擾
	float GetVpWidthUI() const { return m_vp_width_UI; }
	// �_���𑜓x��̃r���[�|�[�g�������擾
	float GetVpHeightUI() const { return m_vp_height_UI; }
	// 
	// �r���[�|�[�g��ݒ�
	void SetViewport(const D3D11_VIEWPORT& viewport) { m_viewPortControll = viewport; }

public:
	// public�֐�
	// �R���X�g���N�^
	MyMouse();
	// �f�X�g���N�^
	~MyMouse();
	// ������
	void Initialize(CommonResources* resources);
	// �X�V
	void Update(const float elapsedTime);
private:
	// private�ϐ�
	// ���ʃ��\�[�X
	CommonResources* m_pCommonResources;
	// �}�E�X�̈ʒu
	DirectX::SimpleMath::Vector2 m_position;
	// ����p�r���[�|�[�g
	D3D11_VIEWPORT m_viewPortControll;
	// �E�B���h�E�̕�
	float m_renderWidth;
	// �E�B���h�E�̍���
	float m_renderHeight;
	// �_���𑜓x��̃r���[�|�[�g����X
	float m_vp_left_UI;
	// �_���𑜓x��̃r���[�|�[�g����Y
	float m_vp_top_UI;
	// �_���𑜓x��̃r���[�|�[�g��
	float m_vp_width_UI;
	// �_���𑜓x��̃r���[�|�[�g����
	float m_vp_height_UI;
};