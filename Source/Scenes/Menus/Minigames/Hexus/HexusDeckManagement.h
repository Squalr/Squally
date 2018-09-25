#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/CardStorage.h"

using namespace cocos2d;

class HexusDeckManagement : public FadeScene
{
public:
	static HexusDeckManagement * create();

protected:
	HexusDeckManagement();
	~HexusDeckManagement();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onCloseClick(MenuSprite* menuSprite);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void loadDeckCards();
	void loadStorageCards();

	void onDeckCardClick(Card* card);
	void onStorageCardClick(Card* card);
	void onDeckCardMouseOver(Card* card);
	void onStorageCardMouseOver(Card* card);

	Sprite* background;
	ScrollPane* storageScrollPane;
	ScrollPane* deckScrollPane;
	Label* storageLabel;
	Label* deckLabel;

	std::vector<Card*> deckCards;
	std::vector<Card*> storageCards;
};

