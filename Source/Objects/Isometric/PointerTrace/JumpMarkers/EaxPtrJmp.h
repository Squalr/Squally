#pragma once

#include "Objects/Isometric/PointerTrace/JumpMarkers/JmpMarker.h"

namespace cocos2d
{
	class Sprite;
}

class EaxPtrJmp : public JmpMarker
{
public:
	static EaxPtrJmp* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	EaxPtrJmp(cocos2d::ValueMap& properties);
	virtual ~EaxPtrJmp();

	void onEnter() override;
	void initializePositions() override;
	int getJumpDestination() override;

private:
	typedef JmpMarker super;

	cocos2d::Sprite* marker;
};
