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
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpotOrcGrunt::MapKeyQuest = "spot-orc-grunt";

SpotOrcGrunt* SpotOrcGrunt::create(GameObject* owner, QuestLine* questLine)
{
	SpotOrcGrunt* instance = new SpotOrcGrunt(owner, questLine);

	instance->autorelease();

	return instance;
}

SpotOrcGrunt::SpotOrcGrunt(GameObject* owner, QuestLine* questLine) : super(owner, questLine, SpotOrcGrunt::MapKeyQuest, true)
{
	this->scrappy = nullptr;
}

SpotOrcGrunt::~SpotOrcGrunt()
{
}

void SpotOrcGrunt::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);
}

void SpotOrcGrunt::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(SpotOrcGrunt::MapKeyQuest, [=](ValueMap args)
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
	if (this->scrappy != nullptr)
	{
		this->runAction(Sequence::create(
			CallFunc::create([=]()
			{
				this->scrappy->getComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
				{
					interactionBehavior->getSpeechBubble()->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_F_OrcGruntSpotted::create(), Voices::GetNextVoiceMedium(Voices::VoiceType::Droid), 4.0f, [=]()
					{
						interactionBehavior->getSpeechBubble()->hideDialogue();
					});
				});
			}),
			nullptr
		));
	}
}
