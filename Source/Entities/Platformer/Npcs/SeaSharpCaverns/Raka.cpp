#include "Raka.h"

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

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Raka::MapKeyRaka = "raka";
HexusOpponentData* Raka::HexusOpponentDataInstance = nullptr;
const std::string Raka::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_RAKA";

Raka* Raka::deserialize(ValueMap& properties)
{
	Raka* instance = new Raka(properties);

	instance->autorelease();

	return instance;
}

Raka::Raka(ValueMap& properties) : super(properties,
	Raka::MapKeyRaka,
	EntityResources::Npcs_SeaSharpCaverns_Raka_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Raka_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Raka::getHexusOpponentData();
}

Raka::~Raka()
{
}

Vec2 Raka::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Raka::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_Raka::create();
}

HexusOpponentData* Raka::getHexusOpponentData()
{
	if (Raka::HexusOpponentDataInstance == nullptr)
	{
		Raka::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(-32.0f, -112.0f),
			Raka::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.357f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
			}),
			nullptr,
			nullptr
		);
	}

	return Raka::HexusOpponentDataInstance;
}