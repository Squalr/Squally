#pragma once
#include <queue>

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
class Sound;

class NotificationHud : public Hud
{
public:
	static NotificationHud* create();

protected:
	NotificationHud();
	virtual ~NotificationHud();

	void onEnter() override;
	void update(float dt) override;
	void initializePositions() override;
	void initializeListeners() override;
	void onHackerModeEnable() override;
	void onHackerModeDisable() override;

private:
	typedef Hud super;

	void showNotificationTakeover(LocalizedString* title, LocalizedString* description, std::string soundResource);
	void pushNotification(LocalizedString* title, LocalizedString* description, std::string iconResource, std::string soundResource, bool keepOpen);
	void closeNotificationMenu();

	cocos2d::Node* previousFocus;

	cocos2d::Node* contentNode;
	cocos2d::LayerColor* backdrop;
	cocos2d::Sprite* menuBack;
	ClickableTextNode* okButton;
	LocalizedLabel* title;
	LocalizedLabel* description;
	cocos2d::Node* takeoverNode;
	cocos2d::Node* notificationsNode;
	Sound* notificationSound;

	std::queue<cocos2d::Node*> toProcess;
	std::vector<float> slotCooldowns;

	static const int SlotCount;
	static const float FadeInDuration;
	static const float SustainDuration;
	static const float FadeOutDuration;
	static const float Cooldown;
};
