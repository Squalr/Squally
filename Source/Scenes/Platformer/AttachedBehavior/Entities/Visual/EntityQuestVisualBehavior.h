#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;

class EntityQuestVisualBehavior : public AttachedBehavior
{
public:
	static EntityQuestVisualBehavior* create(GameObject* owner);

	void enableTurnIn();
	void enableNewQuest();
	void enableIncompleteQuest();
	void disableAll();

	static const std::string MapKey;

protected:
	EntityQuestVisualBehavior(GameObject* owner);
	virtual ~EntityQuestVisualBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;

	cocos2d::Node* contentNode;
	cocos2d::Sprite* questToGive;
	cocos2d::Sprite* questTurnIn;
	cocos2d::Sprite* questIncomplete;
};
