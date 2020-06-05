#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class SmartClippingNode;
class WorldSound;

class WarpGate : public Portal
{
public:
	virtual void closePortal(bool instant);
	virtual void openPortal(bool instant);

	static const std::string TagWarpGate;

protected:
	WarpGate(cocos2d::ValueMap& properties);
	virtual ~WarpGate();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Node* portalEffectNode;

private:
	typedef Portal super;

	SmartClippingNode* portalClip;
	cocos2d::Node* contentNode;
	cocos2d::Sprite* doorFrame;
	WorldSound* portalOpenSound;
};
