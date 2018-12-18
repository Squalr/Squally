#include "HexusOpponentSnowFiend.h"

const std::string HexusOpponentSnowFiend::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SNOW_FIEND";
HexusOpponentSnowFiend* HexusOpponentSnowFiend::instance = nullptr;

HexusOpponentSnowFiend* HexusOpponentSnowFiend::getInstance()
{
	if (HexusOpponentSnowFiend::instance == nullptr)
	{
		HexusOpponentSnowFiend::instance = new HexusOpponentSnowFiend();
	}

	return HexusOpponentSnowFiend::instance;
}

HexusOpponentSnowFiend::HexusOpponentSnowFiend() : HexusOpponentData(
	EntityResources::Enemies_LambdaPeaks_SnowFiend_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-48.0f, -64.0f),
	HexusOpponentSnowFiend::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.69f),
	HexusOpponentData::generateDeck(25, 0.69f,
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentSnowFiend::~HexusOpponentSnowFiend()
{
}
