#include "BeatTutorialD.h"

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
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/EndianForest/Gauntlet/TutorialDBehavior.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BeatTutorialD::MapKeyQuest = "beat-tutorial-D";
const std::string BeatTutorialD::WinLossTrackIdentifier = "Tutorial-D";
const std::string BeatTutorialD::QuestPortalTag = "quest-portal";

BeatTutorialD* BeatTutorialD::create(GameObject* owner, QuestLine* questLine)
{
	BeatTutorialD* instance = new BeatTutorialD(owner, questLine);

	instance->autorelease();

	return instance;
}

BeatTutorialD::BeatTutorialD(GameObject* owner, QuestLine* questLine) : super(owner, questLine, BeatTutorialD::MapKeyQuest, false)
{
	this->mage = dynamic_cast<PlatformerEntity*>(owner);
	this->squally = nullptr;
	this->portal = nullptr;
}

BeatTutorialD::~BeatTutorialD()
{
}

void BeatTutorialD::onLoad(QuestState questState)
{
	this->defer([=]()
	{
		TutorialDBehavior* tutorialBehavior = TutorialDBehavior::create(this->mage);

		tutorialBehavior->registerWinCallback([=]()
		{
			this->complete();
		});
		
    	this->mage->attachBehavior(tutorialBehavior);
	});

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<MagePortal>(this, [=](MagePortal* portal)
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
	}, BeatTutorialD::QuestPortalTag);
}

void BeatTutorialD::onActivate(bool isActiveThroughSkippable)
{
}

void BeatTutorialD::onComplete()
{
	if (this->portal != nullptr)
	{
		this->portal->openPortal(true);
	}
}

void BeatTutorialD::onSkipped()
{
	this->removeAllListeners();
}
