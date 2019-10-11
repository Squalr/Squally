#include "ReturnToSarude.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/DialogueSet.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Sarude.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Doors/MagePortals/MagePortal.h"
#include "Scenes/Platformer/AttachedBehavior/Npcs/Dialogue/NpcDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Npcs/Hexus/EndianForest/SarudeTutorialBehavior.h"

#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Sarude/IChallengeYou.h"

#include "Strings/Hexus/Hexus.h"

using namespace cocos2d;

const std::string ReturnToSarude::MapKeyQuest = "return-to-sarude";
const std::string ReturnToSarude::QuestPortalTag = "quest-portal";

ReturnToSarude* ReturnToSarude::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	ReturnToSarude* instance = new ReturnToSarude(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

ReturnToSarude::ReturnToSarude(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, ReturnToSarude::MapKeyQuest, questTag, false)
{
	this->sarude = nullptr;
	this->squally = nullptr;
	this->portal = nullptr;
}

ReturnToSarude::~ReturnToSarude()
{
}

void ReturnToSarude::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Sarude>(this, [=](Sarude* sarude)
	{
		this->sarude = sarude;

		this->sarude->attachBehavior(SarudeTutorialBehavior::create(this->sarude));
	});

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	});

	ObjectEvents::watchForObject<MagePortal>(this, [=](MagePortal* portal)
	{
		this->portal = portal;
		
		if (questState != QuestState::Complete)
		{
			this->portal->closePortal(true);
		}
	}, ReturnToSarude::QuestPortalTag);
}

void ReturnToSarude::onActivate(bool isActiveThroughSkippable)
{
	this->registerDialogue();
}

void ReturnToSarude::onComplete()
{
}

void ReturnToSarude::onSkipped()
{
	this->removeAllListeners();
}

void ReturnToSarude::registerDialogue()
{
	this->sarude->watchForAttachedBehavior<NpcDialogueBehavior>([=](NpcDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_Sarude_IChallengeYou::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			[=]()
			{
			},
			DialogueEvents::BuildPreviewNode(this->sarude, false),
			DialogueEvents::BuildPreviewNode(this->squally, true)
		));
	});
}
