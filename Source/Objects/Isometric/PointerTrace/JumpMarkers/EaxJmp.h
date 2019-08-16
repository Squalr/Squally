#pragma once

#include "Objects/Isometric/PointerTrace/JumpMarkers/JmpMarker.h"

namespace cocos2d
{
	class Sprite;
}

class EaxJmp : public JmpMarker
{
public:
	static EaxJmp* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyEaxJmp;

protected:
	EaxJmp(cocos2d::ValueMap& properties);
	~EaxJmp();

	void onEnter() override;
	void initializePositions() override;
	int getJumpDestination() override;

private:
	typedef JmpMarker super;

	cocos2d::Sprite* marker;
};
