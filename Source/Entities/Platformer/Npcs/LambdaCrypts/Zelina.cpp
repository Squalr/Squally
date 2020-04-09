#include "Zelina.h"

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

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Zelina::MapKey = "zelina";
HexusOpponentData* Zelina::HexusOpponentDataInstance = nullptr;
const std::string Zelina::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ZELINA";

Zelina* Zelina::deserialize(ValueMap& properties)
{
	Zelina* instance = new Zelina(properties);

	instance->autorelease();

	return instance;
}

Zelina::Zelina(ValueMap& properties) : super(properties,
	Zelina::MapKey,
	EntityResources::Npcs_LambdaCrypts_Zelina_Animations,
	EntityResources::Npcs_LambdaCrypts_Zelina_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Zelina::getHexusOpponentData();
}

Zelina::~Zelina()
{
}

Vec2 Zelina::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Zelina::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Zelina::create();
}

HexusOpponentData* Zelina::getHexusOpponentData()
{
	if (Zelina::HexusOpponentDataInstance == nullptr)
	{
		Zelina::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			Zelina::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.795f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
			}),
			nullptr,
			nullptr
		);
	}

	return Zelina::HexusOpponentDataInstance;
}