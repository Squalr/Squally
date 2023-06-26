#include "TakeArcaneBook.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/Npcs/Mages/Mabel.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Chests/ArcaneBook.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TakeArcaneBook::MapKeyQuest = "take-arcane-book";

TakeArcaneBook* TakeArcaneBook::create(GameObject* owner, QuestLine* questLine)
{
	TakeArcaneBook* instance = new TakeArcaneBook(owner, questLine);

	instance->autorelease();

	return instance;
}

TakeArcaneBook::TakeArcaneBook(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TakeArcaneBook::MapKeyQuest, false)
{
	this->arcaneBook = dynamic_cast<ArcaneBook*>(owner);
}

TakeArcaneBook::~TakeArcaneBook()
{
}

void TakeArcaneBook::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Gecky>(this, [=](Gecky* gecky)
	{
		this->gecky = gecky;
	}, Gecky::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Mabel>(this, [=](Mabel* mabel)
	{
		this->mabel = mabel;
	}, Mabel::MapKey);

	if (this->arcaneBook != nullptr)
	{
		if (questState == QuestState::None)
		{
			this->arcaneBook->disable();
		}
	}

	this->listenForMapEventOnce("arcane-book-taken", [=](ValueMap)
	{
		if (this->arcaneBook != nullptr)
		{
			this->arcaneBook->disable();
		}
		
		this->complete();
	});
}

void TakeArcaneBook::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
	Objectives::SetCurrentObjective(ObjectiveKeys::CVTakeArcaneBook);

	if (this->arcaneBook != nullptr)
	{
		this->arcaneBook->enable();
	}

	this->runCinematicSequencePt1();
}

void TakeArcaneBook::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::CVExamineArcaneEnergy);
}

void TakeArcaneBook::onSkipped()
{
	this->removeAllListeners();
}

void TakeArcaneBook::runCinematicSequencePt1()
{
	if (this->mabel == nullptr)
	{
		return;
	}
}
