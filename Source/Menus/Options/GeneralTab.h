#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
	class Sprite;
	class Label;
}

class Slider;

class GeneralTab : public SmartNode
{
public:
	static GeneralTab* create();

protected:
	GeneralTab();
	virtual ~GeneralTab();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef SmartNode super;
	
	void onSoundVolumeUpdate(float soundVolume);
	void onMusicVolumeUpdate(float musicVolume);

	cocos2d::Sprite* musicIcon;
	cocos2d::Sprite* soundIcon;
	Slider* musicSlider;
	Slider* soundSlider;
};
