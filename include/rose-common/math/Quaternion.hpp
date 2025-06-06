#pragma once

#include "../RoseCommon_Namespace.hpp"

#include "Matrix.hpp"
#include "Trigonometry.hpp"
#include "Vector.hpp"

namespace ROSECOMMON_MATH_NAMESPACE
{
	//template <typename T>
	//class Quaternion
	//{
	//public:
	//	/// <summary>A Quaternion representing no rotation.</summary>
	//	static constexpr Quaternion Identity() { return { 0, 0, 0, 1 }; }

	//public:
	//	/// <summary>
	//	/// Creates a Quaternion from a vector and an angle to rotate about the vector.
	//	/// </summary>
	//	/// <param name="anAxis">The vector axis to rotate around.</param>
	//	/// <param name="anAngle">The angle, in radians, to rotate around the vector.</param>
	//	/// <returns>The created Quaternion.</returns>
	//	static constexpr Quaternion CreateFromAxisAngle(const Vector3<T>& anAxis, const T& anAngle)
	//	{
	//		const T halfAngle = anAngle / 2;
	//		const T s = ROSECOMMON_MATH_NAMESPACE::Sine(halfAngle);

	//		return Quaternion(
	//			anAxis.X * s,
	//			anAxis.Y * s,
	//			anAxis.Z * s,
	//			ROSECOMMON_MATH_NAMESPACE::Cosine(halfAngle)
	//		);
	//	}

	//	/// <summary>
	//	/// Creates a Quaternion from specified yaw, pitch and roll angles.
	//	/// </summary>
	//	/// <param name="aYaw">The yaw angle, in radians, around the y-axis.</param>
	//	/// <param name="aPitch">The pitch angle, in radians, around the x-axis.</param>
	//	/// <param name="aRoll">The roll angle, in radians, around the z-axis.</param>
	//	/// <returns>The created Quaternion expressing the specified angles.</returns>
	//	static constexpr Quaternion CreateFromYawPitchRoll(const T& aYaw, const T& aPitch, const T& aRoll)
	//	{
	//		Quaternion quaternion;
	//		quaternion.Set(aYaw, aPitch, aRoll);
	//		return quaternion;
	//	}

	//	/// <summary>
	//	/// Calculates the dot product of two Quaternions.
	//	/// </summary>
	//	/// <returns>The calculated dot product.</returns>
	//	static constexpr T Dot(const Quaternion& aQuaternion, const Quaternion& anOtherQuaternion)
	//	{
	//		return
	//			(aQuaternion.X * anOtherQuaternion.X) +
	//			(aQuaternion.Y * anOtherQuaternion.Y) +
	//			(aQuaternion.Z * anOtherQuaternion.Z) +
	//			(aQuaternion.W * anOtherQuaternion.W);
	//	}

	//	/// <summary>
	//	/// Returns the inverse of a Quaternion.
	//	/// </summary>
	//	/// <param name="aQuaternion">The Quaternion to invert.</param>
	//	/// <returns>The inverted Quaternion.</returns>
	//	static constexpr Quaternion Inverse(const Quaternion& aQuaternion)
	//	{
	//		return Quaternion(-aQuaternion.X, -aQuaternion.Y, -aQuaternion.Z, aQuaternion.W);
	//	}

	//	/// <summary>
	//	/// Divides each component of the quaternion by the length of the quaternion.
	//	/// </summary>
	//	/// <returns>The normalized Quaternion.</returns>
	//	static constexpr Quaternion Normalize(const Quaternion& aQuaternion)
	//	{
	//		Quaternion resultQuaternion = aQuaternion;
	//		resultQuaternion.Normalize();
	//		return resultQuaternion;
	//	}

	//	/// <summary>
	//	/// Linearly interpolates between two Quaternions.
	//	/// </summary>
	//	/// <param name="aQuaternion">Source Quaternion.</param>
	//	/// <param name="anOtherQuaternion">Source Quaternion.</param>
	//	/// <param name="anAmount">Value indicating how far to interpolate between the quaternions.</param>
	//	/// <returns>The interpolated Quaternion.</returns>
	//	static constexpr Quaternion Lerp(const Quaternion& aQuaternion, const Quaternion& anOtherQuaternion, const T& anAmount)
	//	{
	//		const T scale = static_cast<T>(1) - anAmount;
	//		return (aQuaternion * scale) + (anOtherQuaternion * anAmount);
	//	}

	//	/// <summary>
	//	/// Interpolates between two quaternions, using spherical linear interpolation.
	//	/// </summary>
	//	/// <param name="aQuaternion">Source Quaternion.</param>
	//	/// <param name="anOtherQuaternion">Source Quaternion.</param>
	//	/// <param name="anAmount">Value indicating how far to interpolate between the quaternions.</param>
	//	/// <returns>The interpolated Quaternion.</returns>
	//	static constexpr Quaternion Slerp(const Quaternion& aQuaternion, const Quaternion& anOtherQuaternion, const T& anAmount)
	//	{
	//		const Float32 threshold(0);

	//		Quaternion q1 = aQuaternion;
	//		Quaternion q2 = anOtherQuaternion;

	//		T angle = Quaternion::Dot(q1, q2);

	//		if (angle < static_cast<T>(0.0))
	//		{
	//			q1 *= static_cast<T>(-1.0);
	//			angle *= static_cast<T>(-1.0);
	//		}

	//		if (angle <= (1 - threshold)) // spherical interpolation
	//		{
	//			const T theta = ROSECOMMON_MATH_NAMESPACE::ArcCosine(angle);
	//			const T invsintheta = ROSECOMMON_MATH_NAMESPACE::Reciprocal(ROSECOMMON_MATH_NAMESPACE::Sine(theta));
	//			const T scale = ROSECOMMON_MATH_NAMESPACE::Sine(theta * (1.0f - anAmount)) * invsintheta;
	//			const T invscale = ROSECOMMON_MATH_NAMESPACE::Sine(theta * anAmount) * invsintheta;

	//			Quaternion quaternion((q1 * scale) + (q2 * invscale));
	//			return quaternion;
	//		}
	//		else // linear interpolation
	//		{
	//			return Lerp(q1, q2, anAmount);
	//		}
	//	}

	//public:
	//	constexpr Quaternion()
	//		: Quaternion(0, 0, 0, 0)
	//	{ }

	//	/// <summary>
	//	/// Initializes a new instance of Quaternion.
	//	/// </summary>
	//	/// <param name="anX">The x-value of the quaternion.</param>
	//	/// <param name="aY">The y-value of the quaternion.</param>
	//	/// <param name="aZ">The z-value of the quaternion.</param>
	//	/// <param name="aW">The w-value of the quaternion.</param>
	//	constexpr Quaternion(const T& anX, const T& aY, const T& aZ, const T& aW)
	//		: X(anX)
	//		, Y(aY)
	//		, Z(aZ)
	//		, W(aW)
	//	{ }

	//	/// <summary>
	//	/// Initializes a new instance of Quaternion.
	//	/// </summary>
	//	/// <param name="aVectorPart">The vector component of the Quaternion.</param>
	//	/// <param name="aScalarPart">The rotation component of the quaternion.</param>
	//	explicit constexpr Quaternion(const Vector3& aVectorPart, const T& aScalarPart)
	//		: X(aVectorPart.X)
	//		, Y(aVectorPart.Y)
	//		, Z(aVectorPart.Z)
	//		, W(aScalarPart)
	//	{ }

	//	void Normalize()
	//	{
	//		operator*=(ROSECOMMON_MATH_NAMESPACE::ReciprocalSquareroot(Quaternion::Dot(*this, *this)));
	//	}

	//	void Set(const T& anX, const T& aY, const T& aZ)
	//	{
	//		Float64 angle;

	//		angle = static_cast<Float64>(anX) * static_cast<Float64>(0.5);
	//		const Float64 sr = ROSECOMMON_MATH_NAMESPACE::Sine(angle);
	//		const Float64 cr = ROSECOMMON_MATH_NAMESPACE::Cosine(angle);

	//		angle = static_cast<Float64>(aY) * static_cast<Float64>(0.5);
	//		const Float64 sp = ROSECOMMON_MATH_NAMESPACE::Sine(angle);
	//		const Float64 cp = ROSECOMMON_MATH_NAMESPACE::Cosine(angle);

	//		angle = static_cast<Float64>(aZ) * static_cast<Float64>(0.5);
	//		const Float64 sy = ROSECOMMON_MATH_NAMESPACE::Sine(angle);
	//		const Float64 cy = ROSECOMMON_MATH_NAMESPACE::Cosine(angle);

	//		const Float64 cpcy = cp * cy;
	//		const Float64 spcy = sp * cy;
	//		const Float64 cpsy = cp * sy;
	//		const Float64 spsy = sp * sy;

	//		X = static_cast<Float32>(sr * cpcy - cr * spsy);
	//		Y = static_cast<Float32>(cr * spcy + sr * cpsy);
	//		Z = static_cast<Float32>(cr * cpsy - sr * spcy);
	//		W = static_cast<Float32>(cr * cpcy + sr * spsy);

	//		*this = Quaternion::Normalize(*this);
	//	}

	//	void ToAxisAngle(Vector3& anAxisOut, Float32& anAngleOut) const
	//	{
	//		const Float32 scale = ROSECOMMON_MATH_NAMESPACE::Squareroot(X * X + Y * Y + Z * Z);

	//		if (ROSECOMMON_MATH_NAMESPACE::IsZero(scale) || W > static_cast<Float32>(1.0) || W < static_cast<Float32>(-1.0))
	//		{
	//			anAngleOut = static_cast<Float32>(0);
	//			anAxisOut.X = static_cast<Float32>(0);
	//			anAxisOut.Y = static_cast<Float32>(1);
	//			anAxisOut.Z = static_cast<Float32>(0);
	//		}
	//		else
	//		{
	//			const Float32 invscale = ROSECOMMON_MATH_NAMESPACE::Reciprocal(scale);

	//			anAngleOut = static_cast<Float32>(2.0 * ROSECOMMON_MATH_NAMESPACE::ArcCosine(W));
	//			anAxisOut.X = static_cast<Float32>(X * invscale);
	//			anAxisOut.Y = static_cast<Float32>(Y * invscale);
	//			anAxisOut.Z = static_cast<Float32>(Z * invscale);
	//		}
	//	}

	//	void ToEulerAngles(Vector3& anEulerOut) const
	//	{
	//		const Float64 sqw = W * W;
	//		const Float64 sqx = X * X;
	//		const Float64 sqy = Y * Y;
	//		const Float64 sqz = Z * Z;
	//		const Float64 test = 2.0 * (Y * W - X * Z);

	//		if (ROSECOMMON_MATH_NAMESPACE::Equals(test, static_cast<Float64>(1), static_cast<Float64>(0.000001)))
	//		{
	//			// heading = rotation about z-axis
	//			anEulerOut.Z = (Float32)(-2.0 * ROSECOMMON_MATH_NAMESPACE::ArcTangent2(X, W));
	//			// bank = rotation about x-axis
	//			anEulerOut.X = 0;
	//			// attitude = rotation about y-axis
	//			anEulerOut.Y = (Float32)(ROSECOMMON_MATH_NAMESPACE::Pi64 / 2.0);
	//		}
	//		else if (ROSECOMMON_MATH_NAMESPACE::Equals(test, static_cast<Float64>(-1), static_cast<Float64>(0.000001)))
	//		{
	//			// heading = rotation about z-axis
	//			anEulerOut.Z = (Float32)(2.0 * ROSECOMMON_MATH_NAMESPACE::ArcTangent2(X, W));
	//			// bank = rotation about x-axis
	//			anEulerOut.X = 0;
	//			// attitude = rotation about y-axis
	//			anEulerOut.Y = (Float32)(ROSECOMMON_MATH_NAMESPACE::Pi64 / -2.0);
	//		}
	//		else
	//		{
	//			// heading = rotation about z-axis
	//			anEulerOut.Z = (Float32)ROSECOMMON_MATH_NAMESPACE::ArcTangent2(2.0 * (X * Y + Z * W), (sqx - sqy - sqz + sqw));
	//			// bank = rotation about x-axis
	//			anEulerOut.X = (Float32)ROSECOMMON_MATH_NAMESPACE::ArcTangent2(2.0 * (Y * Z + X * W), (-sqx - sqy + sqz + sqw));
	//			// attitude = rotation about y-axis
	//			anEulerOut.Y = (Float32)ROSECOMMON_MATH_NAMESPACE::ArcSine(ROSECOMMON_MATH_NAMESPACE::Clamp(test, -1.0, 1.0));
	//		}
	//	}

	//	void operator+=(const Quaternion& aQuaternion)
	//	{
	//		X += aQuaternion.X;
	//		Y += aQuaternion.Y;
	//		Z += aQuaternion.Z;
	//		W += aQuaternion.W;
	//	}

	//	void operator*=(const Quaternion& aQuaternion)
	//	{
	//		Quaternion quat(*this);

	//		W = (aQuaternion.W * quat.W) - (aQuaternion.X * quat.X) -
	//			(aQuaternion.Y * quat.Y) - (aQuaternion.Z * quat.Z);

	//		X = (aQuaternion.W * quat.X) + (aQuaternion.X * quat.W) +
	//			(aQuaternion.Y * quat.Z) - (aQuaternion.Z * quat.Y);

	//		Y = (aQuaternion.W * quat.Y) + (aQuaternion.Y * quat.W) +
	//			(aQuaternion.Z * quat.X) - (aQuaternion.X * quat.Z);

	//		Z = (aQuaternion.W * quat.Z) + (aQuaternion.Z * quat.W) +
	//			(aQuaternion.X * quat.Y) - (aQuaternion.Y * quat.X);
	//	}

	//	void operator*=(const T& aScalar)
	//	{
	//		X *= aScalar;
	//		Y *= aScalar;
	//		Z *= aScalar;
	//		W *= aScalar;
	//	}

	//	Vector3 operator*=(const Vector3& aScalar)
	//	{
	//		// nVidia SDK implementation

	//		Vector3 uv, uuv;
	//		Vector3 qvec(X, Y, Z);
	//		uv = Vector3<T>::Cross(qvec, aVector);
	//		uuv = Vector3<T>::Cross(qvec, uv);
	//		uv *= (2.0f * W);
	//		uuv *= 2.0f;

	//		return aVector + uv + uuv;
	//	}

	//	bool operator==(const Quaternion& b) const
	//	{
	//		return ROSECOMMON_MATH_NAMESPACE::Equals(X, b.X)
	//			&& ROSECOMMON_MATH_NAMESPACE::Equals(Y, b.Y)
	//			&& ROSECOMMON_MATH_NAMESPACE::Equals(Z, b.Z)
	//			&& ROSECOMMON_MATH_NAMESPACE::Equals(W, b.W);
	//	}

	//	bool operator!=(const Quaternion& b) const
	//	{
	//		return !operator==(b);
	//	}

	//public:
	//	/// <summary>The X-value of the quaternion vector component.</summary>
	//	T X;
	//	/// <summary>The Y-value of the quaternion vector component.</summary>
	//	T Y;
	//	/// <summary>The Z-value of the quaternion vector component.</summary>
	//	T Z;
	//	/// <summary>The rotation component of the quaternion</summary>
	//	T W;
	//};
}
