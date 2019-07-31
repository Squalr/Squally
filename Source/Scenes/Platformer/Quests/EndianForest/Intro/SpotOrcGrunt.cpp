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
#include "Engine/Sound/Sound.h"
#include "Events/PlatformerEvents.h"
#include "Entities/Platformer/Misc/DaemonsHallow/FlyBot.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"

#include "Strings/Dialogue/Story/Intro/TentHeal.h"
#include "Strings/Dialogue/Story/Intro/OgreSpotted.h"

using namespace cocos2d;

const std::string SpotOrcGrunt::MapKeyQuest = "spot-orc-grunt";

SpotOrcGrunt* SpotOrcGrunt::create(GameObject* owner, std::string questLine)
{
	SpotOrcGrunt* instance = new SpotOrcGrunt(owner, questLine);

	instance->autorelease();

	return instance;
}

SpotOrcGrunt::SpotOrcGrunt(GameObject* owner, std::string questLine) : super(owner, questLine, SpotOrcGrunt::MapKeyQuest, true)
{
	this->hasRunEvent = false;
	this->flyBot = static_cast<FlyBot*>(owner);
}

SpotOrcGrunt::~SpotOrcGrunt()
{
}

void SpotOrcGrunt::onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious)
{
}

void SpotOrcGrunt::onActivateRunOnce()
{
	this->listenForMapEvent(SpotOrcGrunt::MapKeyQuest, [=](ValueMap args)
	{
		QuestEvents::TriggerAdvanceToNextQuestTask(QuestEvents::AdvanceNextQuestArgs(this));

		this->runCinematicSequence();
	});
}

void SpotOrcGrunt::enable(bool isSkippable)
{
	if (this->flyBot != nullptr)
	{
		this->flyBot->animationNode->setFlippedX(true);
	}
}

void SpotOrcGrunt::disable()
{
	this->removeAllListeners();
	
	if (this->flyBot != nullptr)
	{
		this->flyBot->setVisible(false);
	}
}

void SpotOrcGrunt::runCinematicSequence()
{
	if (this->hasRunEvent)
	{
		return;
	}
	
	this->hasRunEvent = true;

	if (this->flyBot != nullptr)
	{
		PlatformerEvents::TriggerCinematicHijack();

		this->runAction(Sequence::create(
			CallFunc::create([=]()
			{
				this->flyBot->droidChatterSound->play();
			}),
			CallFunc::create([=]()
			{
				this->flyBot->speechBubble->runDialogue(Strings::Dialogue_Story_Intro_OgreSpotted::create());
			}),
			DelayTime::create(4.0f),
			CallFunc::create([=]()
			{
				PlatformerEvents::TriggerCinematicRestore();
			}),
			DelayTime::create(4.0f),
			CallFunc::create([=]()
			{
				this->flyBot->speechBubble->hideDialogue();
			}),
			nullptr
		));
	}
}
