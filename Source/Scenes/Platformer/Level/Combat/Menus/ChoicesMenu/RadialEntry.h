#pragma once

#include "Engine/SmartNode.h"

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
	void setContentSize(const cocos2d::Size& size) override;
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
	void toggleAllowInteractionEdits(bool allowInteractionEdits);
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
	bool allowInteractionEdits;
};
