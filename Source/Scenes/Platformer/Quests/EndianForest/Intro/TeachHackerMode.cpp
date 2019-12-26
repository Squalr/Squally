#include "TeachHackerMode.h"

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
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/HelpTotems/HelpTotem.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TeachHackerMode::MapKeyQuest = "teach-hacker-mode";
const std::string TeachHackerMode::TagHelpTotemHacking = "help-totem-hacking";

TeachHackerMode* TeachHackerMode::create(GameObject* owner, QuestLine* questLine)
{
	TeachHackerMode* instance = new TeachHackerMode(owner, questLine);

	instance->autorelease();

	return instance;
}

TeachHackerMode::TeachHackerMode(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TeachHackerMode::MapKeyQuest, false)
{
	this->helpTotem = nullptr;
	this->squally = nullptr;
	this->scrappy = nullptr;
}

TeachHackerMode::~TeachHackerMode()
{
}

void TeachHackerMode::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<HelpTotem>(this, [=](HelpTotem* helpTotem)
	{
		this->helpTotem = helpTotem;
	}, TeachHackerMode::TagHelpTotemHacking);

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);

	ObjectEvents::watchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKeyScrappy);
}

void TeachHackerMode::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(TeachHackerMode::MapKeyQuest, [=](ValueMap args)
	{
		this->runCinematicSequencePt1();
	});
}

void TeachHackerMode::onComplete()
{
}

void TeachHackerMode::onSkipped()
{
	this->removeAllListeners();
}

void TeachHackerMode::runCinematicSequencePt1()
{
	this->complete();

	if (this->scrappy != nullptr)
	{
		this->scrappy->getAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->getSpeechBubble()->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_D_TrapAhead::create(), SoundResources::Platformer_Entities_Droid_DroidChatter, 4.0f, [=]()
			{
			});
		});
	}
}
