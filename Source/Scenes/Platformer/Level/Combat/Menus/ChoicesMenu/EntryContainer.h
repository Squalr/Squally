#pragma once
#include <string>

#include "Engine/Input/ClickableTextNode.h"

class EntryContainer : public ClickableTextNode
{
public:
	static EntryContainer* create(
		cocos2d::Label* normalLabel,
		cocos2d::Label* selectedLabel, 
		cocos2d::Node* nodeNormal,
		cocos2d::Node* nodeSelected);

	void disable(uint8_t newOpacity = 255);
	void enable();

	void disableInteraction(uint8_t newOpacity = 255) override;
	void enableInteraction(uint8_t newOpacity = 255) override;

protected:
	
	EntryContainer(
		cocos2d::Label* normalLabel,
		cocos2d::Label* selectedLabel, 
		cocos2d::Node* nodeNormal,
		cocos2d::Node* nodeSelected);
	virtual ~EntryContainer();

	bool storedEnabled;
	uint8_t storedOpacity;

private:
	typedef ClickableTextNode super;
};
