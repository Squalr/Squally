#include "HauntedLinkBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Shops/ShopItem.h"
#include "Objects/Platformer/Interactables/Anvil/Anvil.h"
#include "Objects/Platformer/Interactables/AlchemyLab/AlchemyLab.h"
#include "Objects/Platformer/Interactables/SmeltingPot/SmeltingPot.h"
#include "Scenes/Platformer/Components/Entities/Petrification/EntityPetrificationBehavior.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string HauntedLinkBehavior::MapKey = "haunted-link";
const std::string HauntedLinkBehavior::PropertyLinkedTag = "linked-tag";

HauntedLinkBehavior* HauntedLinkBehavior::create(GameObject* owner)
{
	HauntedLinkBehavior* instance = new HauntedLinkBehavior(owner);

	instance->autorelease();

	return instance;
}

HauntedLinkBehavior::HauntedLinkBehavior(GameObject* owner) : super(owner)
{
	this->ownerAsItem = dynamic_cast<ShopItem*>(owner);
	this->ownerAsAlchemyLab = dynamic_cast<AlchemyLab*>(owner);
	this->ownerAsAnvil = dynamic_cast<Anvil*>(owner);
	this->linkedTag = GameUtils::getKeyOrDefault(owner->properties, HauntedLinkBehavior::PropertyLinkedTag, Value(false)).asString();
}

HauntedLinkBehavior::~HauntedLinkBehavior()
{
}

void HauntedLinkBehavior::onLoad()
{
	if (this->ownerAsItem != nullptr)
	{
		this->ownerAsItem->deactivate();
	}

	if (this->ownerAsAlchemyLab != nullptr)
	{
		this->ownerAsAlchemyLab->deactivate();
	}

	if (this->ownerAsAnvil != nullptr)
	{
		this->ownerAsAnvil->deactivate();
	}
	
	ObjectEvents::WatchForObject<PlatformerEntity>(this, [=](PlatformerEntity* platformerEntity)
	{
		this->linkedEntity = platformerEntity;

		this->owner->listenForMapEventOnce(EntityPetrificationBehavior::MapEventCured, [=](ValueMap valueMap)
		{
			std::string identifier = GameUtils::getKeyOrDefault(valueMap, EntityPetrificationBehavior::MapEventKeyOwnerId, Value("")).asString();

			if (identifier == this->linkedEntity->getUniqueIdentifier())
			{
				if (this->ownerAsItem != nullptr)
				{
					this->ownerAsItem->activate();
				}

				if (this->ownerAsAlchemyLab != nullptr)
				{
					this->ownerAsAlchemyLab->activate();
				}

				if (this->ownerAsAnvil != nullptr)
				{
					this->ownerAsAnvil->activate();
				}
			}
		});

		this->linkedEntity->watchForComponent<EntityPetrificationBehavior>([=](EntityPetrificationBehavior* petrificationBehavior)
		{
			if (petrificationBehavior->isCured())
			{
				if (this->ownerAsItem != nullptr)
				{
					this->ownerAsItem->activate();
				}

				if (this->ownerAsAlchemyLab != nullptr)
				{
					this->ownerAsAlchemyLab->activate();
				}

				if (this->ownerAsAnvil != nullptr)
				{
					this->ownerAsAnvil->activate();
				}
			}
		});
	}, this->linkedTag);
}

void HauntedLinkBehavior::onDisable()
{
	super::onDisable();
}
