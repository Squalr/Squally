#pragma once

#include "Objects/Isometric/PointerTrace/JumpMarkers/JmpMarker.h"

namespace cocos2d
{
	class Sprite;
}

class EspJmp : public JmpMarker
{
public:
	static EspJmp* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyEspJmp;

protected:
	EspJmp(cocos2d::ValueMap& initProperties);
	~EspJmp();

	void onEnter() override;
	void initializePositions() override;
	int getJumpDestination() override;

private:
	typedef JmpMarker super;

	cocos2d::Sprite* marker;
};
