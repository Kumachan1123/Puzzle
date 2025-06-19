#include <pch.h>
#include "CSVMap.h"

CSVMap::CSVMap(CommonResources* resources)
{
	m_commonResources = resources;
	DrawCollision::Initialize(m_commonResources);// �����蔻��`��̏�����
	LoadModel();
}

CSVMap::~CSVMap()
{
}

void CSVMap::LoadModel()
{
	using namespace DirectX;
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// ���f����ǂݍ��ޏ���
	std::unique_ptr<EffectFactory> fx = std::make_unique<EffectFactory>(device);
	fx->SetDirectory(L"Resources/models");
	//�e�N�X�`���p�X��ݒ肷��
	wcscpy_s(m_modelPath, L"Resources/models/Block.cmo");

	// ���f����ǂݍ���
	m_pModel = m_commonResources->GetModelManager()->GetModel("Block");
}

void CSVMap::LoadMap(const std::string& filePath)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	// csv�t�@�C�����J��
	std::ifstream file = std::ifstream(filePath);
	if (!file.is_open())
	{
		return;
	}
	std::string line;
	for (int i = 0; i < MAXCOL && std::getline(file, line); ++i)
	{
		std::stringstream ss(line);
		std::string cell;
		int j = 0;
		while (j < MAXRAW && std::getline(ss, cell, ','))
		{
			if (!cell.empty() && cell[0] == 'w') // �J���}�ŋ�؂�ꂽ�e�Z��������
			{
				// ()�̒��g�̐��l�������邱�ƂŊԊu�𒲐����邱�Ƃ��ł���
				float x = static_cast<float>(j * 2);
				float z = static_cast<float>(i * 2);
				float y = 0.0f; // �K�v�ɉ����Ă��̒l��ύX

				// �L���[�u�𐳂����ʒu�Ɉړ����邽�߂̕ϊ���K�p
				DirectX::SimpleMath::Matrix worldMatrix;
				worldMatrix = DirectX::SimpleMath::Matrix::CreateScale(1.0f); // �X�P�[����K�p
				worldMatrix *= DirectX::SimpleMath::Matrix::CreateTranslation(x, y, z);

				// ���[���h�s���ۑ�
				worldMatrices.push_back(worldMatrix);
				// ���E�{�b�N�X���쐬
				DirectX::BoundingBox box;
				box.Center = Vector3(x, y, z);
				box.Extents = Vector3(1.0f, 1.0f, 1.0f); // �T�C�Y�𒲐�
				m_wallBox.push_back(box);

			}
			else if (!cell.empty() && cell[0] == 'g')
			{
				// ()�̒��g�̐��l�������邱�ƂŊԊu�𒲐����邱�Ƃ��ł���
				float x = static_cast<float>(j * 2);
				float z = static_cast<float>(i * 2);
				float y = 0.0f; // �K�v�ɉ����Ă��̒l��ύX

				m_goalPosition = Vector3{ x, y, z };
				// �S�[���̋��E�{�b�N�X���쐬
				DirectX::BoundingBox box;
				box.Center = Vector3(x, y, z);
				box.Extents = Vector3(1.0f, 1.0f, 1.0f); // �T�C�Y�𒲐�
				m_goalBox = box;
			}
			++j;
		}
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
	DrawCollision::DrawBoundingBox(m_goalBox, Colors::Green);
	DrawCollision::DrawEnd();// �`��I��

#endif
}

void CSVMap::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	// worlsMatrices�ɕۑ�����Ă���f�[�^��p����Box��`�悷��
	for (const auto& world : worldMatrices)
	{


		// ���f���̕`��i�e�N�X�`��ON�o�[�W�����j
		m_pModel->Draw(context, *states, world, view, proj, false);

	}
	this->DrawCollision(view, proj);
}
