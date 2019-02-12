#pragma once

#include "Engine/SmartNode.h"

class PesudoCollisionObject : public SmartNode
{
public:
	static PesudoCollisionObject* create(float radius);

protected:
	PesudoCollisionObject(float radius);
	virtual	~PesudoCollisionObject();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;

	bool collidesWith();

private:
	typedef SmartNode super;
};
