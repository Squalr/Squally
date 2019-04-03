#pragma once
#include <functional>
#include <string>

#include "cocos/math/CCGeometry.h"

class Card;

class HexusEvents
{
public:
	static const std::string EventCardPreviewed;
	static const std::string EventCardMousedOut;

	struct CardPreviewArgs
	{
		Card* card;

		CardPreviewArgs(Card* card) : card(card)
		{
		}
	};

	static void TriggerCardPreviewed(CardPreviewArgs args);
	static void TriggerCardMousedOut();
};
