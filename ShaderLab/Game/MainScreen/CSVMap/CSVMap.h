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
	// �^�C���̏��\����
	struct TileInfo
	{
		std::string modelName;                   // �g�p���郂�f����
		bool hasCollision = false;              // �����蔻�������
		DirectX::SimpleMath::Vector3 scale = { 1.0f, 1.0f, 1.0f }; // �X�P�[�����O
	};
	struct TileRenderData
	{
		DirectX::Model* model;
		DirectX::SimpleMath::Matrix world;
	};
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
	static const int MAXCOL = 5;
	static const int MAXRAW = 5;
	char m_map[MAXCOL][MAXRAW];
	// CSVMap �̃����o�ɒǉ�
	std::unordered_map<std::string, TileInfo> m_tileDictionary;
	std::vector<TileRenderData> m_tiles;

	std::vector<DirectX::BoundingBox> m_wallBox;
	//std::vector<DirectX::SimpleMath::Matrix> worldMatrices;
	DirectX::Model* m_pModel;
	// ���f���p�X
	wchar_t m_modelPath[256];


};