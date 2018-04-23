#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/MenuSprite.h"
#include "Objects/Hackables/HackableData.h"
#include "Events/HackableEvents.h"

using namespace cocos2d;

class HackableObject : public Node
{
public:

	void onHackableClick(MenuSprite* menuSprite);
	void bindHackableButton(MenuSprite* hackableButton);

	Size size;
	std::vector<HackableData*>* dataList;

protected:
	HackableObject();
	~HackableObject();

	void onEnterTransitionDidFinish() override;

	void setButtonOffset(Vec2 offset);
	void registerData(HackableData* hackableData);
	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

private:
	MenuSprite * boundHackableButton;
	Vec2 buttonOffset;
};

