#include "Azmus.h"

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

const std::string Azmus::MapKeyAzmus = "azmus";
HexusOpponentData* Azmus::HexusOpponentDataInstance = nullptr;
const std::string Azmus::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_AZMUS";

Azmus* Azmus::deserialize(ValueMap& initProperties)
{
	Azmus* instance = new Azmus(initProperties);

	instance->autorelease();

	return instance;
}

Azmus::Azmus(ValueMap& initProperties) : NpcBase(initProperties,
	Azmus::MapKeyAzmus,
	EntityResources::Npcs_LambdaCrypts_Azmus_Animations,
	EntityResources::Npcs_LambdaCrypts_Azmus_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Azmus::getHexusOpponentData();
}

Azmus::~Azmus()
{
}

Vec2 Azmus::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Azmus::getHexusOpponentData()
{
	if (Azmus::HexusOpponentDataInstance == nullptr)
	{
		Azmus::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_LambdaCrypts_Azmus_Animations,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Azmus::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.768f,
			HexusOpponentData::generateDeck(32, 0.768f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::SuddenDeath),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),

			}),
			nullptr
		);
	}

	return Azmus::HexusOpponentDataInstance;
}