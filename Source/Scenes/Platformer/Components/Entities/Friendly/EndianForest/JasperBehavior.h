#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class JasperBehavior : public GameComponent
{
public:
	static JasperBehavior* create(GameObject* owner);

	static const std::string MapKey;
	static const std::string SaveKeyItemGiven;

protected:
	JasperBehavior(GameObject* owner);
	virtual ~JasperBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
