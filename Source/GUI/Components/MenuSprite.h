#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/Utils.h"
#include "audio/include/SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class MenuSprite : public Node
{
public:
	static MenuSprite * create(std::string spriteResource, std::string spriteSelectedResource, std::string spriteClickedResource);

	void SetClickCallback(std::function<void(MenuSprite*)> onMouseClick);
	void SetMouseOverCallback(std::function<void(MenuSprite*)> onMouseClick);
	void SetMouseOverSound(std::string soundResource);
	void SetClickSound(std::string soundResource);

protected:
	MenuSprite(std::string spriteResource, std::string spriteSelectedResource, std::string spriteClickedResource);
	~MenuSprite();

private:
	void onEnter() override;
	void InitializeListeners();
	void OnMouseMove(EventMouse* event);
	void OnMouseDown(EventMouse* event);
	void OnMouseUp(EventMouse* event);

	std::string mouseOverSound;
	std::string clickSound;

	Sprite* sprite;
	Sprite* spriteClicked;
	Sprite* spriteSelected;
	std::function<void(MenuSprite*)> menuOnMouseClick;
	std::function<void(MenuSprite*)> menuOnMouseOver;
};

