#include "GlassDisplayOr.h"

#include "cocos/2d/CCSprite.h"

#include "Events/DialogueEvents.h"
#include "Events/HexusEvents.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GlassDisplayOr::MapKey = "glass-display-or";

GlassDisplayOr* GlassDisplayOr::create(cocos2d::ValueMap& properties)
{
	GlassDisplayOr* instance = new GlassDisplayOr(properties);

	instance->autorelease();

	return instance;
}

GlassDisplayOr::GlassDisplayOr(cocos2d::ValueMap& properties) : super(properties, Size(169.0f, 331.0f))
{
	Sprite* glow = Sprite::create(UIResources::HUD_EmblemGlow);
	Sprite* specialCard = Sprite::create(ItemResources::Collectables_Cards_CardSpecial);

	this->displayContentNode->addChild(glow);
	this->displayContentNode->addChild(specialCard);
}

GlassDisplayOr::~GlassDisplayOr()
{
}
		
bool GlassDisplayOr::tryOpen()
{
	if (!this->isDisplayOpened)
	{
		DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
			DialogueEvents::BuildOptions(Strings::Platformer_Objects_GlassCase_GlassCaseLocked::create(),
				{
					Strings::Platformer_Objects_GlassCase_InspectItem::create()
				}),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(nullptr, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
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
					"",
					true,
					true
				));
			},
			"",
			true,
			false,
			{
				[=]()
				{
					HexusEvents::TriggerShowHelpMenuOutsideOfGame(HexusEvents::HelpMenuArgs(CardList::getInstance()->cardListByName[CardKeys::LogicalOr]));
					return true;
				}
			},
			[=](){ return true; }
		));
		return false;
	}

	this->unlockAndGiveItems();

	return true;
}
