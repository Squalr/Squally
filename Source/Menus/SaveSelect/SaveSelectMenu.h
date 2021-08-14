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
	virtual ~SaveSelectMenu();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef GlobalScene super;

	void buildSaveButtons();
	ClickableTextNode* buildSaveButton(int profileId);
	ClickableNode* buildDeleteButton(int profileId);
	cocos2d::Node* buildSaveGameContent(int profileId);
	cocos2d::Node* buildEntityFrame(PlatformerEntity* entity, cocos2d::Vec2 offsetAdjustment, int eq);
	cocos2d::Sprite* getBackgroundForCurrentSaveProfile();
	void loadSave();
	void goBack();

	cocos2d::Node* backgroundNode = nullptr;
	cocos2d::Sprite* saveSelectWindow = nullptr;
	cocos2d::Node* saveButtonNode = nullptr;
	ClickableTextNode* saveGameButton0 = nullptr;
	ClickableTextNode* saveGameButton1 = nullptr;
	ClickableTextNode* saveGameButton2 = nullptr;
	ClickableNode* closeButton = nullptr;
	ClickableTextNode* returnButton = nullptr;
	LocalizedLabel* titleLabel = nullptr;
	ConfirmationMenu* confirmationMenu = nullptr;
	PlatformerEntityDeserializer* platformerEntityDeserializer = nullptr;

	static SaveSelectMenu* instance;
};
