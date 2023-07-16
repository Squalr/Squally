#include "LavaAxe.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Localization/ConcatString.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Abilities/LavaAxe/LavaAxeGenericPreview.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"

#include "Resources/ObjectResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_LAVA_AXE 11

const std::string LavaAxe::HackIdentifierLavaAxe = "lava-axe";

LavaAxe* LavaAxe::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	LavaAxe* instance = new LavaAxe(caster, target);

	instance->autorelease();

	return instance;
}

LavaAxe::LavaAxe(PlatformerEntity* caster, PlatformerEntity* target) : super(caster, target, true)
{
	this->axe = Sprite::create(ObjectResources::Physics_LavaAxe_LavaAxe);
	this->impactSound = WorldSound::create(SoundResources::Platformer_Spells_FireHit1);

	this->axe->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->addChild(this->axe);
	this->addChild(this->impactSound);
}

LavaAxe::~LavaAxe()
{
}

void LavaAxe::onEnter()
{
	super::onEnter();
	
	CombatEvents::TriggerHackableCombatCue();
}

void LavaAxe::elapse(float dt)
{
	super::elapse(dt);

	this->rotateAxe(dt);

	if (this->axe->getRotation() < -75.0f)
	{
		CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([=](Timeline* timeline)
		{
			for (TimelineEntry* next : timeline->getEntries())
			{
				if (next->isPlayerEntry())
				{
					CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(this->caster, next->getEntity(), 2048, AbilityType::Fire, true));
				}
			}
		}));
		
		this->impactSound->play();
		this->disableUpdate();
		this->despawn();
	}
	else if (this->axe->getRotation() > 75.0f)
	{
		CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([=](Timeline* timeline)
		{
			for (TimelineEntry* next : timeline->getEntries())
			{
				if (!next->isPlayerEntry())
				{
					CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(this->caster, next->getEntity(), 2048, AbilityType::Fire, true));
				}
			}
		}));
		
		this->impactSound->play();
		this->disableUpdate();
		this->despawn();
	}
}

Vec2 LavaAxe::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void LavaAxe::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_LAVA_AXE,
			HackableCode::HackableCodeInfo(
				LavaAxe::HackIdentifierLavaAxe,
				Strings::Menus_Hacking_Abilities_Abilities_LavaAxe_LavaAxe::create(),
				HackableBase::HackBarColor::Red,
				UIResources::Menus_Icons_AxeGlowOrange,
				LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
				{
					{
						HackableCode::Register::zbx, Strings::Menus_Hacking_Abilities_Abilities_LavaAxe_RegisterEbx::create()
					},
				},
				int(HackFlags::None),
				12.0f,
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						ConcatString::create({
							ConstantString::create("subss xmm0, dword ptr [ebx]\n")
						})
						, // x64
						ConcatString::create({
							ConstantString::create("subss xmm0, dword ptr [rbx]\n")
						})
					),
				},
				true
			)
		},
	};

	std::vector<HackableCode*> hackables = CREATE_HACKABLES(LavaAxe::rotateAxe, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* LavaAxe::createDefaultPreview()
{
	return LavaAxeGenericPreview::create();
}

void LavaAxe::runLavaAxe(TimelineEntry* target)
{
	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();
	
	Sprite* icon = Sprite::create(target->getEmblemResource());
	Sprite* impactIcon = Sprite::create(UIResources::Menus_Icons_AxeGlowOrange);

	icon->setFlippedX(true);
	impactIcon->setPosition(icon->getContentSize().width / 2.0f, icon->getContentSize().height / 2.0f);
	impactIcon->setScale(0.5f);

	icon->addChild(impactIcon);
}

NO_OPTIMIZE void LavaAxe::rotateAxe(float dt)
{
	static volatile float rotation = 0;
	static volatile float* rotationPtr = 0;
	static volatile float rotationDelta = 0;
	static volatile float* rotationDeltaPtr = nullptr;

	rotation = this->axe->getRotation();
	rotationPtr = &rotation;
	rotationDelta = 45.0f * dt;
	rotationDeltaPtr = &rotationDelta;

	ASM(push ZAX);
	ASM(push ZBX);

	ASM_MOV_REG_VAR(ZAX, rotationPtr);
	ASM_MOV_REG_VAR(ZBX, rotationDeltaPtr);

	ASM(movss xmm0, dword ptr [ZAX]);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_LAVA_AXE);
	ASM(subss xmm0, dword ptr [ZBX]);
	HACKABLE_CODE_END();

	ASM(movss dword ptr [ZAX], xmm0);

	ASM(pop ZBX);
	ASM(pop ZAX);

	this->axe->setRotation(rotation);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
