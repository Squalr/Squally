#include "Portal.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Interact/InteractMenu.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Portal::MapKey = "portal";
const std::string Portal::PropertyPortalTransition = "transition";
const std::string Portal::PropertyPortalMap = "map";
const std::string Portal::PropertyIsLocked = "is-locked";
const std::string Portal::SaveKeyListenEventTriggered = "SAVE_KEY_LISTEN_EVENT_TRIGGERED";

Portal* Portal::create(ValueMap& properties)
{
	Portal* instance = new Portal(properties, Size(properties.at(GameObject::MapKeyWidth).asFloat(), properties.at(GameObject::MapKeyHeight).asFloat()));

	instance->autorelease();

	return instance;
}

Portal::Portal(ValueMap& properties, Size size, Vec2 offset, Color3B color) : super(properties, InteractObject::InteractType::Input, size, offset, nullptr, InputEvents::KeyCode::KEY_V, color)
{
	this->mapFile = GameUtils::getKeyOrDefault(this->properties, Portal::PropertyPortalMap, Value("")).asString();
	this->transition = GameUtils::getKeyOrDefault(this->properties, Portal::PropertyPortalTransition, Value("")).asString();
	this->isLocked = GameUtils::getKeyOrDefault(this->properties, Portal::PropertyIsLocked, Value(this->isLocked)).asBool();

	this->setName("Portal: " + this->mapFile);

	if (this->mapFile.empty())
	{
		this->setInteractType(InteractType::None);
	}
}

Portal::~Portal()
{
}

void Portal::onEnter()
{
	super::onEnter();

	if (!this->getListenEvent().empty())
	{
		if (!this->loadObjectStateOrDefault(Portal::SaveKeyListenEventTriggered, Value(false)).asBool())
		{
			this->lock(false);

			this->listenForMapEvent(this->getListenEvent(), [=](ValueMap args)
			{
				this->saveObjectState(Portal::SaveKeyListenEventTriggered, Value(true));
				this->unlock(true);
			});
		}
		else
		{
			this->unlock(false);
		}
	}
}

void Portal::initializePositions()
{
	super::initializePositions();
}

void Portal::initializeListeners()
{
	super::initializeListeners();
}

void Portal::onInteract(PlatformerEntity* interactingEntity)
{
	super::onInteract(interactingEntity);

	this->loadMap();
}

void Portal::loadMap()
{
	if (this->disabled || this->mapFile.empty() || this->wasTripped)
	{
		return;
	}

	this->wasTripped = true;

	// Load new map after a short delay -- changing scenes in the middle of a collision causes a crash
	// (not sure why, changing to a combat map is fine)
	this->runAction(Sequence::create(
		DelayTime::create(0.1f),
		CallFunc::create([=]()
		{
			NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
			{
				std::string mapResource = "Public/Platformer/Maps/" + this->mapFile + ".tmx";

				PlatformerEvents::TriggerBeforePlatformerMapChange();
				PlatformerMap* map = PlatformerMap::create(this->transition);

				map->loadMap(mapResource);

				return map;
			}));
		}),
		nullptr
	));
}
