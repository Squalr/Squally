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
class MenuSprite;
class ScrollPane;
class TextMenuSprite;

class HexusOpponentMenuBase : public GlobalScene
{
protected:
	HexusOpponentMenuBase(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter chapter, std::string chapterProgressSaveKey);
	~HexusOpponentMenuBase();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadProgress();
	void onBackClick(MenuSprite* menuSprite);
	void onDeckManagementClick(MenuSprite* menuSprite);
	void onShopClick(MenuSprite* menuSprite);
	void onMouseOver(HexusOpponentPreview* opponent);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter chapter;

	ScrollPane* scrollPane;
	std::vector<HexusOpponentPreview*> opponents;
	std::map<HexusOpponentPreview*, HexusOpponentPreview*> dependencies;

	std::string chapterProgressSaveKey;
	cocos2d::Sprite* background;
	TextMenuSprite* deckManagementButton;
	TextMenuSprite* shopButton;
	LocalizedLabel* opponentSelectLabel;
	TextMenuSprite* backButton;
private:
	typedef GlobalScene super;
};
