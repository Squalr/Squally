#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class ConstantString;
class LocalizedLabel;
class PlatformerEntity;

class QuickSwapMenu : public SmartNode
{
public:
	static QuickSwapMenu* create();

	void open();
	void setReturnClickCallback(std::function<void()> returnClickCallback);

protected:
	QuickSwapMenu();
	virtual ~QuickSwapMenu();
	
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void onReturnClick();

	cocos2d::LayerColor* backdrop = nullptr;
	cocos2d::Sprite* window = nullptr;
	LocalizedLabel* titleLabel = nullptr;
	ClickableNode* closeButton = nullptr;
	ClickableTextNode* returnButton = nullptr;

	ClickableTextNode* guanoNode = nullptr;
	ClickableTextNode* geckyNode = nullptr;
	ClickableTextNode* grimNode = nullptr;

	std::function<void(PlatformerEntity*)> onSelect = nullptr;
	std::function<void()> returnClickCallback = nullptr;
};
