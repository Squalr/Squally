#include "ItemPreview.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ItemPreview* ItemPreview::create(bool allowEquipHint, bool showItemName)
{
	ItemPreview* itemPreview = new ItemPreview(allowEquipHint, showItemName);

	itemPreview->autorelease();

	return itemPreview;
}

ItemPreview::ItemPreview(bool allowEquipHint, bool showItemName)
{
	this->previewNode = Node::create();

	LocalizedString* dashStr = Strings::Common_Dash::create();
	LocalizedString* bracketStr = Strings::Common_Brackets::create();
	LocalizedString* spacebarStr = Strings::Menus_ItemPreview_Spacebar::create();
	LocalizedString* equipStr = Strings::Menus_ItemPreview_Equip::create();

	bracketStr->setStringReplacementVariables(spacebarStr);
	dashStr->setStringReplacementVariables({ bracketStr, equipStr });

	this->equipHint = allowEquipHint ? LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, dashStr) : nullptr;
	this->itemName = showItemName ? LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_Constant::create()) : nullptr;

	this->addChild(this->previewNode);

	if (this->equipHint != nullptr)
	{
		this->equipHint->enableOutline(Color4B::BLACK, 2);
		this->equipHint->setAnchorPoint(Vec2(0.0f, 0.5f));
		this->addChild(this->equipHint);
	}

	if (this->itemName != nullptr)
	{
		this->itemName->enableOutline(Color4B::BLACK, 2);
		this->addChild(this->itemName);
	}

	this->preview(nullptr);
}

ItemPreview::~ItemPreview()
{
}

void ItemPreview::onEnter()
{
	super::onEnter();

	if (this->equipHint != nullptr)
	{
		this->equipHint->setVisible(false);
	}

	if (this->itemName != nullptr)
	{
		this->itemName->setVisible(false);
	}
}

void ItemPreview::initializePositions()
{
	super::initializePositions();

	if (this->equipHint != nullptr)
	{
		this->equipHint->setPosition(Vec2(-172.0f, 160.0f));
	}

	if (this->itemName != nullptr)
	{
		this->itemName->setPosition(Vec2(0.0f, -72.0f));
	}
}

void ItemPreview::preview(Item* item)
{
	this->clearPreview();

	if (item != nullptr)
	{
		this->setVisible(true);

		this->previewNode->addChild(Sprite::create(item->getIconResource()));

		if (this->equipHint != nullptr && dynamic_cast<Equipable*>(item) != nullptr)
		{
			this->equipHint->setVisible(true);
		}

		if (this->itemName != nullptr)
		{
			this->itemName->setStringReplacementVariables(item->getString());
			this->itemName->setVisible(true);
		}
	}
	else
	{
		this->setVisible(false);
	}
}

void ItemPreview::clearPreview()
{
	this->previewNode->removeAllChildren();

	if (this->equipHint != nullptr)
	{
		this->equipHint->setVisible(false);
	}

	if (this->itemName != nullptr)
	{
		this->itemName->setVisible(false);
	}
}
