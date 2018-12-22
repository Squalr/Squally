#pragma once
#include "cocos2d.h"

#include "Engine/Cutscenes/CutsceneClip.h"

namespace cocos2d
{
	class Label;
	class LayerColor;
	class Sprite;
}

class DialogueLabel;
class FlyingCar;
class InfiniteParallaxNode;
class StarLayer;

class NeonCity : public CutsceneClip
{
public:
	enum NeonCityScene {
		Intro,
		Return,
		Singularity
	};

	static NeonCity* create(NeonCityScene neonCityScene);

protected:
	NeonCity(NeonCityScene neonCityScene);
	~NeonCity();

private:
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	void cutscenePan();
	void onDialogueShown();

	NeonCityScene activeScene;

	cocos2d::LayerGradient* sky;
	cocos2d::LayerColor* darkFilter;
	StarLayer* starLayer;
	InfiniteParallaxNode* cityBackground;
	InfiniteParallaxNode* cityMidground;
	cocos2d::Sprite* vaporCorp;
	FlyingCar* junker1;
	FlyingCar* viper1;
	FlyingCar* viper2;
	FlyingCar* propeller1;
	InfiniteParallaxNode* cityForeground;

	cocos2d::LayerColor* dialoguePlate;
	DialogueLabel* dialogue;
	cocos2d::Label* escapeLabel;

	static const float vaporCorpOffset;
};
