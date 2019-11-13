#include "SpotOrcGrunt.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Events/PlatformerEvents.h"

#include "Strings/Platformer/Quests/EndianForest/Intro/EnemySpotted.h"

using namespace cocos2d;

const std::string SpotOrcGrunt::MapKeyQuest = "spot-orc-grunt";

SpotOrcGrunt* SpotOrcGrunt::create(GameObject* owner, QuestLine* questLine, std::string questTag)
{
	SpotOrcGrunt* instance = new SpotOrcGrunt(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

SpotOrcGrunt::SpotOrcGrunt(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, SpotOrcGrunt::MapKeyQuest, questTag, true)
{
	this->hasRunEvent = false;
	this->scrappy = nullptr;
}

SpotOrcGrunt::~SpotOrcGrunt()
{
}

void SpotOrcGrunt::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKeyScrappy);
}

void SpotOrcGrunt::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEvent(SpotOrcGrunt::MapKeyQuest, [=](ValueMap args)
	{
		this->complete();

		this->runCinematicSequence();
	});
}

void SpotOrcGrunt::onComplete()
{
}

void SpotOrcGrunt::onSkipped()
{
	this->removeAllListeners();
}

void SpotOrcGrunt::runCinematicSequence()
{
	if (this->hasRunEvent)
	{
		return;
	}
	
	this->hasRunEvent = true;

	if (this->scrappy != nullptr)
	{
		PlatformerEvents::TriggerCinematicHijack();

		this->runAction(Sequence::create(
			CallFunc::create([=]()
			{
				this->scrappy->droidChatterSound->play();
			}),
			CallFunc::create([=]()
			{
				this->scrappy->speechBubble->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_EnemySpotted::create(), 4.0f, [=]()
				{
					PlatformerEvents::TriggerCinematicRestore();
					this->scrappy->speechBubble->hideDialogue();
				});
			}),
			nullptr
		));
	}
}
