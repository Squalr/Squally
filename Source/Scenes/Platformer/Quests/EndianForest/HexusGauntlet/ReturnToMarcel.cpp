#include "ReturnToMarcel.h"

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
#include "Entities/Platformer/Npcs/EndianForest/Marcel.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Doors/MagePortals/MagePortal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Hexus/EndianForest/MarcelTutorialBehavior.h"

#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/Marcel/IChallengeYou.h"

#include "Strings/Hexus/Hexus.h"

using namespace cocos2d;

const std::string ReturnToMarcel::MapKeyQuest = "return-to-marcel";
const std::string ReturnToMarcel::QuestPortalTag = "quest-portal";

ReturnToMarcel* ReturnToMarcel::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	ReturnToMarcel* instance = new ReturnToMarcel(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

ReturnToMarcel::ReturnToMarcel(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, ReturnToMarcel::MapKeyQuest, questTag, false)
{
	this->marcel = nullptr;
	this->squally = nullptr;
	this->portal = nullptr;
}

ReturnToMarcel::~ReturnToMarcel()
{
}

void ReturnToMarcel::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Marcel>(this, [=](Marcel* marcel)
	{
		this->marcel = marcel;
	}, Marcel::MapKeyMarcel);

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);

	ObjectEvents::watchForObject<MagePortal>(this, [=](MagePortal* portal)
	{
		this->portal = portal;
		
		if (questState != QuestState::Complete)
		{
			this->portal->closePortal(true);
		}
	}, ReturnToMarcel::QuestPortalTag);
}

void ReturnToMarcel::onActivate(bool isActiveThroughSkippable)
{
	this->registerDialogue();
}

void ReturnToMarcel::onComplete()
{
}

void ReturnToMarcel::onSkipped()
{
	this->removeAllListeners();
}

void ReturnToMarcel::registerDialogue()
{
	if (this->marcel != nullptr)
	{
		this->marcel->attachBehavior(MarcelTutorialBehavior::create(this->marcel));
	}
}
