#pragma once

#include "Engine/Input/ClickableNode.h"

namespace cocos2d
{
	class Label;
	class Node;
}

class ClickableTextNode : public ClickableNode
{
public:
	static ClickableTextNode* create(
		cocos2d::Label* label,
		cocos2d::Label* labelSelected,
		std::string spriteResource,
		std::string spriteSelectedResource);
	static ClickableTextNode* create(
		cocos2d::Label* label,
		cocos2d::Label* labelSelected,
		cocos2d::Node* spriteResource,
		std::string spriteSelectedResource);
	static ClickableTextNode* create(
		cocos2d::Label* label,
		cocos2d::Label* labelSelected, 
		cocos2d::Node* content,
		cocos2d::Node* contentSelected);

	void setTextVisible(bool isVisible);
	void setTextOffset(cocos2d::Vec2 offset);

protected:
	ClickableTextNode(
		cocos2d::Label* label,
		cocos2d::Label* labelSelected,
		cocos2d::Node* content,
		cocos2d::Node* contentSelected);
	virtual ~ClickableTextNode();

	cocos2d::Label* label;
	cocos2d::Label* labelSelected;

private:
	typedef ClickableNode super;
};
