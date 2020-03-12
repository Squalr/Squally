#include "SpotTrainingDummy.h"

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
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SpotTrainingDummy::MapKeyQuest = "spot-training-dummy";

SpotTrainingDummy* SpotTrainingDummy::create(GameObject* owner, QuestLine* questLine)
{
	SpotTrainingDummy* instance = new SpotTrainingDummy(owner, questLine);

	instance->autorelease();

	return instance;
}

SpotTrainingDummy::SpotTrainingDummy(GameObject* owner, QuestLine* questLine) : super(owner, questLine, SpotTrainingDummy::MapKeyQuest, true)
{
	this->scrappy = nullptr;
}

SpotTrainingDummy::~SpotTrainingDummy()
{
}

void SpotTrainingDummy::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKeyScrappy);
}

void SpotTrainingDummy::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(SpotTrainingDummy::MapKeyQuest, [=](ValueMap args)
	{
		this->complete();

		this->runCinematicSequence();
	});
}

void SpotTrainingDummy::onComplete()
{
}

void SpotTrainingDummy::onSkipped()
{
	this->removeAllListeners();
}

void SpotTrainingDummy::runCinematicSequence()
{
	if (this->scrappy != nullptr)
	{
		this->runAction(Sequence::create(
			CallFunc::create([=]()
			{
				this->scrappy->getAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
				{
					interactionBehavior->getSpeechBubble()->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_E_TrainingDummySpotted::create(), SoundResources::Platformer_Entities_Droid_DroidChatter, 4.0f, [=]()
					{
						interactionBehavior->getSpeechBubble()->hideDialogue();
					});
				});
			}),
			nullptr
		));
	}
}
