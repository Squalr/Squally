#pragma once
#include "cocos2d.h"

#include "Events/NavigationEvents.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Controls/TextMenuSprite.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Engine/UI/Mouse.h"
#include "Menus/Confirmation/ConfirmationMenu.h"
#include "Menus/MenuBackground.h"
#include "Menus/Options/OptionsMenu.h"

using namespace cocos2d;

class TakeOverMenu : public FadeScene
{
public:
	static TakeOverMenu * create(Node* menu);

protected:
	TakeOverMenu(Node* menu);
	~TakeOverMenu();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	Node* background;
	Node* menu;
};

