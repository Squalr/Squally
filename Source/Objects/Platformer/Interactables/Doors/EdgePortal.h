#pragma once
#include <set>

#include "Objects/Platformer/Interactables/Doors/Portal.h"

class EdgePortal : public Portal
{
public:
	static EdgePortal* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyEdgePortal;

protected:
	EdgePortal(cocos2d::ValueMap& properties);
	~EdgePortal();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef Portal super;
};
