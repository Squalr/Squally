#pragma once
#include "cocos2d.h"
#include "Plushie.h"

using namespace cocos2d;

class PlushieMonkey : public Plushie
{
public:
	static PlushieMonkey* create();

protected:
	PlushieMonkey();
	~PlushieMonkey();

	void update(float) override;
	void registerHackables() override;

private:
	static int puzzleLock;
};
