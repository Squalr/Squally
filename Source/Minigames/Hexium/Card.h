#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Minigames/Hexium/CardData.h"

using namespace cocos2d;

class Card : public Node
{
public:
	enum CardStyle {
		Robotic,
		Shadow,
	};

	static Card* create(CardStyle cardStyle, CardData* data);

	void reveal();
	void hide();

	static const float cardScale;

private:
	Card(CardStyle cardStyle, CardData* data);
	~Card();

	void initializePositions();
	void initializeListeners();
	void onEnter() override;

	CardData* cardData;
	Sprite* cardBack;
	Sprite* cardFront;
};

