#include "ReleasePressure.h"

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
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ReleasePressure::MapKeyQuest = "release-pressure";
const std::string ReleasePressure::MapEventPressureReleased = "pressure-released";
const std::string ReleasePressure::MapTagPressureRaised = "pressure-raised";
const std::string ReleasePressure::MapTagPressureLowered = "pressure-lowered";

ReleasePressure* ReleasePressure::create(GameObject* owner, QuestLine* questLine)
{
	ReleasePressure* instance = new ReleasePressure(owner, questLine);

	instance->autorelease();

	return instance;
}

ReleasePressure::ReleasePressure(GameObject* owner, QuestLine* questLine) : super(owner, questLine, ReleasePressure::MapKeyQuest, false)
{
}

ReleasePressure::~ReleasePressure()
{
}

void ReleasePressure::onLoad(QuestState questState)
{
	switch (questState)
	{
		case QuestState::Active:
		case QuestState::ActiveThroughSkippable:
		default:
		{
			ObjectEvents::QueryObjects<GameObject>([=](GameObject* object)
			{
				object->despawn();
			}, ReleasePressure::MapTagPressureRaised);
			break;
		}
		case QuestState::Complete:
		{
			ObjectEvents::QueryObjects<GameObject>([=](GameObject* object)
			{
				object->despawn();
			}, ReleasePressure::MapTagPressureLowered);
			break;
		}
	}
}

void ReleasePressure::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(ReleasePressure::MapEventPressureReleased, [=](ValueMap)
	{
		this->complete();
	});
}

void ReleasePressure::onComplete()
{
	// Objectives::SetCurrentObjective(ObjectiveKeys::UREnterTheMines); // Enter town maybe
}

void ReleasePressure::onSkipped()
{
	this->removeAllListeners();
}
