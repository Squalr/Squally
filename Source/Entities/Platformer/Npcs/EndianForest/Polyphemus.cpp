#include "Polyphemus.h"

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

const std::string Polyphemus::MapKeyPolyphemus = "polyphemus";
HexusOpponentData* Polyphemus::HexusOpponentDataInstance = nullptr;
const std::string Polyphemus::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_POLYPHEMUS";

Polyphemus* Polyphemus::deserialize(ValueMap& properties)
{
	Polyphemus* instance = new Polyphemus(properties);

	instance->autorelease();

	return instance;
}

Polyphemus::Polyphemus(ValueMap& properties) : super(properties,
	Polyphemus::MapKeyPolyphemus,
	EntityResources::Npcs_EndianForest_Polyphemus_Animations,
	EntityResources::Npcs_EndianForest_Polyphemus_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Polyphemus::getHexusOpponentData();
}

Polyphemus::~Polyphemus()
{
}

Vec2 Polyphemus::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Polyphemus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Polyphemus::create();
}

HexusOpponentData* Polyphemus::getHexusOpponentData()
{
	if (Polyphemus::HexusOpponentDataInstance == nullptr)
	{
		Polyphemus::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameEndianForest,
			Vec2(-32.0f, -112.0f),
			Polyphemus::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.054f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip1),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			}),
			nullptr,
			nullptr
		);
	}

	return Polyphemus::HexusOpponentDataInstance;
}