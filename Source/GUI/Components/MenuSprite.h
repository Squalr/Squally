#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Config/SoundManager.h"
#include "GUI/Components/Mouse.h"
#include "Utils/GameUtils.h"
#include <typeinfo>

using namespace cocos2d;

class MenuSprite : public Node
{
public:
	static MenuSprite * create(std::string spriteNormal, std::string spriteSelectedResource, std::string spriteClickedResource);
	static MenuSprite * create(Node* spriteNormal, std::string spriteSelectedResource, std::string spriteClickedResource);
	static MenuSprite * create(Node* nodeNormal, Node* nodeSelected, Node* nodeClicked);

	void setClickCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseClick);
	void setMouseOverCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseClick);
	void setMouseDownCallback(std::function<void(MenuSprite*, EventMouse* args)> onMouseDown);
	void setMouseDragCallback(std::function<void(MenuSprite*, EventMouse* args)> onDrag);
	void setMouseOverSound(std::string soundResource);
	void setClickSound(std::string soundResource);

protected:
	MenuSprite(Node* nodeNormal, Node* nodeSelected, Node* nodeClicked);
	~MenuSprite();

private:
	void initializeListeners();
	void onEnter() override;
	void update(float) override;
	bool intersects(Vec2 mousePos);
	void onMouseSpriteMove(EventCustom* args);
	void onMouseDown(EventMouse* event);
	void onMouseUp(EventMouse* event);

	std::string mouseOverSound;
	std::string clickSound;

	Node* sprite;
	Node* spriteClicked;
	Node* spriteSelected;

	bool isClickInit;
	bool isClicked;

	std::function<void(MenuSprite*, EventMouse* args)> mouseClickEvent;
	std::function<void(MenuSprite*, EventMouse* args)> mouseDownEvent;
	std::function<void(MenuSprite*, EventMouse* args)> mouseDragEvent;
	std::function<void(MenuSprite*, EventMouse* args)> mouseOverEvent;
};

