#include "ItemPreview.h"

#include <iomanip>
#include <sstream>

#include "cocos/2d/CCSprite.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/HackUtils.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/CardPreview.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Offhands/Offhand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const int ItemPreview::MaxStatlines = 16;

ItemPreview* ItemPreview::create(bool showItemName, bool allowCardPreview)
{
	ItemPreview* itemPreview = new ItemPreview(showItemName, allowCardPreview);

	itemPreview->autorelease();

	return itemPreview;
}

ItemPreview::ItemPreview(bool showItemName, bool allowCardPreview)
{
	this->previewNode = Node::create();
	this->nextStatline = 0;
	this->allowCardPreview = allowCardPreview;

	LocalizedString* dashStr = Strings::Common_Dash::create();
	LocalizedString* bracketStr = Strings::Common_Brackets::create();
	LocalizedString* spacebarStr = Strings::Menus_ItemPreview_Spacebar::create();
	LocalizedString* equipStr = Strings::Menus_ItemPreview_Equip::create();

	bracketStr->setStringReplacementVariables(spacebarStr);
	dashStr->setStringReplacementVariables({ bracketStr, equipStr });

	this->equipHint = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, dashStr);

	LocalizedString* dashStr2 = Strings::Common_Dash::create();
	LocalizedString* bracketStr2 = Strings::Common_Brackets::create();
	LocalizedString* spacebarStr2 = Strings::Menus_ItemPreview_Spacebar::create();
	LocalizedString* unequipStr = Strings::Menus_ItemPreview_Unequip::create();

	bracketStr2->setStringReplacementVariables(spacebarStr2);
	dashStr2->setStringReplacementVariables({ bracketStr2, unequipStr });

	this->unequipHint = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, dashStr2);
	
	this->itemName = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_Constant::create());
	this->cardString = ConstantString::create("--");
	this->cardLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, this->cardString);
	this->cardPreview = CardPreview::create();
	
	this->itemName->enableOutline(Color4B::BLACK, 2);
	this->itemName->setVisible(showItemName);
	this->cardPreview->setVisible(false);
	this->cardLabel->setVisible(false);
	this->cardLabel->enableOutline(Color4B::BLACK, 3);

	this->equipHint->enableOutline(Color4B::BLACK, 2);
	this->equipHint->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->unequipHint->enableOutline(Color4B::BLACK, 2);
	this->unequipHint->setAnchorPoint(Vec2(0.0f, 0.5f));

	for (int index = 0; index < ItemPreview::MaxStatlines; index++)
	{
		this->statlines.push_back(this->createStatline());
	}

	for (auto statline : this->statlines)
	{
		statline->setAnchorPoint(Vec2(0.0f, 0.5f));
		statline->enableOutline(Color4B::BLACK, 2);
	}

	this->addChild(this->previewNode);
	this->addChild(this->equipHint);
	this->addChild(this->unequipHint);
	this->addChild(this->itemName);

	for (auto statline : this->statlines)
	{
		this->addChild(statline);
	}
	
	this->addChild(cardLabel);
	this->addChild(cardPreview);

	this->preview(EquipHintMode::None, nullptr);
}

ItemPreview::~ItemPreview()
{
}

void ItemPreview::onEnter()
{
	super::onEnter();
}

void ItemPreview::initializePositions()
{
	super::initializePositions();

	this->equipHint->setPosition(Vec2(-172.0f, 160.0f));
	this->unequipHint->setPosition(Vec2(-172.0f, 160.0f));

	this->cardPreview->setPosition(Vec2(0.0f, -72.0f));
	this->itemName->setPosition(Vec2(0.0f, -72.0f));
	
	const float OffsetX = -112.0f;
	const float OffsetY = -160.0f;
	int index = 0;

	for (auto statline : this->statlines)
	{
		statline->setPosition(Vec2(OffsetX, OffsetY - 40.0f * float(index++)));
	}
	
	this->cardLabel->setPosition(Vec2(-6.0f, -72.0f));
}

void ItemPreview::toggleShowItemName(bool showItemName)
{
	this->itemName->setVisible(showItemName);
}

void ItemPreview::preview(EquipHintMode equipHintMode, Item* item)
{
	this->clearPreview();

	if (item == nullptr)
	{
		this->setVisible(false);
		return;
	}

	this->setVisible(true);

	if (dynamic_cast<Recipe*>(item) != nullptr)
	{
		this->previewNode->addChild(Sprite::create(dynamic_cast<Recipe*>(item)->getCraftedItemIconResource()));
	}
	else
	{
		this->previewNode->addChild(Sprite::create(item->getIconResource()));
	}

	this->equipHint->setVisible(false);
	this->unequipHint->setVisible(false);

	switch(equipHintMode)
	{
		case EquipHintMode::Equip:
		{
			this->equipHint->setVisible(dynamic_cast<Equipable*>(item) != nullptr || dynamic_cast<HexusCard*>(item) != nullptr);
			break;
		}
		case EquipHintMode::Unequip:
		{
			this->unequipHint->setVisible(dynamic_cast<Equipable*>(item) != nullptr || dynamic_cast<HexusCard*>(item) != nullptr);
			break;
		}
		default:
		case EquipHintMode::None:
		{
			break;
		}
	}

	this->itemName->setStringReplacementVariables(item->getString());

	if (dynamic_cast<Recipe*>(item) != nullptr)
	{
		item = dynamic_cast<Recipe*>(item)->getCraftedItemRef();
	}

	if (dynamic_cast<Weapon*>(item) != nullptr)
	{
		this->setWeaponStatline(dynamic_cast<Weapon*>(item));
	}
	else if (dynamic_cast<HexusCard*>(item) != nullptr)
	{
		this->setHexusInfo(dynamic_cast<HexusCard*>(item));
	}
	else if (dynamic_cast<Equipable*>(item) != nullptr)
	{
		this->setGenericStatline(dynamic_cast<Equipable*>(item));
	}
}

void ItemPreview::setGenericStatline(Equipable* equipable)
{
	Equipable::ItemStats itemStats = equipable->getItemStats();

	this->bindStatlineToNonZeroInt([](){ return Strings::Menus_ItemPreview_Armor::create(); }, itemStats.armorBonus);
	this->bindStatlineToNonZeroInt([](){ return Strings::Menus_ItemPreview_Attack::create(); }, itemStats.attackBonus);
	this->bindStatlineToNonZeroInt([](){ return Strings::Menus_ItemPreview_Health::create(); }, itemStats.healthBonus);
	this->bindStatlineToNonZeroInt([](){ return Strings::Menus_ItemPreview_Mana::create(); }, itemStats.manaBonus);
	this->bindStatlineToNonZeroFloat([](){ return Strings::Menus_ItemPreview_Speed::create(); }, itemStats.speedBonus);
}

void ItemPreview::setWeaponStatline(Weapon* weapon)
{
	Equipable::ItemStats itemStats = weapon->getItemStats();

	this->bindStatlineToIntRange([](){ return Strings::Menus_ItemPreview_Damage::create(); }, weapon->getMinAttack(), weapon->getMaxAttack());
	this->bindStatlineToNonZeroInt([](){ return Strings::Menus_ItemPreview_Armor::create(); }, itemStats.armorBonus);
	this->bindStatlineToNonZeroInt([](){ return Strings::Menus_ItemPreview_Attack::create(); }, itemStats.attackBonus);
	this->bindStatlineToNonZeroInt([](){ return Strings::Menus_ItemPreview_Health::create(); }, itemStats.healthBonus);
	this->bindStatlineToNonZeroInt([](){ return Strings::Menus_ItemPreview_Mana::create(); }, itemStats.manaBonus);
	this->bindStatlineToNonZeroFloat([](){ return Strings::Menus_ItemPreview_Speed::create(); }, itemStats.speedBonus);
}

void ItemPreview::setHexusInfo(HexusCard* hexusCard)
{
	CardData* cardData = CardList::getInstance()->cardListByName[hexusCard->getCardKey()];

	switch (cardData->getCardType())
	{
		case CardData::CardType::Binary:
		{
			this->cardString->setString(HackUtils::toBinary4(cardData->getAttack()));
			this->cardLabel->setTextColor(Card::BinaryColor);
			break;
		}
		case CardData::CardType::Decimal:
		{
			this->cardString->setString(std::to_string(cardData->getAttack()));
			this->cardLabel->setTextColor(Card::DecimalColor);
			break;
		}
		case CardData::CardType::Hexidecimal:
		{
			this->cardString->setString(HackUtils::toHex(cardData->getAttack()));
			this->cardLabel->setTextColor(Card::HexColor);
			break;
		}
		default:
		{
			this->cardString->setString(cardData->getCardTypeString()->getString());
			this->cardLabel->setTextColor(Card::SpecialColor);
			break;
		}
	}

	if (this->allowCardPreview)
	{
		this->cardPreview->previewCardData(CardList::getInstance()->cardListByName[hexusCard->getCardKey()]);
		this->cardPreview->setVisible(true);
	}
	
	this->cardLabel->setVisible(true);
}

LocalizedLabel* ItemPreview::createStatline()
{
	return LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_Constant::create());
}

void ItemPreview::bindStatlineToIntRange(std::function<LocalizedString*()> prefixFunc, int min, int max)
{
	if (this->nextStatline >= int(this->statlines.size()))
	{
		return;
	}

	LocalizedLabel* statline = this->statlines[this->nextStatline++];
	LocalizedString* prefix = prefixFunc == nullptr ? Strings::Common_Constant::create() : prefixFunc();

	prefix->setStringReplacementVariables({ ConstantString::create(std::to_string(min)), ConstantString::create(std::to_string(max)) });
	
	statline->setVisible(true);
	statline->setStringReplacementVariables(prefix);
}

void ItemPreview::bindStatlineToNonZeroInt(std::function<LocalizedString*()> prefixFunc, int value)
{
	if (this->nextStatline >= int(this->statlines.size()) || value == 0)
	{
		return;
	}

	LocalizedLabel* statline = this->statlines[this->nextStatline++];
	LocalizedString* prefix = prefixFunc == nullptr ? Strings::Common_Constant::create() : prefixFunc();

	prefix->setStringReplacementVariables(ConstantString::create(std::to_string(value)));
	
	statline->setVisible(true);
	statline->setStringReplacementVariables(prefix);
}

void ItemPreview::bindStatlineToNonZeroFloat(std::function<LocalizedString*()> prefixFunc, float value)
{
	if (this->nextStatline >= int(this->statlines.size()) || value == 0.0f)
	{
		return;
	}

	LocalizedLabel* statline = this->statlines[this->nextStatline++];

	statline->setVisible(true);

	std::stringstream stream = std::stringstream();
	LocalizedString* prefix = prefixFunc == nullptr ? Strings::Common_Constant::create() : prefixFunc();

	stream << std::fixed << std::setprecision(2) << value;
	std::string valueString = stream.str();

	prefix->setStringReplacementVariables(ConstantString::create(valueString));

	statline->setStringReplacementVariables(prefix);
}

void ItemPreview::clearPreview()
{
	this->nextStatline = 0;
	this->previewNode->removeAllChildren();
	this->cardLabel->setVisible(false);
	this->cardPreview->setVisible(false);

	for (auto statline : this->statlines)
	{
		statline->setVisible(false);
	}

	if (this->equipHint != nullptr)
	{
		this->equipHint->setVisible(false);
	}
}

CardPreview* ItemPreview::getCardPreview()
{
	return this->cardPreview;
}
