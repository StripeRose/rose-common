template<typename T, int N>
bool ROSECOMMON_MATH_NAMESPACE::Intersects(const RadiusNT<N, T>& aRadius, const BoxNT<N, T>& aBox)
{
	return Intersects(aBox, aRadius);
}

template <typename T, int N>
bool ROSECOMMON_MATH_NAMESPACE::Intersects(const RadiusNT<N, T>& aRadius, const VectorNT<N, T>& aPoint)
{
	return
		VectorNT<N, T>::DistanceSquared(aRadius.Center, aPoint)
		<= (aRadius.Radius * aRadius.Radius);
}

template<typename T, int N>
bool ROSECOMMON_MATH_NAMESPACE::Intersects(const RadiusNT<N, T>& aRadius, const RadiusNT<N, T>& aRadiusB)
{
	return
		VectorNT<N, T>::DistanceSquared(aRadius.Center, aRadiusB.Center)
		<= (aRadius.Radius + aRadiusB.Radius) * (aRadius.Radius + aRadiusB.Radius);
}