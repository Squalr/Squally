#include "TalkToElriel.h"

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
#include "Entities/Platformer/Enemies/EndianForest/Gorgon.h"
#include "Entities/Platformer/Npcs/BalmerPeaks/Aster.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Merlin.h"
#include "Entities/Platformer/Npcs/DaemonsHallow/Igneus.h"
#include "Entities/Platformer/Npcs/EndianForest/Elriel.h"
#include "Entities/Platformer/Npcs/EndianForest/Marcel.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Alder.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Sarude.h"
#include "Events/PlatformerEvents.h"

using namespace cocos2d;

const std::string TalkToElriel::MapKeyQuest = "talk-to-elriel";

TalkToElriel* TalkToElriel::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	TalkToElriel* instance = new TalkToElriel(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

TalkToElriel::TalkToElriel(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, TalkToElriel::MapKeyQuest, questTag, false)
{
	this->alder = nullptr;
	this->aster = nullptr;
	this->elriel = nullptr;
	this->gorgon = nullptr;
	this->igneus = nullptr;
	this->marcel = nullptr;
	this->merlin = nullptr;
	this->sarude = nullptr;
}

TalkToElriel::~TalkToElriel()
{
}

void TalkToElriel::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Alder>(this, [=](Alder* alder)
	{
		this->alder = alder;
	}, Alder::MapKeyAlder);
	ObjectEvents::watchForObject<Aster>(this, [=](Aster* aster)
	{
		this->aster = aster;
	}, Aster::MapKeyAster);
	ObjectEvents::watchForObject<Elriel>(this, [=](Elriel* elriel)
	{
		this->elriel = elriel;
	}, Elriel::MapKeyElriel);
	ObjectEvents::watchForObject<Gorgon>(this, [=](Gorgon* gorgon)
	{
		this->gorgon = gorgon;
	}, Gorgon::MapKeyGorgon);
	ObjectEvents::watchForObject<Igneus>(this, [=](Igneus* igneus)
	{
		this->igneus = igneus;
	}, Igneus::MapKeyIgneus);
	ObjectEvents::watchForObject<Marcel>(this, [=](Marcel* marcel)
	{
		this->marcel = marcel;
	}, Marcel::MapKeyMarcel);
	ObjectEvents::watchForObject<Merlin>(this, [=](Merlin* merlin)
	{
		this->merlin = merlin;
	}, Merlin::MapKeyMerlin);
	ObjectEvents::watchForObject<Sarude>(this, [=](Sarude* sarude)
	{
		this->sarude = sarude;
	}, Sarude::MapKeySarude);
}

void TalkToElriel::onActivate(bool isActiveThroughSkippable)
{
	this->runCinematicSequence();
}

void TalkToElriel::onComplete()
{
}

void TalkToElriel::onSkipped()
{
	this->removeAllListeners();
}

void TalkToElriel::runCinematicSequence()
{
	if (this->elriel != nullptr)
	{
	}

	this->runGorgonLoop();
	this->doCastAnim(this->alder);
	this->doCastAnim(this->aster);
	this->doCastAnim(this->igneus);
	this->doCastAnim(this->marcel);
	this->doCastAnim(this->merlin);
	this->doCastAnim(this->sarude);
}

void TalkToElriel::doCastAnim(PlatformerEntity* entity)
{
	if (entity == nullptr)
	{
		return;
	}
	
	entity->getAnimations()->playAnimation("AttackCastChannel", SmartAnimationNode::AnimationPlayMode::Repeat, 1.0f);
}

void TalkToElriel::runGorgonLoop()
{
	if (this->gorgon == nullptr)
	{
		return;
	}
	
	this->gorgon->getAnimations()->clearAnimationPriority();

	this->gorgon->getAnimations()->playAnimation("AttackRebound", SmartAnimationNode::AnimationPlayMode::Callback, 1.0f, 0.25f, [=]()
	{
		this->gorgon->getAnimations()->clearAnimationPriority();

		this->gorgon->getAnimations()->playAnimation("AttackStrongRebound", SmartAnimationNode::AnimationPlayMode::Callback, 1.0f, 0.25f, [=]()
		{
			this->gorgon->getAnimations()->clearAnimationPriority();

			this->gorgon->getAnimations()->playAnimation("AttackChargeRebound", SmartAnimationNode::AnimationPlayMode::Callback, 1.0f, 0.25f, [=]()
			{
				this->runGorgonLoop();
			});
		});
	});
}
