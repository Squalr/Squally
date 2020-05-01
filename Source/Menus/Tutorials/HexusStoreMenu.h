#pragma once
#include <map>
#include <tuple>
#include <vector>

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class LayerColor;
	class ParticleSystem;
	class Sprite;
}

class Card;
class CardData;
class ConstantString;
class ClickableNode;
class ClickableTextNode;
class LocalizedLabel;
class MenuCard;
class ScrollPane;
class Shopkeeper;
class SmartAnimationNode;
class SmartParticles;
class Sound;

class HexusStoreMenu : public GlobalScene
{
public:
	static HexusStoreMenu* getInstance();

protected:
	HexusStoreMenu();
	virtual ~HexusStoreMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GlobalScene super;

	ClickableNode* constructCard(CardData* cardData, int price, std::function<void(CardData*, int)> clickCallback);
	void updateGoldText();
	void onCardClick(CardData* cardData, int price);
	void onChallengeComplete();
	void onResetClick();
	void onBackClick();

	SmartParticles* dustParticles;
	cocos2d::Sprite* storeBack;
	Shopkeeper* shopKeeper;
	cocos2d::Sprite* storeFront;
	cocos2d::Node* storeNode;
	cocos2d::Sprite* storeMenu;
	ClickableNode* xorCard;
	ClickableNode* andCard;
	ClickableNode* inverseCard;
	cocos2d::Sprite* goldPanel;
	cocos2d::Sprite* goldIcon;
	ConstantString* goldString;
	LocalizedLabel* goldLabel;
	ClickableTextNode* backButton;
	ClickableTextNode* resetButton;
	Sound* purchaseSound;
	Sound* errorSound;

	static const std::string SaveKeyGold;
	static const int DefaultGold;
	static HexusStoreMenu* instance;
};
