#include "Aspen.h"

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

const std::string Aspen::MapKeyAspen = "aspen";
HexusOpponentData* Aspen::HexusOpponentDataInstance = nullptr;
const std::string Aspen::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ASPEN";

Aspen* Aspen::deserialize(ValueMap& properties)
{
	Aspen* instance = new Aspen(properties);

	instance->autorelease();

	return instance;
}

Aspen::Aspen(ValueMap& properties) : super(properties,
	Aspen::MapKeyAspen,
	EntityResources::Npcs_BalmerPeaks_Aspen_Animations,
	EntityResources::Npcs_BalmerPeaks_Aspen_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Aspen::getHexusOpponentData();
}

Aspen::~Aspen()
{
}

Vec2 Aspen::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Aspen::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BalmerPeaks_Aspen::create();
}

HexusOpponentData* Aspen::getHexusOpponentData()
{
	if (Aspen::HexusOpponentDataInstance == nullptr)
	{
		Aspen::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			Vec2(-32.0f, -112.0f),
			Aspen::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			HexusOpponentData::generateDeck(32, 0.509f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
			}),
			nullptr,
			nullptr
		);
	}

	return Aspen::HexusOpponentDataInstance;
}