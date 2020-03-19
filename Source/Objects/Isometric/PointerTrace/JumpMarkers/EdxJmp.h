#pragma once

#include "Objects/Isometric/PointerTrace/JumpMarkers/JmpMarker.h"

namespace cocos2d
{
	class Sprite;
}

class EdxJmp : public JmpMarker
{
public:
	static EdxJmp* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	EdxJmp(cocos2d::ValueMap& properties);
	virtual ~EdxJmp();

	void onEnter() override;
	void initializePositions() override;
	int getJumpDestination() override;

private:
	typedef JmpMarker super;

	cocos2d::Sprite* marker;
};
