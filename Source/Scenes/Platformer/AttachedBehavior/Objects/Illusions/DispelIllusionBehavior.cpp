#include "DispelIllusionBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackActivatedAbility.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DispelIllusionBehavior::MapKey = "dispel-illusion";
const std::string DispelIllusionBehavior::PropertyGroup = "illusion-group";
const std::string DispelIllusionBehavior::SaveKeyDispelled = "SAVE_KEY_DISPELLED";

DispelIllusionBehavior* DispelIllusionBehavior::create(GameObject* owner)
{
	DispelIllusionBehavior* instance = new DispelIllusionBehavior(owner);

	instance->autorelease();

	return instance;
}

DispelIllusionBehavior::DispelIllusionBehavior(GameObject* owner) : super(owner)
{
	this->object = dynamic_cast<HackableObject*>(owner);
	this->group = "";

	if (this->object == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->group = GameUtils::getKeyOrDefault(this->object->properties, DispelIllusionBehavior::PropertyGroup, Value("")).asString();
	}
}

DispelIllusionBehavior::~DispelIllusionBehavior()
{
}

void DispelIllusionBehavior::onLoad()
{
	if (this->object->getObjectStateOrDefault(DispelIllusionBehavior::SaveKeyDispelled, Value(false)).asBool())
	{
		this->object->setOpacity(0);
		return;
	}

	this->registerHackables();
}

void DispelIllusionBehavior::onDisable()
{
	super::onDisable();
}

void DispelIllusionBehavior::registerHackables()
{
	this->object->registerHackAbility(HackActivatedAbility::create(
		"dispel-illusion",
		[=]()
		{
			this->onDispelActivated();
		},
		[=]()
		{
		},
		int(HackFlags::None),
		0.0f,
		HackableBase::HackBarColor::Purple,
		UIResources::Menus_Icons_Eye,
		Strings::Menus_Hacking_Abilities_DispelIllusion::create(),
		nullptr
	));
}

void DispelIllusionBehavior::onDispelActivated()
{
	this->object->toggleHackable(false);
	this->object->saveObjectState(DispelIllusionBehavior::SaveKeyDispelled, Value(true));

	PlatformerEvents::TriggerDispelIllusion(PlatformerEvents::DispelIllusionArgs(this->group));

	if (this->object != nullptr)
	{
		this->object->runAction(FadeTo::create(0.25f, 0));
	}
}
