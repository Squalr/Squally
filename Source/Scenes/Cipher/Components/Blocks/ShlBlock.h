#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ShlBlock : public BlockBase
{
public:
	static ShlBlock* create(bool isToolBoxItem = false);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	ShlBlock(bool isToolBoxItem);
	~ShlBlock();

	void onEnter() override;
	void initializePositions() override;
};
