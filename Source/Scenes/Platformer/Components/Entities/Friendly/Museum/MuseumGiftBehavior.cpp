#include "MuseumGiftBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Save/Collectables.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MuseumGiftBehavior::MapKey = "museum-gift";
const std::string MuseumGiftBehavior::PropertyMuseumZone = "museum-zone";

MuseumGiftBehavior* MuseumGiftBehavior::create(GameObject* owner)
{
	MuseumGiftBehavior* instance = new MuseumGiftBehavior(owner);

	instance->autorelease();

	return instance;
}

MuseumGiftBehavior::MuseumGiftBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->museumZone = GameUtils::getKeyOrDefault(owner->properties, MuseumGiftBehavior::PropertyMuseumZone, Value("")).asString();
	}
}

MuseumGiftBehavior::~MuseumGiftBehavior()
{
}

void MuseumGiftBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	this->setPostText();
}

void MuseumGiftBehavior::onDisable()
{
	super::onDisable();
}

void MuseumGiftBehavior::setPostText()
{
	this->defer([=]()
	{
		int collectedAnimalCount = Collectables::getCollectedAnimalCount();
		int collectedAnimalTotal = Collectables::getCollectedAnimalTotal();

		if (collectedAnimalCount >= collectedAnimalTotal && !SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemHGiven, Value(false)).asBool())
		{
			bool hasGottenAllOtherItems = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemAGiven, Value(false)).asBool() &&
				SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemBGiven, Value(false)).asBool() &&
				SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemCGiven, Value(false)).asBool() &&
				SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemDGiven, Value(false)).asBool() &&
				SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemEGiven, Value(false)).asBool() &&
				SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemFGiven, Value(false)).asBool() &&
				SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemGGiven, Value(false)).asBool();

			if (hasGottenAllOtherItems)
			{
				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_Museum_Generic_D_LastAnimal::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Left,
						DialogueEvents::BuildPreviewNode(&this->entity, false),
						DialogueEvents::BuildPreviewNode(&this->squally, true)
					),
					[=]()
					{
						PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ AshenBlade::create() }));
						PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ AmethystNecklace::create() }));
						PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ DarkHeartBand::create() }));
						SaveManager::SaveProfileData(SaveKeys::SaveKeyItemHGiven, Value(true));
						this->setPostText();
					},
					Voices::GetNextVoiceMedium(),
					true
				));

				return;
			}
		}
		
		if (this->museumZone == "ef")
		{
			this->setPostTextEF();
		}
		else if (this->museumZone == "ur")
		{
			this->setPostTextUR();
		}
		else if (this->museumZone == "dm")
		{
			this->setPostTextDM();
		}
		else if (this->museumZone == "cv")
		{
			this->setPostTextCV();
		}
		else if (this->museumZone == "lc")
		{
			this->setPostTextLC();
		}
		else if (this->museumZone == "ff")
		{
			this->setPostTextFF();
		}
		else if (this->museumZone == "bp")
		{
			this->setPostTextBP();
		}
	});
}

void MuseumGiftBehavior::setPostTextEF()
{
	if (SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemAGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_Museum_Generic_C_Thanks::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->setPostText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});

		return;
	}

	int collectedAnimalCount =
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCat, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalDog, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalFox, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBear, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCow, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalMonkey, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalWhale, Value(false)).asBool();
	const int collectedAnimalCountMax = 7;
	
	if (collectedAnimalCount < collectedAnimalCountMax)
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_Museum_Generic_A_Missing::create()
					->setStringReplacementVariables({ ConstantString::create(std::to_string(collectedAnimalCountMax - collectedAnimalCount)), Strings::Platformer_MapNames_EndianForest_EndianForest::create() }),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->setPostText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});

		return;
	}
	
	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_Museum_Generic_B_TakeThis::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->entity, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ GarnetBand::create() }));
				SaveManager::SaveProfileData(SaveKeys::SaveKeyItemAGiven, Value(true));
				this->setPostText();
			},
			Voices::GetNextVoiceMedium(),
			true
		));
	});
}

void MuseumGiftBehavior::setPostTextUR()
{
	if (SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemBGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_Museum_Generic_C_Thanks::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->setPostText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});

		return;
	}

	int collectedAnimalCount =
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalDuck, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalSquid, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalHippo, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalSnail, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalMouse, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalSquirrel, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalGiraffe, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalZebra, Value(false)).asBool();
	const int collectedAnimalCountMax = 8;
	
	if (collectedAnimalCount < collectedAnimalCountMax)
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_Museum_Generic_A_Missing::create()
					->setStringReplacementVariables({ ConstantString::create(std::to_string(collectedAnimalCountMax - collectedAnimalCount)), Strings::Platformer_MapNames_UnderflowRuins_UnderflowRuins::create() }),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->setPostText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});

		return;
	}
	
	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_Museum_Generic_B_TakeThis::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->entity, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ ShellBand::create() }));
				SaveManager::SaveProfileData(SaveKeys::SaveKeyItemBGiven, Value(true));
				this->setPostText();
			},
			Voices::GetNextVoiceMedium(),
			true
		));
	});
}

void MuseumGiftBehavior::setPostTextDM()
{
	if (SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemCGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_Museum_Generic_C_Thanks::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->setPostText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});

		return;
	}

	int collectedAnimalCount =
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalPanda, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalSkunk, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalTiger, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBird, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalTurtle, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalRaccoon, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalRhino, Value(false)).asBool();
	const int collectedAnimalCountMax = 7;
	
	if (collectedAnimalCount < collectedAnimalCountMax)
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_Museum_Generic_A_Missing::create()
					->setStringReplacementVariables({ ConstantString::create(std::to_string(collectedAnimalCountMax - collectedAnimalCount)), Strings::Platformer_MapNames_DataMines_DataMines::create() }),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->setPostText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});

		return;
	}
	
	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_Museum_Generic_B_TakeThis::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->entity, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ EmeraldBand::create() }));
				SaveManager::SaveProfileData(SaveKeys::SaveKeyItemCGiven, Value(true));
				this->setPostText();
			},
			Voices::GetNextVoiceMedium(),
			true
		));
	});
}

void MuseumGiftBehavior::setPostTextCV()
{
	if (SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemDGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_Museum_Generic_C_Thanks::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->setPostText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});

		return;
	}

	int collectedAnimalCount =
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBeaver, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalKoala, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalHorse, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalHedgehog, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalPig, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalParrot, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalSheep, Value(false)).asBool();
	const int collectedAnimalCountMax = 7;
	
	if (collectedAnimalCount < collectedAnimalCountMax)
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_Museum_Generic_A_Missing::create()
					->setStringReplacementVariables({ ConstantString::create(std::to_string(collectedAnimalCountMax - collectedAnimalCount)), Strings::Platformer_MapNames_CastleValgrind_CastleValgrind::create() }),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->setPostText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});

		return;
	}
	
	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_Museum_Generic_B_TakeThis::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->entity, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ MarineBand::create() }));
				SaveManager::SaveProfileData(SaveKeys::SaveKeyItemDGiven, Value(true));
				this->setPostText();
			},
			Voices::GetNextVoiceMedium(),
			true
		));
	});
}

void MuseumGiftBehavior::setPostTextLC()
{
	if (SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemEGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_Museum_Generic_C_Thanks::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->setPostText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});

		return;
	}

	int collectedAnimalCount =
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalLion, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBull, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalWorm, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalChicken, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalMountainLion, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBat, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalWolf, Value(false)).asBool();
	const int collectedAnimalCountMax = 7;
	
	if (collectedAnimalCount < collectedAnimalCountMax)
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_Museum_Generic_A_Missing::create()
					->setStringReplacementVariables({ ConstantString::create(std::to_string(collectedAnimalCountMax - collectedAnimalCount)), Strings::Platformer_MapNames_LambdaCrypts_LambdaCrypts::create() }),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->setPostText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});

		return;
	}
	
	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_Museum_Generic_B_TakeThis::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->entity, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ SkullBand::create() }));
				SaveManager::SaveProfileData(SaveKeys::SaveKeyItemEGiven, Value(true));
				this->setPostText();
			},
			Voices::GetNextVoiceMedium(),
			true
		));
	});
}

void MuseumGiftBehavior::setPostTextFF()
{
	if (SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemFGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_Museum_Generic_C_Thanks::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->setPostText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});

		return;
	}

	int collectedAnimalCount =
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalTucan, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalLizard, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBee, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalLadybug, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalDinosaur, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalSnake, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCrocodile, Value(false)).asBool();
	const int collectedAnimalCountMax = 7;
	
	if (collectedAnimalCount < collectedAnimalCountMax)
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_Museum_Generic_A_Missing::create()
					->setStringReplacementVariables({ ConstantString::create(std::to_string(collectedAnimalCountMax - collectedAnimalCount)), Strings::Platformer_MapNames_FirewallFissure_FirewallFissure::create() }),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->setPostText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});

		return;
	}
	
	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_Museum_Generic_B_TakeThis::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->entity, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ HeartBand::create() }));
				SaveManager::SaveProfileData(SaveKeys::SaveKeyItemFGiven, Value(true));
				this->setPostText();
			},
			Voices::GetNextVoiceMedium(),
			true
		));
	});
}

void MuseumGiftBehavior::setPostTextBP()
{
	if (SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyItemGGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_Museum_Generic_C_Thanks::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->setPostText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});

		return;
	}

	int collectedAnimalCount =
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBlowfish, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalKillerWhale, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBunny, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalPenguin, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalReindeer, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalYeti, Value(false)).asBool() +
		(int)SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalGoat, Value(false)).asBool();
	const int collectedAnimalCountMax = 7;
	
	if (collectedAnimalCount < collectedAnimalCountMax)
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::Platformer_Quests_Museum_Generic_A_Missing::create()
					->setStringReplacementVariables({ ConstantString::create(std::to_string(collectedAnimalCountMax - collectedAnimalCount)), Strings::Platformer_MapNames_BallmerPeaks_BallmerPeaks::create() }),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->setPostText();
				},
				Voices::GetNextVoiceMedium(),
				true
			));
		});

		return;
	}
	
	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_Museum_Generic_B_TakeThis::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->entity, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ SoulBand::create() }));
				SaveManager::SaveProfileData(SaveKeys::SaveKeyItemGGiven, Value(true));
				this->setPostText();
			},
			Voices::GetNextVoiceMedium(),
			true
		));
	});
}

