#include "Illia.h"

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

const std::string Illia::MapKeyIllia = "illia";
HexusOpponentData* Illia::HexusOpponentDataInstance = nullptr;
const std::string Illia::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ILLIA";

Illia* Illia::deserialize(ValueMap& initProperties)
{
	Illia* instance = new Illia(initProperties);

	instance->autorelease();

	return instance;
}

Illia::Illia(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_VoidStar_Illia_Animations,
	EntityResources::Npcs_VoidStar_Illia_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Illia::getHexusOpponentData();
}

Illia::~Illia()
{
}

Vec2 Illia::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Illia::getHexusOpponentData()
{
	if (Illia::HexusOpponentDataInstance == nullptr)
	{
		Illia::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_VoidStar_Illia_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Illia::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.981f,
			HexusOpponentData::generateDeck(32, 0.981f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),

			}),
			nullptr
		);
	}

	return Illia::HexusOpponentDataInstance;
}