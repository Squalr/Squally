#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class LocalizedLabel;
class LocalizedString;

class BlockBase : public CipherComponentBase
{
public:
	void removeConnections();

protected:
	BlockBase(bool isToolBoxItem, ClickableNode* block, std::string iconResource, LocalizedString* label);
	~BlockBase();

	void initializePositions() override;
	void initializeListeners() override;
	virtual BlockBase* spawn() = 0;
	bool isInGameArea();

	bool isToolBoxItem;
	bool isStaticObject;

private:
	typedef CipherComponentBase super;

	ClickableNode* block;
	cocos2d::Sprite* icon;
	LocalizedLabel* label;
	
	cocos2d::Vec2 originalPosition;
	cocos2d::Vec2 clickDelta;
};
