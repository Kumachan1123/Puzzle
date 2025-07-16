/*
*	@file CSVItem.h
*	@brief CSV�`���̃A�C�e�����z��ǂݍ��݁A�`�悷��N���X
*/
#pragma once
// �W�����C�u����
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cassert>
// DirectX�֘A
#include <DeviceResources.h>
#include <SimpleMath.h>
#include <Model.h>
#include <Effects.h>
// �O�����C�u����
#include <Libraries/MyLib/DebugString.h>
// ����w�b�_�[�t�@�C��
#include "Game/CommonResources/CommonResources.h"
#include "KumachiLib/DrawCollision/DrawCollision.h"
#include "Game/TileDatas/TileDatas.h"
#include "Game/MainScreen/Tiles/TileFactory/TileFactory.h"
// �O���錾
class CommonResources;

// CSV�`���̃}�b�v��ǂݍ���
class CSVItem
{
public:
	// �A�N�Z�T
	// �w��ʒu�̃^�C�������擾����(�s, ��)
	const MapTileData& GetTileData(int row, int col) const;
	// �w����W�̃^�C�������擾����(���[���h���W)
	const MapTileData& GetTileData(const DirectX::SimpleMath::Vector3& pos) const;

	// �}�b�v�̍ő�񐔂ƍs�����擾����
	const int GetMaxCol() const { return MAXCOL; }// ��
	const int GetMaxRow() const { return MAXRAW; }// �s��
	//// �w�肵���ʒu�Ɏw�肵�����f����z�u����
	//void SetTileModel(int row, int col, const std::string& modelName);
	//// �X�^�[�g�n�_��Ԃ�
	//const MapTileData& GetStart() const;
public:
	// public�֐�
	// �R���X�g���N�^
	CSVItem(CommonResources* resources);
	// �f�X�g���N�^
	~CSVItem();
	// CSV�`���̃A�C�e���z�u��ǂݍ���
	void LoadItem(const std::string& filePath);
	// �����蔻��`��
	void DrawCollision(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
private:
	// private�֐�
	// ����������������
	void InitializeTileDictionary();

private:
	CommonResources* m_pCommonResources;
	//�}�b�v
	const int MAXCOL = 5;
	const int MAXRAW = 5;
	// �^�C���̎���
	std::unordered_map<std::string, TileInfo> m_tileDictionary;
	// �^�C���̃����_�����O�f�[�^
	std::vector<TileRenderData> m_tiles;
	// �}�b�v�f�[�^
	std::vector<std::vector<MapTileData>> m_mapData;

};