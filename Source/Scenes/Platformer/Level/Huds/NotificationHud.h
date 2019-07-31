#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class LayerColor;
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;
class LocalizedString;
class PlatformerEntity;

class NotificationHud : public Hud
{
public:
	static NotificationHud* create();

private:
	typedef Hud super;
	NotificationHud();
	~NotificationHud();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	void showNotificationMenu(LocalizedString* title, LocalizedString* description);

	cocos2d::Node* previousFocus;

	cocos2d::LayerColor* backdrop;
	cocos2d::Sprite* menuBack;
	ClickableTextNode* okButton;
	LocalizedLabel* title;
	LocalizedLabel* description;
};
