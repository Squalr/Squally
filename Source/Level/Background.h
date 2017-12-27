#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Player/Player.h"
#include "GUI/Components/InfiniteParallaxNode.h"

using namespace cocos2d;

class Background : public Layer
{
public:
	static Background * create();

	void update(float) override;

protected:
	Background();
	~Background();
	Sprite * background;

private:
	InfiniteParallaxNode * clouds;
	ParallaxNode * mountains;
	ParallaxNode * mountains2;
	ParallaxNode * trees1;
	ParallaxNode * trees2;
	ParallaxNode * trees3;
};

