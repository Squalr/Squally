#include "TalkToGrogg.h"

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
#include "Entities/Platformer/Enemies/EndianForest/KingGrogg.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToGrogg::MapKeyQuest = "talk-to-grogg";

TalkToGrogg* TalkToGrogg::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	TalkToGrogg* instance = new TalkToGrogg(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

TalkToGrogg::TalkToGrogg(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, TalkToGrogg::MapKeyQuest, questTag, false)
{
	this->guano = nullptr;
	this->kingGrogg = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
}

TalkToGrogg::~TalkToGrogg()
{
}

void TalkToGrogg::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKeyGuano);

	ObjectEvents::watchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKeyScrappy);

	ObjectEvents::watchForObject<KingGrogg>(this, [=](KingGrogg* kingGrogg)
	{
		this->kingGrogg = kingGrogg;
	}, KingGrogg::MapKeyKingGrogg);

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);
}

void TalkToGrogg::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(TalkToGrogg::MapKeyQuest, [=](ValueMap args)
	{
		this->runCinematicSequence();
	});
}

void TalkToGrogg::onComplete()
{
}

void TalkToGrogg::onSkipped()
{
	this->removeAllListeners();
}

void TalkToGrogg::runCinematicSequence()
{
	if (this->kingGrogg == nullptr)
	{
		return;
	}
	
	this->kingGrogg->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_FindElriel_Queen_A_HowDoWeGetToTheRuins::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->kingGrogg, false),
				DialogueEvents::BuildPreviewNode(&this->guano, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterQuestion1,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_FindElriel_Queen_F_OrderMyGuards::create()
				->setStringReplacementVariables({ Strings::Platformer_Entities_Names_Npcs_EndianForest_Elriel::create() }),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->kingGrogg, false),
				DialogueEvents::BuildPreviewNode(&this->scrappy, true)
			),
			[=]()
			{
				this->complete();
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium4,
			true
		));
	});
}
