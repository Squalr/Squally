#pragma once

#include "Objects/Isometric/PointerTrace/JumpMarkers/JmpMarker.h"

namespace cocos2d
{
	class Sprite;
}

class EcxJmp : public JmpMarker
{
public:
	static EcxJmp* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	EcxJmp(cocos2d::ValueMap& properties);
	virtual ~EcxJmp();

	void onEnter() override;
	void initializePositions() override;
	int getJumpDestination() override;

private:
	typedef JmpMarker super;

	cocos2d::Sprite* marker;
};
