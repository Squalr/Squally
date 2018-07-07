#pragma once
#include "cocos2d.h"

#include "Events/HackableEvents.h"
#include "Engine/Maps/SerializableObject.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Resources.h"

#include "HackableData.h"

using namespace cocos2d;

class HackableObject : public SerializableObject
{
public:
	void onHackableClick(MenuSprite* menuSprite);
	void bindHackableButton(MenuSprite* hackableButton);

	Size size;
	std::vector<HackableData*>* dataList;

protected:
	HackableObject(ValueMap* initProperties);
	~HackableObject();

	void onEnterTransitionDidFinish() override;

	void setButtonOffset(Vec2 offset);
	void registerData(HackableData* hackableData);
	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

private:
	MenuSprite * boundHackableButton;
	Vec2 buttonOffset;
};

