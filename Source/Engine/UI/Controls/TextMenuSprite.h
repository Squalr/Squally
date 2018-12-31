#pragma once
#include "cocos/math/Vec2.h"

#include "MenuSprite.h"

namespace cocos2d
{
	class Label;
	class Node;
}

class TextMenuSprite : public MenuSprite
{
public:
	static TextMenuSprite * create(
		cocos2d::Label* normalLabel,
		cocos2d::Label* selectedLabel,
		std::string spriteNormal,
		std::string spriteSelectedResource);
	static TextMenuSprite * create(
		cocos2d::Label* normalLabel,
		cocos2d::Label* selectedLabel,
		cocos2d::Node* spriteNormal,
		std::string spriteSelectedResource);
	static TextMenuSprite * create(
		cocos2d::Label* normalLabel,
		cocos2d::Label* selectedLabel, 
		cocos2d::Node* nodeNormal,
		cocos2d::Node* nodeSelected);

	void setTextOffset(cocos2d::Vec2 offset);

protected:
	TextMenuSprite(
		cocos2d::Label* normalLabel,
		cocos2d::Label* selectedLabel,
		cocos2d::Node* nodeNormal,
		cocos2d::Node* nodeSelected);
	virtual ~TextMenuSprite();

	cocos2d::Label* normalContentLabel;
	cocos2d::Label* selectedContentLabel;
	cocos2d::Node* normalContent;
	cocos2d::Node* selectedContent;

private:
	typedef MenuSprite super;
};
