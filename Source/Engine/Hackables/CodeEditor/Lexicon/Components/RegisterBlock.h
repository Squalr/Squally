#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class ConstantString;

class RegisterBlock : public SmartNode
{
public:
	static RegisterBlock* create();

	void clearHighlights();
	void highlightEax(bool isDest);
	void highlightEbx(bool isDest);
	void highlightEcx(bool isDest);
	void highlightEdx(bool isDest);
	void highlightEdi(bool isDest);
	void highlightEsi(bool isDest);
	void highlightEbp(bool isDest);
	void highlightEsp(bool isDest);
	void highlightEip(bool isDest);
	void highlightEaxPtr(bool isDest, int offset);
	void highlightEbxPtr(bool isDest, int offset);
	void highlightEcxPtr(bool isDest, int offset);
	void highlightEdxPtr(bool isDest, int offset);
	void highlightEdiPtr(bool isDest, int offset);
	void highlightEsiPtr(bool isDest, int offset);
	void highlightEbpPtr(bool isDest, int offset);
	void highlightEspPtr(bool isDest, int offset);
	void highlightEipPtr(bool isDest, int offset);

	void initEax(unsigned long long eax, std::vector<unsigned int> values = { });
	void initEbx(unsigned long long ebx, std::vector<unsigned int> values = { });
	void initEcx(unsigned long long ecx, std::vector<unsigned int> values = { });
	void initEdx(unsigned long long edx, std::vector<unsigned int> values = { });
	void initEdi(unsigned long long edi, std::vector<unsigned int> values = { });
	void initEsi(unsigned long long esi, std::vector<unsigned int> values = { });
	void initEbp(unsigned long long ebp, std::vector<unsigned int> values = { });
	void initEsp(unsigned long long esp, std::vector<unsigned int> values = { });
	void initEip(unsigned long long eip, std::vector<unsigned int> values = { });

	void setEax(unsigned long long eax);
	void setEbx(unsigned long long ebx);
	void setEcx(unsigned long long ecx);
	void setEdx(unsigned long long edx);
	void setEdi(unsigned long long edi);
	void setEsi(unsigned long long esi);
	void setEbp(unsigned long long ebp);
	void setEsp(unsigned long long esp);
	void setEip(unsigned long long eip);

	void setEaxPtr(unsigned long long value, int offset);
	void setEbxPtr(unsigned long long value, int offset);
	void setEcxPtr(unsigned long long value, int offset);
	void setEdxPtr(unsigned long long value, int offset);
	void setEdiPtr(unsigned long long value, int offset);
	void setEsiPtr(unsigned long long value, int offset);
	void setEbpPtr(unsigned long long value, int offset);
	void setEspPtr(unsigned long long value, int offset);
	void setEipPtr(unsigned long long value, int offset);

	unsigned long long getEax();
	unsigned long long getEbx();
	unsigned long long getEcx();
	unsigned long long getEdx();
	unsigned long long getEdi();
	unsigned long long getEsi();
	unsigned long long getEbp();
	unsigned long long getEsp();
	unsigned long long getEip();

	unsigned long long getEaxPtr(int offset);
	unsigned long long getEbxPtr(int offset);
	unsigned long long getEcxPtr(int offset);
	unsigned long long getEdxPtr(int offset);
	unsigned long long getEdiPtr(int offset);
	unsigned long long getEsiPtr(int offset);
	unsigned long long getEbpPtr(int offset);
	unsigned long long getEspPtr(int offset);
	unsigned long long getEipPtr(int offset);

protected:
	RegisterBlock();
	~RegisterBlock();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void highlightSource(cocos2d::Vec2 position);
	void highlightDest(cocos2d::Vec2 position);

	struct Register
	{
		bool initialized;
		unsigned long long currentValue;
		unsigned long long initialValue;
		std::vector<unsigned int> initialValues;
		std::vector<unsigned int> currentValues;

		Register() : initialized(false), currentValue(0), initialValue(0), initialValues({}), currentValues({}) { }
		Register(unsigned long long currentValue, unsigned long long initialValue, std::vector<unsigned int> initialValues, std::vector<unsigned int> currentValues) :
			initialized(true), currentValue(currentValue), initialValue(initialValue), initialValues(initialValues), currentValues(currentValues) {}
	};

	void addToData(int value, int index, Node* node, std::vector<ConstantString*>* strings, std::vector<LocalizedLabel*>* labels);

	cocos2d::Sprite* registerBlock;
	LocalizedLabel* titleLabel;
	LocalizedLabel* memoryTitleLabel;
	LocalizedLabel* eaxLabel;
	LocalizedLabel* ebxLabel;
	LocalizedLabel* ecxLabel;
	LocalizedLabel* edxLabel;
	LocalizedLabel* ediLabel;
	LocalizedLabel* esiLabel;
	LocalizedLabel* ebpLabel;
	LocalizedLabel* espLabel;
	LocalizedLabel* eipLabel;
	cocos2d::Node* eaxPtrNode;
	cocos2d::Node* ebxPtrNode;
	cocos2d::Node* ecxPtrNode;
	cocos2d::Node* edxPtrNode;
	cocos2d::Node* ediPtrNode;
	cocos2d::Node* esiPtrNode;
	cocos2d::Node* ebpPtrNode;
	cocos2d::Node* espPtrNode;
	cocos2d::Node* eipPtrNode;
	cocos2d::Sprite* destSelector;
	cocos2d::Sprite* srcSelector;

	std::vector<ConstantString*> eaxPtrStrings;
	std::vector<ConstantString*> ebxPtrStrings;
	std::vector<ConstantString*> ecxPtrStrings;
	std::vector<ConstantString*> edxPtrStrings;
	std::vector<ConstantString*> ediPtrStrings;
	std::vector<ConstantString*> esiPtrStrings;
	std::vector<ConstantString*> ebpPtrStrings;
	std::vector<ConstantString*> espPtrStrings;
	std::vector<ConstantString*> eipPtrStrings;

	std::vector<LocalizedLabel*> eaxPtrLabels;
	std::vector<LocalizedLabel*> ebxPtrLabels;
	std::vector<LocalizedLabel*> ecxPtrLabels;
	std::vector<LocalizedLabel*> edxPtrLabels;
	std::vector<LocalizedLabel*> ediPtrLabels;
	std::vector<LocalizedLabel*> esiPtrLabels;
	std::vector<LocalizedLabel*> ebpPtrLabels;
	std::vector<LocalizedLabel*> espPtrLabels;
	std::vector<LocalizedLabel*> eipPtrLabels;

	ConstantString* eaxString;
	ConstantString* ebxString;
	ConstantString* ecxString;
	ConstantString* edxString;
	ConstantString* ediString;
	ConstantString* esiString;
	ConstantString* ebpString;
	ConstantString* espString;
	ConstantString* eipString;

	Register eax;
	Register ebx;
	Register ecx;
	Register edx;
	Register edi;
	Register esi;
	Register ebp;
	Register esp;
	Register eip;

	static const float RegisterPtrSpacing;
	static const cocos2d::Vec2 SelectorRegOffset;
};
