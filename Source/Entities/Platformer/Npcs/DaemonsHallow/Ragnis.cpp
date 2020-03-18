#include "Ragnis.h"

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

const std::string Ragnis::MapKeyRagnis = "ragnis";
HexusOpponentData* Ragnis::HexusOpponentDataInstance = nullptr;
const std::string Ragnis::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_RAGNIS";

Ragnis* Ragnis::deserialize(ValueMap& properties)
{
	Ragnis* instance = new Ragnis(properties);

	instance->autorelease();

	return instance;
}

Ragnis::Ragnis(ValueMap& properties) : super(properties,
	Ragnis::MapKeyRagnis,
	EntityResources::Npcs_DaemonsHallow_Ragnis_Animations,
	EntityResources::Npcs_DaemonsHallow_Ragnis_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Ragnis::getHexusOpponentData();
}

Ragnis::~Ragnis()
{
}

Vec2 Ragnis::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Ragnis::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Ragnis::create();
}

HexusOpponentData* Ragnis::getHexusOpponentData()
{
	if (Ragnis::HexusOpponentDataInstance == nullptr)
	{
		Ragnis::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			Ragnis::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.741f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			}),
			nullptr,
			nullptr
		);
	}

	return Ragnis::HexusOpponentDataInstance;
}