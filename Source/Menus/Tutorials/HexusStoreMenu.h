#pragma once
#include <map>
#include <tuple>
#include <vector>

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Sprite;
}

class CardData;
class ConstantString;
class ClickableNode;
class ClickableTextNode;
class LocalizedLabel;
class Shopkeeper;
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
	bool purchaseCard(CardData* cardData, int price);
	void onChallengeComplete();
	void onResetClick();
	void onBackClick();

	SmartParticles* dustParticles = nullptr;
	cocos2d::Sprite* storeBack = nullptr;
	Shopkeeper* shopKeeper = nullptr;
	cocos2d::Sprite* storeFront = nullptr;
	cocos2d::Node* storeNode = nullptr;
	cocos2d::Sprite* storeMenu = nullptr;
	ClickableNode* xorCard = nullptr;
	ClickableNode* andCard = nullptr;
	ClickableNode* inverseCard = nullptr;
	cocos2d::Sprite* goldPanel = nullptr;
	cocos2d::Sprite* goldIcon = nullptr;
	ConstantString* goldString = nullptr;
	LocalizedLabel* goldLabel = nullptr;
	ClickableTextNode* backButton = nullptr;
	ClickableTextNode* resetButton = nullptr;
	Sound* purchaseSound = nullptr;
	Sound* errorSound = nullptr;

	static const std::string SaveKeyGold;
	static const int DefaultGold;
	static HexusStoreMenu* Instance;
};
