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
	this->avatarEnemy->addChild(Sprite::create(Resources::Backgrounds_Platformer_Day_Sky));

	AnimationNode* playerAnimation = AnimationNode::create(Resources::Entities_Platformer_Squally_Animations);
	SpriterEngine::EntityInstance* playerEntity = playerAnimation->play("Entity");
	playerEntity->setCurrentAnimation("Idle");
	playerAnimation->setScale(0.25f);
	playerAnimation->setPosition(Vec2(-64.0f, -32.0f));

	AnimationNode* enemyAnimation = AnimationNode::create(Resources::Entities_Platformer_Environment_Snow_BossIceGolem_Animations);
	SpriterEngine::EntityInstance* enemyEntity = enemyAnimation->play("Entity");
	enemyEntity->setCurrentAnimation("Idle");
	enemyAnimation->setPosition(Vec2(-24.0f, -212.0f));

	this->avatarPlayer->addChild(playerAnimation);
	this->avatarEnemy->addChild(enemyAnimation);

	DrawNode* stencilLeft = DrawNode::create();
	DrawNode* stencilRight = DrawNode::create();
	stencilLeft->drawSolidCircle(Vec2(0.0f, 0.0f), 184.0f / 2.0f, 0.0f, 48.0f, Color4F::BLACK);
	stencilRight->drawSolidCircle(Vec2(0.0f, 0.0f), 184.0f / 2.0f, 0.0f, 48.0f, Color4F::BLACK);

	// Enable to debug clipping:
	this->addChild(stencilLeft);
	this->addChild(stencilRight);

	this->clipPlayer = ClippingNode::create(stencilLeft);
	this->clipEnemy = ClippingNode::create(stencilRight);

	this->addChild(this->framePlayer);
	this->addChild(this->frameEnemy);
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
