#pragma once
#include "cocos2d.h"
#include "Plushie.h"

using namespace cocos2d;

class Plushie1 : public Plushie
{
public:
	static Plushie1* create();

protected:
	void update(float) override;

protected:
	Plushie1();
	~Plushie1();
};
