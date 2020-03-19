#include "Leroy.h"

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

const std::string Leroy::MapKey = "leroy";
HexusOpponentData* Leroy::HexusOpponentDataInstance = nullptr;
const std::string Leroy::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LEROY";

Leroy* Leroy::deserialize(ValueMap& properties)
{
	Leroy* instance = new Leroy(properties);

	instance->autorelease();

	return instance;
}

Leroy::Leroy(ValueMap& properties) : super(properties,
	Leroy::MapKey,
	EntityResources::Npcs_CastleValgrind_Leroy_Animations,
	EntityResources::Npcs_CastleValgrind_Leroy_Emblem,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Leroy::getHexusOpponentData();
}

Leroy::~Leroy()
{
}

Vec2 Leroy::getDialogueOffset()
{
	return Vec2(-32.0f, -96.0f);
}

LocalizedString* Leroy::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Leroy::create();
}

HexusOpponentData* Leroy::getHexusOpponentData()
{
	if (Leroy::HexusOpponentDataInstance == nullptr)
	{
		Leroy::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameCastleValgrind,
			Vec2(-32.0f, -96.0f),
			Leroy::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			HexusOpponentData::generateDeck(32, 0.420f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
			}),
			nullptr,
			nullptr
		);
	}

	return Leroy::HexusOpponentDataInstance;
}