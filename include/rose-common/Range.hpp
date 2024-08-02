#pragma once

#include <type_traits>

namespace RoseCommon
{
    /**
     * @brief A number range which can be iterated through.
     * @tparam T The integer type to use.
     */
    template<typename T>
    class Range
    {
    public:
        class Iterator
        {
        public:
            Iterator(const T& aValue) noexcept
                : myValue(aValue)
            {}

            const T& operator*() const noexcept { return myValue; }
            const T* operator->() const noexcept { return &myValue; }
            Iterator& operator++() noexcept { ++myValue; return *this; }

            friend bool operator==(const Iterator& aLHV, const Iterator aRHV) noexcept {
                return aLHV.myValue == aRHV.myValue;
            }
            friend bool operator!=(const Iterator& aLHV, const Iterator aRHV) noexcept {
                return aLHV.myValue != aRHV.myValue;
            }

        private:
            T myValue;
        };

    public:
        Range(const T& aFirst, const T& aLast) noexcept
            : myFirst(aFirst)
            , myLast(aLast)
        { }

        Range(T&& aFirst, T&& aLast) noexcept
            : myFirst(std::move(aFirst))
            , myLast(std::move(aLast))
        { }

        Range(Range&& anOther) noexcept
            : myFirst(std::move(anOther.aFirst))
            , myLast(std::move(anOther.aLast))
        { }

        Range& operator=(Range&& anOther) noexcept {
            myFirst = std::move(anOther.myFirst);
            myLast = std::move(anOther.myLast);
            return *this;
        }

        Iterator begin() const noexcept { return myFirst; }
        Iterator end() const noexcept { return myLast; }

    private:
        T myFirst;
        T myLast;
    };
}