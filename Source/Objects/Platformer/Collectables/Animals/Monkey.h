#pragma once

#include "Objects/Platformer/Collectables/Animals/Animal.h"
#include "Engine/Localization/ConstantString.h"

class ConstantString;
class LocalizedLabel;

class Monkey : public Animal
{
public:
	static Monkey* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyMonkey;

protected:
	Monkey(cocos2d::ValueMap& initProperties);
	virtual ~Monkey();

	void update(float) override;
	void onEnter() override;
	void registerHackables() override;

private:
	typedef Animal super;
	HackableData* puzzleData;

	void decreaseLockTimer();

	ConstantString* valueString;
	LocalizedLabel* valueLabel;

	int previousValue;
	int previousValueMax;

	static int lockCountDown;
};
