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
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Offhands/Offhand.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Hats/Hat.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const int ItemPreview::MaxStatlines = 16;

ItemPreview* ItemPreview::create(bool allowEquipHint, bool showItemName)
{
	ItemPreview* itemPreview = new ItemPreview(allowEquipHint, showItemName);

	itemPreview->autorelease();

	return itemPreview;
}

ItemPreview::ItemPreview(bool allowEquipHint, bool showItemName)
{
	this->previewNode = Node::create();
	this->nextStatline = 0;

	LocalizedString* dashStr = Strings::Common_Dash::create();
	LocalizedString* bracketStr = Strings::Common_Brackets::create();
	LocalizedString* spacebarStr = Strings::Menus_ItemPreview_Spacebar::create();
	LocalizedString* equipStr = Strings::Menus_ItemPreview_Equip::create();

	bracketStr->setStringReplacementVariables(spacebarStr);
	dashStr->setStringReplacementVariables({ bracketStr, equipStr });

	this->equipHint = allowEquipHint ? LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, dashStr) : nullptr;
	this->itemName = showItemName ? LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_Constant::create()) : nullptr;
	this->cardString = ConstantString::create("--");
	this->cardLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, this->cardString);
	
	this->cardLabel->setVisible(false);
	this->cardLabel->enableOutline(Color4B::BLACK, 3);

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

	for (auto statline : this->statlines)
	{
		this->addChild(statline);
	}
	
	this->addChild(cardLabel);

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
	
	const float OffsetX = -112.0f;
	const float OffsetY = -160.0f;
	int index = 0;

	for (auto statline : this->statlines)
	{
		statline->setPosition(Vec2(OffsetX, OffsetY - 40.0f * float(index++)));
	}
	
	this->cardLabel->setPosition(Vec2(-6.0f, -72.0f));
}

void ItemPreview::preview(Item* item)
{
	this->clearPreview();

	if (item == nullptr)
	{
		this->setVisible(false);
		return;
	}

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

	if (dynamic_cast<Recipe*>(item) != nullptr)
	{
		item = dynamic_cast<Recipe*>(item)->getCraftedItemRef();
	}

	if (dynamic_cast<Hat*>(item) != nullptr)
	{
		this->setHatStatline(dynamic_cast<Hat*>(item));
	}
	else if (dynamic_cast<Offhand*>(item) != nullptr)
	{
		this->setOffhandStatline(dynamic_cast<Offhand*>(item));
	}
	else if (dynamic_cast<Weapon*>(item) != nullptr)
	{
		this->setWeaponStatline(dynamic_cast<Weapon*>(item));
	}
	else if (dynamic_cast<HexusCard*>(item) != nullptr)
	{
		this->setHexusInfo(dynamic_cast<HexusCard*>(item));
	}
}

void ItemPreview::setHatStatline(Hat* hat)
{
	Equipable::ItemStats itemStats = hat->getItemStats();

	this->bindStatlineToNonZeroInt([](){ return Strings::Menus_ItemPreview_Armor::create(); }, itemStats.armorBonus);
	this->bindStatlineToNonZeroInt([](){ return Strings::Menus_ItemPreview_Attack::create(); }, itemStats.attackBonus);
	this->bindStatlineToNonZeroInt([](){ return Strings::Menus_ItemPreview_Health::create(); }, itemStats.healthBonus);
	this->bindStatlineToNonZeroInt([](){ return Strings::Menus_ItemPreview_Mana::create(); }, itemStats.manaBonus);
	this->bindStatlineToNonZeroFloat([](){ return Strings::Menus_ItemPreview_Speed::create(); }, itemStats.speedBonus);
}

void ItemPreview::setOffhandStatline(Offhand* offhand)
{
	Equipable::ItemStats itemStats = offhand->getItemStats();

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

	for (auto statline : this->statlines)
	{
		statline->setVisible(false);
	}

	if (this->equipHint != nullptr)
	{
		this->equipHint->setVisible(false);
	}

	if (this->itemName != nullptr)
	{
		this->itemName->setVisible(false);
	}
}
