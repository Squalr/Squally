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

	void showNotificationTakeover(LocalizedString* title, LocalizedString* description, std::string soundResource, bool showBackground);
	void pushNotification(LocalizedString* title, LocalizedString* description, std::string iconResource, std::string soundResource, bool keepOpen);
	void closeNotificationMenu();

	cocos2d::Node* previousFocus = nullptr;
	cocos2d::Node* contentNode = nullptr;
	cocos2d::LayerColor* backdrop = nullptr;
	cocos2d::Sprite* menuBack = nullptr;
	ClickableTextNode* okButton = nullptr;
	LocalizedLabel* title = nullptr;
	LocalizedLabel* description = nullptr;
	cocos2d::Node* takeoverNode = nullptr;
	cocos2d::Node* notificationsNode = nullptr;
	Sound* notificationSound = nullptr;

	std::queue<std::tuple<cocos2d::Node*, bool>> toProcess;
	std::vector<float> slotCooldowns;

	static const int SlotCount;
	static const float FadeInDuration;
	static const float SustainDuration;
	static const float FadeOutDuration;
	static const float Cooldown;
};
