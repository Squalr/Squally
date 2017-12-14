#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/Utils.h"

using namespace cocos2d;

class MenuSprite : public Node
{
public:
	MenuSprite(std::string spriteResource, std::string spriteSelectedResource);
	MenuSprite(std::string spriteResource, std::string spriteSelectedResource, std::function<void(MenuSprite*)> onMouseClick);
	~MenuSprite();

private:
	void onEnter() override;
	void InitializeListeners();
	void OnMouseMove(EventMouse* event);
	void OnMouseDown(EventMouse* event);

	Sprite* sprite;
	Sprite* spriteSelected;
	std::function<void(MenuSprite*)> menuOnMouseClick;
};

