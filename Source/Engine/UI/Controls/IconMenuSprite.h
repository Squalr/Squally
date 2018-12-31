#pragma once
#include <string>

#include "cocos/math/Vec2.h"

#include "MenuSprite.h"

namespace cocos2d
{
	class Node;
	class Sprite;
}

class IconMenuSprite : public MenuSprite
{
public:
	static IconMenuSprite * create(
		std::string normalSprite,
		std::string selectedSprite,
		std::string spriteNormal,
		std::string spriteSelectedResource);
	static IconMenuSprite * create(
		cocos2d::Sprite* normalSprite,
		cocos2d::Sprite* selectedSprite,
		std::string spriteNormal,
		std::string spriteSelectedResource);
	static IconMenuSprite * create(
		cocos2d::Sprite* normalSprite,
		cocos2d::Sprite* selectedSprite,
		cocos2d::Node* nodeNormal,
		cocos2d::Node* nodeSelected);

	void setIconOffset(cocos2d::Vec2 offset);

protected:
	typedef MenuSprite super;
	IconMenuSprite(
		cocos2d::Sprite* normalSprite,
		cocos2d::Sprite* selectedSprite,
		cocos2d::Node* nodeNormal,
		cocos2d::Node* nodeSelected);
	virtual ~IconMenuSprite();

	cocos2d::Sprite* normalContentSprite;
	cocos2d::Sprite* selectedContentSprite;
};
