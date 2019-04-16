#pragma once

#include "cocos/2d/CCSprite.h"
#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardEffects.h"

namespace cocos2d
{
	class Sprite;
}

class CardEffects;
class ConstantString;
class ClickableNode;
class LocalizedLabel;

class Card : public SmartNode
{
public:
	enum CardStyle
	{
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
			ROL,
			ROR,
			MOV,
			AND,
			OR,
			XOR,
			ADD,
			SUB,
			NOT,
		};

		OperationType operationType;
		unsigned int immediate;

		Operation(OperationType operationType, unsigned int immediate = 0b0000) : operationType(operationType), immediate(immediate)
		{

		}
	};

	static Card* create(CardStyle cardStyle, CardData* data, bool isPlayerOwnedCard = true);

	Operation toOperation(unsigned int immediate = 0);
	void reveal();
	void hide();
	void focus();
	void unfocus();
	void setFocusTint(cocos2d::Color3B color);
	void addOperation(Operation operation);
	void clearOperations();
	unsigned int getOriginalAttack();
	unsigned int getAttack();
	void doDrawAnimation(float cardDrawDelay);
	void disableInteraction();
	void enableInteraction();
	void setMouseOverCallback(std::function<void(Card*)> callback);
	void setMouseOutCallback(std::function<void(Card*)> callback);
	void setMouseClickCallback(std::function<void(Card*)> callback);
	int simulateOperation(Operation operation);
	void setIsPlayerOwnedCard(bool isPlayerOwnedCard);
	bool getIsPlayerOwnedCard();
	void runOverflowEffect(bool offsetYPosition = false);
	void runUnderflowEffect(bool offsetYPosition = false);
	CardEffects::CardEffect getCorrespondingCardEffect();

	CardData* cardData;
	CardEffects* cardEffects;
	cocos2d::Vec2 position;

	static const float cardScale;
	static const cocos2d::Color4B binaryColor;
	static const cocos2d::Color4B decimalColor;
	static const cocos2d::Color4B hexColor;
	static const cocos2d::Color4B specialColor;
	static const cocos2d::Color4B debuffColor;
	static const cocos2d::Color4B buffColor;

protected:
	Card(CardStyle cardStyle, CardData* data, bool isPlayerOwnedCard = true);
	~Card();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
	void updateText();
	void onMouseOver();
	void onMouseOut();
	void onMouseClick();
	int applyOperation(int attack, Operation operation);

	bool isPlayerOwnedCard;

	std::vector<Operation> operations;
	cocos2d::Sprite* cardBack;
	cocos2d::Sprite* cardFront;
	cocos2d::Sprite* cardSprite;
	ClickableNode* cardSelect;
	cocos2d::Sprite* cardFocus;
	ConstantString* cardString;
	LocalizedLabel* cardLabel;
	LocalizedLabel* overflowLabel;
	LocalizedLabel* underflowLabel;
	std::function<void(Card*)> mouseOverCallback;
	std::function<void(Card*)> mouseOutCallback;
	std::function<void(Card*)> mouseClickCallback;
};
