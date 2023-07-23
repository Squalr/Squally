#include "MapLinkBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Interactables/Chests/ChestBase.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string MapLinkBehavior::MapKey = "map-link";

MapLinkBehavior* MapLinkBehavior::create(GameObject* owner)
{
	MapLinkBehavior* instance = new MapLinkBehavior(owner);

	instance->autorelease();

	return instance;
}

MapLinkBehavior::MapLinkBehavior(GameObject* owner) : super(owner)
{
	this->ownerAsChest = dynamic_cast<ChestBase*>(owner);
	this->ownerAsEntity = dynamic_cast<PlatformerEntity*>(owner);
	this->mapLinkSaveKey = GameUtils::getKeyOrDefault(owner->properties, "link-key", Value("")).asString();

	if (this->mapLinkSaveKey == "" || this->ownerAsChest == nullptr && this->ownerAsEntity == nullptr)
	{
		this->invalidate();
	}
}

MapLinkBehavior::~MapLinkBehavior()
{
}

void MapLinkBehavior::onLoad()
{
	if (this->ownerAsChest != nullptr)
	{
		if (SaveManager::GetProfileDataOrDefault(this->mapLinkSaveKey, Value(false)).asBool())
		{
			this->ownerAsChest->open(true);
		}
		else if (this->ownerAsChest->isOpen())
		{
			// Update map link save data if already open (backwards compatability)
			SaveManager::SoftSaveProfileData(this->mapLinkSaveKey, Value(true));
		}
		else
		{
			this->ownerAsChest->listenForMapEventOnce(this->ownerAsChest->getSendEvent(), [=](ValueMap)
			{
				SaveManager::SoftSaveProfileData(this->mapLinkSaveKey, Value(true));
			});
		}
	}
	else if (this->ownerAsEntity != nullptr)
	{
		if (SaveManager::GetProfileDataOrDefault(this->mapLinkSaveKey, Value(false)).asBool())
		{
			this->ownerAsEntity->watchForComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
			{
				healthBehavior->kill();
			});
		}
		else if (!this->ownerAsEntity->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
		{
			// Update map link save data if already open (backwards compatability)
			SaveManager::SoftSaveProfileData(this->mapLinkSaveKey, Value(true));
		}
		else
		{
			this->ownerAsEntity->listenForStateWrite(StateKeys::IsAlive, [=](Value isAlive)
			{
				if (!isAlive.asBool())
				{
					SaveManager::SoftSaveProfileData(this->mapLinkSaveKey, Value(true));
				}
			});
		}
	}
}

void MapLinkBehavior::enablePortal()
{
}

void MapLinkBehavior::onDisable()
{
	super::onDisable();
}
