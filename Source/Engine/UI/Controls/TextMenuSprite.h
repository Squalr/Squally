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
		std::string spriteNormal,
		std::string spriteSelectedResource);
	static TextMenuSprite * create(
		Label* normalLabel,
		Label* selectedLabel,
		Node* spriteNormal,
		std::string spriteSelectedResource);
	static TextMenuSprite * create(
		Label* normalLabel,
		Label* selectedLabel, 
		Node* nodeNormal,
		Node* nodeSelected);

	void setTextOffset(Vec2 offset);

protected:
	TextMenuSprite(
		Label* normalLabel,
		Label* selectedLabel,
		Node* nodeNormal,
		Node* nodeSelected);
	~TextMenuSprite();

	Label* normalContentLabel;
	Label* selectedContentLabel;
	Node* normalContent;
	Node* selectedContent;
};
