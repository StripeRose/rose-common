template<typename T, int N>
bool ROSECOMMON_MATH_NAMESPACE::Intersects(const BoxNT<N, T>& aBox, const BoxNT<N, T>& aBoxB)
{
	bool intersects = true;
	intersects &= (Max(aBox.Max.X, aBoxB.Max.X) - Min(aBox.Min.X, aBoxB.Min.X)) <= ((aBox.Max.X - aBox.Min.X) + (aBoxB.Max.X - aBoxB.Min.X));
	intersects &= (Max(aBox.Max.Y, aBoxB.Max.Y) - Min(aBox.Min.Y, aBoxB.Min.Y)) <= ((aBox.Max.Y - aBox.Min.Y) + (aBoxB.Max.Y - aBoxB.Min.Y));

	if constexpr (N >= 3)
		intersects &= (Max(aBox.Max.Z, aBoxB.Max.Z) - Min(aBox.Min.Z, aBoxB.Min.Z)) <= ((aBox.Max.Z - aBox.Min.Z) + (aBoxB.Max.Z - aBoxB.Min.Z));
	if constexpr (N >= 4)
		intersects &= (Max(aBox.Max.W, aBoxB.Max.W) - Min(aBox.Min.W, aBoxB.Min.W)) <= ((aBox.Max.W - aBox.Min.W) + (aBoxB.Max.W - aBoxB.Min.W));

	return intersects;
}

template <typename T, int N>
bool ROSECOMMON_MATH_NAMESPACE::Intersects(const BoxNT<N, T>& aBox, const VectorNT<N, T>& aPoint)
{
	bool intersects = true;
	intersects &= aPoint.X >= aBox.Min.X && aPoint.X <= aBox.Max.X;
	intersects &= aPoint.Y >= aBox.Min.Y && aPoint.Y <= aBox.Max.Y;

	if constexpr (N >= 3)
		intersects &= aPoint.Z >= aBox.Min.Z && aPoint.Z <= aBox.Max.Z;
	if constexpr (N >= 4)
		intersects &= aPoint.W >= aBox.Min.W && aPoint.W <= aBox.Max.W;

	return intersects;
}

template<typename T, int N>
bool ROSECOMMON_MATH_NAMESPACE::Intersects(const BoxNT<N, T>& aBox, const RadiusNT<N, T>& aRadius)
{
	auto square = [](auto v) { return v * v; };

	T distanceSquared = square(aRadius.Radius);

	auto perComponent = [&](const T aRadiusComponent, const T aBoxMinComponent, const T aBoxMaxComponent) {
		if (aRadiusComponent < aBoxMinComponent)
			distanceSquared -= square(aRadiusComponent - aBoxMinComponent);
		else if (aRadiusComponent > aBoxMaxComponent)
			distanceSquared -= square(aRadiusComponent - aBoxMaxComponent);
		};

	perComponent(aRadius.Center.X, aBox.Min.X, aBox.Max.X);
	perComponent(aRadius.Center.Y, aBox.Min.Y, aBox.Max.Y);
	if constexpr (N >= 3)
		perComponent(aRadius.Center.Z, aBox.Min.Z, aBox.Max.Z);
	if constexpr (N >= 4)
		perComponent(aRadius.Center.W, aBox.Min.W, aBox.Max.W);

	return distanceSquared >= 0;
}
