#include "ShadowBomb.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Abilities/ShadowBomb/ShadowBombGenericPreview.h"
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

#define LOCAL_FUNC_ID_SHADOW_BOMB 11

const std::string ShadowBomb::HackIdentifierShadowBomb = "shadow-bomb";

ShadowBomb* ShadowBomb::create(PlatformerEntity* caster, PlatformerEntity* target, std::function<void(int)> onImpact)
{
	ShadowBomb* instance = new ShadowBomb(caster, target, onImpact);

	instance->autorelease();

	return instance;
}

ShadowBomb::ShadowBomb(PlatformerEntity* caster, PlatformerEntity* target, std::function<void(int)> onImpact) : super(caster, target, true)
{
	this->animationNode = SmartAnimationSequenceNode::create();
	this->impactSound = WorldSound::create(SoundResources::Platformer_Spells_FireHit1);
	this->onImpact = onImpact;

	this->addChild(this->animationNode);
	this->addChild(this->impactSound);
}

ShadowBomb::~ShadowBomb()
{
}

void ShadowBomb::onEnter()
{
	super::onEnter();
	
	CombatEvents::TriggerHackableCombatCue();
}

void ShadowBomb::update(float dt)
{
	super::update(dt);
}

Vec2 ShadowBomb::getButtonOffset()
{
	return Vec2(0.0f, 96.0f);
}

void ShadowBomb::registerHackables()
{
	super::registerHackables();

	HackableCode::CodeInfoMap codeInfoMap =
	{
		{
			LOCAL_FUNC_ID_SHADOW_BOMB,
			HackableCode::HackableCodeInfo(
				ShadowBomb::HackIdentifierShadowBomb,
				Strings::Menus_Hacking_Abilities_Abilities_ShadowBomb_ShadowBomb::create(),
				HackableBase::HackBarColor::Purple,
				UIResources::Menus_Icons_SpellImpactPurple,
				LazyNode<HackablePreview>::create([=](){ return this->createDefaultPreview(); }),
				{
					{
						HackableCode::Register::zax, Strings::Menus_Hacking_Abilities_Abilities_ShadowBomb_RegisterEax::create()
					},
				},
				int(HackFlags::None),
				12.0f,
				0.0f,
				{
					HackableCode::ReadOnlyScript(
						Strings::Menus_Hacking_CodeEditor_OriginalCode::create(),
						// x86
						"and eax, 15\n"
						, // x64
						"and rax, 15\n"
					),
				},
				true
			)
		},
	};

	auto func = &ShadowBomb::dealDamage;
	std::vector<HackableCode*> hackables = HackableCode::create((void*&)func, codeInfoMap);

	for (HackableCode* next : hackables)
	{
		this->registerCode(next);
	}
}

HackablePreview* ShadowBomb::createDefaultPreview()
{
	return ShadowBombGenericPreview::create();
}

void ShadowBomb::runShadowBomb(TimelineEntry* target)
{
	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();
	
	Sprite* icon = Sprite::create(target->getEmblemResource());
	Sprite* impactIcon = Sprite::create(UIResources::Menus_Icons_SpellImpactPurple);

	icon->setFlippedX(true);
	impactIcon->setPosition(icon->getContentSize().width / 2.0f, icon->getContentSize().height / 2.0f);
	impactIcon->setScale(0.5f);

	icon->addChild(impactIcon);

	this->animationNode->playAnimationAndReverseRepeat({ FXResources::ShadowBomb_ShadowBomb_0000, FXResources::ShadowBomb_ShadowBomb_0001 }, 0.05f, 0.0f, 0.05f);

	timelineEvents.push_back(TimelineEvent::create(
			target->getEntity(),
			icon,
			2.5f, [=]()
		{
			this->animationNode->playAnimation(FXResources::ShadowBomb_ShadowBomb_0000, 0.05f, true);
			this->impactSound->play();
			this->dealDamage(target);
			int currentHealth = 0;
			target->getEntity()->getComponent<EntityHealthBehavior>([&](EntityHealthBehavior* healthBehavior)
			{
				currentHealth = healthBehavior->getHealth();
			});
			onImpact(currentHealth - this->HackStateStorage[CombatObject::HackStorageKeyHealth].asInt());
		})
	);

	CombatEvents::TriggerRegisterTimelineEventGroup(CombatEvents::RegisterTimelineEventGroupArgs(
		TimelineEventGroup::create(timelineEvents, nullptr, target->getEntity(), [=]()
		{
			this->runAction(Sequence::create(
				DelayTime::create(2.0f),
				CallFunc::create([=]()
				{
					this->despawn();
				}),
				nullptr
			));
		})
	));
}

NO_OPTIMIZE void ShadowBomb::dealDamage(TimelineEntry* target)
{
	static volatile int health = 0;

	target->getEntity()->getComponent<EntityHealthBehavior>([&](EntityHealthBehavior* healthBehavior)
	{
		health = healthBehavior->getHealth();
	});

	ASM(push ZAX);

	ASM(MOV ZAX, 0);
	ASM_MOV_REG_VAR(eax, health);

	HACKABLE_CODE_BEGIN(LOCAL_FUNC_ID_SHADOW_BOMB);
	ASM(and ZAX, 15);
	HACKABLE_CODE_END();

	ASM_MOV_VAR_REG(health, eax);
	ASM(pop ZAX);

	this->HackStateStorage[CombatObject::HackStorageKeyHealth] = Value(health);

	HACKABLES_STOP_SEARCH();
}
END_NO_OPTIMIZE
