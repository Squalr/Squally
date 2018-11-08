#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/SmartNode.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/HackUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardEffects.h"
#include "Scenes/Hexus/Config.h"

using namespace cocos2d;

class Card : public SmartNode
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
			MOV,
			AND,
			OR,
			XOR,
			ADD,
			SUB,
		};

		OperationType operationType;
		unsigned int immediate;

		Operation(OperationType operationType, unsigned int immediate) : operationType(operationType), immediate(immediate)
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
	int simulateOperation(Operation operation);

	CardData* cardData;
	CardEffects* cardEffects;
	Vec2 position;

	static const float cardScale;
	static const Color4B binaryColor;
	static const Color4B decimalColor;
	static const Color4B hexColor;
	static const Color4B specialColor;
	static const Color4B debuffColor;
	static const Color4B buffColor;

protected:
	Card(CardStyle cardStyle, CardData* data);
	~Card();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	void updateText();
	void onMouseOver(MenuSprite* menuSprite);
	void onMouseClick(MenuSprite* menuSprite);
	int applyOperation(int attack, Operation operation);

	std::vector<Operation>* operations;
	Sprite* cardBack;
	Sprite* cardFront;
	Sprite* cardSprite;
	MenuSprite* cardSelect;
	Sprite* cardFocus;
	Label* cardText;
	std::function<void(Card*)> mouseOverCallback;
	std::function<void(Card*)> mouseClickCallback;
};

