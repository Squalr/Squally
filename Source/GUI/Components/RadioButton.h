#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/MenuSprite.h"
#include "GUI/Components/RadioButtonGroup.h"

using namespace cocos2d;

class RadioButton : public Node
{
public:
	static RadioButton * create(RadioButtonGroup* group);

	void Check();
	void Uncheck();

protected:
	RadioButton(RadioButtonGroup* group);
	~RadioButton();

private:
	void OnUncheck(MenuSprite* menuSprite);
	void OnCheck(MenuSprite* menuSprite);

	MenuSprite * unchecked;
	MenuSprite * checked;
	RadioButtonGroup * group;

	std::function<void(RadioButton*)> onCheck;
};

