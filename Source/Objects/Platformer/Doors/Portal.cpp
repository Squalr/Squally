#include "Portal.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Menus/Interact/InteractMenu.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Portal::MapKeyPortalArgs = "args";
const std::string Portal::MapKeyPortalTransition = "transition";
const std::string Portal::MapKeyPortalMap = "map";

Portal::Portal(ValueMap& initProperties, Size size, Vec2 offset) : super(initProperties)
{
	this->portalCollision = CollisionObject::create(PhysicsBody::createBox(size), (CollisionType)PlatformerCollisionType::Trigger, false, false);
	this->interactMenu = InteractMenu::create(ConstantString::create("[V]"));
	this->wasTripped = false;
	this->mapArgs = StrUtils::splitOn(GameUtils::getKeyOrDefault(this->properties, Portal::MapKeyPortalArgs, Value("")).asString(), ", ");
	this->mapFile = GameUtils::getKeyOrDefault(this->properties, Portal::MapKeyPortalMap, Value("")).asString();
	this->isLocked = !this->mapEvent.empty();
	this->requiresInteraction = false;

	std::string transition = GameUtils::getKeyOrDefault(this->properties, Portal::MapKeyPortalTransition, Value("")).asString();

	this->mapArgs.push_back(PlatformerMap::MapArgClearSavedPosition);

	this->portalCollision->setPosition(offset);
	this->interactMenu->setPosition(offset);

	this->addChild(this->portalCollision);
	this->addChild(this->interactMenu);
}

Portal::~Portal()
{
}

void Portal::onEnter()
{
	super::onEnter();
}

void Portal::initializePositions()
{
	super::initializePositions();
}

void Portal::initializeListeners()
{
	super::initializeListeners();

	if (!this->mapEvent.empty())
	{
		this->listenForMapEvent(this->mapEvent, [=](ValueMap args)
		{
			this->isLocked = false;
		});
	}
 
	this->portalCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->canInteract = true;

		if (!this->isLocked)
		{
			if (this->requiresInteraction)
			{
				this->interactMenu->show();
			}
			else
			{
				// Load new map after a short delay -- changing scenes in the middle of a collision causes a crash
				// (not sure why, changing to a combat map is fine)
				this->runAction(Sequence::create(
					DelayTime::create(0.1f),
					CallFunc::create([=]()
					{
						this->loadMap();
					}),
					nullptr
				));
			}
		}

		return CollisionObject::CollisionResult::DoNothing;
	});
		 
	this->portalCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->canInteract = false;
		this->interactMenu->hide();

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_V }, [=](InputEvents::InputArgs* args)
	{
		if (!this->isLocked && this->canInteract)
		{
			this->loadMap();
		} 
	});
}

void Portal::setLocked(bool isLocked)
{
	this->isLocked = isLocked;

	if (this->canInteract && !this->isLocked)
	{
		this->interactMenu->show();
	}
	else
	{
		this->interactMenu->hide();
	}
}

void Portal::setRequiresInteraction(bool requiresInteraction)
{
	this->requiresInteraction = requiresInteraction;
}

void Portal::loadMap()
{
	if (!this->wasTripped)
	{
		this->wasTripped = true;
		PlatformerMap* map = PlatformerMap::create("Platformer/Maps/" + this->mapFile + ".tmx", this->mapArgs);

		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(map));
	}
}
