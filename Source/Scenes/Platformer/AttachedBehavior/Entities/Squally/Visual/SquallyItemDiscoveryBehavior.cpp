#include "SquallyItemDiscoveryBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"

#include "Resources/ObjectResources.h"
#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string SquallyItemDiscoveryBehavior::MapKeyAttachedBehavior = "squally-item-discovery";

SquallyItemDiscoveryBehavior* SquallyItemDiscoveryBehavior::create(GameObject* owner)
{
	SquallyItemDiscoveryBehavior* instance = new SquallyItemDiscoveryBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyItemDiscoveryBehavior::SquallyItemDiscoveryBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);
	this->container = Node::create();
	this->itemNode = Node::create();
	this->glow = Sprite::create(ObjectResources::Collectables_Animals_CollectShine);
	this->discoverSound = Sound::create(SoundResources::Notifications_Reveal1);

	this->container->setOpacity(0);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}

	this->container->addChild(this->glow);
	this->container->addChild(this->itemNode);
	this->addChild(this->container);
	this->addChild(this->discoverSound);
}

SquallyItemDiscoveryBehavior::~SquallyItemDiscoveryBehavior()
{
}

void SquallyItemDiscoveryBehavior::onLoad()
{
	this->container->setPosition(this->squally->getEntityCenterPoint() + Vec2 (0.0f, 96.0f));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventDiscoverItem, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::ItemDiscoveryArgs* args = static_cast<PlatformerEvents::ItemDiscoveryArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->item != nullptr)
		{
			this->discoverItem(args->item);
		}
	}));
}

void SquallyItemDiscoveryBehavior::onDisable()
{
	super::onDisable();
}

void SquallyItemDiscoveryBehavior::discoverItem(Item* item)
{
	PlatformerEvents::TriggerCinematicHijack();

	this->container->runAction(FadeTo::create(0.25f, 255));
	this->glow->runAction(RotateBy::create(2.0f, 360.0f));
	this->discoverSound->play();

	this->itemNode->removeAllChildren();
	this->itemNode->addChild(Sprite::create(item->getIconResource()));

	this->squally->getAnimations()->clearAnimationPriority();
	this->squally->getAnimations()->playAnimation("Discover", SmartAnimationNode::AnimationPlayMode::Repeat);

	this->runAction(Sequence::create(
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			PlatformerEvents::TriggerCinematicRestore();

			this->squally->getAnimations()->clearAnimationPriority();
			this->squally->getAnimations()->playAnimation();
			this->container->runAction(FadeTo::create(0.25f, 0));
		}),
		nullptr
	));
}
