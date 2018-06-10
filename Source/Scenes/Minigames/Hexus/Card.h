#pragma once
#include "cocos2d.h"

#include "Engine/Rendering/Components/MenuSprite.h"
#include "Resources.h"
#include "Utils/HackUtils.h"

#include "CardData.h"
#include "Config.h"

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

	struct Operation
	{
		enum OperationType
		{
			SHL,
			SHR,
			AND,
			OR,
			XOR,
			ADD,
			SUB,
		};

		OperationType opterationType;
		unsigned int immediate;

		Operation(OperationType opterationType, unsigned int immediate) : opterationType(opterationType), immediate(immediate)
		{

		}
	};

	static Card* create(CardStyle cardStyle, CardData* data);
	static Operation toOperation(CardData::CardType playedCardType, unsigned int immediate);

	void reveal();
	void hide();
	void focus();
	void unfocus();
	void setFocusTint(Color3B color);
	void addOperation(Operation operation);
	unsigned int getAttack();
	void doDrawAnimation(float cardDrawDelay);
	void setScale(float scale) override;
	void disableInteraction();
	void enableInteraction();
	void setMouseOverCallback(std::function<void(Card*)> callback);
	void setMouseClickCallback(std::function<void(Card*)> callback);

	CardData* cardData;
	Vec2 position;

	static const float cardScale;
	static const Color4B binaryColor;
	static const Color4B decimalColor;
	static const Color4B hexColor;
	static const Color4B specialColor;
	static const Color4B debuffColor;
	static const Color4B buffColor;

private:
	Card(CardStyle cardStyle, CardData* data);
	~Card();

	void initializePositions();
	void initializeListeners();
	void onEnter() override;
	void updateText();
	void onMouseOver(MenuSprite* menuSprite);
	void onMouseClick(MenuSprite* menuSprite);

	std::vector<Operation>* operations;
	Sprite* cardBack;
	Sprite* cardFront;
	Sprite* cardImage;
	MenuSprite* cardSprite;
	Sprite* cardFocus;
	LayerColor* attackFrame;
	Label* cardText;
	std::function<void(Card*)> mouseOverCallback;
	std::function<void(Card*)> mouseClickCallback;
};

