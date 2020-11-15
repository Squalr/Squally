#pragma once
#include <string>

#include "Engine/SmartNode.h"

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
	static ClickableNode* create(std::string spriteResource, std::string spriteSelectedResource);
	static ClickableNode* create(cocos2d::Node* content, cocos2d::Node* contentSelected);
	
	void interact();
	bool canInteract();
	void setContentSize(const cocos2d::Size & size) override;
	void setMouseClickCallback(std::function<void(MouseEventArgs* args)> onMouseClick);
	void setMouseInCallback(std::function<void(MouseEventArgs* args)> onMouseIn);
	void setMouseOverCallback(std::function<void(MouseEventArgs* args)> onMouseOver);
	void setMouseOutCallback(std::function<void(MouseEventArgs* args)> onMouseOut);
	void setMouseDownCallback(std::function<void(MouseEventArgs* args)> onMouseDown);
	void setMousePressCallback(std::function<void(MouseEventArgs* args)> mousePressEvent);
	void setMouseReleaseNoHitTestCallback(std::function<void(MouseEventArgs* args)> mouseReleaseNoHitTestEvent);
	void setMouseReleaseCallback(std::function<void(MouseEventArgs* args)> mouseReleaseEvent);
	void setMouseDragCallback(std::function<void(MouseEventArgs* args)> onDrag);
	void setMouseScrollCallback(std::function<void(MouseEventArgs* args)> onScroll);
	void setMouseOverSound(std::string soundResource);
	void setClickSound(std::string soundResource);
	void setAllowCollisionWhenInvisible(bool allowCollisionWhenInvisible);
	virtual void disableInteraction(uint8_t newOpacity = 255);
	virtual void enableInteraction(uint8_t newOpacity = 255);
	void setClickModifier(cocos2d::EventKeyboard::KeyCode modifier);
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
	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;

	cocos2d::Node* content;
	cocos2d::Node* contentSelected;

private:
	typedef SmartNode super;
	void setDebugDrawPosition();
	void showContent(cocos2d::Node* content);
	void clearState();
	void mouseMove(MouseEventArgs* args, cocos2d::EventCustom* event = nullptr, bool isRefresh = false);
	void mouseDown(MouseEventArgs* args, cocos2d::EventCustom* event = nullptr);
	void mouseUp(MouseEventArgs* args, cocos2d::EventCustom* event = nullptr);
	void mouseScroll(MouseEventArgs* args, cocos2d::EventCustom* event = nullptr);
	void mouseOut(MouseEventArgs* args, bool force = false);
	bool intersects(cocos2d::Vec2 mousePos);

	Sound* mouseOverSound;
	Sound* clickSound;

	cocos2d::Node* currentSprite;

	bool allowMouseOutDeselection;
	bool allowCollisionWhenInvisible;
	bool interactionEnabled;
	bool wasAnywhereClicked;
	bool wasClickedDirectly;
	bool isMousedOver;
	bool isNeverHandleEnabled;
	std::function<bool(cocos2d::Vec2 mousePos)> intersectFunction;
	cocos2d::EventKeyboard::KeyCode modifier;
	cocos2d::EventListener* modifierReleasedListener;
	cocos2d::DrawNode* debugHitbox;
	cocos2d::Vec2 debugCachedPos;

	std::function<void(MouseEventArgs* args)> mouseClickEvent;
	std::function<void(MouseEventArgs* args)> mouseInEvent;
	std::function<void(MouseEventArgs* args)> mouseDownEvent;
	std::function<void(MouseEventArgs* args)> mousePressEvent;
	std::function<void(MouseEventArgs* args)> mouseReleaseNoHitTestEvent;
	std::function<void(MouseEventArgs* args)> mouseReleaseEvent;
	std::function<void(MouseEventArgs* args)> mouseDragEvent;
	std::function<void(MouseEventArgs* args)> mouseOverEvent;
	std::function<void(MouseEventArgs* args)> mouseOutEvent;
	std::function<void(MouseEventArgs* args)> mouseScrollEvent;
};
