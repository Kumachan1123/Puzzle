/*
*	@file ItemBase.h
*	@brief アイテムのベースクラス
*/
#pragma once
// 自作ヘッダーファイル
#include "Game/MainScreen/Items/ItemDatas/ItemDatas.h"
// 前方宣言
class MiniCharacter;
class CommonResources;
// アイテムベースクラス
class ItemBase
{
	// アクセサ
public:
	// アイテムの位置を取得する
	virtual const DirectX::SimpleMath::Vector3& GetPosition() const = 0;
	// アイテムの位置を設定する
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& pos) = 0;
	// アイテムのモデルを取得する
	virtual DirectX::Model* GetModel() const = 0;
	// アイテムのモデルを設定する
	virtual void SetModel(DirectX::Model* model) = 0;
	// アイテムのワールド行列を取得する
	virtual const DirectX::SimpleMath::Matrix& GetWorldMatrix() const = 0;
	// アイテムのワールド行列を設定する
	virtual void SetWorldMatrix(const DirectX::SimpleMath::Matrix& world) = 0;


	// public関数
public:
	// デストラクタ
	virtual ~ItemBase() = default;
	// 初期化
	virtual void Initialize(CommonResources* resources, const ItemInfo& info) = 0;
	// 更新
	virtual void Update(float elapsedTime) = 0;
	// 描画
	virtual void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj) = 0;
	// アイテムを取得したときの処理
	virtual void OnGet(MiniCharacter* miniCharacter) = 0;
	// アイテムを使用したときの処理
	virtual void OnUse(MiniCharacter* miniCharacter) = 0;
	// アイテムを破棄したときの処理
	virtual void OnDiscard(MiniCharacter* miniCharacter) = 0;

};