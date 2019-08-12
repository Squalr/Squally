#include "QueenElise.h"

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

const std::string QueenElise::MapKeyQueenElise = "queen-elise";
HexusOpponentData* QueenElise::HexusOpponentDataInstance = nullptr;
const std::string QueenElise::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_QUEEN_ELISE";

QueenElise* QueenElise::deserialize(ValueMap& initProperties)
{
	QueenElise* instance = new QueenElise(initProperties);

	instance->autorelease();

	return instance;
}

QueenElise::QueenElise(ValueMap& initProperties) : NpcBase(initProperties,
	QueenElise::MapKeyQueenElise,
	EntityResources::Npcs_VoidStar_QueenElise_Animations,
	EntityResources::Npcs_VoidStar_QueenElise_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = QueenElise::getHexusOpponentData();
}

QueenElise::~QueenElise()
{
}

Vec2 QueenElise::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* QueenElise::getHexusOpponentData()
{
	if (QueenElise::HexusOpponentDataInstance == nullptr)
	{
		QueenElise::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_VoidStar_QueenElise_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			QueenElise::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.933f,
			HexusOpponentData::generateDeck(32, 0.933f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::SuddenDeath),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),

			}),
			nullptr
		);
	}

	return QueenElise::HexusOpponentDataInstance;
}