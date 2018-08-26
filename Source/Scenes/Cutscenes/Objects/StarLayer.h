#pragma once
#include "cocos2d.h"

#include "Engine/Utils/GameUtils.h"
#include "Resources.h"

using namespace cocos2d;

class StarLayer : public Node
{
public:
	static StarLayer* create();

protected:
	StarLayer();
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

	static std::map<Stars, int> frequencyMap;
};
