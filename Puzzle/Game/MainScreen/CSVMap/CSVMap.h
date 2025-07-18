/*
*	@file CSVMap.h
*	@brief CSV形式のマップを読み込み、描画するクラス
*/
#pragma once
// 標準ライブラリ
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cassert>
// DirectX関連
#include <DeviceResources.h>
#include <SimpleMath.h>
#include <Model.h>
#include <Effects.h>
// 外部ライブラリ
#include <Libraries/MyLib/DebugString.h>
// 自作ヘッダーファイル
#include "Game/CommonResources/CommonResources.h"
#include "KumachiLib/DrawCollision/DrawCollision.h"
#include "Game/MainScreen/Tiles/TileDatas/TileDatas.h"
#include "Game/MainScreen/Tiles/TileFactory/TileFactory.h"
// 前方宣言
class CommonResources;

// CSV形式のマップを読み込む
class CSVMap
{
public:
	// アクセサ
	// 指定位置のタイル情報を取得する(行, 列)
	const MapTileData& GetTileData(int row, int col) const;
	// 指定座標のタイル情報を取得する(ワールド座標)
	const MapTileData& GetTileData(const DirectX::SimpleMath::Vector3& pos) const;
	// 指定座標の行番号を取得する
	int GetRowFromPosition(const DirectX::SimpleMath::Vector3& pos) const;
	// 指定座標の列番号を取得する
	int GetColFromPosition(const DirectX::SimpleMath::Vector3& pos) const;
	// マップの最大列数と行数を取得する
	const int GetMaxCol() const { return MAXCOL; }// 列数
	const int GetMaxRow() const { return MAXRAW; }// 行数
	// 指定した位置に指定したモデルを配置する
	void SetTileModel(int row, int col, const std::string& modelName);
	// スタート地点を返す
	const MapTileData& GetStart() const;
public:
	// public関数
	// コンストラクタ
	CSVMap(CommonResources* resources);
	// デストラクタ
	~CSVMap();
	// 初期化
	void LoadModel();
	// CSV形式のマップを読み込む
	void LoadMap(const std::string& filePath);
	// 当たり判定描画
	void DrawCollision(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);
private:
	// private関数
	// 辞書を初期化する
	void InitializeTileDictionary();
private:
	// 場外のタイルデータ
	const MapTileData m_outOfMapData = { {""},DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f) };
private:
	CommonResources* m_pCommonResources;
	//マップ
	const int MAXCOL = 5;
	const int MAXRAW = 5;
	// タイルの辞書
	std::unordered_map<std::string, TileInfo> m_tileDictionary;
	// タイルのレンダリングデータ
	std::vector<TileRenderData> m_tiles;
	// マップデータ
	std::vector<std::vector<MapTileData>> m_mapData;

};