#include "BeatTutorialB.h"

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
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/EndianForest/Gauntlet/TutorialBBehavior.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BeatTutorialB::MapKeyQuest = "beat-tutorial-B";
const std::string BeatTutorialB::WinLossTrackIdentifier = "Tutorial-B";
const std::string BeatTutorialB::QuestPortalTag = "quest-portal";

BeatTutorialB* BeatTutorialB::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	BeatTutorialB* instance = new BeatTutorialB(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

BeatTutorialB::BeatTutorialB(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, BeatTutorialB::MapKeyQuest, questTag, false)
{
	this->mage = dynamic_cast<PlatformerEntity*>(owner);
	this->squally = nullptr;
	this->portal = nullptr;
}

BeatTutorialB::~BeatTutorialB()
{
}

void BeatTutorialB::onLoad(QuestState questState)
{
    TutorialBBehavior* tutorialBehavior = TutorialBBehavior::create(this->mage);

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
	}, BeatTutorialB::QuestPortalTag);
}

void BeatTutorialB::onActivate(bool isActiveThroughSkippable)
{
}

void BeatTutorialB::onComplete()
{
	if (this->portal != nullptr)
	{
		this->portal->openPortal(true);
	}
}

void BeatTutorialB::onSkipped()
{
	this->removeAllListeners();
}
