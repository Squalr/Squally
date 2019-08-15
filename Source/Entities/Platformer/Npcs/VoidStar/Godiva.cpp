#include "Godiva.h"

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

const std::string Godiva::MapKeyGodiva = "godiva";
HexusOpponentData* Godiva::HexusOpponentDataInstance = nullptr;
const std::string Godiva::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GODIVA";

Godiva* Godiva::deserialize(ValueMap& initProperties)
{
	Godiva* instance = new Godiva(initProperties);

	instance->autorelease();

	return instance;
}

Godiva::Godiva(ValueMap& initProperties) : super(initProperties,
	Godiva::MapKeyGodiva,
	EntityResources::Npcs_VoidStar_Godiva_Animations,
	EntityResources::Npcs_VoidStar_Godiva_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Godiva::getHexusOpponentData();
}

Godiva::~Godiva()
{
}

Vec2 Godiva::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Godiva::getHexusOpponentData()
{
	if (Godiva::HexusOpponentDataInstance == nullptr)
	{
		Godiva::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_VoidStar_Godiva_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			1.05f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Godiva::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.990f,
			HexusOpponentData::generateDeck(32, 0.990f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::SuddenDeath),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),

			}),
			nullptr
		);
	}

	return Godiva::HexusOpponentDataInstance;
}