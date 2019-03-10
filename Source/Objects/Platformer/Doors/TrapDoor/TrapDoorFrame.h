#pragma once

#include "Engine/Maps/SerializableObject.h"

namespace cocos2d
{
	class Sprite;
}

class TrapDoorFrame : public SerializableObject
{
public:
	static TrapDoorFrame* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTrapDoorFrame;

protected:
	TrapDoorFrame(cocos2d::ValueMap& initProperties);
	virtual ~TrapDoorFrame();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef SerializableObject super;

	bool isFlipped;
	cocos2d::Sprite* trapDoorFrame;
};
