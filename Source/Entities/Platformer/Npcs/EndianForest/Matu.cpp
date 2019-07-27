#include "Matu.h"

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

const std::string Matu::MapKeyMatu = "matu";
HexusOpponentData* Matu::HexusOpponentDataInstance = nullptr;
const std::string Matu::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PRINCESS_MATU";

Matu* Matu::deserialize(ValueMap& initProperties)
{
	Matu* instance = new Matu(initProperties);

	instance->autorelease();

	return instance;
}

Matu::Matu(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_EndianForest_Matu_Animations,
	EntityResources::Npcs_EndianForest_Matu_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Matu::getHexusOpponentData();
}

Matu::~Matu()
{
}

Vec2 Matu::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Matu::getHexusOpponentData()
{
	if (Matu::HexusOpponentDataInstance == nullptr)
	{
		Matu::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_EndianForest_Matu_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Matu::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.045f,
			HexusOpponentData::generateDeck(32, 0.045f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),

			}),
			nullptr
		);
	}

	return Matu::HexusOpponentDataInstance;
}