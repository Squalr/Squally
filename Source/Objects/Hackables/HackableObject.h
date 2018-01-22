#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/MenuSprite.h"
#include "Objects/Hackables/HackableData.h"
#include "Objects/Hackables/HackableCode.h"

using namespace cocos2d;

class HackableObject : public Node
{
public:
	struct HackableObjectEditArgs
	{
		HackableObject* hackableObject;
		Sprite* previewSprite;

		HackableObjectEditArgs(HackableObject* hackableObject, Sprite* previewSprite) : hackableObject(hackableObject), previewSprite(previewSprite)
		{
		}
	};

	static const std::string HackableObjectEditEvent;
	void onHackableClick(MenuSprite* menuSprite);
	void bindHackableButton(MenuSprite* hackableButton);

	std::vector<HackableData*>* dataList;
	std::vector<HackableCode*>* codeList;

protected:
	HackableObject();
	~HackableObject();

	void setPreviewImage(std::string previewResource);
	void setButtonOffset(Vec2 offset);
	void registerData(HackableData* hackableData);
	void registerCode(HackableCode* hackableCode);
	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

private:
	MenuSprite * boundHackableButton;
	Sprite * previewSprite;
	Vec2 buttonOffset;
};

