#include "Irmik.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/BalmerPeaks/Irmik.h"

using namespace cocos2d;

const std::string Irmik::MapKeyIrmik = "irmik";
HexusOpponentData* Irmik::HexusOpponentDataInstance = nullptr;
const std::string Irmik::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_IRMIK";

Irmik* Irmik::deserialize(ValueMap& properties)
{
	Irmik* instance = new Irmik(properties);

	instance->autorelease();

	return instance;
}

Irmik::Irmik(ValueMap& properties) : super(properties,
	Irmik::MapKeyIrmik,
	EntityResources::Npcs_BalmerPeaks_Irmik_Animations,
	EntityResources::Npcs_BalmerPeaks_Irmik_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Irmik::getHexusOpponentData();
}

Irmik::~Irmik()
{
}

Vec2 Irmik::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Irmik::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BalmerPeaks_Irmik::create();
}

HexusOpponentData* Irmik::getHexusOpponentData()
{
	if (Irmik::HexusOpponentDataInstance == nullptr)
	{
		Irmik::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			Vec2(-32.0f, -112.0f),
			Irmik::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			HexusOpponentData::generateDeck(32, 0.554f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
			}),
			nullptr,
			nullptr
		);
	}

	return Irmik::HexusOpponentDataInstance;
}