#pragma once

#include "cocos/2d/CCSprite.h"
#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"
#include "Scenes/Hexus/CardData/CardData.h"

namespace cocos2d
{
	class Sprite;
}

class CardEffects;
class ConstantString;
class LocalizedLabel;
class ClickableNode;

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
	static Operation toOperation(CardData::CardType playedCardType, unsigned int immediate = 0);

	void reveal();
	void hide();
	void focus();
	void unfocus();
	void setFocusTint(cocos2d::Color3B color);
	void addOperation(Operation operation);
	void clearOperations();
	unsigned int getOriginalAttack();
	unsigned int getAttack();
	void setHibernating(bool isHibernating);
	void setProtected(bool isProtected);
	bool getHibernating();
	bool getProtected();
	void doDrawAnimation(float cardDrawDelay);
	void disableInteraction();
	void enableInteraction();
	void setMouseOverCallback(std::function<void(Card*)> callback);
	void setMouseClickCallback(std::function<void(Card*)> callback);
	int simulateOperation(Operation operation);

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
	Card(CardStyle cardStyle, CardData* data);
	~Card();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
	void updateText();
	void onMouseOver();
	void onMouseClick();
	int applyOperation(int attack, Operation operation);

	bool isHibernating;
	bool isProtected;

	std::vector<Operation> operations;
	cocos2d::Sprite* cardBack;
	cocos2d::Sprite* cardFront;
	cocos2d::Sprite* cardSprite;
	ClickableNode* cardSelect;
	cocos2d::Sprite* cardFocus;
	ConstantString* cardString;
	LocalizedLabel* cardLabel;
	std::function<void(Card*)> mouseOverCallback;
	std::function<void(Card*)> mouseClickCallback;
};
