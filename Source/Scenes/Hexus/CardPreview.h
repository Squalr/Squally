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
		Card* previewCard;
		CardData* cardData;
		cocos2d::Node* previewNode;
		ConstantString* binStrRef;
		ConstantString* decStrRef;
		ConstantString* hexStrRef;
		LocalizedLabel* binLabelRef;
		LocalizedLabel* decLabelRef;
		LocalizedLabel* hexLabelRef;

		PreviewData() : previewCard(nullptr), cardData(nullptr), previewNode(nullptr), binStrRef(binStrRef), decStrRef(decStrRef), hexStrRef(hexStrRef) { }
		PreviewData(Card* previewCard, CardData* cardData, cocos2d::Node* previewNode, ConstantString* binStrRef, ConstantString* decStrRef, ConstantString* hexStrRef, LocalizedLabel* binLabelRef, LocalizedLabel* decLabelRef, LocalizedLabel* hexLabelRef)
			: previewCard(previewCard), cardData(cardData), previewNode(previewNode), binStrRef(binStrRef), decStrRef(decStrRef), hexStrRef(hexStrRef), binLabelRef(binLabelRef), decLabelRef(decLabelRef), hexLabelRef(hexLabelRef) { }
	};

	CardPreview::PreviewData constructPreview(CardData* cardData, Card* card);
	void updatePreview(PreviewData previewData);

	cocos2d::Sprite* cardPad;
	PreviewData currentPreviewData;
	cocos2d::Node* previewPanel;
	ClickableTextNode* helpButton;
	
	std::function<void(CardData*)> onHelpClick;
	std::map<std::string, PreviewData> previewCache;
};
