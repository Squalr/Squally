#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class HexusOpponentData;
class LocalizedString;
class PlatformerEntity;

class HexusBehaviorBase : public AttachedBehavior
{
public:
	virtual HexusOpponentData* createOpponentData() = 0;

protected:
	HexusBehaviorBase(GameObject* owner, LocalizedString* dialogueChoiceOverride = nullptr);
	~HexusBehaviorBase();

	void onLoad() override;
	void onWin();
	void onLoss();
	void onDraw();

	PlatformerEntity* entity;

private:
	typedef AttachedBehavior super;

	LocalizedString* dialogueChoiceOverride;
};
