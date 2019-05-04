#pragma once

#include "Objects/Isometric/PointerTrace/JumpMarkers/JmpMarker.h"

namespace cocos2d
{
	class Sprite;
}

class EspPtrJmp : public JmpMarker
{
public:
	static EspPtrJmp* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyEspPtrJmp;

protected:
	EspPtrJmp(cocos2d::ValueMap& initProperties);
	~EspPtrJmp();

	void onEnter() override;
	void initializePositions() override;
	int getJumpDestination() override;

private:
	typedef JmpMarker super;

	cocos2d::Sprite* marker;
};
