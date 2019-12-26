#include "BeatTutorialF.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/MagePortals/MagePortal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/EndianForest/Gauntlet/TutorialFBehavior.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BeatTutorialF::MapKeyQuest = "beat-tutorial-F";
const std::string BeatTutorialF::WinLossTrackIdentifier = "Tutorial-F";
const std::string BeatTutorialF::QuestPortalTag = "quest-portal";

BeatTutorialF* BeatTutorialF::create(GameObject* owner, QuestLine* questLine)
{
	BeatTutorialF* instance = new BeatTutorialF(owner, questLine);

	instance->autorelease();

	return instance;
}

BeatTutorialF::BeatTutorialF(GameObject* owner, QuestLine* questLine) : super(owner, questLine, BeatTutorialF::MapKeyQuest, false)
{
	this->mage = dynamic_cast<PlatformerEntity*>(owner);
	this->squally = nullptr;
	this->portal = nullptr;
}

BeatTutorialF::~BeatTutorialF()
{
}

void BeatTutorialF::onLoad(QuestState questState)
{
	this->defer([=]()
	{
		TutorialFBehavior* tutorialBehavior = TutorialFBehavior::create(this->mage);

		tutorialBehavior->registerWinCallback([=]()
		{
			this->complete();
		});
		
    	this->mage->attachBehavior(tutorialBehavior);
	});

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);

	ObjectEvents::watchForObject<MagePortal>(this, [=](MagePortal* portal)
	{
		this->portal = portal;
		
		if (questState == QuestState::Complete)
		{
			this->portal->openPortal(true);
		}
		else
		{
			this->portal->closePortal(true);
		}
	}, BeatTutorialF::QuestPortalTag);
}

void BeatTutorialF::onActivate(bool isActiveThroughSkippable)
{
}

void BeatTutorialF::onComplete()
{
	if (this->portal != nullptr)
	{
		this->portal->openPortal(true);
	}
}

void BeatTutorialF::onSkipped()
{
	this->removeAllListeners();
}
