#include "Atreus.h"

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

const std::string Atreus::MapKey = "atreus";
HexusOpponentData* Atreus::HexusOpponentDataInstance = nullptr;
const std::string Atreus::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ATREUS";

Atreus* Atreus::deserialize(ValueMap& properties)
{
	Atreus* instance = new Atreus(properties);

	instance->autorelease();

	return instance;
}

Atreus::Atreus(ValueMap& properties) : super(properties,
	Atreus::MapKey,
	EntityResources::Npcs_VoidStar_Atreus_Animations,
	EntityResources::Npcs_VoidStar_Atreus_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Atreus::getHexusOpponentData();
}

Atreus::~Atreus()
{
}

Vec2 Atreus::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Atreus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_VoidStar_Atreus::create();
}

HexusOpponentData* Atreus::getHexusOpponentData()
{
	if (Atreus::HexusOpponentDataInstance == nullptr)
	{
		Atreus::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameVoidStar,
			Vec2(-32.0f, -112.0f),
			Atreus::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 1.000f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
			}),
			nullptr,
			nullptr
		);
	}

	return Atreus::HexusOpponentDataInstance;
}