#include "MuseumGiftBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
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
const std::string MuseumGiftBehavior::SaveKeyItemAGiven = "MUSEUM_A_ITEM_GIVEN";
const std::string MuseumGiftBehavior::SaveKeyItemBGiven = "MUSEUM_B_ITEM_GIVEN";
const std::string MuseumGiftBehavior::SaveKeyItemCGiven = "MUSEUM_C_ITEM_GIVEN";
const std::string MuseumGiftBehavior::SaveKeyItemDGiven = "MUSEUM_D_ITEM_GIVEN";
const std::string MuseumGiftBehavior::SaveKeyItemEGiven = "MUSEUM_E_ITEM_GIVEN";
const std::string MuseumGiftBehavior::SaveKeyItemFGiven = "MUSEUM_F_ITEM_GIVEN";
const std::string MuseumGiftBehavior::SaveKeyItemGGiven = "MUSEUM_G_ITEM_GIVEN";
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

	// int collectedAnimalCount = Collectables::getCollectedAnimalCount();
	// int collectedAnimalTotal = Collectables::getCollectedAnimalTotal();

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
		else if (this->museumZone == "vs")
		{
			this->setPostTextVS();
		}
	});
}

void MuseumGiftBehavior::setPostTextEF()
{
	if (this->entity->loadObjectStateOrDefault(MuseumGiftBehavior::SaveKeyItemAGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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

	bool hasNecessaryAnimals =
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCat, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalWhale, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalDog, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalFox, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBear, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCow, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalMonkey, Value(false)).asBool();
	
	if (hasNecessaryAnimals)
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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
			Strings::TODO::create(),
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
}

void MuseumGiftBehavior::setPostTextUR()
{
	if (this->entity->loadObjectStateOrDefault(MuseumGiftBehavior::SaveKeyItemBGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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

	bool hasNecessaryAnimals =
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCat, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalWhale, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalDog, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalFox, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBear, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCow, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalMonkey, Value(false)).asBool();
	
	if (hasNecessaryAnimals)
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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
			Strings::TODO::create(),
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
}

void MuseumGiftBehavior::setPostTextDM()
{
	if (this->entity->loadObjectStateOrDefault(MuseumGiftBehavior::SaveKeyItemCGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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

	bool hasNecessaryAnimals =
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCat, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalWhale, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalDog, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalFox, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBear, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCow, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalMonkey, Value(false)).asBool();
	
	if (hasNecessaryAnimals)
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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
			Strings::TODO::create(),
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
}

void MuseumGiftBehavior::setPostTextCV()
{
	if (this->entity->loadObjectStateOrDefault(MuseumGiftBehavior::SaveKeyItemDGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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

	bool hasNecessaryAnimals =
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCat, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalWhale, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalDog, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalFox, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBear, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCow, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalMonkey, Value(false)).asBool();
	
	if (hasNecessaryAnimals)
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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
			Strings::TODO::create(),
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
}

void MuseumGiftBehavior::setPostTextLC()
{
	if (this->entity->loadObjectStateOrDefault(MuseumGiftBehavior::SaveKeyItemDGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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

	bool hasNecessaryAnimals =
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCat, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalWhale, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalDog, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalFox, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBear, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCow, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalMonkey, Value(false)).asBool();
	
	if (hasNecessaryAnimals)
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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
			Strings::TODO::create(),
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
}

void MuseumGiftBehavior::setPostTextFF()
{
	if (this->entity->loadObjectStateOrDefault(MuseumGiftBehavior::SaveKeyItemEGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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

	bool hasNecessaryAnimals =
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCat, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalWhale, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalDog, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalFox, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBear, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCow, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalMonkey, Value(false)).asBool();
	
	if (hasNecessaryAnimals)
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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
			Strings::TODO::create(),
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
}

void MuseumGiftBehavior::setPostTextBP()
{
	if (this->entity->loadObjectStateOrDefault(MuseumGiftBehavior::SaveKeyItemFGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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

	bool hasNecessaryAnimals =
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCat, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalWhale, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalDog, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalFox, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBear, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCow, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalMonkey, Value(false)).asBool();
	
	if (hasNecessaryAnimals)
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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
			Strings::TODO::create(),
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
}

void MuseumGiftBehavior::setPostTextVS()
{
	if (this->entity->loadObjectStateOrDefault(MuseumGiftBehavior::SaveKeyItemGGiven, Value(false)).asBool())
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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

	bool hasNecessaryAnimals =
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCat, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalWhale, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalDog, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalFox, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalBear, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalCow, Value(false)).asBool() &&
		SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCollectableAnimalMonkey, Value(false)).asBool();
	
	if (hasNecessaryAnimals)
	{
		this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
				Strings::TODO::create(),
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
			Strings::TODO::create(),
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
}
