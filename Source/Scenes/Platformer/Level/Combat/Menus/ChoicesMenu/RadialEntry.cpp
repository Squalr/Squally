#include "RadialEntry.h"

#include "Engine/Input/ClickableTextNode.h"

using namespace cocos2d;

RadialEntry* RadialEntry::create(
	cocos2d::Label* label,
	cocos2d::Label* labelSelected,
	std::string spriteResource,
	std::string spriteSelectedResource)
{
	RadialEntry* instance = new RadialEntry(ClickableTextNode::create(label, labelSelected, spriteResource, spriteSelectedResource));

	instance->autorelease();

	return instance;
}

RadialEntry* RadialEntry::create(
	cocos2d::Label* label,
	cocos2d::Label* labelSelected,
	cocos2d::Node* spriteResource,
	std::string spriteSelectedResource)
{
	RadialEntry* instance = new RadialEntry(ClickableTextNode::create(label, labelSelected, spriteResource, spriteSelectedResource));

	instance->autorelease();

	return instance;
}

RadialEntry* RadialEntry::create(
	cocos2d::Label* label,
	cocos2d::Label* labelSelected, 
	cocos2d::Node* content,
	cocos2d::Node* contentSelected)
{
	RadialEntry* instance = new RadialEntry(ClickableTextNode::create(label, labelSelected, content, contentSelected));

	instance->autorelease();

	return instance;
}

RadialEntry::RadialEntry(ClickableTextNode* entry) : super()
{
	this->entry = entry;

	this->addChild(this->entry);
}

RadialEntry::~RadialEntry()
{
}

void RadialEntry::addIcon(cocos2d::Node* icon)
{
	if (icon == nullptr)
	{
		return;
	}

	this->entry->addChild(icon);
}

void RadialEntry::setTextVisible(bool isVisible)
{
	this->entry->setTextVisible(isVisible);
}

void RadialEntry::setTextOffset(cocos2d::Vec2 offset)
{
	this->entry->setTextOffset(offset);
}

bool RadialEntry::canInteract()
{
	return this->entry->canInteract();
}

void RadialEntry::interact()
{
	this->entry->interact();
}

void RadialEntry::setContentSize(const cocos2d::Size & size)
{
	this->entry->setContentSize(size);
}

void RadialEntry::setMouseClickCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseClick)
{
	this->entry->setMouseClickCallback(onMouseClick);
}

void RadialEntry::setMouseInCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseIn)
{
	this->entry->setMouseInCallback(onMouseIn);
}

void RadialEntry::setMouseOverCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseOver)
{
	this->entry->setMouseOverCallback(onMouseOver);
}

void RadialEntry::setMouseOutCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseOut)
{
	this->entry->setMouseOutCallback(onMouseOut);
}

void RadialEntry::setMouseDownCallback(std::function<void(InputEvents::MouseEventArgs* args)> onMouseDown)
{
	this->entry->setMouseDownCallback(onMouseDown);
}

void RadialEntry::setMousePressCallback(std::function<void(InputEvents::MouseEventArgs* args)> mousePressEvent)
{
	this->entry->setMousePressCallback(mousePressEvent);
}

void RadialEntry::setMouseReleaseNoHitTestCallback(std::function<void(InputEvents::MouseEventArgs* args)> mouseReleaseNoHitTestEvent)
{
	this->entry->setMouseReleaseNoHitTestCallback(mouseReleaseNoHitTestEvent);
}

void RadialEntry::setMouseReleaseCallback(std::function<void(InputEvents::MouseEventArgs* args)> mouseReleaseEvent)
{
	this->entry->setMouseReleaseCallback(mouseReleaseEvent);
}

void RadialEntry::setMouseDragCallback(std::function<void(InputEvents::MouseEventArgs* args)> onDrag)
{
	this->entry->setMouseDragCallback(onDrag);
}

void RadialEntry::setMouseScrollCallback(std::function<void(InputEvents::MouseEventArgs* args)> onScroll)
{
	this->entry->setMouseScrollCallback(onScroll);
}

void RadialEntry::setMouseOverSound(std::string soundResource)
{
	this->entry->setMouseOverSound(soundResource);
}

void RadialEntry::setClickSound(std::string soundResource)
{
	this->entry->setClickSound(soundResource);
}

void RadialEntry::setAllowCollisionWhenInvisible(bool allowCollisionWhenInvisible)
{
	this->entry->setAllowCollisionWhenInvisible(allowCollisionWhenInvisible);
}

void RadialEntry::disableInteraction(uint8_t newOpacity)
{
	this->entry->disableInteraction(newOpacity);
}

void RadialEntry::enableInteraction(uint8_t newOpacity)
{
	this->entry->enableInteraction(newOpacity);
}

void RadialEntry::setClickModifier(cocos2d::EventKeyboard::KeyCode modifier)
{
	this->entry->setClickModifier(modifier);
}

cocos2d::Node* RadialEntry::getContent()
{
	return this->entry->getContent();
}

cocos2d::Node* RadialEntry::getContentSelected()
{
	return this->entry->getContentSelected();
}

void RadialEntry::setIntersectFunction(std::function<bool(cocos2d::Vec2 mousePos)> intersectFunction)
{
	this->entry->setIntersectFunction(intersectFunction);
}
