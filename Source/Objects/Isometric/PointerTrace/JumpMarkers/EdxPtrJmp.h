#pragma once

#include "Objects/Isometric/PointerTrace/JumpMarkers/JmpMarker.h"

namespace cocos2d
{
	class Sprite;
}

class EdxPtrJmp : public JmpMarker
{
public:
	static EdxPtrJmp* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyEdxPtrJmp;

protected:
	EdxPtrJmp(cocos2d::ValueMap& initProperties);
	~EdxPtrJmp();

	void onEnter() override;
	void initializePositions() override;
	int getJumpDestination() override;

private:
	typedef JmpMarker super;

	cocos2d::Sprite* marker;
};
