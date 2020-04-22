#include "EntityQuestVisualBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string EntityQuestVisualBehavior::MapKey = "quest-visual";

EntityQuestVisualBehavior* EntityQuestVisualBehavior::create(GameObject* owner)
{
	EntityQuestVisualBehavior* instance = new EntityQuestVisualBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityQuestVisualBehavior::EntityQuestVisualBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->contentNode = Node::create();
	this->questToGive = Sprite::create(ObjectResources::Interactive_Help_Exclamation);
	this->questTurnIn = Sprite::create(ObjectResources::Interactive_Help_QuestionMark);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->questToGive->setOpacity(0);
	this->questTurnIn->setOpacity(0);

	this->contentNode->addChild(this->questToGive);
	this->contentNode->addChild(this->questTurnIn);
	this->addChild(this->contentNode);
}

EntityQuestVisualBehavior::~EntityQuestVisualBehavior()
{
}

void EntityQuestVisualBehavior::onLoad()
{
	const Vec2 BottomPosition = this->entity->getEntityTopPoint() + Vec2(0.0f, 96.0f);

	this->contentNode->setPosition(BottomPosition);

	this->contentNode->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(1.25f, BottomPosition)),
		EaseSineInOut::create(MoveTo::create(1.25f, BottomPosition + Vec2(0.0f, 16.0f))),
		nullptr
	)));
}

void EntityQuestVisualBehavior::onDisable()
{
	super::onDisable();

	this->contentNode->setVisible(false);
}

void EntityQuestVisualBehavior::enableTurnIn()
{
	this->questTurnIn->runAction(FadeTo::create(0.5f, 255));
}

void EntityQuestVisualBehavior::disableTurnIn()
{
	this->questTurnIn->runAction(FadeTo::create(0.5f, 0));
}

void EntityQuestVisualBehavior::enableNewQuest()
{
	this->questToGive->runAction(FadeTo::create(0.5f, 255));
}

void EntityQuestVisualBehavior::disableNewQuest()
{
	this->questToGive->runAction(FadeTo::create(0.5f, 0));
}
