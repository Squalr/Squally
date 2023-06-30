#include "IllusionBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"

using namespace cocos2d;

const std::string IllusionBehavior::MapKey = "illusion";
const std::string IllusionBehavior::PropertyGroup = "illusion-group";
const std::string IllusionBehavior::SaveKeyDispelled = "SAVE_KEY_DISPELLED";

IllusionBehavior* IllusionBehavior::create(GameObject* owner)
{
	IllusionBehavior* instance = new IllusionBehavior(owner);

	instance->autorelease();

	return instance;
}

IllusionBehavior::IllusionBehavior(GameObject* owner) : super(owner)
{
	this->portal = dynamic_cast<Portal*>(owner);
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->object = owner;

	if (this->object == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->group = GameUtils::getKeyOrDefault(this->object->properties, IllusionBehavior::PropertyGroup, Value("")).asString();
	}
}

IllusionBehavior::~IllusionBehavior()
{
}

void IllusionBehavior::onLoad()
{
	if (this->object->loadObjectStateOrDefault(IllusionBehavior::SaveKeyDispelled, Value(false)).asBool())
	{
		return;
	}

	this->object->setVisible(false);
	this->object->setOpacity(0);

	if (this->portal != nullptr)
	{
		this->portal->disable();
	}

	if (this->entity != nullptr)
	{
		// Killing the hidden entity is good for hiding all functionality
		this->entity->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
		{
			healthBehavior->kill();
		});
	}

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventDispelIllusion, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::DispelIllusionArgs* args = static_cast<PlatformerEvents::DispelIllusionArgs*>(eventCustom->getData());

		if (args != nullptr && args->group == this->group)
		{
			this->object->saveObjectState(IllusionBehavior::SaveKeyDispelled, Value(true));
			this->object->setOpacity(0);
			this->object->setVisible(true);
			this->object->runAction(FadeTo::create(0.25f, 255));

			if (this->portal != nullptr)
			{
				this->portal->enable();
			}

			if (this->entity != nullptr)
			{
				this->entity->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
				{
					healthBehavior->revive();
				});
			}
		}
	}));
}

void IllusionBehavior::onDisable()
{
	super::onDisable();
}
