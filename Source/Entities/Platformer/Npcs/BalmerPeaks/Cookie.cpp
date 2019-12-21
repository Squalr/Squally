#include "Cookie.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Cookie::MapKeyCookie = "cookie";
HexusOpponentData* Cookie::HexusOpponentDataInstance = nullptr;
const std::string Cookie::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_COOKIE";

Cookie* Cookie::deserialize(ValueMap& properties)
{
	Cookie* instance = new Cookie(properties);

	instance->autorelease();

	return instance;
}

Cookie::Cookie(ValueMap& properties) : super(properties,
	Cookie::MapKeyCookie,
	EntityResources::Npcs_BalmerPeaks_Cookie_Animations,
	EntityResources::Npcs_BalmerPeaks_Cookie_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Cookie::getHexusOpponentData();
}

Cookie::~Cookie()
{
}

Vec2 Cookie::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Cookie::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BalmerPeaks_Cookie::create();
}

HexusOpponentData* Cookie::getHexusOpponentData()
{
	if (Cookie::HexusOpponentDataInstance == nullptr)
	{
		Cookie::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			Vec2(-32.0f, -112.0f),
			Cookie::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			HexusOpponentData::generateDeck(32, 0.545f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
			}),
			nullptr,
			nullptr
		);
	}

	return Cookie::HexusOpponentDataInstance;
}