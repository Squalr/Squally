#include "SquallySwimHackBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Hackables/Clippy.h"
#include "Engine/Hackables/HackableCode.h"
#include "Entities/Platformer/EntityPreview.h"
#include "Entities/Platformer/Squally/IsAliveClippy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_CAN_SWIM 1

const std::string SquallySwimHackBehavior::MapKeyAttachedBehavior = "squally-can-swim-hack";
const std::string SquallySwimHackBehavior::IdentifierCanSwim = "can-swim";

SquallySwimHackBehavior* SquallySwimHackBehavior::create(GameObject* owner)
{
	SquallySwimHackBehavior* instance = new SquallySwimHackBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallySwimHackBehavior::SquallySwimHackBehavior(GameObject* owner) : super(owner)
{
	this->clippy = IsAliveClippy::create();
	this->squally = dynamic_cast<Squally*>(owner);
	this->cooldown = 0.0f;

	this->registerClippy(this->clippy);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallySwimHackBehavior::~SquallySwimHackBehavior()
{
}

void SquallySwimHackBehavior::update(float dt)
{
	super::update(dt);

	if (this->cooldown > 0.0f)
	{
		this->cooldown -= dt;
	}
	else if (this->canSwimHack())
	{
		this->squally->controlStateOverride = PlatformerEntity::ControlState::Swimming;
		this->cooldown = 3.0f;
	}
	else if (this->squally->controlStateOverride == PlatformerEntity::ControlState::Swimming)
	{
		this->squally->controlStateOverride = PlatformerEntity::ControlState::None;
	}
}

void SquallySwimHackBehavior::onLoad()
{
	this->scheduleUpdate();
}

void SquallySwimHackBehavior::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_CAN_SWIM,
			HackableCode::HackableCodeInfo(
				SquallySwimHackBehavior::IdentifierCanSwim,
				Strings::Menus_Hacking_Entities_Squally_IsAlive_IsAlive::create(),
				UIResources::Menus_Icons_Bubbles,
				EntityPreview::create(this->squally),
				{
				},
				int(HackFlags::Water),
				2.0f,
				this->clippy
			)
		},
	};

	auto canSwimHackFunc = &SquallySwimHackBehavior::canSwimHack;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)canSwimHackFunc, codeInfoMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->squally->registerCode(*it);
	}
}

NO_OPTIMIZE bool SquallySwimHackBehavior::canSwimHack()
{
	static volatile int canSwim = false;

	ASM(PUSH ZAX);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_CAN_SWIM);
	ASM(mov ZAX, 0);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(canSwim, ZAX);
	ASM(POP ZAX);
	HACKABLES_STOP_SEARCH();

	return canSwim;
}
END_NO_OPTIMIZE
