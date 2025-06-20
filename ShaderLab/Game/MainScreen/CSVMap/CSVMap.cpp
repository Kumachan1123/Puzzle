/*
*	@file CSVMap.cpp
*	@brief CSV�`���̃}�b�v��ǂݍ��݁A�`�悷��N���X
*/
#include <pch.h>
#include "CSVMap.h"
/*
*	@brief �R���X�g���N�^
*	@details �������ɋ��ʃ��\�[�X�ւ̃|�C���^���󂯎��A���������s���B
*	@param resources ���ʃ��\�[�X�ւ̃|�C���^
*	@return �Ȃ�
*/
CSVMap::CSVMap(CommonResources* resources)
{
	// ���ʃ��\�[�X�ւ̃|�C���^��ۑ�
	m_commonResources = resources;
	// �}�b�v�̃^�C���̎�����������
	InitializeTileDictionary();
	// �����蔻��`��̏�����
	DrawCollision::Initialize(m_commonResources);
	// �}�b�v�̓ǂݍ���
	LoadModel();
}
/*
*	@brief �f�X�g���N�^
*	@details �������Ɋm�ۂ������\�[�X���������B
*	@param �Ȃ�
*	@return �Ȃ�
*/
CSVMap::~CSVMap()
{
	// ���ʃ��\�[�X�̉���͕s�v
	// DrawCollision�̏I�������͕s�v
	// �^�C���̎������N���A
	m_tileDictionary.clear();
	// �^�C���̃����_�����O�f�[�^���N���A
	m_tiles.clear();

}
/*
*	@brief �^�C���̎���������������
*	@details �^�C���̎�ނƂ��̏��������ɓo�^����B
*	@param �Ȃ�
*	@return �Ȃ�
*/
void CSVMap::InitializeTileDictionary()
{
	// �^�C���̎�ނƂ��̏��������ɓo�^
	// �ʏ�̏�
	m_tileDictionary["w"] = TileInfo{ "Block", true };
	// �X�^�[�g�n�_
	m_tileDictionary["s"] = TileInfo{ "Start", true };
	// �S�[���n�_
	m_tileDictionary["g"] = TileInfo{ "Goal", true };
}
/*
*	@brief ���f����ǂݍ���
*	@details ���f���}�l�[�W���[����K�v�ȃ��f�����擾����B
*	@param �Ȃ�
*	@return �Ȃ�
*/
void CSVMap::LoadModel()
{
	// ���f����ǂݍ���
	m_pModel = m_commonResources->GetModelManager()->GetModel("Block");
}
/*
*	@brief CSV�`���̃}�b�v��ǂݍ���
*	@details �w�肳�ꂽ�t�@�C���p�X����CSV�`���̃}�b�v�f�[�^��ǂݍ��݁A�^�C���̏�����͂��ă}�b�v���\�z����B
*	@param filePath �ǂݍ���CSV�t�@�C���̃p�X
*	@return �Ȃ�
*/
void CSVMap::LoadMap(const std::string& filePath)
{
	// DirectX��SimpleMath�̖��O��Ԃ��g�p
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	// �t�@�C�����J��
	std::ifstream file(filePath);
	// �t�@�C�����J���Ȃ������ꍇ�͉������Ȃ�
	if (!file.is_open()) return;
	// �}�b�v�̏�����
	std::string line;
	// �s�ԍ���������
	int row = 0;
	// �}�b�v���S�␳�l�v�Z
	float mapWidth = MAXRAW * 2.0f;
	float mapHeight = MAXCOL * 2.0f;
	// ���S�␳�l���v�Z
	float offsetX = mapWidth / 2.0f - 1.0f;
	float offsetZ = mapHeight / 2.0f - 1.0f;
	// �}�b�v�̍s�Ɨ��ǂݍ���
	while (std::getline(file, line) && row < MAXCOL)
	{
		// �s�̕�������J���}�ŕ������ăZ�����Ƃɏ���
		std::stringstream ss(line);
		// �Z���̕�������i�[����ϐ�
		std::string cell;
		// ��ԍ���������
		int col = 0;
		// �Z�����Ƃɏ���
		while (std::getline(ss, cell, ',') && col < MAXRAW)
		{
			// �Z���̕����񂪋�̏ꍇ�̓X�L�b�v
			auto it = m_tileDictionary.find(cell);
			// �Z���̕����񂪎����ɑ��݂���ꍇ
			if (it != m_tileDictionary.end())
			{
				// �^�C�������擾
				const TileInfo& tileInfo = it->second;
				// �^�C���̈ʒu�v�Z�i�}�b�v���S�␳�j
				float x = static_cast<float>(col * 2) - offsetX;
				float z = static_cast<float>(row * 2) - offsetZ;
				// ���[���h���W���v�Z
				Vector3 pos(x, 0.0f, z);
				// ���[���h�s����쐬�i�X�P�[�����O�ƈʒu�̐ݒ�j
				Matrix world = Matrix::CreateScale(tileInfo.scale) * Matrix::CreateTranslation(pos);
				// ���f���擾
				DirectX::Model* model = m_commonResources->GetModelManager()->GetModel(tileInfo.modelName);
				// �^�C���f�[�^�ۑ�
				m_tiles.push_back(TileRenderData{ model, world });
				// �����蔻��
				if (tileInfo.hasCollision)
				{
					// �����蔻��p�̃{�b�N�X���쐬
					BoundingBox box;
					// �{�b�N�X�̒��S�Ɗg�嗦��ݒ�
					box.Center = pos;
					// �g�嗦��ݒ�
					box.Extents = tileInfo.scale;
					// �{�b�N�X�̊g�嗦��2�{�ɂ���i�����蔻��p�j
					m_wallBox.push_back(box);
				}
			}
			// �}�b�v�̗�ɒl��ݒ�
			++col;
		}
		// �}�b�v�̍s�ɒl��ݒ�
		++row;
	}
}
/*
*	@brief �����蔻���`�悷��
*	@details �f�o�b�O���[�h�œ����蔻��̃{�b�N�X��`�悷��B
*	@param view �r���[�s��
*	@param proj �v���W�F�N�V�����s��
*	@return �Ȃ�
*/
void CSVMap::DrawCollision(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	// DirectX��SimpleMath�̖��O��Ԃ��g�p
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	// ���g�p�̌x�����o���Ȃ�
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(proj);
	// �����蔻��̕`����J�n
#ifdef _DEBUG
	// �`��J�n
	DrawCollision::DrawStart(view, proj);
	// �����蔻��̃{�b�N�X��`��
	for (int i = 0; i < m_wallBox.size(); i++)	DrawCollision::DrawBoundingBox(m_wallBox[i], Colors::Red);
	// �`��I��
	DrawCollision::DrawEnd();

#endif
}
/*
*	@brief �}�b�v��`�悷��
*	@details �}�b�v�̃^�C����`�悷��B
*	@param view �r���[�s��
*	@param proj �v���W�F�N�V�����s��
*	@return �Ȃ�
*/
void CSVMap::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	// �f�o�C�X�R���e�L�X�g���擾
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	// ���ʂ̃X�e�[�g���擾
	auto states = m_commonResources->GetCommonStates();
	// �S�^�C����`�悷��
	for (const auto& tile : m_tiles)
	{
		// ���f�������݂���ꍇ�̂ݕ`��
		if (tile.model)
		{
			// ���f���̕`��
			tile.model->Draw(context, *states, tile.world, view, proj, false);
		}
	}
	//// �����蔻��̕`��
	//DrawCollision(view, proj);
}
