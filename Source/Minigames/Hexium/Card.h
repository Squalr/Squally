#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Minigames/Hexium/CardData.h"
#include "Utils/HackUtils.h"
#include "GUI/Components/MenuSprite.h"

using namespace cocos2d;

class Card : public Node
{
public:
	enum CardStyle {
		Earth,
		Water,
		Air,
		Fire,
		Light,
		Shadow,
	};

	static Card* create(CardStyle cardStyle, CardData* data);

	void reveal();
	void hide();
	int getAttack();
	void doDrawAnimation(float cardDrawDelay);
	void setScale(float scale) override;
	void setMouseOverCallback(std::function<void(Card*)> callback);

	CardData* cardData;

	static const float cardScale;
	static const Color4B binaryColor;
	static const Color4B decimalColor;
	static const Color4B hexColor;
	static const Color4B specialColor;

private:
	Card(CardStyle cardStyle, CardData* data);
	~Card();

	void initializePositions();
	void initializeListeners();
	void onEnter() override;
	void updateText();
	void onMouseOver(MenuSprite* menuSprite);

	Sprite* cardBack;
	Sprite* cardFront;
	Sprite* cardImage;
	Node* cardSelected;
	MenuSprite* cardSprite;
	LayerColor* attackFrame;
	Label* cardText;
	std::function<void(Card*)>  mouseOverCallback;
};

