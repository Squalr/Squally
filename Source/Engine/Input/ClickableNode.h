#pragma once
#include <string>

#include "cocos/math/Vec2.h"

#include "Engine/SmartNode.h"
#include "Engine/Events/InputEvents.h"

namespace cocos2d
{
	class DrawNode;
	class EventCustom;
	class EventListener;
	class Node;
}

class Sound;

class ClickableNode : public SmartNode
{
public:
	static ClickableNode* create();
	static ClickableNode* create(std::string spriteNormal, std::string spriteSelectedResource);
	static ClickableNode* create(cocos2d::Node* nodeNormal, cocos2d::Node* nodeSelected);

	void interact();
	void setContentSize(const cocos2d::Size & size) override;
	void setMouseClickCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseClick);
	void setMouseInCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseIn);
	void setMouseOverCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseOver);
	void setMouseOutCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseOut);
	void setMouseDownCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseDown);
	void setMousePressCallback(std::function<void(InputEvents::MouseEventArgs* args)> mousePressEvent);
	void setMouseReleaseNoHitTestCallback(std::function<void(InputEvents::MouseEventArgs* args)> mouseReleaseNoHitTestEvent);
	void setMouseReleaseCallback(std::function<void(InputEvents::MouseEventArgs* args)> mouseReleaseEvent);
	void setMouseDragCallback(std::function<void(InputEvents::MouseEventArgs* args)> onDrag);
	void setMouseScrollCallback(std::function<void(InputEvents::MouseEventArgs* args)> onScroll);
	void setMouseOverSound(std::string soundResource);
	void setClickSound(std::string soundResource);
	void setAllowCollisionWhenInvisible(bool allowCollisionWhenInvisible);
	virtual void disableInteraction(uint8_t newOpacity = 255);
	virtual void enableInteraction(uint8_t newOpacity = 255);
	void setClickModifier(cocos2d::EventKeyboard::KeyCode modifier);
	cocos2d::Node* getSprite();
	cocos2d::Node* getSpriteSelected();
	void setIntersectFunction(std::function<bool(cocos2d::Vec2 mousePos)> intersectFunction);

protected:
	ClickableNode(cocos2d::Node* nodeNormal, cocos2d::Node* nodeSelected);
	virtual ~ClickableNode();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;
	void update(float) override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;

	cocos2d::Node* sprite;
	cocos2d::Node* spriteSelected;

private:
	typedef SmartNode super;
	void setDebugDrawPosition();
	void showSprite(cocos2d::Node* sprite);
	void clearState();
	void mouseMove(InputEvents::MouseEventArgs* args, cocos2d::EventCustom* event = nullptr, bool isRefresh = false);
	void mouseDown(InputEvents::MouseEventArgs* args, cocos2d::EventCustom* event = nullptr);
	void mouseUp(InputEvents::MouseEventArgs* args, cocos2d::EventCustom* event = nullptr);
	void mouseScroll(InputEvents::MouseEventArgs* args, cocos2d::EventCustom* event = nullptr);
	void mouseOut(InputEvents::MouseEventArgs* args, bool force = false);
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
	cocos2d::EventListener* modifierReleasedListener;
	cocos2d::DrawNode* debugHitbox;
	cocos2d::Vec2 debugCachedPos;

	std::function<void(InputEvents::MouseEventArgs* args)> mouseClickEvent;
	std::function<void(InputEvents::MouseEventArgs* args)> mouseInEvent;
	std::function<void(InputEvents::MouseEventArgs* args)> mouseDownEvent;
	std::function<void(InputEvents::MouseEventArgs* args)> mousePressEvent;
	std::function<void(InputEvents::MouseEventArgs* args)> mouseReleaseNoHitTestEvent;
	std::function<void(InputEvents::MouseEventArgs* args)> mouseReleaseEvent;
	std::function<void(InputEvents::MouseEventArgs* args)> mouseDragEvent;
	std::function<void(InputEvents::MouseEventArgs* args)> mouseOverEvent;
	std::function<void(InputEvents::MouseEventArgs* args)> mouseOutEvent;
	std::function<void(InputEvents::MouseEventArgs* args)> mouseScrollEvent;
};
