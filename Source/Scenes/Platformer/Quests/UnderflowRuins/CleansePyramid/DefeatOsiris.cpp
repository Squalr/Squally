#include "DefeatOsiris.h"

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
#include "Entities/Platformer/Enemies/UnderflowRuins/Osiris.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Cinematic/Sarcophagus/Sarcophagus.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string DefeatOsiris::MapKeyQuest = "defeat-osiris";
const std::string DefeatOsiris::MapEventAwakenOsiris = "awaken-osiris";
	

DefeatOsiris* DefeatOsiris::create(GameObject* owner, QuestLine* questLine)
{
	DefeatOsiris* instance = new DefeatOsiris(owner, questLine);

	instance->autorelease();

	return instance;
}

DefeatOsiris::DefeatOsiris(GameObject* owner, QuestLine* questLine) : super(owner, questLine, DefeatOsiris::MapKeyQuest, false)
{
	this->osiris = nullptr;
	this->squally = nullptr;
}

DefeatOsiris::~DefeatOsiris()
{
}

void DefeatOsiris::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Osiris>(this, [=](Osiris* osiris)
	{
		this->osiris = osiris;

		if (questState != QuestState::Complete)
		{
			if (!this->osiris->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
			{
				this->complete();
			}
			else
			{
				this->osiris->setOpacity(0);
			}
		}
	}, Osiris::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Sarcophagus>(this, [=](Sarcophagus* sarcophagus)
	{
		this->sarcophagus = sarcophagus;
		
		if (questState == QuestState::Complete)
		{
			this->sarcophagus->getLid()->setVisible(false);
		}
	}, Sarcophagus::MapKey);
}

void DefeatOsiris::onActivate(bool isActiveThroughSkippable)
{
	this->osiris->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->complete();
		}
	});

	this->listenForMapEventOnce(DefeatOsiris::MapEventAwakenOsiris, [=](ValueMap)
	{
		this->runCinematicSequencePt1();
	});
}

void DefeatOsiris::onComplete()
{
}

void DefeatOsiris::onSkipped()
{
	this->removeAllListeners();
}

void DefeatOsiris::runCinematicSequencePt1()
{
	PlatformerEvents::TriggerCinematicHijack();

	if (this->sarcophagus != nullptr)
	{
		const float RotationAngle = 2.5f;
		const float RotationSpeed = 0.05f;
		const float HalfRotationSpeed = RotationSpeed / 2.0f;
		const float RumbleTime = 3.0f;
		const float FloatTime = 2.0f;
		const int Rumbles = int(std::round((RumbleTime - RotationSpeed) / RotationSpeed)) / 2;

		this->sarcophagus->getLid()->runAction(Sequence::create(
			EaseSineInOut::create(RotateTo::create(HalfRotationSpeed, RotationAngle)),
			Repeat::create(Sequence::create(
				EaseSineInOut::create(RotateTo::create(RotationSpeed, -RotationAngle)),
				EaseSineInOut::create(RotateTo::create(RotationSpeed, RotationAngle)),
				nullptr
			), Rumbles),
			EaseSineInOut::create(RotateTo::create(HalfRotationSpeed, 0.0f)),
			nullptr
		));

		this->sarcophagus->getLid()->runAction(Sequence::create(
			DelayTime::create(RumbleTime - FloatTime),
			MoveBy::create(FloatTime, Vec2(0.0f, 144.0f)),
			CallFunc::create([=]()
			{
				this->runCinematicSequencePt2();
			}),
			EaseSineInOut::create(MoveBy::create(0.75f, Vec2(0.0f, -24.0f))),
			EaseSineInOut::create(MoveBy::create(0.75f, Vec2(0.0f, 24.0f))),
			EaseSineInOut::create(MoveBy::create(0.75f, Vec2(0.0f, -24.0f))),
			EaseSineInOut::create(MoveBy::create(0.75f, Vec2(0.0f, 24.0f))),
			nullptr
		));
	}
	else
	{
		this->runCinematicSequencePt2();
	}
}

void DefeatOsiris::runCinematicSequencePt2()
{
	if (this->osiris != nullptr)
	{
		this->osiris->runAction(Sequence::create(
			FadeTo::create(0.5f, 255),
			DelayTime::create(0.75f),
			CallFunc::create([=]()
			{
				this->runCinematicSequencePt3();
			}),
			nullptr
		));
	}
}

void DefeatOsiris::runCinematicSequencePt3()
{
	PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(this->osiris, true));
}
