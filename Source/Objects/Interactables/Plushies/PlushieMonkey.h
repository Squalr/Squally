#pragma once
#include "cocos2d.h"
#include "Plushie.h"

using namespace cocos2d;

class PlushieMonkey : public Plushie
{
public:
	static PlushieMonkey* create();

protected:
	void update(float) override;

protected:
	PlushieMonkey();
	~PlushieMonkey();

	void registerHackables() override;
};
