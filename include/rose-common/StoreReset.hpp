#pragma once

namespace RoseCommon
{
	/**
	 * @brief A structure which changes a value, then resets it when the object is destroyed.
	 *        Can be used to make it easier to change and reset values for the duration of a scope,
	 *        if there are multiple exit-points from the scope.
	 * @tparam T 
	 */
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
