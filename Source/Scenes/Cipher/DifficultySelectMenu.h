#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;

class DifficultySelectMenu : public SmartNode
{
public:
	static DifficultySelectMenu* create();

	void show(std::function<void()> onEasySelect, std::function<void()> onHardSelect, std::function<void()> onCancelSelect);

private:
	typedef SmartNode super;
	DifficultySelectMenu();
	~DifficultySelectMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Sprite* panel;
	LocalizedLabel* cipherLabel;
	LocalizedLabel* bonusMessage;
	ClickableTextNode* easyButton;
	ClickableTextNode* hardButton;
	ClickableTextNode* cancelButton;
};
