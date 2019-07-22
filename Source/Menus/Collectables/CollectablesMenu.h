#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class LocalizedLabel;
class LocalizedString;
class ScrollPane;

class CollectablesMenu : public SmartNode
{
public:
	static CollectablesMenu* create();

	void setReturnClickCallback(std::function<void()> returnClickCallback);
	void open();

protected:
	CollectablesMenu();
	~CollectablesMenu();

private:
	typedef SmartNode super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void updateCollectedVisualState();
	void registerCollectableAnimal(std::string resource, std::string resourceLocked, std::string saveKey);

	cocos2d::Sprite* collectablesWindow;
	ScrollPane* contentPane;
	LocalizedLabel* collectablesLabel;
	ClickableNode* closeButton;
	ClickableTextNode* returnButton;

	std::vector<std::string> saveKeys;
	std::vector<cocos2d::Sprite*> sprites;
	std::vector<cocos2d::Sprite*> lockedSprites;

	std::function<void()> returnClickCallback;
};
