#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class Item;
class LocalizedLabel;
class LocalizedString;

class MenuEntry : public SmartNode
{
public:
	static MenuEntry* create(LocalizedString* text, std::string iconResource);

	void hideIcon();
	void showIcon();

protected:
	MenuEntry(LocalizedString* text, std::string iconResource);
	~MenuEntry();
	void onEnter() override;
	void initializePositions() override;

private:
	typedef SmartNode super;

	cocos2d::Sprite* icon;
	LocalizedLabel* label;

	static const cocos2d::Size LabelSize;
};
