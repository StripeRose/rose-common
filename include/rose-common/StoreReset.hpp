#pragma once

namespace RoseCommon
{
	template <typename T>
	class StoreReset
	{
	public:
		StoreReset(T& aVariable, const T& aValue)
		{
			myVariablePtr = &aVariable;
			myBackupValue = aVariable;
			aVariable = aValue;
		}

		~StoreReset()
		{
			(*myVariablePtr) = myBackupValue;
		}

	private:
		T* myVariablePtr;
		T myBackupValue;
	};
}
