#pragma once

#include "Engine/SmartNode.h"

class StarLayer : public SmartNode
{
public:
	static StarLayer* create(cocos2d::Vec2 size);

protected:
	StarLayer(cocos2d::Vec2 size);
	~StarLayer();

private:
	void onEnter() override;
	void createStars();

	enum Stars {
		StarSmall,
		StarMedium,
		StarLarge,
		StarShineSmall,
		StarShineSmallHallow,
		StarShineLarge,
		StarShineExtraLarge,
	};

	cocos2d::Size layerSize;

	static std::map<Stars, int> frequencyMap;
};
