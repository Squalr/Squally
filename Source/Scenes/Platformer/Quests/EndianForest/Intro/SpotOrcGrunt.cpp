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

SpotOrcGrunt* SpotOrcGrunt::create(GameObject* owner)
{
	SpotOrcGrunt* instance = new SpotOrcGrunt(owner);

	instance->autorelease();

	return instance;
}

SpotOrcGrunt::SpotOrcGrunt(GameObject* owner) : super(owner, SpotOrcGrunt::MapKeyQuest, true)
{
	this->hasRunEvent = false;
	this->flyBot = static_cast<FlyBot*>(owner);
}

SpotOrcGrunt::~SpotOrcGrunt()
{
}

void SpotOrcGrunt::onLoad(bool isQuestActive, bool isQuestActiveAsSkippable, bool isQuestComplete)
{
	if (isQuestActive || isQuestActiveAsSkippable)
	{
		if (this->flyBot != nullptr)
		{
			this->flyBot ->animationNode->setFlippedX(true);

			if (isQuestComplete)
			{
				this->flyBot ->setVisible(false);
			}
		}
	}
}

void SpotOrcGrunt::onActivate()
{
	this->listenForMapEvent(SpotOrcGrunt::MapKeyQuest, [=](ValueMap args)
	{
		if (this->isQuestActive())
		{
			QuestEvents::TriggerAdvanceToNextQuestTask(QuestEvents::AdvanceNextQuestArgs(this));

			this->runCinematicSequence();
		}
	});
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
