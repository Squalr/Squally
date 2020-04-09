#include "Bonnie.h"

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

const std::string Bonnie::MapKey = "bonnie";
HexusOpponentData* Bonnie::HexusOpponentDataInstance = nullptr;
const std::string Bonnie::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BONNIE";

Bonnie* Bonnie::deserialize(ValueMap& properties)
{
	Bonnie* instance = new Bonnie(properties);

	instance->autorelease();

	return instance;
}

Bonnie::Bonnie(ValueMap& properties) : super(properties,
	Bonnie::MapKey,
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

Vec2 Bonnie::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Bonnie::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_Bonnie::create();
}

HexusOpponentData* Bonnie::getHexusOpponentData()
{
	if (Bonnie::HexusOpponentDataInstance == nullptr)
	{
		Bonnie::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(-32.0f, -112.0f),
			Bonnie::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
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
			nullptr,
			nullptr
		);
	}

	return Bonnie::HexusOpponentDataInstance;
}