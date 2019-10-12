#include "KingRedsong.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/CastleValgrind/KingRedsong.h"

using namespace cocos2d;

const std::string KingRedsong::MapKeyKingRedsong = "king-redsong";
HexusOpponentData* KingRedsong::HexusOpponentDataInstance = nullptr;
const std::string KingRedsong::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KING_REDSONG";

KingRedsong* KingRedsong::deserialize(ValueMap& properties)
{
	KingRedsong* instance = new KingRedsong(properties);

	instance->autorelease();

	return instance;
}

KingRedsong::KingRedsong(ValueMap& properties) : super(properties,
	KingRedsong::MapKeyKingRedsong,
	EntityResources::Npcs_CastleValgrind_KingRedsong_Animations,
	EntityResources::Npcs_CastleValgrind_KingRedsong_Emblem,
	Size(160.0f, 192.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = KingRedsong::getHexusOpponentData();
}

KingRedsong::~KingRedsong()
{
}

Vec2 KingRedsong::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* KingRedsong::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_KingRedsong::create();
}

HexusOpponentData* KingRedsong::getHexusOpponentData()
{
	if (KingRedsong::HexusOpponentDataInstance == nullptr)
	{
		KingRedsong::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_CastleValgrind_KingRedsong_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			KingRedsong::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.411f,
			HexusOpponentData::generateDeck(32, 0.411f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
			}),
			nullptr,
			nullptr
		);
	}

	return KingRedsong::HexusOpponentDataInstance;
}