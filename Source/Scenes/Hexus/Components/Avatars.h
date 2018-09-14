#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"

#include "ComponentBase.h"

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

	void initializePositions() override;
	void setAvatars(GameState* gameState);

	ClippingNode* clipPlayer;
	ClippingNode* clipEnemy;
	Sprite* framePlayer;
	Sprite* frameEnemy;
	Node* avatarPlayer;
	Node* avatarEnemy;
};
