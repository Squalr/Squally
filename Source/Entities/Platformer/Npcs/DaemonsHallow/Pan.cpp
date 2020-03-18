#include "Pan.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Pan::MapKeyPan = "pan";
HexusOpponentData* Pan::HexusOpponentDataInstance = nullptr;
const std::string Pan::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PAN";

Pan* Pan::deserialize(ValueMap& properties)
{
	Pan* instance = new Pan(properties);

	instance->autorelease();

	return instance;
}

Pan::Pan(ValueMap& properties) : super(properties,
	Pan::MapKeyPan,
	EntityResources::Npcs_DaemonsHallow_Pan_Animations,
	EntityResources::Npcs_DaemonsHallow_Pan_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Pan::getHexusOpponentData();
}

Pan::~Pan()
{
}

Vec2 Pan::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Pan::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Pan::create();
}

HexusOpponentData* Pan::getHexusOpponentData()
{
	if (Pan::HexusOpponentDataInstance == nullptr)
	{
		Pan::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			Pan::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.723f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
			}),
			nullptr,
			nullptr
		);
	}

	return Pan::HexusOpponentDataInstance;
}