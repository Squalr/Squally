#pragma once
#include <queue>

#include "Engine/UI/HUD/Hud.h"

class ConfirmationMenu;
class LocalizedString;

class ConfirmationHud : public Hud
{
public:
	static ConfirmationHud* create();

protected:
	ConfirmationHud();
	virtual ~ConfirmationHud();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void pause() override;
	void onHackerModeEnable() override;
	void onHackerModeDisable() override;

private:
	typedef Hud super;

	void showNotificationTakeover(LocalizedString* title, LocalizedString* description, std::string soundResource);
	void pushNotification(LocalizedString* title, LocalizedString* description, std::string iconResource, std::string soundResource, bool keepOpen);
	void closeNotificationMenu();

	cocos2d::Node* contentNode;
	ConfirmationMenu* confirmationMenu;
};
