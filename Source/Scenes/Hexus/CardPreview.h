#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class Card;
class CardData;
class ClickableTextNode;
class ConstantString;
class LocalizedLabel;

class CardPreview : public SmartNode
{
public:
	static CardPreview* create();
	
	void previewCard(Card* card);
	void previewCardData(CardData* cardData, Card* card = nullptr);
	void clearPreview();
	void setHelpClickCallback(std::function<void(CardData*)> onHelpClick);

protected:
	CardPreview();
	virtual ~CardPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef SmartNode super;

	struct PreviewData
	{
		Card* previewCard = nullptr;
		CardData* cardData = nullptr;
		cocos2d::Node* previewNode = nullptr;
		ConstantString* binStrRef = nullptr;
		ConstantString* decStrRef = nullptr;
		ConstantString* hexStrRef = nullptr;
		LocalizedLabel* binLabelRef = nullptr;
		LocalizedLabel* decLabelRef = nullptr;
		LocalizedLabel* hexLabelRef = nullptr;

		PreviewData() { }
		PreviewData(Card* previewCard, CardData* cardData, cocos2d::Node* previewNode, ConstantString* binStrRef, ConstantString* decStrRef, ConstantString* hexStrRef, LocalizedLabel* binLabelRef, LocalizedLabel* decLabelRef, LocalizedLabel* hexLabelRef)
			: previewCard(previewCard), cardData(cardData), previewNode(previewNode), binStrRef(binStrRef), decStrRef(decStrRef), hexStrRef(hexStrRef), binLabelRef(binLabelRef), decLabelRef(decLabelRef), hexLabelRef(hexLabelRef) { }
	};

	CardPreview::PreviewData constructPreview(CardData* cardData, Card* card);
	void updatePreview(PreviewData previewData, Card* refCard);

	cocos2d::Sprite* cardPad = nullptr;
	PreviewData currentPreviewData;
	cocos2d::Node* previewPanel = nullptr;
	ClickableTextNode* helpButton = nullptr;
	
	std::function<void(CardData*)> onHelpClick = nullptr;
	std::map<std::string, PreviewData> previewCache;
};
