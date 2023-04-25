#include "OpenDemonPortal.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/Sound.h"
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
#include "Objects/Platformer/Interactables/Doors/HellGate/HellGate.h"
#include "Objects/Platformer/Switches/Trigger.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Movement/SquallyRespawnBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Components/Objects/Illusions/DispelIllusionBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string OpenDemonPortal::MapKeyQuest = "open-demon-portal";

OpenDemonPortal* OpenDemonPortal::create(GameObject* owner, QuestLine* questLine)
{
	OpenDemonPortal* instance = new OpenDemonPortal(owner, questLine);

	instance->autorelease();

	return instance;
}

OpenDemonPortal::OpenDemonPortal(GameObject* owner, QuestLine* questLine) : super(owner, questLine, OpenDemonPortal::MapKeyQuest, false)
{
}

OpenDemonPortal::~OpenDemonPortal()
{
}

void OpenDemonPortal::onLoad(QuestState questState)
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

	ObjectEvents::WatchForObject<HellGate>(this, [=](HellGate* hellGate)
	{
		this->hellGate = hellGate;

		this->defer([=]()
		{
			if (!this->hellGate->getIsLocked())
			{
				this->complete();
			}

			this->hellGate->setInteractCallback([=]()
			{
				this->complete();
				return true;
			});
		});
	}, HellGate::MapKey);
}

void OpenDemonPortal::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void OpenDemonPortal::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::FFExploreFirewallFissure);
}

void OpenDemonPortal::onSkipped()
{
	this->removeAllListeners();
}

void OpenDemonPortal::runCinematicSequencePt1()
{
}

void OpenDemonPortal::runCinematicSequenceStrikeZone()
{
}
