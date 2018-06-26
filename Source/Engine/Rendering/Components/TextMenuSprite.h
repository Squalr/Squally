#pragma once
#include <typeinfo>
#include "cocos2d.h"

#include "MenuSprite.h"

using namespace cocos2d;

class TextMenuSprite : public MenuSprite
{
public:
	static TextMenuSprite * create(
		Label* normalLabel,
		Label* selectedLabel,
		Label* clickedLabel,
		std::string spriteNormal,
		std::string spriteSelectedResource,
		std::string spriteClickedResource);
	static TextMenuSprite * create(
		Label* normalLabel,
		Label* selectedLabel,
		Label* clickedLabel, 
		Node* spriteNormal,
		std::string spriteSelectedResource,
		std::string spriteClickedResource);
	static TextMenuSprite * create(
		Label* normalLabel,
		Label* selectedLabel,
		Label* clickedLabel, 
		Node* nodeNormal,
		Node* nodeSelected, 
		Node* nodeClicked);

protected:
	TextMenuSprite(
		Label* normalLabel,
		Label* selectedLabel,
		Label* clickedLabel, 
		Node* nodeNormal,
		Node* nodeSelected,
		Node* nodeClicked);
	~TextMenuSprite();

};

