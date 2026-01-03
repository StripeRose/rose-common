template <typename T, int N>
bool ROSECOMMON_MATH_NAMESPACE::Intersects(const VectorN<N, T>& aPoint, const Box<N, T>& aBox)
{
	return Intersects(aBox, aPoint);
}

template <typename T, int N>
bool ROSECOMMON_MATH_NAMESPACE::Intersects(const VectorN<N, T>& aPoint, const VectorN<N, T>& aPointB)
{
	return aPoint == aPointB;
}

template <typename T, int N>
bool ROSECOMMON_MATH_NAMESPACE::Intersects(const VectorN<N, T>& aPoint, const Radius<N, T>& aRadius)
{
	return Intersects(aRadius, aPoint);
}