#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

namespace cocos2d
{
	class ClippingNode;
	class Sprite;
}

class HexusOpponentData;
class SmartAnimationNode;
class SmartClippingNode;

class Avatars : public ComponentBase
{
public:
	static Avatars* create();

	void initializeEnemyAvatar(HexusOpponentData* opponentData);

protected:
	Avatars();
	virtual ~Avatars();

	void onEnter() override;
	void initializePositions() override;
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	void setAvatars(GameState* gameState);

	SmartClippingNode* clipPlayer;
	SmartClippingNode* clipEnemy;
	cocos2d::Sprite* framePlayer;
	cocos2d::Sprite* frameEnemy;
	cocos2d::Node* avatarPlayer;
	cocos2d::Node* avatarEnemy;
	cocos2d::Node* playerBackground;
	SmartAnimationNode* playerPreview;
	cocos2d::Node* opponentPreview;
};
