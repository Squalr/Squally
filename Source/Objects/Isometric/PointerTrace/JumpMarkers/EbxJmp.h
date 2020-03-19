#pragma once

#include "Objects/Isometric/PointerTrace/JumpMarkers/JmpMarker.h"

namespace cocos2d
{
	class Sprite;
}

class EbxJmp : public JmpMarker
{
public:
	static EbxJmp* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	EbxJmp(cocos2d::ValueMap& properties);
	virtual ~EbxJmp();

	void onEnter() override;
	void initializePositions() override;
	int getJumpDestination() override;

private:
	typedef JmpMarker super;

	cocos2d::Sprite* marker;
};
