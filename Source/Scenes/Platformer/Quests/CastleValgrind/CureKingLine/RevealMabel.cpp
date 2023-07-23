#include "RevealMabel.h"

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
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Enemies/VoidStar/Perceptron.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/Npcs/Mages/Mabel.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Camera/CameraStop.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Components/Objects/Illusions/DispelIllusionBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Quests/CastleValgrind/CureKingLine/UnhauntCastle.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RevealMabel::MapKeyQuest = "reveal-mabel";
const std::string RevealMabel::MapEventMabelRevealed = "mabel-revealed";

RevealMabel* RevealMabel::create(GameObject* owner, QuestLine* questLine)
{
	RevealMabel* instance = new RevealMabel(owner, questLine);

	instance->autorelease();

	return instance;
}

RevealMabel::RevealMabel(GameObject* owner, QuestLine* questLine) : super(owner, questLine, RevealMabel::MapKeyQuest, false)
{
}

RevealMabel::~RevealMabel()
{
}

void RevealMabel::onLoad(QuestState questState)
{
}

void RevealMabel::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
	this->listenForMapEventOnce(RevealMabel::MapEventMabelRevealed, [=](ValueMap valueMap)
	{
		this->complete();
	});
}

void RevealMabel::onComplete()
{
}

void RevealMabel::onSkipped()
{
}
