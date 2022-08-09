#include "WinGauntlet.h"

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
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Special/KillingMachines/KillingMachine1.h"
#include "Entities/Platformer/Special/KillingMachines/KillingMachine2.h"
#include "Entities/Platformer/Special/KillingMachines/KillingMachine3.h"
#include "Entities/Platformer/Special/KillingMachines/KillingMachine4.h"
#include "Entities/Platformer/Special/KillingMachines/KillingMachine5.h"
#include "Entities/Platformer/Special/KillingMachines/KillingMachine6.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Interactables/Mounts/GatlingGun/GatlingGun.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string WinGauntlet::MapKeyQuest = "win-gauntlet";
const std::string WinGauntlet::MapEventBeginGauntlet = "begin-gauntlet";

WinGauntlet* WinGauntlet::create(GameObject* owner, QuestLine* questLine)
{
	WinGauntlet* instance = new WinGauntlet(owner, questLine);

	instance->autorelease();

	return instance;
}

WinGauntlet::WinGauntlet(GameObject* owner, QuestLine* questLine) : super(owner, questLine, WinGauntlet::MapKeyQuest, false)
{
}

WinGauntlet::~WinGauntlet()
{
}

void WinGauntlet::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<KillingMachine1>(this, [=](KillingMachine1* killingMachine1)
	{
		this->killingMachine1 = killingMachine1;
	}, KillingMachine1::MapKey);

	ObjectEvents::WatchForObject<KillingMachine2>(this, [=](KillingMachine2* killingMachine2)
	{
		this->killingMachine2 = killingMachine2;
	}, KillingMachine2::MapKey);

	ObjectEvents::WatchForObject<KillingMachine3>(this, [=](KillingMachine3* killingMachine3)
	{
		this->killingMachine3 = killingMachine3;
	}, KillingMachine3::MapKey);
	
	ObjectEvents::WatchForObject<KillingMachine4>(this, [=](KillingMachine4* killingMachine4)
	{
		this->killingMachine4 = killingMachine4;
	}, KillingMachine4::MapKey);
	
	ObjectEvents::WatchForObject<KillingMachine5>(this, [=](KillingMachine5* killingMachine5)
	{
		this->killingMachine5 = killingMachine5;
	}, KillingMachine5::MapKey);
	
	ObjectEvents::WatchForObject<KillingMachine6>(this, [=](KillingMachine6* killingMachine6)
	{
		this->killingMachine6 = killingMachine6;
	}, KillingMachine6::MapKey);
	
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<GatlingGun>(this, [=](GatlingGun* gatlingGun)
	{
		this->gatlingGun = gatlingGun;
	}, GatlingGun::MapKey);
}

void WinGauntlet::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(WinGauntlet::MapEventBeginGauntlet, [=](ValueMap)
	{
		this->runCinematicSequencePt1();
	});
}

void WinGauntlet::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::UREnterTheMines);
}

void WinGauntlet::onSkipped()
{
	this->removeAllListeners();
}

void WinGauntlet::runCinematicSequencePt1()
{
	if (this->killingMachine1 == nullptr)
	{
		this->runCinematicSequencePt2();
		return;
	}

	this->killingMachine1->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(this->killingMachine1).x));
	this->killingMachine1->setState(StateKeys::CinematicDestinationX, Value(-4096.0f));
	this->killingMachine1->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->runCinematicSequencePt2();
		}
	});
}

void WinGauntlet::runCinematicSequencePt2()
{
	if (this->killingMachine2 == nullptr)
	{
		this->runCinematicSequencePt3();
		return;
	}

	this->killingMachine2->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(this->killingMachine2).x));
	this->killingMachine2->setState(StateKeys::CinematicDestinationX, Value(-4096.0f));
	this->killingMachine2->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->runCinematicSequencePt3();
		}
	});
}

void WinGauntlet::runCinematicSequencePt3()
{
	if (this->killingMachine3 == nullptr)
	{
		this->runCinematicSequencePt4();
		return;
	}

	this->killingMachine3->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(this->killingMachine3).x));
	this->killingMachine3->setState(StateKeys::CinematicDestinationX, Value(-4096.0f));
	this->killingMachine3->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->runCinematicSequencePt4();
		}
	});
}

void WinGauntlet::runCinematicSequencePt4()
{
	if (this->killingMachine4 == nullptr)
	{
		this->runCinematicSequencePt5();
		return;
	}

	this->killingMachine4->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(this->killingMachine4).x));
	this->killingMachine4->setState(StateKeys::CinematicDestinationX, Value(-4096.0f));
	this->killingMachine4->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->runCinematicSequencePt5();
		}
	});
}

void WinGauntlet::runCinematicSequencePt5()
{
	if (this->killingMachine5 == nullptr)
	{
		this->runCinematicSequencePt6();
		return;
	}

	this->killingMachine5->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(this->killingMachine5).x));
	this->killingMachine5->setState(StateKeys::CinematicDestinationX, Value(-4096.0f));
	this->killingMachine5->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->runCinematicSequencePt6();
		}
	});
}

void WinGauntlet::runCinematicSequencePt6()
{
	if (this->killingMachine6 == nullptr)
	{
		this->runCinematicSequencePt7();
		return;
	}

	this->killingMachine6->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(this->killingMachine6).x));
	this->killingMachine6->setState(StateKeys::CinematicDestinationX, Value(-4096.0f));
	this->killingMachine6->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->runCinematicSequencePt7();
		}
	});
}

void WinGauntlet::runCinematicSequencePt7()
{
	this->complete();
}
