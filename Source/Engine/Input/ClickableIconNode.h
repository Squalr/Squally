#pragma once
#include <string>

#include "ClickableNode.h"

namespace cocos2d
{
	class Node;
	class Sprite;
}

class ClickableIconNode : public ClickableNode
{
public:
	static ClickableIconNode * create(
		std::string normalSprite,
		std::string selectedSprite,
		std::string spriteNormal,
		std::string spriteSelectedResource);
	static ClickableIconNode * create(
		cocos2d::Sprite* normalSprite,
		cocos2d::Sprite* selectedSprite,
		std::string spriteNormal,
		std::string spriteSelectedResource);
	static ClickableIconNode * create(
		cocos2d::Sprite* normalSprite,
		cocos2d::Sprite* selectedSprite,
		cocos2d::Node* nodeNormal,
		cocos2d::Node* nodeSelected);

	void setIconOffset(cocos2d::Vec2 offset);

protected:
	typedef ClickableNode super;
	ClickableIconNode(
		cocos2d::Sprite* normalSprite,
		cocos2d::Sprite* selectedSprite,
		cocos2d::Node* nodeNormal,
		cocos2d::Node* nodeSelected);
	virtual ~ClickableIconNode();

	cocos2d::Sprite* normalContentSprite;
	cocos2d::Sprite* selectedContentSprite;
};
