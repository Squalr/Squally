#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class SmartAnimationSequenceNode;

class AddDoorPreview : public HackablePreview
{
public:
	static AddDoorPreview* create();

	HackablePreview* clone() override;

protected:
	AddDoorPreview();
	virtual ~AddDoorPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
