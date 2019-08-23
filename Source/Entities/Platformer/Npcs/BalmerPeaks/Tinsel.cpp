#include "Tinsel.h"

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

const std::string Tinsel::MapKeyTinsel = "tinsel";
HexusOpponentData* Tinsel::HexusOpponentDataInstance = nullptr;
const std::string Tinsel::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TINSEL";

Tinsel* Tinsel::deserialize(ValueMap& properties)
{
	Tinsel* instance = new Tinsel(properties);

	instance->autorelease();

	return instance;
}

Tinsel::Tinsel(ValueMap& properties) : super(properties,
	Tinsel::MapKeyTinsel,
	EntityResources::Npcs_BalmerPeaks_Tinsel_Animations,
	EntityResources::Npcs_BalmerPeaks_Tinsel_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Tinsel::getHexusOpponentData();
}

Tinsel::~Tinsel()
{
}

Vec2 Tinsel::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* Tinsel::getEntityName()
{
	return nullptr;
}

HexusOpponentData* Tinsel::getHexusOpponentData()
{
	if (Tinsel::HexusOpponentDataInstance == nullptr)
	{
		Tinsel::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_BalmerPeaks_Tinsel_Animations,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Tinsel::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			0.616f,
			HexusOpponentData::generateDeck(32, 0.616f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),

			}),
			nullptr
		);
	}

	return Tinsel::HexusOpponentDataInstance;
}