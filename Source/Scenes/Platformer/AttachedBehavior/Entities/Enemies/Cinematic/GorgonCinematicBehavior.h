#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Gorgon;

class GorgonCinematicBehavior : public AttachedBehavior
{
public:
	static GorgonCinematicBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	GorgonCinematicBehavior(GameObject* owner);
	virtual ~GorgonCinematicBehavior();
	
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void runGorgonLoop();

	Gorgon* gorgon;
};
