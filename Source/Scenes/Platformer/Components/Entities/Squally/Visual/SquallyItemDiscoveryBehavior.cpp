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

const std::string SquallyItemDiscoveryBehavior::MapKey = "squally-item-discovery";

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
	this->iconsNode = Node::create();
	this->glowNode = Node::create();
	this->discoverSound = Sound::create(SoundResources::Notifications_Reveal1);

	this->container->setOpacity(0);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}

	this->container->addChild(this->glowNode);
	this->container->addChild(this->iconsNode);
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
		PlatformerEvents::ItemDiscoveryArgs* args = static_cast<PlatformerEvents::ItemDiscoveryArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			std::vector<Item*> items = { args->item };
			this->discoverItems(items, args->cinematicHijack);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventDiscoverItems, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::ItemsDiscoveryArgs* args = static_cast<PlatformerEvents::ItemsDiscoveryArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->discoverItems(args->items, args->cinematicHijack);
		}
	}));
}

void SquallyItemDiscoveryBehavior::onDisable()
{
	super::onDisable();
}

void SquallyItemDiscoveryBehavior::discoverItems(std::vector<Item*> items, bool cinematicHijack)
{
	if (cinematicHijack)
	{
		PlatformerEvents::TriggerCinematicHijack();
	}

	this->container->runAction(FadeTo::create(0.25f, 255));
	this->discoverSound->play();

	int iconIndex = 0;
	int itemCount = int(items.size());
	float extraDelay = 0.5f * float(itemCount - 1); // If showing multiple items, add more delay so the user can process the information

	for (int index = 0; index < itemCount; index++)
	{
		if (items[index] == nullptr)
		{
			continue;
		}

		Vec2 position = Vec2((float(index) - float(itemCount - 1) / 2.0f) * 72.0f, 0.0f);

		// Create icon and glow if not already created
		if (createdIcons <= iconIndex)
		{
			Sprite* glow = Sprite::create(ObjectResources::Collectables_Animals_CollectShine);
			Sprite* icon = Sprite::create(items[iconIndex]->getIconResource());
			
			this->glows.push_back(glow);
			this->icons.push_back(icon);
			this->glowNode->addChild(glow);
			this->iconsNode->addChild(icon);

			createdIcons++;
		}
		else
		{
			// Otherwise update sprite
			this->icons[iconIndex]->setTexture(items[iconIndex]->getIconResource());
		}

		// Position based on number of icons to show (generally only one)
		this->glows[iconIndex]->setPosition(position);
		this->icons[iconIndex]->setPosition(position);
		this->glows[iconIndex]->runAction(RotateBy::create(2.0f + extraDelay, 360.0f + 90.0f * extraDelay));

		iconIndex++;
	}

	this->squally->getAnimations()->clearAnimationPriority();
	this->squally->getAnimations()->playAnimation("Discover", SmartAnimationNode::AnimationPlayMode::Repeat);

	this->runAction(Sequence::create(
		DelayTime::create(1.5f + extraDelay),
		CallFunc::create([=]()
		{
			if (cinematicHijack)
			{
				PlatformerEvents::TriggerCinematicRestore();
			}

			this->squally->getAnimations()->clearAnimationPriority();
			this->squally->getAnimations()->playAnimation();
			this->container->runAction(FadeTo::create(0.25f, 0));
		}),
		nullptr
	));
}
