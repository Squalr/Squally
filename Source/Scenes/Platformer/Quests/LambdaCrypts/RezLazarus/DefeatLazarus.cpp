#include "DefeatLazarus.h"

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
#include "Entities/Platformer/Enemies/LambdaCrypts/Lazarus.h"
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

const std::string DefeatLazarus::MapKeyQuest = "defeat-lazarus";

DefeatLazarus* DefeatLazarus::create(GameObject* owner, QuestLine* questLine)
{
	DefeatLazarus* instance = new DefeatLazarus(owner, questLine);

	instance->autorelease();

	return instance;
}

DefeatLazarus::DefeatLazarus(GameObject* owner, QuestLine* questLine) : super(owner, questLine, DefeatLazarus::MapKeyQuest, false)
{
	this->lazarus = dynamic_cast<Lazarus*>(owner);
}

DefeatLazarus::~DefeatLazarus()
{
}

void DefeatLazarus::onLoad(QuestState questState)
{
	if (this->lazarus != nullptr)
	{
		if (!this->lazarus->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
		{
			this->defer([=]()
			{
				this->complete();
			});
		}
	}

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void DefeatLazarus::onActivate(bool isActiveThroughSkippable)
{
	this->lazarus->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->complete();
		}
	});
}

void DefeatLazarus::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::LCEnterGreaterCrypt);
	PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ HeartOfShadow::create() }));
	PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ AncientKey::create() }));
	PlatformerEvents::TriggerDiscoverItems(PlatformerEvents::ItemsDiscoveryArgs({ HeartOfShadow::create(), AncientKey::create() }));
}

void DefeatLazarus::onSkipped()
{
	this->removeAllListeners();
}
