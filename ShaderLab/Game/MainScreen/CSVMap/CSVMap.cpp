#include <pch.h>
#include "CSVMap.h"

CSVMap::CSVMap(CommonResources* resources)
{
	m_commonResources = resources;
	InitializeTileDictionary();
	DrawCollision::Initialize(m_commonResources);// �����蔻��`��̏�����
	LoadModel();
}

CSVMap::~CSVMap()
{
}
void CSVMap::InitializeTileDictionary()
{
	m_tileDictionary["w"] = TileInfo{ "Block", true };
	m_tileDictionary["s"] = TileInfo{ "Start", true };
	m_tileDictionary["g"] = TileInfo{ "Goal", true };
	m_tileDictionary[""] = TileInfo{ "", false }; // �󔒗p
}

void CSVMap::LoadModel()
{
	using namespace DirectX;
	// ���f����ǂݍ���
	m_pModel = m_commonResources->GetModelManager()->GetModel("Block");
}

void CSVMap::LoadMap(const std::string& filePath)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	std::ifstream file(filePath);
	if (!file.is_open()) return;

	std::string line;
	int row = 0;
	while (std::getline(file, line) && row < MAXCOL)
	{
		std::stringstream ss(line);
		std::string cell;
		int col = 0;
		while (std::getline(ss, cell, ',') && col < MAXRAW)
		{
			auto it = m_tileDictionary.find(cell);
			if (it != m_tileDictionary.end())
			{
				const TileInfo& tileInfo = it->second;

				//if (tileInfo.modelName.empty()) continue;

				// ���W�v�Z
				Vector3 pos(static_cast<float>(col * 2), 0.0f, static_cast<float>(row * 2));
				Matrix world = Matrix::CreateScale(tileInfo.scale) * Matrix::CreateTranslation(pos);

				// ���f���擾
				DirectX::Model* model = m_commonResources->GetModelManager()->GetModel(tileInfo.modelName);

				// �^�C���f�[�^�ۑ�
				m_tiles.push_back(TileRenderData{ model, world });

				// �����蔻��
				if (tileInfo.hasCollision)
				{
					BoundingBox box;
					box.Center = pos;
					box.Extents = tileInfo.scale;
					m_wallBox.push_back(box);
				}
			}

			++col;
		}
		++row;
	}
}

void CSVMap::DrawCollision(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(view);// ���g�p�̌x�����o���Ȃ�
	UNREFERENCED_PARAMETER(proj);// ���g�p�̌x�����o���Ȃ�
#ifdef _DEBUG
	DrawCollision::DrawStart(view, proj);// �`��J�n
	for (int i = 0; i < m_wallBox.size(); i++)
	{
		DrawCollision::DrawBoundingBox(m_wallBox[i], Colors::Red);
	}
	DrawCollision::DrawEnd();// �`��I��

#endif
}

void CSVMap::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	for (const auto& tile : m_tiles)
	{
		if (tile.model)
		{
			tile.model->Draw(context, *states, tile.world, view, proj, false);
		}
	}

	DrawCollision(view, proj);
}
