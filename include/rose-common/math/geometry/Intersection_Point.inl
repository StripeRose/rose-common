template <typename T, int N>
bool ROSECOMMON_MATH_NAMESPACE::Intersects(const VectorNT<N, T>& aPoint, const BoxNT<N, T>& aBox)
{
	return Intersects(aBox, aPoint);
}

template <typename T, int N>
bool ROSECOMMON_MATH_NAMESPACE::Intersects(const VectorNT<N, T>& aPoint, const VectorNT<N, T>& aPointB)
{
	return aPoint == aPointB;
}

template <typename T, int N>
bool ROSECOMMON_MATH_NAMESPACE::Intersects(const VectorNT<N, T>& aPoint, const RadiusNT<N, T>& aRadius)
{
	return Intersects(aRadius, aPoint);
}