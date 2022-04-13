#include "TalkToPrincessOpal.h"

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
#include "Entities/Platformer/Npcs/CastleValgrind/PrincessOpal.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Camera/CameraStop.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/CastleValgrind/MageTowerKey.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToPrincessOpal::MapKeyQuest = "talk-to-princess-opal";

TalkToPrincessOpal* TalkToPrincessOpal::create(GameObject* owner, QuestLine* questLine)
{
	TalkToPrincessOpal* instance = new TalkToPrincessOpal(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToPrincessOpal::TalkToPrincessOpal(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToPrincessOpal::MapKeyQuest, false)
{
}

TalkToPrincessOpal::~TalkToPrincessOpal()
{
}

void TalkToPrincessOpal::onLoad(QuestState questState)
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

	ObjectEvents::WatchForObject<PrincessOpal>(this, [=](PrincessOpal* princessOpal)
	{
		this->princessOpal = princessOpal;
		
		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->runCinematicSequence();
		}
	}, PrincessOpal::MapKey);
}

void TalkToPrincessOpal::onActivate(bool isActiveThroughSkippable)
{
}

void TalkToPrincessOpal::onComplete()
{
}

void TalkToPrincessOpal::onSkipped()
{
	this->removeAllListeners();
}

void TalkToPrincessOpal::runCinematicSequence()
{
	if (this->princessOpal == nullptr)
	{
		return;
	}
	
	this->princessOpal->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Menus_StoryMode::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->princessOpal, true)
			),
			[=]()
			{
				PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ MageTowerKey::create() }));
				this->complete();
			},
			Voices::GetNextVoiceShort(),
			false
		));
	});
}
