#include "Poseidon.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/UnderflowRuins/Poseidon.h"

using namespace cocos2d;

const std::string Poseidon::MapKeyPoseidon = "poseidon";
HexusOpponentData* Poseidon::HexusOpponentDataInstance = nullptr;
const std::string Poseidon::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_POSEIDON";

Poseidon* Poseidon::deserialize(ValueMap& properties)
{
	Poseidon* instance = new Poseidon(properties);

	instance->autorelease();

	return instance;
}

Poseidon::Poseidon(ValueMap& properties) : super(properties,
	Poseidon::MapKeyPoseidon,
	nullptr,
	EntityResources::Npcs_UnderflowRuins_Poseidon_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Poseidon::getHexusOpponentData();
}

Poseidon::~Poseidon()
{
}

Vec2 Poseidon::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Poseidon::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Poseidon::create();
}

HexusOpponentData* Poseidon::getHexusOpponentData()
{
	if (Poseidon::HexusOpponentDataInstance == nullptr)
	{
		Poseidon::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-32.0f, -112.0f),
			Poseidon::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			HexusOpponentData::generateDeck(32, 0.223f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
			}),
			nullptr,
			nullptr
		);
	}

	return Poseidon::HexusOpponentDataInstance;
}