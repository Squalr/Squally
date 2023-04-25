#include "CraftDemonHeart.h"

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
#include "Entities/Platformer/Npcs/Transition/Drak.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Camera/CameraStop.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Switches/Trigger.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Movement/SquallyRespawnBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Components/Objects/Illusions/DispelIllusionBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CraftDemonHeart::MapKeyQuest = "craft-demon-heart";

CraftDemonHeart* CraftDemonHeart::create(GameObject* owner, QuestLine* questLine)
{
	CraftDemonHeart* instance = new CraftDemonHeart(owner, questLine);

	instance->autorelease();

	return instance;
}

CraftDemonHeart::CraftDemonHeart(GameObject* owner, QuestLine* questLine) : super(owner, questLine, CraftDemonHeart::MapKeyQuest, false)
{
}

CraftDemonHeart::~CraftDemonHeart()
{
}

void CraftDemonHeart::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Drak>(this, [=](Drak* drak)
	{
		this->drak = drak;

		this->drak->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_LambdaCrypts_CraftDemonHeart_Drak_A_CraftDemonHeart::create()
					->setStringReplacementVariables({ Strings::Items_Misc_Keys_DemonHeart::create(), Strings::Platformer_MapNames_LambdaCrypts_LambdaCrypts::create(), Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_KingZul::create() }),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Right,
					DialogueEvents::BuildPreviewNode(&this->squally, false),
					DialogueEvents::BuildPreviewNode(&this->drak, true)
				),
				[=]()
				{
				},
				Voices::GetNextVoiceLong(),
				true
			));
		});
	}, Drak::MapKey);

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
}

void CraftDemonHeart::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventGiveItems, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::GiveItemsArgs* args = static_cast<PlatformerEvents::GiveItemsArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			for (Item* item : args->items)
			{
				if (dynamic_cast<DemonHeart*>(item) != nullptr)
				{
					this->complete();
				}
			}
		}
	}));
}

void CraftDemonHeart::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::LCOpenDemonPortal);
}

void CraftDemonHeart::onSkipped()
{
	this->removeAllListeners();
}
