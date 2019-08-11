#include "SquallyIsAliveHackBehavior.h"

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
#include "Scenes/Platformer/AttachedBehavior/Squally/Stats/SquallyHealthBehavior.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

#include "Strings/Hacking/Entities/Squally/IsAlive/IsAlive.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_IS_ALIVE 1

const std::string SquallyIsAliveHackBehavior::MapKeyAttachedBehavior = "squally-is-alive-hack";
const std::string SquallyIsAliveHackBehavior::IdentifierIsAlive = "is-alive";
const std::string SquallyIsAliveHackBehavior::EventSquallyTrapped = "event-squally-trapped";

SquallyIsAliveHackBehavior* SquallyIsAliveHackBehavior::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyIsAliveHackBehavior* instance = new SquallyIsAliveHackBehavior(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyIsAliveHackBehavior::SquallyIsAliveHackBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->squally = static_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyIsAliveHackBehavior::~SquallyIsAliveHackBehavior()
{
}

void SquallyIsAliveHackBehavior::update(float dt)
{
	// Check for player suicide
	if (!this->isSquallyAliveHack())
	{
		SquallyHealthBehavior* health = squally->getAttachedBehavior<SquallyHealthBehavior>();
		
		health->killAndRespawn();
	}
}

void SquallyIsAliveHackBehavior::onLoad()
{
	this->scheduleUpdate();

	this->listenForMapEvent(SquallyIsAliveHackBehavior::EventSquallyTrapped, [=](ValueMap args)
	{
		for (auto it = this->codeList.begin(); it != this->codeList.end(); it++)
		{
			if ((*it)->getHackableCodeIdentifier() == SquallyIsAliveHackBehavior::IdentifierIsAlive)
			{
				(*it)->getClippy()->setIsEnabled(true);
			}
		}
	});
}

void SquallyIsAliveHackBehavior::registerHackables()
{
	super::registerHackables();

	IsAliveClippy* isAliveClippy = IsAliveClippy::create();

	isAliveClippy->setIsEnabled(true);

	std::map<unsigned char, HackableCode::LateBindData> lateBindMap =
	{
		{
			LOCAL_FUNC_ID_IS_ALIVE,
			HackableCode::LateBindData(
				SquallyIsAliveHackBehavior::IdentifierIsAlive,
				Strings::Hacking_Entities_Squally_IsAlive_IsAlive::create(),
				UIResources::Menus_Icons_Heart,
				EntityPreview::create(this->squally),
				{
				},
				2,
				1.0f,
				isAliveClippy
			)
		},
	};

	auto isSquallyAliveHackFunc = &SquallyIsAliveHackBehavior::isSquallyAliveHack;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)isSquallyAliveHackFunc, lateBindMap);

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		this->squally->registerCode(*it);
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
