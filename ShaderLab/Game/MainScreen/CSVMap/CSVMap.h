/*
*	@file CSVMap.h
*	@brief CSV�`���̃}�b�v��ǂݍ��݁A�`�悷��N���X
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
// ����w�b�_�[�t�@�C��
#include "Game/CommonResources/CommonResources.h"
#include "KumachiLib/DrawCollision/DrawCollision.h"

// �O���錾
class CommonResources;

// CSV�`���̃}�b�v��ǂݍ���
class CSVMap
{
public:
	// �^�C���̏��\����
	struct TileInfo
	{
		std::string modelName;                   // �g�p���郂�f����
		bool hasCollision = false;              // �����蔻�������
		DirectX::SimpleMath::Vector3 scale = { 1.0f, 1.0f, 1.0f }; // �X�P�[�����O
	};
	// �^�C���̃����_�����O�f�[�^�\����
	struct TileRenderData
	{
		DirectX::Model* model;
		DirectX::SimpleMath::Matrix world;
	};
	// �}�b�v��1�}�X���̏��
	struct MapTileData
	{
		TileInfo tileInfo;               // ���̏ꏊ�̃^�C����ށiBlock�AStart�AGoal�Ȃǁj
		DirectX::SimpleMath::Vector3 pos; // ���̃}�X�̃��[���h���W
		bool hasCollision = false;               // �����蔻�肠�邩
	};
public:
	// �A�N�Z�T
	// �w��ʒu�̃^�C�������擾����
	const MapTileData& GetTileData(int col, int row) const;
	// �}�b�v�̍ő�񐔂ƍs�����擾����
	const int GetMaxCol() const { return MAXCOL; }// ��
	const int GetMaxRow() const { return MAXRAW; }// �s��
public:
	CSVMap(CommonResources* resources);
	~CSVMap();
	void LoadModel();
	void LoadMap(const std::string& filePath);
	void DrawCollision(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
private:
	void InitializeTileDictionary();

private:
	CommonResources* m_commonResources;
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