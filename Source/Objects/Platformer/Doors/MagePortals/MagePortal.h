#pragma once
#include <set>

#include "Objects/Platformer/Doors/Portal.h"

namespace cocos2d
{
	class DrawNode;
}

class MagePortal : public Portal
{
public:

protected:
	MagePortal(cocos2d::ValueMap& properties);
	~MagePortal();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void drawEdge(cocos2d::Color4F edgeColor, cocos2d::DrawNode* drawNode, float radius, int thickness);

	cocos2d::Node* contentNode;

private:
	typedef Portal super;
};
