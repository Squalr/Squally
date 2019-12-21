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
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

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
				this->scrappy->getAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
				{
					interactionBehavior->getSpeechBubble()->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_E_EnemySpotted::create(), SoundResources::Platformer_Entities_Droid_DroidChatter, 4.0f, [=]()
					{
						interactionBehavior->getSpeechBubble()->hideDialogue();
					});
				});
			}),
			nullptr
		));
	}
}
