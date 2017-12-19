#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/Utils.h"

using namespace cocos2d;

class MenuSprite : public Node
{
public:
	static MenuSprite * create(std::string spriteResource, std::string spriteSelectedResource, std::string spriteDownResource);
	static MenuSprite * create(std::string spriteResource, std::string spriteSelectedResource, std::string spriteDownResource, std::function<void(MenuSprite*)> onMouseClick);

	MenuSprite(std::string spriteResource, std::string spriteSelectedResource, std::string spriteDownResource);
	MenuSprite(std::string spriteResource, std::string spriteSelectedResource, std::string spriteDownResource, std::function<void(MenuSprite*)> onMouseClick);
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

