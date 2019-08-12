#include "Necron.h"

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

const std::string Necron::MapKeyNecron = "necron";
HexusOpponentData* Necron::HexusOpponentDataInstance = nullptr;
const std::string Necron::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_NECRON";

Necron* Necron::deserialize(ValueMap& initProperties)
{
	Necron* instance = new Necron(initProperties);

	instance->autorelease();

	return instance;
}

Necron::Necron(ValueMap& initProperties) : NpcBase(initProperties,
	Necron::MapKeyNecron,
	EntityResources::Npcs_LambdaCrypts_Necron_Animations,
	EntityResources::Npcs_LambdaCrypts_Necron_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Necron::getHexusOpponentData();
}

Necron::~Necron()
{
}

Vec2 Necron::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Necron::getHexusOpponentData()
{
	if (Necron::HexusOpponentDataInstance == nullptr)
	{
		Necron::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_LambdaCrypts_Necron_Animations,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Necron::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.804f,
			HexusOpponentData::generateDeck(32, 0.804f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),

			}),
			nullptr
		);
	}

	return Necron::HexusOpponentDataInstance;
}