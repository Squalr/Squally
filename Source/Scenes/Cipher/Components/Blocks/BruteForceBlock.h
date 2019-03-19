#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class BruteForceBlock : public BlockBase
{
public:
	static BruteForceBlock* create(bool isToolBoxItem = false);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	BruteForceBlock(bool isToolBoxItem);
	~BruteForceBlock();

	void onEnter() override;
	void initializePositions() override;
};
