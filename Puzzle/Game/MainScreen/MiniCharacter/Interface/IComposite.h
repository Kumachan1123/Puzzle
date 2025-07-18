#pragma once
#include "Game/MainScreen/MiniCharacter/Interface/IComponent.h"

class IComposite : public IComponent
{
public:
	// 部品を追加する
	virtual void Attach(std::unique_ptr<IComponent> turretParts) = 0;
	// 部品を削除する
	virtual void Detach(std::unique_ptr<IComponent> turretPart) = 0;
};