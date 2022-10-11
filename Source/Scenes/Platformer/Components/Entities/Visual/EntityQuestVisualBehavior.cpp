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
	this->questIncomplete = Sprite::create(ObjectResources::Interactive_Help_QuestionMarkDisabled);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->questToGive->setOpacity(0);
	this->questTurnIn->setOpacity(0);
	this->questIncomplete->setOpacity(0);

	this->contentNode->addChild(this->questToGive);
	this->contentNode->addChild(this->questTurnIn);
	this->contentNode->addChild(this->questIncomplete);
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
	this->disableAll();
	this->questTurnIn->stopAllActions();
	this->questTurnIn->runAction(FadeTo::create(0.5f, 255));
}

void EntityQuestVisualBehavior::enableNewQuest()
{
	this->disableAll();
	this->questToGive->stopAllActions();
	this->questToGive->runAction(FadeTo::create(0.5f, 255));
}

void EntityQuestVisualBehavior::enableIncompleteQuest()
{
	this->disableAll();
	this->questIncomplete->stopAllActions();
	this->questIncomplete->runAction(FadeTo::create(0.5f, 255));
}

void EntityQuestVisualBehavior::disableAll()
{
	this->questTurnIn->stopAllActions();
	this->questToGive->stopAllActions();
	this->questIncomplete->stopAllActions();
	this->questTurnIn->runAction(FadeTo::create(0.5f, 0));
	this->questToGive->runAction(FadeTo::create(0.5f, 0));
	this->questIncomplete->runAction(FadeTo::create(0.5f, 0));
}
