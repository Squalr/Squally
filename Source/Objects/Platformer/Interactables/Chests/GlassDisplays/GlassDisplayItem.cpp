#include "GlassDisplayItem.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/InventoryEvents.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/DialogueEvents.h"
#include "Events/HexusEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/ItemResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GlassDisplayItem::MapKey = "glass-display-item";
const std::string GlassDisplayItem::PropertyItemName = "item-name";
const std::string GlassDisplayItem::PropertyTutorial = "tutorial";
const std::string GlassDisplayItem::TutorialAndHint = "and-hint";
const std::string GlassDisplayItem::TutorialOrHint = "or-hint";
const std::string GlassDisplayItem::TutorialXorHint = "xor-hint";
const std::string GlassDisplayItem::PropertyDisplayGroup = "display-group";
const std::string GlassDisplayItem::MapEventDisableDisplayGroup = "disable-display-group";
const std::string GlassDisplayItem::SaveKeyIsDisabled = "SAVE_KEY_GLASS_DISPLAY_DISABLED";

GlassDisplayItem* GlassDisplayItem::create(cocos2d::ValueMap& properties)
{
	GlassDisplayItem* instance = new GlassDisplayItem(properties);

	instance->autorelease();

	return instance;
}

GlassDisplayItem::GlassDisplayItem(cocos2d::ValueMap& properties) : super(properties, Size(169.0f, 331.0f))
{
	this->itemName = GameUtils::getKeyOrDefault(this->properties, GlassDisplayItem::PropertyItemName, Value("")).asString();
	this->tutorialName = GameUtils::getKeyOrDefault(this->properties, GlassDisplayItem::PropertyTutorial, Value("")).asString();
	this->displayGroup = GameUtils::getKeyOrDefault(this->properties, GlassDisplayItem::PropertyDisplayGroup, Value("")).asString();
	this->item = nullptr;
}

GlassDisplayItem::~GlassDisplayItem()
{
}

void GlassDisplayItem::onEnter()
{
	super::onEnter();

	InventoryEvents::TriggerRequestItemDeserialization(InventoryEvents::RequestItemDeserializationArgs(this->itemName, [=](Item* item)
	{
		this->item = item;

		Sprite* icon = Sprite::create(this->item->getIconResource());

		this->addChild(this->item);
		this->displayContentNode->addChild(icon);
	}));
}

void GlassDisplayItem::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent(GlassDisplayItem::MapEventDisableDisplayGroup, [=](ValueMap args)
	{
		if (GameUtils::getKeyOrDefault(args, GlassDisplayItem::MapEventDisableDisplayGroup, Value("")).asString() == this->displayGroup)
		{
			this->saveObjectState(GlassDisplayItem::SaveKeyIsDisabled, Value(true));
		}
	});

	this->listenForMapEvent(this->listenEvent, [=](ValueMap args)
	{
		this->unlock();
	});
}
		
bool GlassDisplayItem::tryOpen()
{
	if (this->isDisplayOpened)
	{
		this->unlockAndGiveItems();

		return true;
	}

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		DialogueEvents::BuildOptions(this->canTakeGroupedItem()
				? (LocalizedString*)Strings::Platformer_Objects_GlassCase_GlassCaseGrouped::create()
				: (LocalizedString*)Strings::Platformer_Objects_GlassCase_GlassCaseLocked::create(),
			{
				Strings::Platformer_Objects_GlassCase_InspectItem::create(),
				Strings::Menus_Cancel::create(),
			}),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(nullptr, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
		},
		"",
		true,
		false,
		{
			[=]()
			{
				return this->inspectItem();
			},
			[=]()
			{
				return true;
			}
		},
		[=](){ return true; }
	));

	return false;
}

void GlassDisplayItem::unlockAndGiveItems()
{
	this->open(true);

	if (this->item == nullptr)
	{
		return;
	}

	PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ this->item->clone() }));
}

void GlassDisplayItem::tryRunTutorials()
{
	if (this->tutorialName == GlassDisplayItem::TutorialAndHint
		|| this->tutorialName == GlassDisplayItem::TutorialOrHint
		|| this->tutorialName == GlassDisplayItem::TutorialXorHint)
	{
		DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Objects_GlassCase_Clue::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
			true,
			true
		));
	}
}

bool GlassDisplayItem::inspectItem()
{
	if (this->item == nullptr)
	{
		return false;
	}

	if (dynamic_cast<HexusCard*>(this->item) != nullptr)
	{
		HexusCard* hexusCard = dynamic_cast<HexusCard*>(this->item);

		HexusEvents::TriggerShowHelpMenuOutsideOfGame(HexusEvents::HelpMenuArgs(
			CardList::getInstance()->cardListByName[hexusCard->getCardKey()],
			[=](){ this->tryRunTutorials(); }
		));
	}
	else
	{
		if (this->canTakeGroupedItem())
		{
			PlatformerEvents::TriggerOpenItemInfo(PlatformerEvents::ItemInfoArgs(
				this->item,
				[=](){ this->tryRunTutorials(); },
				[=](){ this->takeGroupedItem(); }
			));
		}
		else
		{
			PlatformerEvents::TriggerOpenItemInfo(PlatformerEvents::ItemInfoArgs(
				this->item,
				[=](){ this->tryRunTutorials(); }
			));
		}
	}

	return true;
}

void GlassDisplayItem::takeGroupedItem()
{
	this->unlockAndGiveItems();

	this->saveObjectState(GlassDisplayItem::SaveKeyIsDisabled, Value(true));

	ValueMap args = ValueMap();

	args[MapEventDisableDisplayGroup] = this->displayGroup;

	this->broadcastMapEvent(GlassDisplayItem::MapEventDisableDisplayGroup, args);
}

bool GlassDisplayItem::canTakeGroupedItem()
{
	// Glass display groups are special. The intent is that they allow the user to choose one item from the display group.
	// The disabled flag is saved on all glass cases in the group once one case is looted.
	if (!this->displayGroup.empty() && !this->loadObjectStateOrDefault(GlassDisplayItem::SaveKeyIsDisabled, Value(false)).asBool())
	{
		return true;
	}

	return false;
}
