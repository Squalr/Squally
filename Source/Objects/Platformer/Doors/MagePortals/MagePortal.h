#pragma once
#include <set>

#include "Objects/Platformer/Doors/Portal.h"

namespace cocos2d
{
	class DrawNode;
}

class SmartClippingNode;

class MagePortal : public Portal
{
public:
	virtual void closePortal(bool instant);
	virtual void openPortal(bool instant);

protected:
	MagePortal(cocos2d::ValueMap& properties, float portalRadius, cocos2d::Color4B portalBaseColor);
	~MagePortal();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void drawEdge(cocos2d::Color4F edgeColor, cocos2d::DrawNode* drawNode, float radius, int thickness);

	cocos2d::Node* portalEffectNode;

private:
	typedef Portal super;

	SmartClippingNode* portalBase;
	cocos2d::Node* contentNode;
	cocos2d::DrawNode* background;
	cocos2d::DrawNode* edge;
};
