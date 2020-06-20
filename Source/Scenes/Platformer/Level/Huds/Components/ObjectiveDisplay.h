#pragma once

#include "Engine/SmartNode.h"

class ConstantString;
class LocalizedLabel;

class ObjectiveDisplay : public SmartNode
{
public:
	static ObjectiveDisplay* create();

protected:
	ObjectiveDisplay();
	virtual ~ObjectiveDisplay();

	void onEnter() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;
	
	void loadObjective();
	
	LocalizedLabel* label;
};
