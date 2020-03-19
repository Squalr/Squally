#pragma once

#include "Objects/Isometric/PointerTrace/JumpMarkers/JmpMarker.h"

namespace cocos2d
{
	class Sprite;
}

class EbpJmp : public JmpMarker
{
public:
	static EbpJmp* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	EbpJmp(cocos2d::ValueMap& properties);
	virtual ~EbpJmp();

	void onEnter() override;
	void initializePositions() override;
	int getJumpDestination() override;

private:
	typedef JmpMarker super;

	cocos2d::Sprite* marker;
};
