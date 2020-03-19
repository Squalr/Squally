#pragma once

#include "Objects/Isometric/PointerTrace/JumpMarkers/JmpMarker.h"

namespace cocos2d
{
	class Sprite;
}

class EsiJmp : public JmpMarker
{
public:
	static EsiJmp* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	EsiJmp(cocos2d::ValueMap& properties);
	virtual ~EsiJmp();

	void onEnter() override;
	void initializePositions() override;
	int getJumpDestination() override;

private:
	typedef JmpMarker super;

	cocos2d::Sprite* marker;
};
