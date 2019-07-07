#pragma once
#include <string>

#include "cocos/math/Vec2.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ClippingNode;
	class DrawNode;
}

class SmartClippingNode : public SmartNode
{
public:
	static SmartClippingNode* create(cocos2d::Node* contentNode, cocos2d::DrawNode* stencil);

protected:
	SmartClippingNode(cocos2d::Node* contentNode, cocos2d::DrawNode* stencil);
	~SmartClippingNode();

	void onEnter() override;
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;
	
private:
	typedef SmartNode super;

	cocos2d::ClippingNode* clip;
	cocos2d::DrawNode* stencil;
};