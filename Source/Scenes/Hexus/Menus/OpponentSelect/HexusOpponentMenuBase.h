#pragma once
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/GlobalScene.h"
#include "Events/NavigationEvents.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class HexusOpponentPreview;
class ClickableNode;
class ScrollPane;
class ClickableTextNode;

class HexusOpponentMenuBase : public GlobalScene
{
protected:
	HexusOpponentMenuBase(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter chapter, std::string chapterProgressSaveKey);
	~HexusOpponentMenuBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadProgress();
	void onBackClick(ClickableNode* menuSprite);
	void onDeckManagementClick(ClickableNode* menuSprite);
	void onShopClick(ClickableNode* menuSprite);
	void onMouseOver(HexusOpponentPreview* opponent);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter chapter;

	ScrollPane* scrollPane;
	std::vector<HexusOpponentPreview*> opponents;
	std::map<HexusOpponentPreview*, HexusOpponentPreview*> dependencies;

	std::string chapterProgressSaveKey;
	cocos2d::Sprite* background;
	ClickableTextNode* deckManagementButton;
	ClickableTextNode* shopButton;
	LocalizedLabel* opponentSelectLabel;
	ClickableTextNode* backButton;
private:
	typedef GlobalScene super;
};
