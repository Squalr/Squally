#include "PerceptronEscape.h"

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
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/Enemies/VoidStar/Perceptron.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PerceptronEscape::MapKeyQuest = "perceptron-escape";

PerceptronEscape* PerceptronEscape::create(GameObject* owner, QuestLine* questLine)
{
	PerceptronEscape* instance = new PerceptronEscape(owner, questLine);

	instance->autorelease();

	return instance;
}

PerceptronEscape::PerceptronEscape(GameObject* owner, QuestLine* questLine) : super(owner, questLine, PerceptronEscape::MapKeyQuest, false)
{
	this->perceptron = dynamic_cast<Perceptron*>(owner);
}

PerceptronEscape::~PerceptronEscape()
{
}

void PerceptronEscape::onLoad(QuestState questState)
{
	if (this->perceptron != nullptr)
	{
		if (questState == QuestState::Active)
		{
			this->perceptron->getAnimations()->setFlippedX(false);
		}
		else if (questState == QuestState::Complete)
		{
			this->perceptron->getAnimations()->setFlippedX(false);
			this->perceptron->getAnimations()->clearAnimationPriority();
			this->perceptron->getAnimations()->playAnimation("Dead_Escaped", SmartAnimationNode::AnimationPlayMode::Repeat);
		}
	}

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Portal>(this, [=](Portal* exitPortal)
	{
		this->exitPortal = exitPortal;

		if (questState != QuestState::Complete)
		{
			this->exitPortal->disable();
		}
	}, "exit");
}

void PerceptronEscape::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
	// 1 frame delay otherwise hijack wont get picked up
	this->defer([=]()
	{
		this->runCinematicSequencePt1();
	});
}

void PerceptronEscape::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::VSDestroyPerceptron);

	if (this->exitPortal != nullptr)
	{
		this->exitPortal->enable();
	}
}

void PerceptronEscape::onSkipped()
{
	this->removeAllListeners();
}

void PerceptronEscape::runCinematicSequencePt1()
{
	if (this->perceptron == nullptr)
	{
		return;
	}

	PlatformerEvents::TriggerCinematicHijack();

	this->perceptron->getAnimations()->setFlippedX(false);

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::TODO::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Top,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->perceptron, true)
		),
		[=]()
		{
			this->runCinematicSequencePt2();
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Demon),
		false
	));
}

void PerceptronEscape::runCinematicSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::TODO::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Top,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->perceptron, true)
		),
		[=]()
		{
			this->perceptron->getAnimations()->clearAnimationPriority();
			this->perceptron->getAnimations()->playAnimation("Escape", SmartAnimationNode::AnimationPlayMode::Callback, SmartAnimationNode::AnimParams(), [=]()
			{
				this->perceptron->getAnimations()->clearAnimationPriority();
				this->perceptron->getAnimations()->playAnimation("Dead_Escaped", SmartAnimationNode::AnimationPlayMode::Repeat);
			});
			this->complete();
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Demon),
		true
	));
}
