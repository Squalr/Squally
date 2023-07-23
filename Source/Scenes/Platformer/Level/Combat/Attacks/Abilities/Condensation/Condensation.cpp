#include "Condensation.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Particles/SmartParticles.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Level/Combat/TimelineEvent.h"
#include "Scenes/Platformer/Level/Combat/TimelineEventGroup.h"

#include "Resources/ParticleResources.h"
#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_UNDYING 1

const std::string Condensation::CondensationIdentifier = "condensation";
const float Condensation::TimeBetweenTicks = 0.5f;
const int Condensation::Ticks = 4;
const float Condensation::StartDelay = 0.15f;

Condensation* Condensation::create(PlatformerEntity* caster, PlatformerEntity* target)
{
	Condensation* instance = new Condensation(caster, target);

	instance->autorelease();

	return instance;
}

Condensation::Condensation(PlatformerEntity* caster, PlatformerEntity* target)
	: super(caster, target, "", AbilityType::Water, BuffData())
{
	this->spellEffect = SmartParticles::create(ParticleResources::Platformer_Combat_Abilities_Bubbles);
	this->restoreEffect = SmartAnimationSequenceNode::create();
	this->restoreSound = WorldSound::create(SoundResources::Platformer_Spells_Bubbles1);
	
	this->restoreEffect->setAnimationAnchor(Vec2(0.5f, 0.0f));

	this->addChild(this->restoreEffect);
	this->addChild(this->restoreSound);

	this->addChild(this->spellEffect);
}

Condensation::~Condensation()
{
}

void Condensation::onEnter()
{
	super::onEnter();

	this->spellEffect->start();

	std::vector<TimelineEvent*> timelineEvents = std::vector<TimelineEvent*>();

	for (int healIndex = 0; healIndex < Condensation::Ticks; healIndex++)
	{
		Sprite* icon = Sprite::create(UIResources::Menus_Icons_Bubbles);

		icon->setScale(0.5f);

		timelineEvents.push_back(TimelineEvent::create(
				this->owner,
				icon,
				Condensation::TimeBetweenTicks * float(healIndex) + Condensation::StartDelay, [=]()
			{
				if (!this->restoreEffect->isPlayingAnimation())
				{
					this->restoreEffect->playAnimation(FXResources::HealMP_Heal_0000, 0.05f);
				}
				
				this->restoreSound->play();
				CombatEvents::TriggerManaRestore(CombatEvents::ManaRestoreOrDrainArgs(this->caster, this->owner, 1, this->abilityType));
			})
		);
	}

	CombatEvents::TriggerRegisterTimelineEventGroup(CombatEvents::RegisterTimelineEventGroupArgs(
		TimelineEventGroup::create(timelineEvents, this, this->owner, [=]()
		{
			this->removeBuff();
		})
	));
}

void Condensation::initializePositions()
{
	super::initializePositions();
	
	this->restoreEffect->setPositionY(this->owner->getEntityBottomPointRelative().y - 12.0f);
}
