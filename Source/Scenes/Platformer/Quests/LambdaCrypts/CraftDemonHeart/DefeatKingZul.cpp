#include "DefeatKingZul.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/KingZul.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DefeatKingZul::MapKeyQuest = "defeat-king-zul";

DefeatKingZul* DefeatKingZul::create(GameObject* owner, QuestLine* questLine)
{
	DefeatKingZul* instance = new DefeatKingZul(owner, questLine);

	instance->autorelease();

	return instance;
}

DefeatKingZul::DefeatKingZul(GameObject* owner, QuestLine* questLine) : super(owner, questLine, DefeatKingZul::MapKeyQuest, false)
{
	this->kingZul = dynamic_cast<KingZul*>(owner);
}

DefeatKingZul::~DefeatKingZul()
{
}

void DefeatKingZul::onLoad(QuestState questState)
{
	if (this->kingZul != nullptr)
	{
		if (!this->kingZul->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
		{
			this->complete();
		}
	}

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void DefeatKingZul::onActivate(bool isActiveThroughSkippable)
{
	this->kingZul->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->complete();
		}
	});
}

void DefeatKingZul::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::LCCraftHellKey);
	PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(HeartOfFire::create()));
}

void DefeatKingZul::onSkipped()
{
	this->removeAllListeners();
}
