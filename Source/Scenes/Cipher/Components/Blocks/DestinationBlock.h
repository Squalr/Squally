#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class DestinationBlock : public BlockBase
{
public:
	static DestinationBlock* create();
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	DestinationBlock();
	~DestinationBlock();

	void onEnter() override;
	void initializePositions() override;
};
