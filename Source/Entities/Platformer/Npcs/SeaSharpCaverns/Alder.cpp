#include "Alder.h"

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

const std::string Alder::MapKey = "alder";
HexusOpponentData* Alder::HexusOpponentDataInstance = nullptr;
const std::string Alder::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ALDER";

Alder* Alder::deserialize(ValueMap& properties)
{
	Alder* instance = new Alder(properties);

	instance->autorelease();

	return instance;
}

Alder::Alder(ValueMap& properties) : super(properties,
	Alder::MapKey,
	EntityResources::Npcs_SeaSharpCaverns_Alder_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Alder_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Alder::getHexusOpponentData();
}

Alder::~Alder()
{
}

Vec2 Alder::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Alder::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_Alder::create();
}

HexusOpponentData* Alder::getHexusOpponentData()
{
	if (Alder::HexusOpponentDataInstance == nullptr)
	{
		Alder::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(-32.0f, -112.0f),
			Alder::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.259f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			}),
			nullptr,
			nullptr
		);
	}

	return Alder::HexusOpponentDataInstance;
}