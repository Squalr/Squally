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

	void SetClickCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseClick);
	void SetMouseOverCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseClick);
	void SetMouseDownCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseDown);
	void SetMouseDragCallback(std::function<void(MenuSprite*, EventMouse* args)> onDrag);
	void SetMouseOverSound(std::string soundResource);
	void SetClickSound(std::string soundResource);

protected:
	MenuSprite(std::string spriteResource, std::string spriteSelectedResource, std::string spriteClickedResource);
	~MenuSprite();

private:
	void InitializeListeners();
	void OnMouseSpriteMove(EventCustom* args);
	void OnMouseDown(EventMouse* event);
	void OnMouseUp(EventMouse* event);

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

