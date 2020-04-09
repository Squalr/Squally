#pragma once

#include "Objects/Isometric/PointerTrace/JumpMarkers/JmpMarker.h"

namespace cocos2d
{
	class Sprite;
}

class EbxPtrJmp : public JmpMarker
{
public:
	static EbxPtrJmp* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	EbxPtrJmp(cocos2d::ValueMap& properties);
	virtual ~EbxPtrJmp();

	void onEnter() override;
	void initializePositions() override;
	int getJumpDestination() override;

private:
	typedef JmpMarker super;

	cocos2d::Sprite* marker;
};
