#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

class SmartAnimationNode;

class Avatars : public ComponentBase
{
public:
	static Avatars* create();

	void initializeEnemyAvatar(HexusOpponentData* opponentData);

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	Avatars();
	~Avatars();

	void initializePositions() override;
	void setAvatars(GameState* gameState);

	cocos2d::ClippingNode* clipPlayer;
	cocos2d::ClippingNode* clipEnemy;
	cocos2d::Sprite* framePlayer;
	cocos2d::Sprite* frameEnemy;
	cocos2d::Node* avatarPlayer;
	cocos2d::Node* avatarEnemy;
	SmartAnimationNode* playerSprite;
	SmartAnimationNode* opponentSprite;
};
