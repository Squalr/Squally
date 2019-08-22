#include "Mildred.h"

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

const std::string Mildred::MapKeyMildred = "mildred";
HexusOpponentData* Mildred::HexusOpponentDataInstance = nullptr;
const std::string Mildred::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MILDRED";

Mildred* Mildred::deserialize(ValueMap& properties)
{
	Mildred* instance = new Mildred(properties);

	instance->autorelease();

	return instance;
}

Mildred::Mildred(ValueMap& properties) : super(properties,
	Mildred::MapKeyMildred,
	EntityResources::Npcs_SeaSharpCaverns_Mildred_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Mildred_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Mildred::getHexusOpponentData();
}

Mildred::~Mildred()
{
}

Vec2 Mildred::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Mildred::getHexusOpponentData()
{
	if (Mildred::HexusOpponentDataInstance == nullptr)
	{
		Mildred::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_SeaSharpCaverns_Mildred_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Mildred::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.330f,
			HexusOpponentData::generateDeck(32, 0.330f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),

			}),
			nullptr
		);
	}

	return Mildred::HexusOpponentDataInstance;
}