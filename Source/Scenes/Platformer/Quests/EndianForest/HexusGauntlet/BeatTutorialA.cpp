#include "BeatTutorialA.h"

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
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/EndianForest/Gauntlet/TutorialABehavior.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Hexus/Hexus.h"

using namespace cocos2d;

const std::string BeatTutorialA::MapKeyQuest = "beat-tutorial-A";
const std::string BeatTutorialA::WinLossTrackIdentifier = "Tutorial-A";
const std::string BeatTutorialA::QuestPortalTag = "quest-portal";

BeatTutorialA* BeatTutorialA::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	BeatTutorialA* instance = new BeatTutorialA(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

BeatTutorialA::BeatTutorialA(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, BeatTutorialA::MapKeyQuest, questTag, false)
{
	this->mage = dynamic_cast<PlatformerEntity*>(owner);
	this->squally = nullptr;
	this->portal = nullptr;
}

BeatTutorialA::~BeatTutorialA()
{
}

void BeatTutorialA::onLoad(QuestState questState)
{
    TutorialABehavior* tutorialBehavior = TutorialABehavior::create(this->mage);

    tutorialBehavior->registerWinCallback([=]()
    {
        this->complete();
    });

    this->mage->attachBehavior(tutorialBehavior);

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
	}, BeatTutorialA::QuestPortalTag);
}

void BeatTutorialA::onActivate(bool isActiveThroughSkippable)
{
}

void BeatTutorialA::onComplete()
{
	if (this->portal != nullptr)
	{
		this->portal->openPortal(true);
	}
}

void BeatTutorialA::onSkipped()
{
	this->removeAllListeners();
}
