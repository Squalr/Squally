#pragma once

#include "Objects/Isometric/PointerTrace/JumpMarkers/JmpMarker.h"

namespace cocos2d
{
	class Sprite;
}

class EcxPtrJmp : public JmpMarker
{
public:
	static EcxPtrJmp* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	EcxPtrJmp(cocos2d::ValueMap& properties);
	virtual ~EcxPtrJmp();

	void onEnter() override;
	void initializePositions() override;
	int getJumpDestination() override;

private:
	typedef JmpMarker super;

	cocos2d::Sprite* marker;
};
