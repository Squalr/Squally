#include "Avatars.h"

Avatars* Avatars::create()
{
	Avatars* instance = new Avatars();

	instance->autorelease();

	return instance;
}

Avatars::Avatars()
{
	this->framePlayer = Sprite::create(Resources::Minigames_Hexus_AvatarFrame);
	this->frameEnemy = Sprite::create(Resources::Minigames_Hexus_AvatarFrame);
	this->avatarPlayer = Node::create();
	this->avatarEnemy = Node::create();
	this->avatarPlayer->addChild(Sprite::create(Resources::Backgrounds_Platformer_Jungle_Background));
	this->playerSprite = AnimationNode::create(Resources::Entities_Platformer_Squally_Animations);

	playerSprite->setScale(0.25f);
	playerSprite->setPosition(Vec2(-64.0f, -32.0f));

	SpriterEngine::EntityInstance* playerEntity = this->playerSprite->play("Entity");
	playerEntity->setCurrentAnimation("Idle");

	DrawNode* stencilLeft = DrawNode::create();
	DrawNode* stencilRight = DrawNode::create();
	stencilLeft->drawSolidCircle(Vec2(0.0f, 0.0f), 184.0f / 2.0f, 0.0f, 48.0f, Color4F::GREEN);
	stencilRight->drawSolidCircle(Vec2(0.0f, 0.0f), 184.0f / 2.0f, 0.0f, 48.0f, Color4F::GREEN);

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
	this->opponentSprite = AnimationNode::create(opponentData->animationResourceFile);
	this->avatarEnemy->addChild(Sprite::create(opponentData->backgroundResourceFile));
	this->avatarEnemy->addChild(this->opponentSprite);

	SpriterEngine::EntityInstance* opponentEntity = this->opponentSprite->play("Entity");
	opponentEntity->setCurrentAnimation("Idle");

	this->opponentSprite->setScale(opponentData->animationScale);
	this->opponentSprite->setPosition(opponentData->avatarOffset);
}

void Avatars::onStateChange(GameState* gameState)
{
	switch (gameState->stateType)
	{
		case GameState::StateType::ControlNeutral:
			break;
		default:
			break;
	}
}

void Avatars::setAvatars(GameState* gameState)
{
}
