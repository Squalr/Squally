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
		unsigned int immediate = 0;

		Operation(OperationType operationType, unsigned int immediate = 0b0000) : operationType(operationType), immediate(immediate)
		{

		}
	};

	static Card* create(CardStyle cardStyle, CardData* data, bool isPlayerOwnedCard = true, bool relocateUI = true);

	Card* clone(bool relocateUI);
	Operation toOperation(unsigned int immediate = 0);
	void reveal();
	void hide();
	void showUI();
	void hideUI();
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
	void runUnderflowEffect(bool offsetYPosition = false, bool isGoodEffect = true);
	CardEffects::CardEffect getCorrespondingCardEffect();

	CardData* cardData = nullptr;
	CardEffects* cardEffects = nullptr;
	cocos2d::Vec2 position = cocos2d::Vec2::ZERO;

	static const float cardScale;
	static const cocos2d::Color4B BinaryColor;
	static const cocos2d::Color4B DecimalColor;
	static const cocos2d::Color4B HexColor;
	static const cocos2d::Color4B SpecialColor;
	static const cocos2d::Color4B DebuffColor;
	static const cocos2d::Color4B BuffColor;

protected:
	Card(CardStyle cardStyle, CardData* data, bool isPlayerOwnedCard = true, bool relocateUI = true);
	virtual ~Card();

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

	CardStyle cardStyle = CardStyle::Shadow;
	bool isPlayerOwnedCard = false;
	bool relocateUI = false;

	std::vector<Operation> operations;
	cocos2d::Sprite* cardBack = nullptr;
	cocos2d::Sprite* cardFront = nullptr;
	cocos2d::Sprite* cardSprite = nullptr;
	ClickableNode* cardSelect = nullptr;
	cocos2d::Sprite* cardFocus = nullptr;
	ConstantString* cardString = nullptr;
	LocalizedLabel* cardLabel = nullptr;
	LocalizedLabel* overflowLabel = nullptr;
	LocalizedLabel* underflowLabel = nullptr;
	std::function<void(Card*)> mouseOverCallback = nullptr;
	std::function<void(Card*)> mouseOutCallback = nullptr;
	std::function<void(Card*)> mouseClickCallback = nullptr;
};
