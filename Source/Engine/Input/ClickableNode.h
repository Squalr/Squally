#pragma once
#include <string>

#include "cocos/math/Vec2.h"

#include "Engine/SmartNode.h"
#include "Engine/Events/MouseEvents.h"

namespace cocos2d
{
	class DrawNode;
	class EventCustom;
	class Node;
}

class Sound;

class ClickableNode : public SmartNode
{
public:
	static ClickableNode* create();
	static ClickableNode* create(std::string spriteNormal, std::string spriteSelectedResource);
	static ClickableNode* create(cocos2d::Node* nodeNormal, cocos2d::Node* nodeSelected);

	void setContentSize(const cocos2d::Size & size) override;
	void setMouseClickCallback(std::function<void(MouseEvents::MouseEventArgs* args)> onMouseClick);
	void setMouseInCallback(std::function<void(MouseEvents::MouseEventArgs* args)> onMouseIn);
	void setMouseOverCallback(std::function<void(MouseEvents::MouseEventArgs* args)> onMouseOver);
	void setMouseOutCallback(std::function<void(MouseEvents::MouseEventArgs* args)> onMouseOut);
	void setMouseDownCallback(std::function<void(MouseEvents::MouseEventArgs* args)> onMouseDown);
	void setMousePressCallback(std::function<void(MouseEvents::MouseEventArgs* args)> mousePressEvent);
	void setMouseReleaseNoHitTestCallback(std::function<void(MouseEvents::MouseEventArgs* args)> mouseReleaseNoHitTestEvent);
	void setMouseReleaseCallback(std::function<void(MouseEvents::MouseEventArgs* args)> mouseReleaseEvent);
	void setMouseDragCallback(std::function<void(MouseEvents::MouseEventArgs* args)> onDrag);
	void setMouseScrollCallback(std::function<void(MouseEvents::MouseEventArgs* args)> onScroll);
	void setMouseOverSound(std::string soundResource);
	void setClickSound(std::string soundResource);
	void setAllowCollisionWhenInvisible(bool allowCollisionWhenInvisible);
	void disableInteraction(uint8_t newOpacity = 255);
	void enableInteraction(uint8_t newOpacity = 255);
	void setClickModifier(cocos2d::EventKeyboard::KeyCode modifier);
	cocos2d::Node* getSprite();
	cocos2d::Node* getSpriteSelected();
	void setIntersectFunction(std::function<bool(cocos2d::Vec2 mousePos)> intersectFunction);

protected:
	ClickableNode(cocos2d::Node* nodeNormal, cocos2d::Node* nodeSelected);
	virtual ~ClickableNode();

	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;

	cocos2d::Node* sprite;
	cocos2d::Node* spriteSelected;

private:
	typedef SmartNode super;
	void initializeListeners() override;
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void update(float) override;
	void setDebugDrawPosition();
	void showSprite(cocos2d::Node* sprite);
	void clearState();
	void mouseMove(MouseEvents::MouseEventArgs* args, cocos2d::EventCustom* event = nullptr, bool isRefresh = false);
	void mouseDown(MouseEvents::MouseEventArgs* args, cocos2d::EventCustom* event = nullptr);
	void mouseUp(MouseEvents::MouseEventArgs* args, cocos2d::EventCustom* event = nullptr);
	void mouseScroll(MouseEvents::MouseEventArgs* args, cocos2d::EventCustom* event = nullptr);
	bool intersects(cocos2d::Vec2 mousePos);

	Sound* mouseOverSound;
	Sound* clickSound;

	cocos2d::Node* currentSprite;

	bool allowCollisionWhenInvisible;
	bool interactionEnabled;
	bool wasAnywhereClicked;
	bool wasClickedDirectly;
	bool isMousedOver;
	std::function<bool(cocos2d::Vec2 mousePos)> intersectFunction;
	cocos2d::EventKeyboard::KeyCode modifier;
	cocos2d::DrawNode* debugHitbox;
	cocos2d::Vec2 debugCachedPos;

	std::function<void(MouseEvents::MouseEventArgs* args)> mouseClickEvent;
	std::function<void(MouseEvents::MouseEventArgs* args)> mouseInEvent;
	std::function<void(MouseEvents::MouseEventArgs* args)> mouseDownEvent;
	std::function<void(MouseEvents::MouseEventArgs* args)> mousePressEvent;
	std::function<void(MouseEvents::MouseEventArgs* args)> mouseReleaseNoHitTestEvent;
	std::function<void(MouseEvents::MouseEventArgs* args)> mouseReleaseEvent;
	std::function<void(MouseEvents::MouseEventArgs* args)> mouseDragEvent;
	std::function<void(MouseEvents::MouseEventArgs* args)> mouseOverEvent;
	std::function<void(MouseEvents::MouseEventArgs* args)> mouseOutEvent;
	std::function<void(MouseEvents::MouseEventArgs* args)> mouseScrollEvent;
};
