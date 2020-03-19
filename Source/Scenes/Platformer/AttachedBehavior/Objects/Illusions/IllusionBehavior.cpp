#include "IllusionBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"

using namespace cocos2d;

const std::string IllusionBehavior::MapKey = "illusion";
const std::string IllusionBehavior::PropertyGroup = "illusion-group";

IllusionBehavior* IllusionBehavior::create(GameObject* owner)
{
	IllusionBehavior* instance = new IllusionBehavior(owner);

	instance->autorelease();

	return instance;
}

IllusionBehavior::IllusionBehavior(GameObject* owner) : super(owner)
{
	this->portal = dynamic_cast<Portal*>(owner);
	this->object = owner;
	this->group = GameUtils::getKeyOrDefault(this->properties, IllusionBehavior::PropertyGroup, Value("")).asString();

	if (this->object == nullptr)
	{
		this->invalidate();
	}
}

IllusionBehavior::~IllusionBehavior()
{
}

void IllusionBehavior::onLoad()
{
	this->object->setOpacity(0);

	if (this->portal != nullptr)
	{
		this->portal->disable();
	}

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventDispelIllusion, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::DispelIllusionArgs* args = static_cast<PlatformerEvents::DispelIllusionArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->group == this->group)
		{
			this->object->runAction(FadeTo::create(0.25f, 255));

			if (this->portal != nullptr)
			{
				this->portal->enable();
			}
		}
	}));
}

void IllusionBehavior::onDisable()
{
	super::onDisable();
}
