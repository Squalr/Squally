#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Config/SoundManager.h"
#include "Utils/Utils.h"
#include "GUI/Components/Mouse.h"
#include <typeinfo>

using namespace cocos2d;

class MenuSprite : public Node
{
public:
	static MenuSprite * create(std::string spriteResource, std::string spriteSelectedResource, std::string spriteClickedResource);

	void setClickCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseClick);
	void setMouseOverCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseClick);
	void setMouseDownCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseDown);
	void setMouseDragCallback(std::function<void(MenuSprite*, EventMouse* args)> onDrag);
	void setMouseOverSound(std::string soundResource);
	void setClickSound(std::string soundResource);

protected:
	MenuSprite(std::string spriteResource, std::string spriteSelectedResource, std::string spriteClickedResource);
	~MenuSprite();

private:
	void initializeListeners();
	void onMouseSpriteMove(EventCustom* args);
	void onMouseDown(EventMouse* event);
	void onMouseUp(EventMouse* event);

	std::string mouseOverSound;
	std::string clickSound;

	Sprite* sprite;
	Sprite* spriteClicked;
	Sprite* spriteSelected;

	bool isDragging;

	std::function<void(MenuSprite*, EventMouse* args)> mouseClickEvent;
	std::function<void(MenuSprite*, EventMouse* args)> mouseDownEvent;
	std::function<void(MenuSprite*, EventMouse* args)> mouseDragEvent;
	std::function<void(MenuSprite*, EventMouse* args)> mouseOverEvent;
};

