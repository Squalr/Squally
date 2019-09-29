#pragma once
#include <functional>
#include <string>

#include "cocos/math/CCGeometry.h"

class Card;
class HexusOpponentData;

class HexusEvents
{
public:
	static const std::string EventOpenHexus;
	static const std::string EventExitHexus;
	static const std::string EventCardPreviewed;
	static const std::string EventCardMousedOut;

	struct HexusOpenArgs
	{
		HexusOpponentData* opponentData;

		HexusOpenArgs(HexusOpponentData* opponentData) : opponentData(opponentData) { }
	};

	struct HexusExitArgs
	{
		HexusOpponentData* opponentData;

		HexusExitArgs(HexusOpponentData* opponentData) : opponentData(opponentData) { }
	};

	struct CardPreviewArgs
	{
		Card* card;

		CardPreviewArgs(Card* card) : card(card)
		{
		}
	};

	static void TriggerOpenHexus(HexusOpenArgs args);
	static void TriggerExitHexus();
	static void TriggerCardPreviewed(CardPreviewArgs args);
	static void TriggerCardMousedOut();
};
