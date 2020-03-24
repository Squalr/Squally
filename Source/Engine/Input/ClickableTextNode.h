#pragma once

#include "Engine/Input/ClickableNode.h"

namespace cocos2d
{
	class Node;
}

class LocalizedLabel;

class ClickableTextNode : public ClickableNode
{
public:
	static ClickableTextNode* create(
		LocalizedLabel* label,
		LocalizedLabel* labelSelected,
		std::string spriteResource,
		std::string spriteSelectedResource);
	static ClickableTextNode* create(
		LocalizedLabel* label,
		LocalizedLabel* labelSelected,
		cocos2d::Node* spriteResource,
		std::string spriteSelectedResource);
	static ClickableTextNode* create(
		LocalizedLabel* label,
		LocalizedLabel* labelSelected, 
		cocos2d::Node* content,
		cocos2d::Node* contentSelected);

	void setTextVisible(bool isVisible);
	void setTextOffset(cocos2d::Vec2 offset);

protected:
	ClickableTextNode(
		LocalizedLabel* label,
		LocalizedLabel* labelSelected,
		cocos2d::Node* content,
		cocos2d::Node* contentSelected);
	virtual ~ClickableTextNode();

	LocalizedLabel* label;
	LocalizedLabel* labelSelected;

private:
	typedef ClickableNode super;
};
