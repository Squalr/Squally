#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ShrBlock : public BlockBase
{
public:
	static ShrBlock* create(bool isToolBoxItem = false);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	ShrBlock(bool isToolBoxItem);
	~ShrBlock();

	void onEnter() override;
	void initializePositions() override;
};
