#include "Fraya.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/SeaSharpCaverns/Fraya.h"

using namespace cocos2d;

const std::string Fraya::MapKeyFraya = "fraya";
HexusOpponentData* Fraya::HexusOpponentDataInstance = nullptr;
const std::string Fraya::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_FRAYA";

Fraya* Fraya::deserialize(ValueMap& properties)
{
	Fraya* instance = new Fraya(properties);

	instance->autorelease();

	return instance;
}

Fraya::Fraya(ValueMap& properties) : super(properties,
	Fraya::MapKeyFraya,
	nullptr,
	EntityResources::Npcs_SeaSharpCaverns_Fraya_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Fraya::getHexusOpponentData();
}

Fraya::~Fraya()
{
}

Vec2 Fraya::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Fraya::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_Fraya::create();
}

HexusOpponentData* Fraya::getHexusOpponentData()
{
	if (Fraya::HexusOpponentDataInstance == nullptr)
	{
		Fraya::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(-32.0f, -112.0f),
			Fraya::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.304f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
			}),
			nullptr,
			nullptr
		);
	}

	return Fraya::HexusOpponentDataInstance;
}