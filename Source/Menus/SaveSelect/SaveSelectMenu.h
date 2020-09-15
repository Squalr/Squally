#pragma once

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;
class ClickableTextNode;
class ConfirmationMenu;
class LocalizedLabel;
class PlatformerEntity;
class PlatformerEntityDeserializer;

class SaveSelectMenu : public GlobalScene
{
public:
	static SaveSelectMenu* getInstance();

protected:
	SaveSelectMenu();
	~SaveSelectMenu();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

	void buildSaveButtons();
	ClickableTextNode* buildSaveButton(int profileId);
	ClickableNode* buildDeleteButton(int profileId);
	cocos2d::Node* buildSaveGameContent(int profileId);
	cocos2d::Node* buildEntityFrame(PlatformerEntity* entity, cocos2d::Vec2 offsetAdjustment, int eq);
	cocos2d::Sprite* getBackgroundForCurrentSaveProfile();
	void loadSave();
	void goBack();

	cocos2d::Node* backgroundNode;
	cocos2d::Sprite* saveSelectWindow;
	cocos2d::Node* saveButtonNode;
	ClickableTextNode* saveGameButton0;
	ClickableTextNode* saveGameButton1;
	ClickableTextNode* saveGameButton2;
	ClickableNode* closeButton;
	ClickableTextNode* returnButton;
	LocalizedLabel* titleLabel;
	ConfirmationMenu* confirmationMenu;
	PlatformerEntityDeserializer* platformerEntityDeserializer;

	static SaveSelectMenu* instance;
};
