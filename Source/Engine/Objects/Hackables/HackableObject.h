#pragma once
#include "cocos2d.h"

#include "Events/HackableEvents.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Maps/SerializableObject.h"
#include "Engine/Rendering/Components/MenuSprite.h"
#include "Resources.h"

#include "HackableData.h"

using namespace cocos2d;

class HackableObject : public SerializableObject
{
public:
	void onHackableClick(MenuSprite* menuSprite);

	Size size;
	std::vector<HackableData*>* dataList;

	MenuSprite * hackButton;

protected:
	HackableObject(ValueMap* initProperties);
	~HackableObject();

	void pause() override;
	void onEnterTransitionDidFinish() override;
	virtual Vec2 getButtonOffset();
	void registerData(HackableData* hackableData);

	void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags) override;

private:
	Vec2 buttonOffset;
};

