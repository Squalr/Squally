#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/MenuSprite.h"

using namespace cocos2d;

class HackableObject : public Node
{
public:
	static HackableObject * create(Node* parentNode, Vec2 offset);

	static const std::string HackableObjectEditEvent;

	struct HackableObjectEditArgs
	{
		HackableObject* hackableObject;

		HackableObjectEditArgs(HackableObject* hackableObject) : hackableObject(hackableObject)
		{
		}
	};

private:
	HackableObject(Node* parentNode, Vec2 offset);
	~HackableObject();

	void onObjectClick(MenuSprite* menuSprite);
	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

	MenuSprite* hackableMenuButton;
	Node* parent;
	Vec2 buttonOffset;
};

