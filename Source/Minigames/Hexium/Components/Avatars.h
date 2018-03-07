#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexium/Components/ComponentBase.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class Avatars : public ComponentBase
{
public:
	static Avatars * create();

protected:
	void onStateChange(GameState* eventCustom) override;

private:
	Avatars();
	~Avatars();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void setAvatars(GameState* gameState);

	Sprite* playerFrame;
	Sprite* enemyFrame;
};
