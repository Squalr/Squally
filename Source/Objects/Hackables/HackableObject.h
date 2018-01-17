#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Components/MenuSprite.h"

using namespace cocos2d;

class HackableObject : public Node
{
public:
	static HackableObject * create(Node* parentNode, std::string previewResource, Vec2 offset);

	static const std::string HackableObjectEditEvent;

	struct HackableObjectEditArgs
	{
		HackableObject* hackableObject;
		std::string previewResource;

		HackableObjectEditArgs(HackableObject* hackableObject, std::string previewResource) : hackableObject(hackableObject), previewResource(previewResource)
		{
		}
	};

	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

private:
	HackableObject(Node* parentNode, std::string previewResource, Vec2 offset);
	~HackableObject();

	void onObjectClick(MenuSprite* menuSprite);

	std::string previewSpriteResource;
	MenuSprite* hackableMenuButton;
	Node* parent;
	Vec2 buttonOffset;
};

