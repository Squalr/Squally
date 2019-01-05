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
	static ClickableTextNode * create(
		cocos2d::Label* normalLabel,
		cocos2d::Label* selectedLabel,
		std::string spriteNormal,
		std::string spriteSelectedResource);
	static ClickableTextNode * create(
		cocos2d::Label* normalLabel,
		cocos2d::Label* selectedLabel,
		cocos2d::Node* spriteNormal,
		std::string spriteSelectedResource);
	static ClickableTextNode * create(
		cocos2d::Label* normalLabel,
		cocos2d::Label* selectedLabel, 
		cocos2d::Node* nodeNormal,
		cocos2d::Node* nodeSelected);

	void setTextOffset(cocos2d::Vec2 offset);

protected:
	ClickableTextNode(
		cocos2d::Label* normalLabel,
		cocos2d::Label* selectedLabel,
		cocos2d::Node* nodeNormal,
		cocos2d::Node* nodeSelected);
	virtual ~ClickableTextNode();

	cocos2d::Label* normalContentLabel;
	cocos2d::Label* selectedContentLabel;
	cocos2d::Node* normalContent;
	cocos2d::Node* selectedContent;

private:
	typedef ClickableNode super;
};
