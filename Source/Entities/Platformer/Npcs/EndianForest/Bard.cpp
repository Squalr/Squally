#include "Bard.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/EndianForest/Bard.h"

using namespace cocos2d;

const std::string Bard::MapKeyBard = "bard";
HexusOpponentData* Bard::HexusOpponentDataInstance = nullptr;
const std::string Bard::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BARD";

Bard* Bard::deserialize(ValueMap& properties)
{
	Bard* instance = new Bard(properties);

	instance->autorelease();

	return instance;
}

Bard::Bard(ValueMap& properties) : super(properties,
	Bard::MapKeyBard,
	EntityResources::Npcs_EndianForest_Bard_Animations,
	EntityResources::Npcs_EndianForest_Bard_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Bard::getHexusOpponentData();
}

Bard::~Bard()
{
}

Vec2 Bard::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Bard::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Bard::create();
}

HexusOpponentData* Bard::getHexusOpponentData()
{
	if (Bard::HexusOpponentDataInstance == nullptr)
	{
		Bard::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_EndianForest_Bard_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Bard::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.018f,
			HexusOpponentData::generateDeck(32, 0.018f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip1),
			}),
			{ },
			nullptr
		);
	}

	return Bard::HexusOpponentDataInstance;
}