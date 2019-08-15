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

using namespace cocos2d;

const std::string Fraya::MapKeyFraya = "fraya";
HexusOpponentData* Fraya::HexusOpponentDataInstance = nullptr;
const std::string Fraya::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_FRAYA";

Fraya* Fraya::deserialize(ValueMap& initProperties)
{
	Fraya* instance = new Fraya(initProperties);

	instance->autorelease();

	return instance;
}

Fraya::Fraya(ValueMap& initProperties) : super(initProperties,
	Fraya::MapKeyFraya,
	EntityResources::Npcs_SeaSharpCaverns_Fraya_Animations,
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

Vec2 Fraya::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Fraya::getHexusOpponentData()
{
	if (Fraya::HexusOpponentDataInstance == nullptr)
	{
		Fraya::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_SeaSharpCaverns_Fraya_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Fraya::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.304f,
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
			nullptr
		);
	}

	return Fraya::HexusOpponentDataInstance;
}