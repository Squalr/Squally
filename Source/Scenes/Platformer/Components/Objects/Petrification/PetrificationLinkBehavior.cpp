#include "PetrificationLinkBehavior.h"

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

const std::string PetrificationLinkBehavior::MapKey = "petrification-link";
const std::string PetrificationLinkBehavior::PropertyLinkedTag = "linked-tag";

PetrificationLinkBehavior* PetrificationLinkBehavior::create(GameObject* owner)
{
	PetrificationLinkBehavior* instance = new PetrificationLinkBehavior(owner);

	instance->autorelease();

	return instance;
}

PetrificationLinkBehavior::PetrificationLinkBehavior(GameObject* owner) : super(owner)
{
	this->ownerAsItem = dynamic_cast<ShopItem*>(owner);
	this->ownerAsAlchemyLab = dynamic_cast<AlchemyLab*>(owner);
	this->ownerAsAnvil = dynamic_cast<Anvil*>(owner);
	this->linkedEntity = nullptr;
	this->linkedTag = GameUtils::getKeyOrDefault(owner->properties, PetrificationLinkBehavior::PropertyLinkedTag, Value(false)).asString();
}

PetrificationLinkBehavior::~PetrificationLinkBehavior()
{
}

void PetrificationLinkBehavior::onLoad()
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

void PetrificationLinkBehavior::onDisable()
{
	super::onDisable();
}
