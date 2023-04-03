#include "DefeatElric.h"

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
#include "Entities/Platformer/Enemies/LambdaCrypts/ZombieElric.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DefeatElric::MapKeyQuest = "defeat-elric";

DefeatElric* DefeatElric::create(GameObject* owner, QuestLine* questLine)
{
	DefeatElric* instance = new DefeatElric(owner, questLine);

	instance->autorelease();

	return instance;
}

DefeatElric::DefeatElric(GameObject* owner, QuestLine* questLine) : super(owner, questLine, DefeatElric::MapKeyQuest, false)
{
	this->zombieElric = dynamic_cast<ZombieElric*>(owner);
}

DefeatElric::~DefeatElric()
{
}

void DefeatElric::onLoad(QuestState questState)
{
	if (this->zombieElric != nullptr)
	{
		if (!this->zombieElric->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
		{
			this->complete();
		}
		else
		{
			this->zombieElric->setOpacity(0);
		}
	}

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void DefeatElric::onActivate(bool isActiveThroughSkippable)
{
	this->zombieElric->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->complete();
		}
	});
}

void DefeatElric::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::LCEnterSecondCrypt);
}

void DefeatElric::onSkipped()
{
	this->removeAllListeners();
}
