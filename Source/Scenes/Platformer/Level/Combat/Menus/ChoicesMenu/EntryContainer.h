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

protected:
	
	EntryContainer(
		cocos2d::Label* normalLabel,
		cocos2d::Label* selectedLabel, 
		cocos2d::Node* nodeNormal,
		cocos2d::Node* nodeSelected);
	virtual ~EntryContainer();

private:
	typedef ClickableTextNode super;
};
