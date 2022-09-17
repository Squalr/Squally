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
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Interactables/Doors/MineDoor/MineDoor.h"
#include "Objects/Platformer/Physics/Lifts/CartLift.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RestorePower::MapKeyQuest = "restore-power";

RestorePower* RestorePower::create(GameObject* owner, QuestLine* questLine)
{
	RestorePower* instance = new RestorePower(owner, questLine);

	instance->autorelease();

	return instance;
}

RestorePower::RestorePower(GameObject* owner, QuestLine* questLine) : super(owner, questLine, RestorePower::MapKeyQuest, false)
{
}

RestorePower::~RestorePower()
{
}

void RestorePower::onLoad(QuestState questState)
{
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
			// Delayed because the lift moves by default, and stopping actions too close to starting them seems to be broken
			this->defer([=]()
			{
				this->cartLift->setMoving(false);
			}, 5);
		}
	}, CartLift::MapKey);

	ObjectEvents::WatchForObject<MineDoor>(this, [=](MineDoor* mineDoor)
	{
		this->mineDoor = mineDoor;

		if (questState != QuestState::Active && questState != QuestState::ActiveThroughSkippable)
		{
			this->mineDoor->lock();
		}
	}, MineDoor::MapKey);
}

void RestorePower::onActivate(bool isActiveThroughSkippable)
{
}

void RestorePower::onComplete()
{	
}

void RestorePower::onSkipped()
{
	this->removeAllListeners();
}
