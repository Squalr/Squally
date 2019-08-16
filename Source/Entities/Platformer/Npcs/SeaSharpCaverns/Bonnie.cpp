#include "Bonnie.h"

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

using namespace cocos2d;

const std::string Bonnie::MapKeyBonnie = "bonnie";
HexusOpponentData* Bonnie::HexusOpponentDataInstance = nullptr;
const std::string Bonnie::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BONNIE";

Bonnie* Bonnie::deserialize(ValueMap& properties)
{
	Bonnie* instance = new Bonnie(properties);

	instance->autorelease();

	return instance;
}

Bonnie::Bonnie(ValueMap& properties) : super(properties,
	Bonnie::MapKeyBonnie,
	EntityResources::Npcs_SeaSharpCaverns_Bonnie_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Bonnie_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Bonnie::getHexusOpponentData();
}

Bonnie::~Bonnie()
{
}

Vec2 Bonnie::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Bonnie::getHexusOpponentData()
{
	if (Bonnie::HexusOpponentDataInstance == nullptr)
	{
		Bonnie::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_SeaSharpCaverns_Bonnie_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Bonnie::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.312f,
			HexusOpponentData::generateDeck(32, 0.312f,
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
			nullptr
		);
	}

	return Bonnie::HexusOpponentDataInstance;
}