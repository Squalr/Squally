#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"

#include "Scenes/Hexus/Components/ComponentBase.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class Avatars : public ComponentBase
{
public:
	static Avatars * create();

	void initializeEnemyAvatar(HexusOpponentData* opponentData);

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

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
	AnimationNode* playerSprite;
	AnimationNode* opponentSprite;
};
