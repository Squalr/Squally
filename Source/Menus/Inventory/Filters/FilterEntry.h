#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class Item;
class LocalizedLabel;
class LocalizedString;

class FilterEntry : public SmartNode
{
public:
	LocalizedString* getLabelString();
	virtual std::vector<Item*> filter(std::vector<Item*> itemList) = 0;

protected:
	FilterEntry(LocalizedString* text, std::string spriteResource);
	~FilterEntry();
	void onEnter() override;
	void initializePositions() override;

private:
	typedef SmartNode super;

	cocos2d::Node* buildMenuLabel(LocalizedString* text, std::string spriteResource);

	cocos2d::Node* labelNode;

	static const cocos2d::Size LabelSize;
};
