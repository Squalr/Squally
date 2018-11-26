#pragma once
#include <typeinfo>
#include "cocos2d.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/SmartNode.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

class MenuSprite : public SmartNode
{
public:
	static MenuSprite * create(std::string spriteNormal, std::string spriteSelectedResource);
	static MenuSprite * create(Node* nodeNormal, Node* nodeSelected);

	void setContentScale(float scale);
	void setOffsetCorrection(Vec2 newOffsetCorrection);
	void setClickCallback(std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> onMouseClick);
	void setMouseOverCallback(std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> onMouseClick);
	void setMouseOutCallback(std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> onMouseOut);
	void setMouseDownCallback(std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> onMouseDown);
	void setMouseDragCallback(std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> onDrag);
	void setMouseOverSound(std::string soundResource);
	void setClickSound(std::string soundResource);
	void disableInteraction(GLubyte newOpacity = 255);
	void enableInteraction(GLubyte newOpacity = 255);

protected:
	MenuSprite(Node* nodeNormal, Node* nodeSelected);
	~MenuSprite();

	Node* sprite;
	Node* spriteSelected;

private:
	void initializeListeners() override;
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void update(float) override;
	bool intersects(Vec2 mousePos);
	void showSprite(Node* sprite);
	void onMouseMove(EventCustom* event);
	void onMouseRefresh(EventCustom* event);
	void onMouseDown(EventCustom* event);
	void onMouseUp(EventCustom* event);
	void mouseMove(MouseEvents::MouseEventArgs* args, EventCustom* event = nullptr, bool isRefresh = false);
	void mouseDown(MouseEvents::MouseEventArgs* args, EventCustom* event = nullptr);
	void mouseUp(MouseEvents::MouseEventArgs* args, EventCustom* event = nullptr);

	std::string mouseOverSound;
	std::string clickSound;

	Node* currentSprite;
	Vec2 offsetCorrection;

	bool interactionEnabled;
	bool isClickInit;
	bool isClicked;
	bool isMousedOver;

	std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> mouseClickEvent;
	std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> mouseDownEvent;
	std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> mouseDragEvent;
	std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> mouseOverEvent;
	std::function<void(MenuSprite*, MouseEvents::MouseEventArgs* args)> mouseOutEvent;
};

