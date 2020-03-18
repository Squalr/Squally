#include "PrincessDawn.h"

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

const std::string PrincessDawn::MapKeyPrincessDawn = "princess-dawn";
HexusOpponentData* PrincessDawn::HexusOpponentDataInstance = nullptr;
const std::string PrincessDawn::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PRINCESS_DAWN";

PrincessDawn* PrincessDawn::deserialize(ValueMap& properties)
{
	PrincessDawn* instance = new PrincessDawn(properties);

	instance->autorelease();

	return instance;
}

PrincessDawn::PrincessDawn(ValueMap& properties) : super(properties,
	PrincessDawn::MapKeyPrincessDawn,
	EntityResources::Npcs_SeaSharpCaverns_PrincessDawn_Animations,
	EntityResources::Npcs_SeaSharpCaverns_PrincessDawn_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = PrincessDawn::getHexusOpponentData();
}

PrincessDawn::~PrincessDawn()
{
}

Vec2 PrincessDawn::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* PrincessDawn::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_PrincessDawn::create();
}

HexusOpponentData* PrincessDawn::getHexusOpponentData()
{
	if (PrincessDawn::HexusOpponentDataInstance == nullptr)
	{
		PrincessDawn::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(-32.0f, -112.0f),
			PrincessDawn::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.348f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
			}),
			nullptr,
			nullptr
		);
	}

	return PrincessDawn::HexusOpponentDataInstance;
}