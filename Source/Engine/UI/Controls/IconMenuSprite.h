#pragma once
#include <typeinfo>
#include "cocos2d.h"

#include "MenuSprite.h"

using namespace cocos2d;

class IconMenuSprite : public MenuSprite
{
public:
	static IconMenuSprite * create(
		std::string normalSprite,
		std::string selectedSprite,
		std::string spriteNormal,
		std::string spriteSelectedResource);
	static IconMenuSprite * create(
		Sprite* normalSprite,
		Sprite* selectedSprite,
		std::string spriteNormal,
		std::string spriteSelectedResource);
	static IconMenuSprite * create(
		Sprite* normalSprite,
		Sprite* selectedSprite,
		Node* nodeNormal,
		Node* nodeSelected);

	void setIconOffset(Vec2 offset);

protected:
	IconMenuSprite(
		Sprite* normalSprite,
		Sprite* selectedSprite,
		Node* nodeNormal,
		Node* nodeSelected);
	~IconMenuSprite();

	Sprite* normalContentSprite;
	Sprite* selectedContentSprite;
};
