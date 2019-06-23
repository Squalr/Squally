//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Leopold.h"

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

using namespace cocos2d;

const std::string Leopold::MapKeyLeopold = "leopold";
HexusOpponentData* Leopold::HexusOpponentDataInstance = nullptr;
const std::string Leopold::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LEOPOLD";

Leopold* Leopold::deserialize(ValueMap& initProperties)
{
	Leopold* instance = new Leopold(initProperties);

	instance->autorelease();

	return instance;
}

Leopold::Leopold(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_CastleValgrind_Leopold_Animations,
	EntityResources::Npcs_CastleValgrind_Leopold_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	0.95f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Leopold::getHexusOpponentData();
}

Leopold::~Leopold()
{
}

Vec2 Leopold::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Leopold::getHexusOpponentData()
{
	if (Leopold::HexusOpponentDataInstance == nullptr)
	{
		Leopold::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_CastleValgrind_Leopold_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			0.95f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Leopold::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.491f,
			HexusOpponentData::generateDeck(32, 0.491f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),

			}),
			nullptr
		);
	}

	return Leopold::HexusOpponentDataInstance;
}