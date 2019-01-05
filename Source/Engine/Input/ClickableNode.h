#pragma once
#include <string>

#include "cocos/math/Vec2.h"

#include "Engine/SmartNode.h"
#include "Engine/Events/MouseEvents.h"

namespace cocos2d
{
	class EventCustom;
	class Node;
}

class ClickableNode : public SmartNode
{
public:
	static ClickableNode * create(std::string spriteNormal, std::string spriteSelectedResource);
	static ClickableNode * create(cocos2d::Node* nodeNormal, cocos2d::Node* nodeSelected);

	void setContentScale(float scale);
	void setOffsetCorrection(cocos2d::Vec2 newOffsetCorrection);
	void setClickCallback(std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> onMouseClick);
	void setMouseOverCallback(std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> onMouseClick);
	void setMouseOutCallback(std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> onMouseOut);
	void setMouseDownCallback(std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> onMouseDown);
	void setMouseDragCallback(std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> onDrag);
	void setMouseOverSound(std::string soundResource);
	void setClickSound(std::string soundResource);
	void disableInteraction(uint8_t newOpacity = 255);
	void enableInteraction(uint8_t newOpacity = 255);
	void setClickModifier(cocos2d::EventKeyboard::KeyCode modifier);

protected:
	ClickableNode(cocos2d::Node* nodeNormal, cocos2d::Node* nodeSelected);
	virtual ~ClickableNode();

	cocos2d::Node* sprite;
	cocos2d::Node* spriteSelected;

private:
	typedef SmartNode super;
	void initializeListeners() override;
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void update(float) override;
	bool intersects(cocos2d::Vec2 mousePos);
	void showSprite(cocos2d::Node* sprite);
	void onMouseMove(cocos2d::EventCustom* event);
	void onMouseRefresh(cocos2d::EventCustom* event);
	void onMouseDown(cocos2d::EventCustom* event);
	void onMouseUp(cocos2d::EventCustom* event);
	void mouseMove(MouseEvents::MouseEventArgs* args, cocos2d::EventCustom* event = nullptr, bool isRefresh = false);
	void mouseDown(MouseEvents::MouseEventArgs* args, cocos2d::EventCustom* event = nullptr);
	void mouseUp(MouseEvents::MouseEventArgs* args, cocos2d::EventCustom* event = nullptr);

	std::string mouseOverSound;
	std::string clickSound;

	cocos2d::Node* currentSprite;
	cocos2d::Vec2 offsetCorrection;

	bool interactionEnabled;
	bool isClickInit;
	bool isClicked;
	bool isMousedOver;
	cocos2d::EventKeyboard::KeyCode modifier;

	std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> mouseClickEvent;
	std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> mouseDownEvent;
	std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> mouseDragEvent;
	std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> mouseOverEvent;
	std::function<void(ClickableNode*, MouseEvents::MouseEventArgs* args)> mouseOutEvent;
};

