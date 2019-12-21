#include "Avatars.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/UI/SmartClippingNode.h"
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
	this->playerBackground = Node::create();
	this->playerPreview = SmartAnimationNode::create(EntityResources::Squally_Animations);
	this->opponentPreview = nullptr;

	this->playerPreview->playAnimation(SmartAnimationNode::AnimationPlayMode::Repeat);
	
	this->clipPlayer = SmartClippingNode::create(this->avatarPlayer, 188.0f / 2.0f, Vec2::ZERO, 48);
	this->clipEnemy = SmartClippingNode::create(this->avatarEnemy, 188.0f / 2.0f, Vec2::ZERO, 48);

	this->avatarPlayer->addChild(this->playerBackground);
	this->avatarPlayer->addChild(this->playerPreview);
	this->addChild(this->clipPlayer);
	this->addChild(this->clipEnemy);
	this->addChild(this->framePlayer);
	this->addChild(this->frameEnemy);
}

Avatars::~Avatars()
{
}

void Avatars::onEnter()
{
	super::onEnter();

	this->playerPreview->playAnimation(SmartAnimationNode::AnimationPlayMode::Repeat);
}

void Avatars::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->framePlayer->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::frameOffsetX, visibleSize.height / 2.0f - Config::frameOffsetY);
	this->frameEnemy->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::frameOffsetX, visibleSize.height / 2.0f + Config::frameOffsetY);
	this->clipPlayer->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::frameOffsetX, visibleSize.height / 2.0f - Config::frameOffsetY);
	this->clipEnemy->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::frameOffsetX, visibleSize.height / 2.0f + Config::frameOffsetY);
	
	this->playerPreview->setPosition(Vec2(-24.0f, -112.0f));
}

void Avatars::initializeEnemyAvatar(HexusOpponentData* opponentData)
{
	this->avatarEnemy->removeAllChildren();
	this->playerBackground->removeAllChildren();

	this->opponentPreview = opponentData->entityPreviewNode;

	this->playerBackground->addChild(Sprite::create(opponentData->backgroundResourceFile));
	this->avatarEnemy->addChild(Sprite::create(opponentData->backgroundResourceFile));
	this->avatarEnemy->addChild(this->opponentPreview);
	this->avatarEnemy->setPosition(opponentData->avatarOffset);
}

void Avatars::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void Avatars::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);
}

void Avatars::setAvatars(GameState* gameState)
{
}
