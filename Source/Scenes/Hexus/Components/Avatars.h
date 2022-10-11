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

	SmartClippingNode* clipPlayer = nullptr;
	SmartClippingNode* clipEnemy = nullptr;
	cocos2d::Sprite* framePlayer = nullptr;
	cocos2d::Sprite* frameEnemy = nullptr;
	cocos2d::Node* avatarPlayer = nullptr;
	cocos2d::Node* avatarEnemy = nullptr;
	cocos2d::Node* playerBackground = nullptr;
	SmartAnimationNode* playerPreview = nullptr;
	cocos2d::Node* opponentPreview = nullptr;
};
