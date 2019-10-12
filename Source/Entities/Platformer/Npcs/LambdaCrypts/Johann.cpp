#include "Johann.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/LambdaCrypts/Johann.h"

using namespace cocos2d;

const std::string Johann::MapKeyJohann = "johann";
HexusOpponentData* Johann::HexusOpponentDataInstance = nullptr;
const std::string Johann::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_JOHANN";

Johann* Johann::deserialize(ValueMap& properties)
{
	Johann* instance = new Johann(properties);

	instance->autorelease();

	return instance;
}

Johann::Johann(ValueMap& properties) : super(properties,
	Johann::MapKeyJohann,
	EntityResources::Npcs_LambdaCrypts_Johann_Animations,
	EntityResources::Npcs_LambdaCrypts_Johann_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Johann::getHexusOpponentData();
}

Johann::~Johann()
{
}

Vec2 Johann::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Johann::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Johann::create();
}

HexusOpponentData* Johann::getHexusOpponentData()
{
	if (Johann::HexusOpponentDataInstance == nullptr)
	{
		Johann::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_LambdaCrypts_Johann_Animations,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Johann::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.866f,
			HexusOpponentData::generateDeck(32, 0.866f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
			}),
			{ },
			nullptr
		);
	}

	return Johann::HexusOpponentDataInstance;
}