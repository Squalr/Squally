#include "DefeatRhinoman.h"

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
#include "Entities/Platformer/Enemies/DataMines/Rhinoman.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Cinematic/Sarcophagus/Sarcophagus.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string DefeatRhinoman::MapKeyQuest = "defeat-rhinoman";
const std::string DefeatRhinoman::MapEventAwakenRhinoman = "awaken-rhinoman";
const std::string DefeatRhinoman::TagExitPortal = "exit-portal";

DefeatRhinoman* DefeatRhinoman::create(GameObject* owner, QuestLine* questLine)
{
	DefeatRhinoman* instance = new DefeatRhinoman(owner, questLine);

	instance->autorelease();

	return instance;
}

DefeatRhinoman::DefeatRhinoman(GameObject* owner, QuestLine* questLine) : super(owner, questLine, DefeatRhinoman::MapKeyQuest, false)
{
	this->rumbleSound = WorldSound::create(SoundResources::Platformer_FX_Rumbles_StoneRumbleAndRumble1);

	this->addChild(this->rumbleSound);
}

DefeatRhinoman::~DefeatRhinoman()
{
}

void DefeatRhinoman::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Portal>(this, [=](Portal* portal)
	{
		if (questState != QuestState::Complete)
		{
			portal->lock(false);
		}

		ObjectEvents::WatchForObject<Rhinoman>(this, [=](Rhinoman* rhinoman)
		{
			this->rhinoman = rhinoman;

			if (questState != QuestState::Complete)
			{
				if (!this->rhinoman->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
				{
					this->complete();
				}
				else
				{
					this->rhinoman->setOpacity(0);
				}
			}
		}, Rhinoman::MapKey);
	}, DefeatRhinoman::TagExitPortal);

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

void DefeatRhinoman::onActivate(bool isActiveThroughSkippable)
{
	this->rhinoman->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->complete();
		}
	});

	this->listenForMapEventOnce(DefeatRhinoman::MapEventAwakenRhinoman, [=](ValueMap)
	{
		this->runCinematicSequencePt1();
	});
}

void DefeatRhinoman::onComplete()
{
	ObjectEvents::WatchForObject<Portal>(this, [=](Portal* portal)
	{
		portal->unlock(false);
	}, DefeatRhinoman::TagExitPortal);
	
	ObjectEvents::WatchForObject<Sarcophagus>(this, [=](Sarcophagus* sarcophagus)
	{
		this->sarcophagus = sarcophagus;
		
		this->sarcophagus->getLid()->setVisible(false);
	}, Sarcophagus::MapKey);

	Objectives::SetCurrentObjective(ObjectiveKeys::UREnterTheMines);
}

void DefeatRhinoman::onSkipped()
{
	this->removeAllListeners();
}

void DefeatRhinoman::runCinematicSequencePt1()
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

		this->rumbleSound->play();

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

void DefeatRhinoman::runCinematicSequencePt2()
{
	if (this->rhinoman != nullptr)
	{
		this->rhinoman->runAction(Sequence::create(
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

void DefeatRhinoman::runCinematicSequencePt3()
{
	PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(this->rhinoman, true));
}
