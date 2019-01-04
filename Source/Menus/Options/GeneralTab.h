#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
	class Sprite;
	class Label;
}

class CSlider;

class GeneralTab : public SmartNode
{
public:
	static GeneralTab* create();

protected:
	GeneralTab();
	~GeneralTab();

private:
	typedef SmartNode super;

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;
	void onSoundVolumeUpdate(float soundVolume);
	void onMusicVolumeUpdate(float musicVolume);

	cocos2d::Sprite* musicIcon;
	cocos2d::Sprite* soundIcon;
	CSlider* musicSlider;
	CSlider* soundSlider;
};
