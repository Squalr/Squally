#pragma once
#include <set>

#include "Objects/Platformer/Doors/Portal.h"

class MagePortal : public Portal
{
public:

protected:
	MagePortal(cocos2d::ValueMap& properties);
	~MagePortal();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Node* contentNode;

private:
	typedef Portal super;
};
