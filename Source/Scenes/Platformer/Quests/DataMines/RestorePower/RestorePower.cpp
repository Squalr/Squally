#include "RestorePower.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/DataMines/PrincessDawn.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Physics/Lifts/CartLift.h"
#include "Objects/Platformer/Interactables/Computer/Computer.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RestorePower::MapKeyQuest = "restore-power";
const std::string RestorePower::MapEventPowerRestored = "power-restored";
const std::string RestorePower::TagCartLiftPowered = "cart-lift-powered";

RestorePower* RestorePower::create(GameObject* owner, QuestLine* questLine)
{
	RestorePower* instance = new RestorePower(owner, questLine);

	instance->autorelease();

	return instance;
}

RestorePower::RestorePower(GameObject* owner, QuestLine* questLine) : super(owner, questLine, RestorePower::MapKeyQuest, false)
{
	this->computer = dynamic_cast<Computer*>(owner);
}

RestorePower::~RestorePower()
{
}

void RestorePower::onLoad(QuestState questState)
{
	if (this->computer != nullptr)
	{
		this->computer->enable();
	}

	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<CartLift>(this, [=](CartLift* cartLift)
	{
		this->cartLift = cartLift;

		if (questState != QuestState::Complete)
		{
			this->cartLift->setMoving(false);
		}
	}, RestorePower::TagCartLiftPowered);

	if (questState == QuestState::Complete)
	{
		this->powerOnComputers();
	}
	
	this->listenForMapEvent(RestorePower::MapEventPowerRestored, [=](ValueMap)
	{
		Objectives::SetCurrentObjective(ObjectiveKeys::DMReturnToPrincessDawn);
		this->complete();
	});
}

void RestorePower::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void RestorePower::onComplete()
{
	SaveManager::SaveProfileData(SaveKeys::SaveKeyCrackProgress, Value(1));
	this->powerOnComputers();
}

void RestorePower::onSkipped()
{
}

void RestorePower::powerOnComputers()
{
	ObjectEvents::QueryObjects<Computer>([=](Computer* computer)
	{
		computer->turnOn();
	}, Computer::MapKey);
}
