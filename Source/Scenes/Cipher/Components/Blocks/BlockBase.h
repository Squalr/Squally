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
protected:
	BlockBase(ClickableNode* block, std::string iconResource, LocalizedString* label);
	~BlockBase();

	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef CipherComponentBase super;

	ClickableNode* block;
	cocos2d::Sprite* icon;
	LocalizedLabel* label;
	cocos2d::Vec2 originalPosition;
};
