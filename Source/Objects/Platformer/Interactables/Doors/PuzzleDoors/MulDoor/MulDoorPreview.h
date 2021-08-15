#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class SmartAnimationSequenceNode;

class MulDoorPreview : public HackablePreview
{
public:
	static MulDoorPreview* create();

	HackablePreview* clone() override;

protected:
	MulDoorPreview();
	virtual ~MulDoorPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
