#pragma once
#include <string>

#include "cocos/base/CCInputEvents.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class DrawNode;
	class EventCustom;
	class EventListenerCustom;
	class Node;
}

class Sound;

class ClickableNode : public SmartNode
{
public:
	static ClickableNode* create();
	static ClickableNode* create(std::string spriteResource, std::string spriteSelectedResource);
	static ClickableNode* create(cocos2d::Node* content, cocos2d::Node* contentSelected);
	
	void interact();
	bool canInteract();
	void setContentSize(const cocos2d::CSize & size) override;
	void setMouseClickCallback(std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> onMouseClick);
	void setMouseInCallback(std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> onMouseIn);
	void setMouseOverCallback(std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> onMouseOver);
	void setMouseOutCallback(std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> onMouseOut);
	void setMouseDownCallback(std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> onMouseDown);
	void setMousePressCallback(std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> mousePressEvent);
	void setMouseReleaseNoHitTestCallback(std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> mouseReleaseNoHitTestEvent);
	void setMouseReleaseCallback(std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> mouseReleaseEvent);
	void setMouseDragCallback(std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> onDrag);
	void setMouseScrollCallback(std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> onScroll);
	void setMouseOverSound(std::string soundResource);
	void setClickSound(std::string soundResource);
	void setAllowCollisionWhenInvisible(bool allowCollisionWhenInvisible);
	virtual void disableInteraction(uint8_t newOpacity = 255);
	virtual void enableInteraction(uint8_t newOpacity = 255);
	void setClickModifier(cocos2d::InputEvents::KeyCode modifier);
	void toggleAllowMouseOutDeselection(bool allowMouseOutDeselection);
	void select();
	void deselect();
	bool isSelected();
	cocos2d::Node* getContent();
	cocos2d::Node* getContentSelected();
	void setIntersectFunction(std::function<bool(cocos2d::Vec2 mousePos)> intersectFunction);
	void neverHandle();

protected:
	ClickableNode(cocos2d::Node* content, cocos2d::Node* contentSelected);
	virtual ~ClickableNode();

	void onEnter() override;
	void initializeListeners() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;

	cocos2d::Node* content = nullptr;
	cocos2d::Node* contentSelected = nullptr;

private:
	typedef SmartNode super;
	void setDebugDrawPosition();
	void showContent(cocos2d::Node* content);
	void clearState();
	void mouseMove(cocos2d::EventCustom* event);
	void mouseDown(cocos2d::EventCustom* event);
	void mouseUp(cocos2d::EventCustom* event);
	void mouseScroll(cocos2d::EventCustom* event);
	void mouseOut(cocos2d::EventCustom* event, bool force = false);
	void mouseHitTest(cocos2d::EventCustom* event);
	bool intersects(cocos2d::Vec2 mousePos);

	Sound* mouseOverSound = nullptr;
	Sound* clickSound = nullptr;
	cocos2d::Node* currentSprite = nullptr;

	bool allowMouseOutDeselection = true;
	bool allowCollisionWhenInvisible = false;
	bool interactionEnabled = true;
	bool wasAnywhereClicked = false;
	bool wasClickedDirectly = false;
	bool isMousedOver = false;
	bool isNeverHandleEnabled = false;
	std::function<bool(cocos2d::Vec2 mousePos)> intersectFunction = nullptr;
	cocos2d::InputEvents::KeyCode modifier;
	cocos2d::DrawNode* debugHitbox = nullptr;
	cocos2d::Vec2 debugCachedPos;

	std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> mouseClickEvent = nullptr;
	std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> mouseInEvent = nullptr;
	std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> mouseDownEvent = nullptr;
	std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> mousePressEvent = nullptr;
	std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> mouseReleaseNoHitTestEvent = nullptr;
	std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> mouseReleaseEvent = nullptr;
	std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> mouseDragEvent = nullptr;
	std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> mouseOverEvent = nullptr;
	std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> mouseOutEvent = nullptr;
	std::function<void(cocos2d::InputEvents::MouseEventArgs* args)> mouseScrollEvent = nullptr;
};
