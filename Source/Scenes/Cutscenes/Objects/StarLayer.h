#pragma once
#include "cocos2d.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

class StarLayer : public Node
{
public:
	static StarLayer* create(Vec2 size);

protected:
	StarLayer(Vec2 size);
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

	Size layerSize;

	static std::map<Stars, int> frequencyMap;
};
