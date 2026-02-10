#include "DefeatKingZul.h"

#include "2d/CCActionEase.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "2d/CCSprite.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCValue.h"

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

void DefeatKingZul::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
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
	Objectives::SetCurrentObjective(ObjectiveKeys::LCCraftDemonHeart);
	// Just give everything in case something went wrong / for debug use. These should be redundant with drop pool.
	PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ HeartOfFire::create(), HeartOfShadow::create(), AncientKey::create() }));
	PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(HeartOfFire::create()));
}

void DefeatKingZul::onSkipped()
{
	this->removeAllListeners();
}
