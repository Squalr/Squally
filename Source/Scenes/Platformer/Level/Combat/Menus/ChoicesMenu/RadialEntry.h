#pragma once

#include "cocos/math/Vec2.h"

#include "Engine/SmartNode.h"
#include "Engine/Events/InputEvents.h"

class ClickableTextNode;
class LocalizedLabel;

class RadialEntry : public SmartNode
{
public:
	static RadialEntry* create(
		LocalizedLabel* label,
		LocalizedLabel* labelSelected,
		std::string spriteResource,
		std::string spriteSelectedResource);
	static RadialEntry* create(
		LocalizedLabel* label,
		LocalizedLabel* labelSelected,
		cocos2d::Node* spriteResource,
		std::string spriteSelectedResource);
	static RadialEntry* create(
		LocalizedLabel* label,
		LocalizedLabel* labelSelected, 
		cocos2d::Node* content,
		cocos2d::Node* contentSelected);

	std::string getIconResource();
	void addIcon(std::string iconResource);

	// ClickableTextNode wrapper
	void setTextVisible(bool isVisible);
	void setTextOffset(cocos2d::Vec2 offset);
	
	// ClickableNode wrapper
	void interact();
	bool canInteract();
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
	cocos2d::Node* getContent();
	cocos2d::Node* getContentSelected();
	void setIntersectFunction(std::function<bool(cocos2d::Vec2 mousePos)> intersectFunction);

protected:
	RadialEntry(ClickableTextNode* entry);
	virtual ~RadialEntry();

private:
	typedef SmartNode super;

	ClickableTextNode* entry;
	std::string iconResource;
};
