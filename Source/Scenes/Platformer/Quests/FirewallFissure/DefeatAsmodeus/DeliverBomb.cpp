#include "DeliverBomb.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/FirewallFissure/Scaldor.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Camera/CameraTarget.h"
#include "Objects/Platformer/Decor/LavaFall.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Traps/FloatingBomb/FloatingBomb.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Quests/FirewallFissure/DefeatAsmodeus/LavaFlood.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string DeliverBomb::MapKeyQuest = "deliver-bomb";

DeliverBomb* DeliverBomb::create(GameObject* owner, QuestLine* questLine)
{
	DeliverBomb* instance = new DeliverBomb(owner, questLine);

	instance->autorelease();

	return instance;
}

DeliverBomb::DeliverBomb(GameObject* owner, QuestLine* questLine) : super(owner, questLine, DeliverBomb::MapKeyQuest, false)
{
	this->explosionSound = Sound::create(SoundResources::Platformer_FX_Explosions_Explosion1);

	this->addChild(this->explosionSound);
}

DeliverBomb::~DeliverBomb()
{
}

void DeliverBomb::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;

		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			// A bit lazy, ensures Scaldor is available by delaying 1 frame
			this->defer([=]()
			{
				this->runCinematicSequencePt1();
			});
		}
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Scaldor>(this, [=](Scaldor* scaldor)
	{
		this->scaldor = scaldor;

		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->scaldor->watchForComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
			{
				questBehavior->enableTurnIn();
			});
		}
	});

	ObjectEvents::WatchForObject<CameraTarget>(this, [=](CameraTarget* cameraTarget)
	{
		this->cinematicFocus = cameraTarget;
	}, "cinematic-geyser");

	ObjectEvents::WatchForObject<LavaFall>(this, [=](LavaFall* cinematicLavaFall)
	{
		this->cinematicLavaFall = cinematicLavaFall;

		if (questState != QuestState::Complete)
		{
			this->cinematicLavaFall->setOpacity(0);
		}
	}, "cinematic-lava-fall");
	
	CameraTarget* cinematicFocus = nullptr;
	LavaFall* cinematicLavaFall = nullptr;

	ObjectEvents::WatchForObject<FloatingBomb>(this, [=](FloatingBomb* floatingBomb)
	{
		this->floatingBomb = floatingBomb;

		CollisionObject* bombCollision = this->floatingBomb->getCollision();
		bombCollision->setGravity(Vec2(540.0f, 768.0f));
		bombCollision->setHorizontalDampening(bombCollision->getVerticalDampening());
		bombCollision->setPhysicsFlagEnabled(false);
		this->floatingBomb->setOpacity(0);
	});
}

void DeliverBomb::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void DeliverBomb::onComplete()
{	
	Objectives::SetCurrentObjective(ObjectiveKeys::FFFindAsmodeus);

	if (this->scaldor != nullptr)
	{
		this->scaldor->getComponent<EntityQuestVisualBehavior>([=](EntityQuestVisualBehavior* questBehavior)
		{
			questBehavior->disableAll();
		});
	}
	
	if (this->squally != nullptr)
	{
		this->squally->getComponent<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
		{
			HeliumBomb* heliumBomb = entityInventoryBehavior->getInventory()->getItemOfType<HeliumBomb>();

			if (heliumBomb != nullptr)
			{
				entityInventoryBehavior->getInventory()->tryRemove(heliumBomb);
			}
		});
	}
}

void DeliverBomb::onSkipped()
{
	this->removeAllListeners();
}

void DeliverBomb::runCinematicSequencePt1()
{
	if (this->squally == nullptr)
	{
		return;
	}
	
	this->squally->watchForComponent<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
	{
		this->scaldor->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			if (entityInventoryBehavior->getInventory()->hasItemOfType<HeliumBomb>())
			{
				interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_FirewallFissure_DefeatAsmodeus_Scaldor_A_BombReady::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(&this->scrappy, false),
						DialogueEvents::BuildPreviewNode(&this->scaldor, true)
					),
					[=]()
					{
						PlatformerEvents::TriggerDiscoverItem(PlatformerEvents::ItemDiscoveryArgs(HeliumBomb::create(), false));
					},
					Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
					false
				));

				interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_FirewallFissure_DefeatAsmodeus_Scaldor_B_Excellent::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Right,
						DialogueEvents::BuildPreviewNode(&this->scrappy, false),
						DialogueEvents::BuildPreviewNode(&this->scaldor, true)
					),
					[=]()
					{
						if (this->floatingBomb != nullptr && this->cinematicLavaFall != nullptr)
						{
							PlatformerEvents::TriggerCinematicHijack();

							this->floatingBomb->runAction(Sequence::create(
								FadeTo::create(0.5f, 255),
								CallFunc::create([=]()
								{
									PlatformerEvents::TriggerCinematicHijack();
									GameCamera::getInstance()->pushTarget(CameraTrackingData(
									this->floatingBomb->getCollision(), Vec2::ZERO, Vec2::ZERO, CameraTrackingData::CameraScrollType::Rectangle, CameraTrackingData::DefaultCameraFollowSpeed, 0.5f));
									this->floatingBomb->getCollision()->setPhysicsFlagEnabled(true);
								}),
								DelayTime::create(4.0f),
								CallFunc::create([=]()
								{
									PlatformerEvents::TriggerCinematicHijack();
									this->cinematicLavaFall->runAction(FadeTo::create(0.5f, 255));
									this->explosionSound->play();
									GameCamera::getInstance()->shakeCamera(0.5f, 12.0f, 1.5f);
									this->owner->broadcastMapEvent("lava-flood", ValueMap()); // Event to make platforms fall
									this->owner->broadcastMapEvent(LavaFlood::MapEventLavaFlooded, ValueMap());
									this->complete();
								}),
								DelayTime::create(4.0f),
								CallFunc::create([=]()
								{
									GameCamera::getInstance()->popTarget();
									this->runCinematicSequencePt2();
								}),
								nullptr
							));
						}
						else
						{
							// Fail-safe
							this->runCinematicSequencePt2();
						}
					},
					Voices::GetNextVoiceMedium(),
					false
				));
			}
			else
			{
				interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_FirewallFissure_DefeatAsmodeus_Scaldor_A_CraftBombPls::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(&this->scrappy, false),
						DialogueEvents::BuildPreviewNode(&this->scaldor, true)
					),
					[=]()
					{
					},
					Voices::GetNextVoiceLong(),
					true
				));
			}
		});
	});
}

void DeliverBomb::runCinematicSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_FirewallFissure_DefeatAsmodeus_Scaldor_C_WeDidIt::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->scaldor, true)
		),
		[=]()
		{
			PlatformerEvents::TriggerCinematicRestore();
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Human),
		false
	));
}