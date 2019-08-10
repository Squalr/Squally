#include "KingRedsongSlime.h"

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

const std::string KingRedsongSlime::MapKeyKingRedsongSlime = "king-redsong-slime";
HexusOpponentData* KingRedsongSlime::HexusOpponentDataInstance = nullptr;
const std::string KingRedsongSlime::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KING_REDSONG_SLIME";

KingRedsongSlime* KingRedsongSlime::deserialize(ValueMap& initProperties)
{
	KingRedsongSlime* instance = new KingRedsongSlime(initProperties);

	instance->autorelease();

	return instance;
}

KingRedsongSlime::KingRedsongSlime(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_CastleValgrind_KingRedsongSlime_Animations,
	EntityResources::Npcs_CastleValgrind_KingRedsongSlime_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = KingRedsongSlime::getHexusOpponentData();
}

KingRedsongSlime::~KingRedsongSlime()
{
}

Vec2 KingRedsongSlime::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -96.0f);
}

HexusOpponentData* KingRedsongSlime::getHexusOpponentData()
{
	if (KingRedsongSlime::HexusOpponentDataInstance == nullptr)
	{
		KingRedsongSlime::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_CastleValgrind_KingRedsongSlime_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -128.0f),
			Vec2(-32.0f, -96.0f),
			KingRedsongSlime::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.402f,
			HexusOpponentData::generateDeck(32, 0.402f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),

			}),
			nullptr
		);
	}

	return KingRedsongSlime::HexusOpponentDataInstance;
}