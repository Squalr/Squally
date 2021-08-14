#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class ConfirmationMenu;
class LocalizedLabel;
class LocalizedString;

class PauseMenu : public SmartNode
{
public:
	static PauseMenu* create();

	void open(std::function<void()> resumeClickCallback);
	void close();
	void setOptionsClickCallback(std::function<void()> optionsClickCallback);
	void setQuitToTitleClickCallback(std::function<void()> quitToTitleClickCallback);
	ClickableTextNode* addNewButton(LocalizedString* text);

protected:
	PauseMenu(bool ownerInitialized = false);
	virtual ~PauseMenu();
	
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Sprite* pauseWindow = nullptr;
	LocalizedLabel* pauseLabel = nullptr;
	ClickableNode* closeButton = nullptr;
	ClickableTextNode* resumeButton = nullptr;
	ClickableTextNode* optionsButton = nullptr;
	ClickableTextNode* quitToTitleButton = nullptr;
	cocos2d::Node* newButtonsNode = nullptr;
	std::vector<ClickableTextNode*> addedButtons;
	ConfirmationMenu* exitConfirmMenu = nullptr;

	std::function<void()> resumeClickCallback = nullptr;
	std::function<void()> optionsClickCallback = nullptr;
	std::function<void()> quitToTitleClickCallback = nullptr;

private:
	typedef SmartNode super;
};
