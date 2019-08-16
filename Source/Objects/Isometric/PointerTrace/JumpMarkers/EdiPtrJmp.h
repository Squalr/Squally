#pragma once

#include "Objects/Isometric/PointerTrace/JumpMarkers/JmpMarker.h"

namespace cocos2d
{
	class Sprite;
}

class EdiPtrJmp : public JmpMarker
{
public:
	static EdiPtrJmp* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyEdiPtrJmp;

protected:
	EdiPtrJmp(cocos2d::ValueMap& properties);
	~EdiPtrJmp();

	void onEnter() override;
	void initializePositions() override;
	int getJumpDestination() override;

private:
	typedef JmpMarker super;

	cocos2d::Sprite* marker;
};
