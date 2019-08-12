#include "Thurstan.h"

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

const std::string Thurstan::MapKeyThurstan = "thurstan";
HexusOpponentData* Thurstan::HexusOpponentDataInstance = nullptr;
const std::string Thurstan::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_THURSTAN";

Thurstan* Thurstan::deserialize(ValueMap& initProperties)
{
	Thurstan* instance = new Thurstan(initProperties);

	instance->autorelease();

	return instance;
}

Thurstan::Thurstan(ValueMap& initProperties) : NpcBase(initProperties,
	Thurstan::MapKeyThurstan,
	EntityResources::Npcs_CastleValgrind_Thurstan_Animations,
	EntityResources::Npcs_CastleValgrind_Thurstan_Emblem,
	Size(124.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Thurstan::getHexusOpponentData();
}

Thurstan::~Thurstan()
{
}

Vec2 Thurstan::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Thurstan::getHexusOpponentData()
{
	if (Thurstan::HexusOpponentDataInstance == nullptr)
	{
		Thurstan::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_CastleValgrind_Thurstan_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			1.05f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Thurstan::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.482f,
			HexusOpponentData::generateDeck(32, 0.482f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),

			}),
			nullptr
		);
	}

	return Thurstan::HexusOpponentDataInstance;
}