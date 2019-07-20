#include "ItemPreview.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"

#include "Strings/Common/Brackets.h"
#include "Strings/Common/Dash.h"
#include "Strings/Menus/ItemPreview/Equip.h"
#include "Strings/Menus/ItemPreview/Spacebar.h"

using namespace cocos2d;

ItemPreview* ItemPreview::create(bool allowEquipHint)
{
	ItemPreview* itemPreview = new ItemPreview(allowEquipHint);

	itemPreview->autorelease();

	return itemPreview;
}

ItemPreview::ItemPreview(bool allowEquipHint)
{
	this->allowEquipHint = allowEquipHint;
	this->previewNode = Node::create();

	LocalizedString* dashStr = Strings::Common_Dash::create();
	LocalizedString* bracketStr = Strings::Common_Brackets::create();
	LocalizedString* spacebarStr = Strings::Menus_ItemPreview_Spacebar::create();
	LocalizedString* equipStr = Strings::Menus_ItemPreview_Equip::create();

	bracketStr->setStringReplacementVariables(spacebarStr);
	dashStr->setStringReplacementVariables({ bracketStr, equipStr });

	this->equipHint = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, dashStr);

	this->equipHint->enableOutline(Color4B::BLACK, 2);
	this->equipHint->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->previewNode);
	this->addChild(this->equipHint);
}

ItemPreview::~ItemPreview()
{
}

void ItemPreview::onEnter()
{
	super::onEnter();

	this->equipHint->setVisible(false);
}

void ItemPreview::initializePositions()
{
	super::initializePositions();

	this->equipHint->setPosition(Vec2(-172.0f, 160.0f));
}

void ItemPreview::preview(Item* item)
{
	this->clearPreview();
	this->previewNode->addChild(Sprite::create(item->getIconResource()));

	if (this->allowEquipHint && dynamic_cast<Equipable*>(item) != nullptr)
	{
		this->equipHint->setVisible(true);
	}
}

void ItemPreview::clearPreview()
{
	this->previewNode->removeAllChildren();

	this->equipHint->setVisible(false);
}
