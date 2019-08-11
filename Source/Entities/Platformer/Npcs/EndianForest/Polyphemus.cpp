#include "Polyphemus.h"

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

const std::string Polyphemus::MapKeyPolyphemus = "polyphemus";
HexusOpponentData* Polyphemus::HexusOpponentDataInstance = nullptr;
const std::string Polyphemus::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_POLYPHEMUS";

Polyphemus* Polyphemus::deserialize(ValueMap& initProperties)
{
	Polyphemus* instance = new Polyphemus(initProperties);

	instance->autorelease();

	return instance;
}

Polyphemus::Polyphemus(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_EndianForest_Polyphemus_Animations,
	EntityResources::Npcs_EndianForest_Polyphemus_Emblem,
	Size(112.0f, 160.0f),
	1.1f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Polyphemus::getHexusOpponentData();
}

Polyphemus::~Polyphemus()
{
}

Vec2 Polyphemus::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Polyphemus::getHexusOpponentData()
{
	if (Polyphemus::HexusOpponentDataInstance == nullptr)
	{
		Polyphemus::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_EndianForest_Polyphemus_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			1.1f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Polyphemus::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.054f,
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
			nullptr
		);
	}

	return Polyphemus::HexusOpponentDataInstance;
}