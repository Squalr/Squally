#include "BoardCharterShip.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Events/ObjectEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Transportation/Ship.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BoardCharterShip::MapKeyQuest = "board-charter-ship";
const std::string BoardCharterShip::TagDespawnableShip = "charter-ship";

BoardCharterShip* BoardCharterShip::create(GameObject* owner, QuestLine* questLine)
{
	BoardCharterShip* instance = new BoardCharterShip(owner, questLine);

	instance->autorelease();

	return instance;
}

BoardCharterShip::BoardCharterShip(GameObject* owner, QuestLine* questLine) : super(owner, questLine, BoardCharterShip::MapKeyQuest, false)
{
	this->portal = dynamic_cast<Portal*>(owner);
}

BoardCharterShip::~BoardCharterShip()
{
}

void BoardCharterShip::onLoad(QuestState questState)
{
	if (questState == QuestState::None)
	{
		if (this->portal != nullptr)
		{
			this->portal->disable();
		}
	}

	ObjectEvents::WatchForObject<Ship>(this, [=](Ship* ship)
	{
		this->ship = ship;

		if (questState == QuestState::None)
		{
			this->ship->setVisible(false);
		}
	}, BoardCharterShip::TagDespawnableShip);
	
	this->setReturnMap();
}

void BoardCharterShip::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
	if (this->portal != nullptr)
	{
		this->portal->enable();
	}
}

void BoardCharterShip::onComplete()
{
}

void BoardCharterShip::onSkipped()
{
}

void BoardCharterShip::setReturnMap()
{
	std::string mapResource = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyMap, Value("")).asString();
	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyCharterShipReturnMap, Value(mapResource));
}
