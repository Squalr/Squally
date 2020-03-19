#include "Jingles.h"

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

const std::string Jingles::MapKey = "jingles";
HexusOpponentData* Jingles::HexusOpponentDataInstance = nullptr;
const std::string Jingles::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_JINGLES";

Jingles* Jingles::deserialize(ValueMap& properties)
{
	Jingles* instance = new Jingles(properties);

	instance->autorelease();

	return instance;
}

Jingles::Jingles(ValueMap& properties) : super(properties,
	Jingles::MapKey,
	EntityResources::Npcs_BalmerPeaks_Jingles_Animations,
	EntityResources::Npcs_BalmerPeaks_Jingles_Emblem,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Jingles::getHexusOpponentData();
}

Jingles::~Jingles()
{
}

Vec2 Jingles::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Jingles::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BalmerPeaks_Jingles::create();
}

HexusOpponentData* Jingles::getHexusOpponentData()
{
	if (Jingles::HexusOpponentDataInstance == nullptr)
	{
		Jingles::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			Vec2(-32.0f, -112.0f),
			Jingles::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			HexusOpponentData::generateDeck(32, 0.562f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
			}),
			nullptr,
			nullptr
		);
	}

	return Jingles::HexusOpponentDataInstance;
}