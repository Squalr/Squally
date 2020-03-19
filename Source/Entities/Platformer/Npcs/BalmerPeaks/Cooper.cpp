#include "Cooper.h"

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

const std::string Cooper::MapKey = "cooper";
HexusOpponentData* Cooper::HexusOpponentDataInstance = nullptr;
const std::string Cooper::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_COOPER";

Cooper* Cooper::deserialize(ValueMap& properties)
{
	Cooper* instance = new Cooper(properties);

	instance->autorelease();

	return instance;
}

Cooper::Cooper(ValueMap& properties) : super(properties,
	Cooper::MapKey,
	EntityResources::Npcs_BalmerPeaks_Cooper_Animations,
	EntityResources::Npcs_BalmerPeaks_Cooper_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Cooper::getHexusOpponentData();
}

Cooper::~Cooper()
{
}

Vec2 Cooper::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Cooper::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BalmerPeaks_Cooper::create();
}

HexusOpponentData* Cooper::getHexusOpponentData()
{
	if (Cooper::HexusOpponentDataInstance == nullptr)
	{
		Cooper::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			Vec2(-32.0f, -112.0f),
			Cooper::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			HexusOpponentData::generateDeck(32, 0.527f,
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

	return Cooper::HexusOpponentDataInstance;
}