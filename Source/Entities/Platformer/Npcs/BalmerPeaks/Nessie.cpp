#include "Nessie.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/BalmerPeaks/Nessie.h"

using namespace cocos2d;

const std::string Nessie::MapKeyNessie = "nessie";
HexusOpponentData* Nessie::HexusOpponentDataInstance = nullptr;
const std::string Nessie::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_NESSIE";

Nessie* Nessie::deserialize(ValueMap& properties)
{
	Nessie* instance = new Nessie(properties);

	instance->autorelease();

	return instance;
}

Nessie::Nessie(ValueMap& properties) : super(properties,
	Nessie::MapKeyNessie,
	EntityResources::Npcs_BalmerPeaks_Nessie_Animations,
	EntityResources::Npcs_BalmerPeaks_Nessie_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Nessie::getHexusOpponentData();
}

Nessie::~Nessie()
{
}

Vec2 Nessie::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Nessie::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BalmerPeaks_Nessie::create();
}

HexusOpponentData* Nessie::getHexusOpponentData()
{
	if (Nessie::HexusOpponentDataInstance == nullptr)
	{
		Nessie::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_BalmerPeaks_Nessie_Animations,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Nessie::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			0.589f,
			HexusOpponentData::generateDeck(32, 0.589f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
			}),
			nullptr,
			nullptr
		);
	}

	return Nessie::HexusOpponentDataInstance;
}