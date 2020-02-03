#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class LocalizedLabel;
class LocalizedString;
class PlatformerEntity;

class EntityTextOverlayBehavior : public AttachedBehavior
{
public:
	static EntityTextOverlayBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityTextOverlayBehavior(GameObject* owner);
	virtual ~EntityTextOverlayBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void runLabelOverEntity(PlatformerEntity* target, LocalizedLabel* label);

	struct TextOverlay
	{
		LocalizedString* overlayString;
		LocalizedLabel* overlayLabel;

		TextOverlay(LocalizedString* overlayString, LocalizedLabel* overlayLabel) : overlayString(overlayString), overlayLabel(overlayLabel) { }
	};

	PlatformerEntity* entity;
	cocos2d::Node* contentNode;
	std::vector<TextOverlay> textOverlays;

	static const int MaxOverlays;
};
