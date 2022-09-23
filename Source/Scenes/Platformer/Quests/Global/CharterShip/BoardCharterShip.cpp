#include "BoardCharterShip.h"

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
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Npcs/Transition/Blackbeard.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Objects/DisabledPortal.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/SoundResources.h"
#include "Resources/MapResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BoardCharterShip::MapKeyQuest = "board-charter-ship";

BoardCharterShip* BoardCharterShip::create(GameObject* owner, QuestLine* questLine)
{
	BoardCharterShip* instance = new BoardCharterShip(owner, questLine);

	instance->autorelease();

	return instance;
}

BoardCharterShip::BoardCharterShip(GameObject* owner, QuestLine* questLine) : super(owner, questLine, BoardCharterShip::MapKeyQuest, false)
{
}

BoardCharterShip::~BoardCharterShip()
{
}

void BoardCharterShip::onLoad(QuestState questState)
{
	std::string mapResource = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyMap, Value("")).asString();
	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyCharterShipReturnMap, Value(mapResource));
}

void BoardCharterShip::onActivate(bool isActiveThroughSkippable)
{
}

void BoardCharterShip::onComplete()
{
}

void BoardCharterShip::onSkipped()
{
}
