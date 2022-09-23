#include "CharterShip.h"

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
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/MapResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CharterShip::MapKeyQuest = "charter-ship";
const std::string CharterShip::QuestTagShipPortal = "ship-portal";

CharterShip* CharterShip::create(GameObject* owner, QuestLine* questLine)
{
	CharterShip* instance = new CharterShip(owner, questLine);

	instance->autorelease();

	return instance;
}

CharterShip::CharterShip(GameObject* owner, QuestLine* questLine) : super(owner, questLine, CharterShip::MapKeyQuest, false)
{
	this->portal = dynamic_cast<Portal*>(owner);
}

CharterShip::~CharterShip()
{
}

void CharterShip::onLoad(QuestState questState)
{
	std::string returnMap = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCharterShipReturnMap, Value("")).asString();
	this->portal->setMapFile(returnMap);
}

void CharterShip::onActivate(bool isActiveThroughSkippable)
{
}

void CharterShip::onComplete()
{
}

void CharterShip::onSkipped()
{
}
