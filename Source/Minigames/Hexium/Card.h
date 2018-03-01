#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Minigames/Hexium/CardData.h"
#include "Utils/HackUtils.h"

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
	void doDrawAnimation(float cardDrawDelay);

	static const float cardScale;

	CardData* cardData;

private:
	Card(CardStyle cardStyle, CardData* data);
	~Card();

	void initializePositions();
	void initializeListeners();
	void onEnter() override;
	void updateText();

	Sprite* cardBack;
	Sprite* cardFront;
	LayerColor* attackFrame;
	Label* cardText;

	static const Color4B binaryColor;
	static const Color4B decimalColor;
	static const Color4B hexColor;
	static const Color4B specialColor;
};

