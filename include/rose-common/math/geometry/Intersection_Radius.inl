template<typename T, int N>
bool ROSECOMMON_MATH_NAMESPACE::Intersects(const Radius<N, T>& aRadius, const Box<N, T>& aBox)
{
	return Intersects(aBox, aRadius);
}

template <typename T, int N>
bool ROSECOMMON_MATH_NAMESPACE::Intersects(const Radius<N, T>& aRadius, const VectorN<N, T>& aPoint)
{
	return
		VectorN<N, T>::DistanceSquared(aRadius.Center, aPoint)
		<= (aRadius.Radius * aRadius.Radius);
}

template<typename T, int N>
bool ROSECOMMON_MATH_NAMESPACE::Intersects(const Radius<N, T>& aRadius, const Radius<N, T>& aRadiusB)
{
	return
		VectorN<N, T>::DistanceSquared(aRadius.Center, aRadiusB.Center)
		<= (aRadius.Radius + aRadiusB.Radius) * (aRadius.Radius + aRadiusB.Radius);
}