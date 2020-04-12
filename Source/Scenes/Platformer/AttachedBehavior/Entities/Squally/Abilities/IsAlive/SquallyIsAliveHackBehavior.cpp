#include "SquallyIsAliveHackBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Hackables/Menus/Clippy.h"
#include "Engine/Hackables/HackableCode.h"
#include "Entities/Platformer/EntityPreview.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Abilities/IsAlive/IsAliveClippy.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_IS_ALIVE 1

const std::string SquallyIsAliveHackBehavior::MapKey = "squally-is-alive-hack";
const std::string SquallyIsAliveHackBehavior::IdentifierIsAlive = "is-alive";
const std::string SquallyIsAliveHackBehavior::EventSquallyTrapped = "event-squally-trapped";

SquallyIsAliveHackBehavior* SquallyIsAliveHackBehavior::create(GameObject* owner)
{
	SquallyIsAliveHackBehavior* instance = new SquallyIsAliveHackBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyIsAliveHackBehavior::SquallyIsAliveHackBehavior(GameObject* owner) : super(owner)
{
	this->clippy = IsAliveClippy::create();
	this->squally = dynamic_cast<Squally*>(owner);
	this->cooldown = 0.0f;

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->squally->registerClippy(this->clippy);
	}
}

SquallyIsAliveHackBehavior::~SquallyIsAliveHackBehavior()
{
}

void SquallyIsAliveHackBehavior::update(float dt)
{
	super::update(dt);

	if (this->cooldown > 0.0f)
	{
		this->cooldown -= dt;
	}
	else if (!this->isSquallyAliveHack())
	{
		// Check for player suicide
		this->squally->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
		{
			healthBehavior->kill();
		});
		
		this->cooldown = 3.0f;
	}
}

void SquallyIsAliveHackBehavior::onLoad()
{
	/*
	this->squally->listenForMapEvent(SquallyIsAliveHackBehavior::EventSquallyTrapped, [=](ValueMap args)
	{
		for (auto next : this->codeList)
		{
			if (next->getHackableCodeIdentifier() == SquallyIsAliveHackBehavior::IdentifierIsAlive)
			{
				next->getClippy()->setIsEnabled(true);
			}
		}
	});
	*/

	this->registerHackables();
	this->scheduleUpdate();
}

void SquallyIsAliveHackBehavior::onDisable()
{
	super::onDisable();
}

void SquallyIsAliveHackBehavior::registerHackables()
{
	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_IS_ALIVE,
			HackableCode::HackableCodeInfo(
				SquallyIsAliveHackBehavior::IdentifierIsAlive,
				Strings::Menus_Hacking_Abilities_Squally_IsAlive::create(),
				UIResources::Menus_Icons_Heart,
				EntityPreview::create(this->squally),
				{
				},
				int(HackFlags::Light),
				1.0f,
				0.0f,
				this->clippy
			)
		},
	};

	auto isSquallyAliveHackFunc = &SquallyIsAliveHackBehavior::isSquallyAliveHack;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)isSquallyAliveHackFunc, codeInfoMap);

	for (auto next : hackables)
	{
		this->squally->registerCode(next);
	}
}

NO_OPTIMIZE bool SquallyIsAliveHackBehavior::isSquallyAliveHack()
{
	static volatile int isAlive = true;

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_IS_ALIVE);

	ASM(mov ZAX, 1);

	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(isAlive, ZAX);

	HACKABLES_STOP_SEARCH();

	return isAlive;
}
END_NO_OPTIMIZE
