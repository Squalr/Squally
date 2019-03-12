#include "Avatars.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

Avatars* Avatars::create()
{
	Avatars* instance = new Avatars();

	instance->autorelease();

	return instance;
}

Avatars::Avatars()
{
	this->framePlayer = Sprite::create(HexusResources::AvatarFrame);
	this->frameEnemy = Sprite::create(HexusResources::AvatarFrame);
	this->avatarPlayer = Node::create();
	this->avatarEnemy = Node::create();
	this->playerSprite = SmartAnimationNode::create(EntityResources::Squally_Animations);

	this->playerSprite->playAnimation(SmartAnimationNode::AnimationPlayMode::Repeat);

	DrawNode* stencilLeft = DrawNode::create();
	DrawNode* stencilRight = DrawNode::create();
	stencilLeft->drawSolidCircle(Vec2(0.0f, 0.0f), 184.0f / 2.0f, 0.0f, 48, Color4F::GREEN);
	stencilRight->drawSolidCircle(Vec2(0.0f, 0.0f), 184.0f / 2.0f, 0.0f, 48, Color4F::GREEN);

	// Enable to debug clipping:
	// this->addChild(stencilLeft);
	// this->addChild(stencilRight);

	this->clipPlayer = ClippingNode::create(stencilLeft);
	this->clipEnemy = ClippingNode::create(stencilRight);

	this->addChild(this->framePlayer);
	this->addChild(this->frameEnemy);
	this->avatarPlayer->addChild(this->playerSprite);
	this->clipPlayer->addChild(this->avatarPlayer);
	this->clipEnemy->addChild(this->avatarEnemy);
	this->addChild(this->clipPlayer);
	this->addChild(this->clipEnemy);
}

Avatars::~Avatars()
{
}

void Avatars::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->framePlayer->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::frameOffsetX, visibleSize.height / 2.0f - Config::frameOffsetY);
	this->frameEnemy->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::frameOffsetX, visibleSize.height / 2.0f + Config::frameOffsetY);
	this->clipPlayer->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::frameOffsetX, visibleSize.height / 2.0f - Config::frameOffsetY);
	this->clipEnemy->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::frameOffsetX, visibleSize.height / 2.0f + Config::frameOffsetY);
}

void Avatars::initializeEnemyAvatar(HexusOpponentData* opponentData)
{
	this->avatarEnemy->removeAllChildren();
	GameUtils::changeParent(this->playerSprite, nullptr, true);

	this->opponentSprite = SmartAnimationNode::create(opponentData->animationResourceFile);

	this->avatarEnemy->addChild(Sprite::create(opponentData->backgroundResourceFile));
	this->avatarEnemy->addChild(this->opponentSprite);

	this->avatarPlayer->addChild(Sprite::create(opponentData->backgroundResourceFile));
	GameUtils::changeParent(this->playerSprite, this->avatarPlayer, true);

	this->opponentSprite->playAnimation(SmartAnimationNode::AnimationPlayMode::Repeat);
	this->playerSprite->playAnimation(SmartAnimationNode::AnimationPlayMode::Repeat);

	this->opponentSprite->setScale(opponentData->animationScale);
	this->opponentSprite->setPosition(opponentData->animationOffset + opponentData->avatarOffset);
	this->playerSprite->setPosition(Vec2(-24.0f, -112.0f));
}

void Avatars::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void Avatars::onAnyStateChange(GameState* gameState)
{
	ComponentBase::onAnyStateChange(gameState);
}

void Avatars::setAvatars(GameState* gameState)
{
}
