#include "variablecontainer.h"

#include "../global/settings.h"

#include "../objectinfo/universalobjectinterface.h"

#include "variableinstancenameandidmap.h"

namespace SpriterEngine
{

	VariableContainer::VariableContainer()
	{
	}

	VariableContainer::~VariableContainer()
	{
		for (auto& it : variables)
		{
			delete it;
		}
	}

	Variable *VariableContainer::getVariable(int variableIndex)
	{
		if (variableIndex<variables.size())
		{
			return variables.at(variableIndex);
		}
		else
		{
			Settings::error("VariableContainer::getVariable - variable index " + std::to_string(variableIndex) + " out of range");
			return 0;
		}
	}

	void VariableContainer::addStringVariable(std::string variableName, std::string defaultValue)
	{
		variables.push_back(new Variable(variableName, Variable::VARIABLETYPE_STRING));
		variables.back()->getDefaultValue()->setStringValue(defaultValue);
	}

	void VariableContainer::addIntVariable(std::string variableName, int defaultValue)
	{
		variables.push_back(new Variable(variableName, Variable::VARIABLETYPE_INT));
		variables.back()->getDefaultValue()->setIntValue(defaultValue);
	}

	void VariableContainer::addRealVariable(std::string variableName, real defaultValue)
	{
		variables.push_back(new Variable(variableName, Variable::VARIABLETYPE_REAL));
		variables.back()->getDefaultValue()->setRealValue(defaultValue);
	}

	void VariableContainer::setupVariableInstances(VariableInstanceNameAndIdMap * variableMap)
	{
		if (variableMap->isEmpty())
		{
			for (auto& it : variables)
			{
				variableMap->pushBackVariable(it);
			}
		}
	}

	void VariableContainer::setupDefaultVariableTimelines(Animation * animation, int objectId)
	{
		int i = 0;
		for (auto& it : variables)
		{
			it->setupDefaultInAnimation(animation, objectId, i);
			++i;
		}
	}

}
