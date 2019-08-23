#include "PrincessNebea.h"

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

const std::string PrincessNebea::MapKeyPrincessNebea = "princess-nebea";
HexusOpponentData* PrincessNebea::HexusOpponentDataInstance = nullptr;
const std::string PrincessNebea::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PRINCESS_NEBEA";

PrincessNebea* PrincessNebea::deserialize(ValueMap& properties)
{
	PrincessNebea* instance = new PrincessNebea(properties);

	instance->autorelease();

	return instance;
}

PrincessNebea::PrincessNebea(ValueMap& properties) : super(properties,
	PrincessNebea::MapKeyPrincessNebea,
	EntityResources::Npcs_LambdaCrypts_PrincessNebea_Animations,
	EntityResources::Npcs_LambdaCrypts_PrincessNebea_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = PrincessNebea::getHexusOpponentData();
}

PrincessNebea::~PrincessNebea()
{
}

Vec2 PrincessNebea::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* PrincessNebea::getEntityName()
{
	return nullptr;
}

HexusOpponentData* PrincessNebea::getHexusOpponentData()
{
	if (PrincessNebea::HexusOpponentDataInstance == nullptr)
	{
		PrincessNebea::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_LambdaCrypts_PrincessNebea_Animations,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			PrincessNebea::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.812f,
			HexusOpponentData::generateDeck(32, 0.812f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),

			}),
			nullptr
		);
	}

	return PrincessNebea::HexusOpponentDataInstance;
}