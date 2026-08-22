// Copyright (c) 2026 Maxime "mrouffet" ROUFFET. All Rights Reserved.

#pragma once

#ifndef EDO_SH_MATHS_GUARD
#define EDO_SH_MATHS_GUARD

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>

// Edo Debug Module
#if __has_include(<edo_debug.hpp>)
	#include <edo_debug.hpp>
#else
	#define EDO_LOG(...) {}
	#define EDO_WARN(...) {}
	#define EDO_ERROR(...) {}
	#define EDO_ASSERT(...) {}
	#define EDO_THROW(...) {}
#endif

#if !defined(EDO_MATHS_MATRIX_DEFAULT_RAW_MAJOR) && !defined(EDO_MATHS_MATRIX_DEFAULT_COLUMN_MAJOR)
#define EDO_MATHS_MATRIX_DEFAULT_RAW_MAJOR 1
#endif

namespace edo
{
// ##############################################################
// #					TYPES									#
// ##############################################################

	template <typename T>
	class Rad;

	template <typename T>
	class Deg;


	template <typename T>
	struct Vec2;

	template <typename T>
	struct Vec3;

	template <typename T>
	struct Vec4;


	template <typename T>
	struct Quat;


	/// Matrix major enum.
	enum class MatrixMajor : uint8_t
	{
		/// Row major standard.
		Row = 1u,

		/// Column major standard.
		Column = 2u,


		/// Default standard.
#if EDO_MATHS_MATRIX_DEFAULT_RAW_MAJOR
		Default = Row
#elif EDO_MATHS_MATRIX_DEFAULT_COLUMN_MAJOR
		Default = Column
#endif
	};

	/// Shortcut alias.
	using MatMaj = MatrixMajor;

	template <typename T, MatrixMajor major>
	struct Mat3;

	template <typename T, MatrixMajor major>
	struct Mat4;

// ##############################################################


// ##############################################################
// #					CONSTANTS								#
// ##############################################################

	/// PI constant.
	template <typename T = double>
	static constexpr T Pi = T{ 3.1415926535897932384 };

	/// 2 * PI constant.
	template <typename T = double>
	static constexpr T PiX2 = T{ 2.0 } * Pi<T>;

	/// PI / 2 constant.
	template <typename T = double>
	static constexpr T PiOv2 = Pi<T> / T{ 2.0 };

	/// PI / 3 constant.
	template <typename T = double>
	static constexpr T PiOv3 = Pi<T> / T{ 3.0 };

	/// PI / 4 constant.
	template <typename T>
	static constexpr T PiOv4 = Pi<T> / T{ 4.0 };

	/// PI / 6 constant.
	template <typename T = double>
	static constexpr T PiOv6 = Pi<T> / T{ 6.0 };

	/// Conversion constant to convert degree to radian.
	template <typename T = double>
	static constexpr T DegToRad = Pi<T> / T{ 180.0 };

	/// Conversion constant to convert radian to degree.
	template <typename T = double>
	static constexpr T RadToDeg = T{ 180.0 } / Pi<T>;

// ##############################################################


// ##############################################################
// #					COS/SIN/TAN								#
// ##############################################################

	/**
	*	\brief \e Compute the \b cosine of the input.
	*
	*	\param[in] _in	Input in radian to compute cosine.
	*
	*	\return Cosine of the input.
	*/
	template <typename T>
	constexpr T Cos(Rad<T> _in) noexcept
	{
		return std::cos(_in.Handle());
	}


	/**
	*	\brief \e Compute the \b arc-cosine of the input.
	*
	*	\param[in] _in	Input to compute arc-cosine.
	*
	*	\return Arc-cosine in radian of the input.
	*/
	template <typename T>
	constexpr Rad<T> ACos(T _in) noexcept
	{
		return std::acos(_in);
	}


	/**
	*	\brief \e Compute the \b sine of the input.
	*
	*	\param[in] _in	Input in radian to compute sine.
	*
	*	\return Sine of the input.
	*/
	template <typename T>
	constexpr T Sin(Rad<T> _in) noexcept
	{
		return std::sin(_in.Handle());
	}

	/**
	*	\brief \e Compute the \b arc-sine of the input.
	*
	*	\param[in] _in	Input to compute arc-sine.
	*
	*	\return Arc-sine in radian of the input.
	*/
	template <typename T>
	constexpr Rad<T> ASin(T _in) noexcept
	{
		return std::asin(_in);
	}


	/**
	*	\brief \e Compute the \b tangent of the input.
	*
	*	\param[in] _in	Input in radian to compute tangent.
	*
	*	\return Tangent of the input.
	*/
	template <typename T>
	constexpr T Tan(Rad<T> _in) noexcept
	{
		return std::tan(_in.Handle());
	}

	/**
	*	\brief \e Compute the \b arc-tangent of the input.
	*
	*	\param[in] _in	Input to compute arc-tangent.
	*
	*	\return Arc-tangent in radian of the input.
	*/
	template <typename T>
	constexpr Rad<T> ATan(T _in) noexcept
	{
		return std::atan(_in);
	}


	/**
	*	\brief \e Compute the \b arc-tangent 2 of _y / _x.
	*
	*	\param[in] _y	Y term to compute arc-tangent 2.
	*	\param[in] _x	X term to compute arc-tangent 2.
	*
	*	\return Arc-tangent 2 in radian of the inputs.
	*/
	template <typename T>
	constexpr Rad<T> ATan2(T _y, T _x) noexcept
	{
		return std::atan2(_y, _x);
	}

// ##############################################################


// ##############################################################
// #					EQUALS									#
// ##############################################################

	/**
	*	\brief Compare two T objects.
	*
	*	\tparam T			Type of operands.
	*	\tparam EpsT		Type of epsilon.
	*
	*	\param[in] _lhs		Left hand side operand to compare.
	*	\param[in] _rhs		Right hand side operand to compare.
	*	\param[in] _epsilon	Epsilon value for threshold compare.
	*
	*	\return	True on equality, otherwise false.
	*/
	template <typename T, typename EpsT = T>
	constexpr bool Equals(const T& _lhs, const T& _rhs, EpsT _epsilon = std::numeric_limits<EpsT>::epsilon())
	{
		// Do not use std::abs for unsigned compatibility.

		return (_lhs < _rhs ? _rhs - _lhs : _lhs - _rhs) <= _epsilon;
	}

	/**
	*	\brief \e Compare one T to T(0).
	*
	*	\tparam T		Type of input.
	*	\tparam EpsT	Type of epsilon.
	*
	*	\param[in] _in			Operand to compare to 0.
	*	\param[in] _epsilon	Allowed threshold to accept equality.
	*
	*	\return Whether _in is equal to 0.
	*/
	template <typename T, typename EpsT = T>
	constexpr bool Equals0(const T& _in, EpsT _epsilon = std::numeric_limits<EpsT>::epsilon()) noexcept
	{
		return Equals(_in, T{ 0 }, _epsilon);
	}

	/**
	*	\brief \e Compare one T to T(1).
	*
	*	\tparam T		Type of input.
	*	\tparam EpsT	Type of epsilon.
	*
	*	\param[in] _in			Operand to compare to 1.
	*	\param[in] _epsilon	Allowed threshold to accept equality.
	*
	*	\return Whether _in is equal to 1.
	*/
	template <typename T, typename EpsT = T>
	constexpr bool Equals1(const T& _in, EpsT _epsilon = std::numeric_limits<EpsT>::epsilon()) noexcept
	{
		return Equals(_in, T{ 1 }, _epsilon);
	}

// ##############################################################


// ##############################################################
// #					LERPS									#
// ##############################################################

	/**
	*	\brief <b> Unclamped Lerp </b> from _start to _end at _alpha.
	*
	*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
	*
	*	\tparam T			Input type.
	*	\tparam AlphaT		Input Alpha type.
	*
	*	\param[in] _start	Starting point of the lerp.
	*	\param[in] _end		Ending point of the lerp.
	*	\param[in] _alpha	Alpha of the lerp.
	*
	*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
	*/
	template <typename T, typename AlphaT>
	T LerpUnclamped(const T& _start, const T& _end, AlphaT _alpha) noexcept
	{
		return (AlphaT{ 1 } - _alpha) * _start + _alpha * _end;
	}

	/**
	*	\brief <b> Clamped Lerp </b> from _start to _end at _time.
	*
	*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
	*
	*	\tparam T		Input type.
	*	\tparam AlphaT		Input Alpha type.
	*
	*	\param[in] _start	Starting point of the lerp.
	*	\param[in] _end		Ending point of the lerp.
	*	\param[in] _alpha	Alpha of the lerp.
	*
	*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
	*/
	template <typename T, typename AlphaT>
	T Lerp(const T& _start, const T& _end, AlphaT _alpha) noexcept
	{
		EDO_WARN(_alpha >= AlphaT{ 0 } && _alpha <= AlphaT{ 1 }, Edo.Maths.Lerp,
			(L"Alpha[%1] clamped to range [0, 1]! Use LerpUnclamped if intended instead.", _alpha));

		return LerpUnclamped(_start, _end, std::clamp(_alpha, AlphaT{ 0 }, AlphaT{ 1 }));
	}


	/**
	*	\brief <b> Unclamped SLerp </b> from _start to _end at _alpha.
	*
	*	Reference: https://en.wikipedia.org/wiki/Slerp
	*
	*	\tparam T			Input type.
	*	\tparam AlphaT		Input Alpha type.
	*
	*	\param[in] _start	Starting point of the lerp.
	*	\param[in] _end		Ending point of the lerp.
	*	\param[in] _alpha	Alpha of the lerp.
	*
	*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
	*/
	template <typename T, typename AlphaT>
	T SLerpUnclamped(const T& _start, const T& _end, AlphaT _alpha) noexcept
	{
		/**
		*	Reference: https://en.wikipedia.org/wiki/Slerp
		*	Formula: (Sin((1.0f - _alpha) * angle) * _start) / sin + (sinStep * _end) / sin.
		*/

		using TScalar = typename T::Type;
		TScalar dot = T::Dot(_start, _end);
		TScalar endSign = 1.0f;

		// Ensure shortest path between _start and _end.
		if (dot < 0.0f)
		{
			endSign = -1.0f;
			dot = -dot;
		}

		// Dot too close to 1 cause angle of 0.
		if (Equals1(dot))
		{
			// Basic linear interpolation.
			return LerpUnclamped(_start, _end * endSign, _alpha);
		}

		// Current angle.
		Rad<TScalar> angle = ACos(dot);

		// Angle step to apply.
		Rad<TScalar> angleStep = angle * _alpha;

		// Current sin.
		TScalar sin = Sin(angle);

		// Sin Step ratio.
		TScalar sinRatio = Sin(angleStep) / sin;

		TScalar s0 = Cos(angleStep) - dot * sinRatio;

		return s0 * _start + sinRatio * _end * endSign;
	}

	/**
	*	\brief <b> Clamped SLerp </b> from _start to _end at _alpha.
	*
	*	Reference: https://en.wikipedia.org/wiki/Slerp
	*
	*	\tparam T		Input type.
	*	\tparam AlphaT		Input Alpha type.
	*
	*	\param[in] _start	Starting point of the lerp.
	*	\param[in] _end		Ending point of the lerp.
	*	\param[in] _alpha	Alpha of the lerp.
	*
	*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
	*/
	template <typename T, typename AlphaT>
	T SLerp(const T& _start, const T& _end, AlphaT _alpha) noexcept
	{
		EDO_WARN(_alpha >= AlphaT{ 0 } && _alpha <= AlphaT{ 1 }, Edo.Maths.Lerp,
			(L"Alpha[%1] clamped to range [0, 1]! Use LerpUnclamped if intended instead.", _alpha));

		return SLerpUnclamped(_start, _end, std::clamp(_alpha, AlphaT{ 0 }, AlphaT{ 1 }));
	}

// ##############################################################


// ##############################################################
// #					RAD										#
// ##############################################################

	/**
	*	\brief Maths \b Radian type.
	* 
	*	Handle Degree / Radian \b conversion.
	*/
	template <typename T>
	class Rad
	{
		/// Handled value.
		T mHandle = T(0.0);

	public:
		/// \b Default contructor.
		Rad() = default;

		/**
		*	\brief \e Value constructor without conversion.
		*
		*	\param[in] _rad		The value in radian to assign.
		*/
		constexpr Rad(T _rad) noexcept :
			mHandle{ _rad }
		{
		}

		/**
		*	\brief \e Value constructor without conversion.
		*
		*	\param[in] _other		The value in radian to assign.
		*/
		template <typename TIn>
		constexpr Rad(Rad<TIn> _other) noexcept :
			mHandle{ static_cast<T>(_other.Handle()) }
		{
		}

		/**
		*	\brief \e Value constructor from radian.
		*
		*	\param[in] _deg		The value in degree to assign.
		*/
		template <typename TIn>
		constexpr Rad(Deg<TIn> _deg) noexcept :
			mHandle{ static_cast<T>(_deg.Handle()) * DegToRad<T> }
		{
		}


		/**
		*	\brief Access the handled value.
		*
		*	\return handle as \c T without conversion.
		*/
		constexpr T Handle() const noexcept
		{
			return mHandle;
		}

		/**
		*	\brief \e Compare 2 Rad.
		*
		*	\param[in] _other		Other Rad to compare to.
		*	\param[in] _epsilon		Epsilon value for threshold compare.
		*
		*	\return Whether this and _other are equal.
		*/
		constexpr bool Equals(Rad _other, T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept
		{
			return edo::Equals(mHandle, _other.mHandle, _epsilon);
		}


		/**
		*	\brief clamp this angle between [-Pi, Pi].
		*/
		void Clamp() noexcept
		{
			mHandle = std::fmod(mHandle, PiX2<T>);

			if (mHandle < -Pi<T>)
				mHandle += PiX2<T>;
			else if (mHandle > Pi<T>)
				mHandle -= PiX2<T>;
		}


//{ Operators

		/**
		*	\brief \e Getter of the opposite signed radian.
		*
		*	\return new opposite signed radian.
		*/
		constexpr Rad operator-() const noexcept
		{
			return -mHandle;
		}

		/**
		*	\brief \b Add Radian to handle.
		*
		*	\param[in] _rhs		radian to add.
		*
		*	\return new Radian result.
		*/
		constexpr Rad operator+(Rad _rhs) const noexcept
		{
			return mHandle + _rhs.mHandle;
		}

		/**
		*	\brief \b Substract Radian to handle.
		*
		*	\param[in] _rhs		radian to substract.
		*
		*	\return new Radian result.
		*/
		constexpr Rad operator-(Rad _rhs) const noexcept
		{
			return mHandle - _rhs.mHandle;
		}

		/**
		*	\brief \b Multiply Radian to handle.
		*
		*	\param[in] _rhs		radian to multiply.
		*
		*	\return new Radian result.
		*/
		constexpr Rad operator*(Rad _rhs) const noexcept
		{
			return mHandle * _rhs.mHandle;
		}

		/**
		*	\brief \b Divide Radian to handle.
		*
		*	\param[in] _rhs		radian to divide.
		*
		*	\return new Radian result.
		*/
		Rad operator/(Rad _rhs) const noexcept
		{
			EDO_ERROR(!Equals0(_rhs.mHandle), Edo.Maths.Rad, L"Divide Rad by 0.");

			return mHandle / _rhs.mHandle;
		}

		/**
		*	\brief \b Scale angle.
		*
		*	\tparam TIn			Type of the input scale.
		*
		*	\param[in] _scale	scale to apply.
		*
		*	\return new radian result.
		*/
		template <typename TIn>
		constexpr Rad operator*(TIn _scale) const noexcept
		{
			return Rad(static_cast<T>(mHandle * _scale));
		}

		/**
		*	\brief \b Unscale angle.
		*
		*	\tparam TIn			Type of the input scale.
		*
		*	\param[in] _scale	un-scale to apply.
		*
		*	\return new radian result.
		*/
		template <typename TIn>
		Rad operator/(TIn _scale) const noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Rad, L"Divide Rad by 0.");

			return Rad(static_cast<T>(mHandle / _scale));
		}


		/**
		*	\brief \b Add Radian to handle.
		*
		*	\param[in] _rhs		radian to add.
		*
		*	\return self Radian.
		*/
		Rad& operator+=(Rad _rhs) noexcept
		{
			mHandle += _rhs.mHandle;

			return *this;
		}

		/**
		*	\brief \b Substract Radian to handle.
		*
		*	\param[in] _rhs		radian to substract.
		*
		*	\return self Radian.
		*/
		Rad& operator-=(Rad _rhs) noexcept
		{
			mHandle -= _rhs.mHandle;

			return *this;
		}

		/**
		*	\brief \b Multiply Radian to handle.
		*
		*	\param[in] _rhs		radian to multiply.
		*
		*	\return self Radian.
		*/
		Rad& operator*=(Rad _rhs) noexcept
		{
			mHandle *= _rhs.mHandle;

			return *this;
		}

		/**
		*	\brief \b Divide Radian to handle.
		*
		*	\param[in] _rhs		radian to divide.
		*
		*	\return self Radian.
		*/
		Rad& operator/=(Rad _rhs) noexcept
		{
			EDO_ERROR(!Equals0(_rhs.mHandle), Edo.Maths.Rad, L"Divide Rad by 0.");

			mHandle /= _rhs.mHandle;

			return *this;
		}

		/**
		*	\brief \b Scale angle.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	scale to apply.
		*
		*	\return this radian scaled.
		*/
		template <typename TIn>
		Rad& operator*=(TIn _scale) noexcept
		{
			mHandle *= _scale;

			return *this;
		}

		/**
		*	\brief \b Unscale angle.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	un-scale to apply.
		*
		*	\return this radian unscaled.
		*/
		template <typename TIn>
		Rad& operator/=(TIn _scale) noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Rad, L"Divide Rad by 0.");

			mHandle /= _scale;

			return *this;
		}


		/**
		*	\brief \e Compare 2 radian equality.
		*
		*	\param[in] _rhs		Other radian to compare to.
		*
		*	\return Whether this and _rhs are equal.
		*/
		constexpr bool operator==(Rad _rhs) const noexcept
		{
			return Equals(_rhs);
		}

		/**
		*	\brief \e Compare 2 radian inequality.
		*
		*	\param[in] _rhs		Other radian to compare to.
		*
		*	\return Whether this and _rhs are non-equal.
		*/
		constexpr bool operator!=(Rad _rhs) const noexcept
		{
			return !(*this == _rhs);
		}


		/**
		*	\brief Access the handled value.
		*
		*	\return handle as \c float without conversion.
		*/
		explicit constexpr operator T() const noexcept
		{
			return mHandle;
		}

//}
	};


	/**
	*	\brief _rad \b literal operator.
	*
	*	\param[in] _lit		Operand to convert to Radian.
	*
	*	\return \c Radian without maths-conversion.
	*/
	constexpr Rad<float> operator""_rad(unsigned long long _lit) noexcept
	{
		return Rad<float>(static_cast<float>(_lit));
	}

	/**
	*	\brief _rad \b literal operator.
	*
	*	\param[in] _lit		Operand to convert to Radian.
	*
	*	\return \c Radian without maths-conversion.
	*/
	constexpr Rad<double> operator""_rad(long double _lit) noexcept
	{
		return Rad<double>(static_cast<double>(_lit));
	}


#if __has_include(<edo_debug.hpp>)
	template <typename T>
	std::string ToString(const Rad<T> _rad) noexcept
	{
		return edo::ToString(_rad.Handle()) + "_rad";
	}
#endif // edo_debug


//{ Aliases

	/// Alias for float Rad.
	using Radf = Rad<float>;

	/// Alias for double Rad.
	using Radd = Rad<double>;

	/// Template alias of Rad
	template <typename T>
	using Radian = Rad<T>;

//}

// ##############################################################


// ##############################################################
// #					DEG										#
// ##############################################################

	/**
	*	\brief Maths \b Degree type.
	* 
	*	Handle Degree / Radian \b conversion.
	*/
	template <typename T>
	class Deg
	{
		/// Handled value.
		T mHandle = T(0);

	public:
		/// Default contructor.
		Deg() = default;

		/**
		*	\brief \e Value constructor without conversion.
		*
		*	\param[in] _deg		The value in degree to assign.
		*/
		constexpr Deg(T _deg) noexcept :
			mHandle{ _deg }
		{
		}

		/**
		*	\brief \e Value constructor without conversion.
		*
		*	\param[in] _other		The value in degree to assign.
		*/
		template <typename TIn>
		constexpr Deg(Deg<TIn> _other) noexcept :
			mHandle{ static_cast<T>(_other.Handle()) }
		{
		}

		/**
		*	\brief \e Value constructor from radian.
		*
		*	\param[in] _rad		The value in radian to assign.
		*/
		template <typename TIn>
		constexpr Deg(Rad<TIn> _rad) noexcept :
			mHandle{ static_cast<T>(_rad.Handle()) * RadToDeg<T> }
		{
		}


		/**
		*	\brief Access the handled value.
		*
		*	\return handle as \c T without conversion.
		*/
		constexpr T Handle() const noexcept
		{
			return mHandle;
		}


		/**
		*	\brief \e Compare 2 Deg.
		*
		*	\param[in] _other		Other Deg to compare to.
		*	\param[in] _epsilon		Epsilon value for threshold compare.
		*
		*	\return Whether this and _other are equal.
		*/
		constexpr bool Equals(Deg _other, T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept
		{
			return edo::Equals(mHandle, _other.mHandle, _epsilon);
		}


		/// clamp this angle between [-180, 180].
		void Clamp() noexcept
		{
			mHandle = std::fmod(mHandle, T{ 360 });

			if (mHandle < -T{ 180 })
				mHandle += T{ 360 };
			else if (mHandle > T{ 180 })
				mHandle -= T{ 360 };
		}


//{ Operators

		/**
		*	\brief \e Getter of the opposite signed degree.
		*
		*	\return new opposite signed degree.
		*/
		constexpr Deg operator-() const noexcept
		{
			return -mHandle;
		}

		/**
		*	\brief \b Add degrees to handle.
		*
		*	\param[in] _rhs		degrees to add.
		*
		*	\return new degree result.
		*/
		constexpr Deg operator+(Deg _rhs) const noexcept
		{
			return mHandle + _rhs.mHandle;
		}

		/**
		*	\brief \b Substract degrees to handle.
		*
		*	\param[in] _rhs		degrees to substract.
		*
		*	\return new degree result.
		*/
		constexpr Deg operator-(Deg _rhs) const noexcept
		{
			return mHandle - _rhs.mHandle;
		}

		/**
		*	\brief \b Multiply degrees to handle.
		*
		*	\param[in] _rhs		degrees to multiply.
		*
		*	\return new degree result.
		*/
		constexpr Deg operator*(Deg _rhs) const noexcept
		{
			return mHandle * _rhs.mHandle;
		}

		/**
		*	\brief \b Divide degrees to handle.
		*
		*	\param[in] _rhs		degrees to divide.
		*
		*	\return new degree result.
		*/
		Deg operator/(Deg _rhs) const noexcept
		{
			EDO_ERROR(!Equals0(_rhs.mHandle), Edo.Maths.Deg, L"Divide Deg by 0.");

			return mHandle / _rhs.mHandle;
		}

		/**
		*	\brief \b Scale angle.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	scale to apply.
		*
		*	\return new degree result.
		*/
		template <typename TIn>
		constexpr Deg operator*(TIn _scale) const noexcept
		{
			return Deg(static_cast<T>(mHandle * _scale));
		}

		/**
		*	\brief \b Unscale angle.
		*
		*	\tparam TIn			Type of the input scale.
		*
		*	\param[in] _scale	un-scale to apply.
		*
		*	\return new degree result.
		*/
		template <typename TIn>
		Deg operator/(TIn _scale) const noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Deg, L"Divide Deg by 0.");

			return Deg(static_cast<T>(mHandle / _scale));
		}


		/**
		*	\brief \b Add degrees to handle.
		*
		*	\param[in] _rhs		degrees to add.
		*
		*	\return self degree.
		*/
		Deg& operator+=(Deg _rhs) noexcept
		{
			mHandle += _rhs.mHandle;

			return *this;
		}

		/**
		*	\brief \b Substract degrees to handle.
		*
		*	\param[in] _rhs		degrees to substract.
		*
		*	\return self degree.
		*/
		Deg& operator-=(Deg _rhs) noexcept
		{
			mHandle -= _rhs.mHandle;

			return *this;
		}

		/**
		*	\brief \b Multiply degrees to handle.
		*
		*	\param[in] _rhs		degrees to multiply.
		*
		*	\return self degree.
		*/
		Deg& operator*=(Deg _rhs) noexcept
		{
			mHandle *= _rhs.mHandle;

			return *this;
		}

		/**
		*	\brief \b Divide degrees to handle.
		*
		*	\param[in] _rhs		degrees to divide.
		*
		*	\return self degree.
		*/
		Deg& operator/=(Deg _rhs) noexcept
		{
			EDO_ERROR(!Equals0(_rhs.mHandle), Edo.Maths.Deg, L"Divide Deg by 0.");

			mHandle /= _rhs.mHandle;

			return *this;
		}

		/**
		*	\brief \b Scale angle.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	scale to apply.
		*
		*	\return this degree scaled.
		*/
		template <typename TIn>
		Deg& operator*=(TIn _scale) noexcept
		{
			mHandle *= _scale;

			return *this;
		}

		/**
		*	\brief \b Unscale angle.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	un-scale to apply.
		*
		*	\return this degree unscaled.
		*/
		template <typename TIn>
		Deg& operator/=(TIn _scale) noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Deg, L"Divide Deg by 0.");

			mHandle /= _scale;

			return *this;
		}


		/**
		*	\brief \e Compare 2 degree equality.
		*
		*	\param[in] _rhs		Other degree to compare to.
		*
		*	\return Whether this and _rhs are equal.
		*/
		constexpr bool operator==(Deg _rhs) const noexcept
		{
			return Equals(_rhs);
		}

		/**
		*	\brief \e Compare 2 degree inequality.
		*
		*	\param[in] _rhs		Other degree to compare to.
		*
		*	\return Whether this and _rhs are non-equal.
		*/
		constexpr bool operator!=(Deg _rhs) const noexcept
		{
			return !(*this == _rhs);
		}


		/**
		*	\brief Access the handled value.
		*
		*	\return handle as \c float without conversion.
		*/
		explicit constexpr operator T() const noexcept
		{
			return mHandle;
		}

//}
	};


	/**
	*	\brief _deg \b literal operator.
	*
	*	\param[in] _lit		Operand to convert to Degree.
	*
	*	\return \c Degree without maths-conversion.
	*/
	constexpr Deg<float> operator""_deg(unsigned long long _lit) noexcept
	{
		return Deg<float>(static_cast<float>(_lit));
	}

	/**
	*	\brief _deg \b literal operator.
	*
	*	\param[in] _lit		Operand to convert to Degree.
	*
	*	\return \c Degree without maths-conversion.
	*/
	constexpr Deg<double> operator""_deg(long double _lit) noexcept
	{
		return Deg<double>(static_cast<double>(_lit));
	}


#if __has_include(<edo_debug.hpp>)
	template <typename T>
	std::string ToString(const Deg<T> _deg) noexcept
	{
		return edo::ToString(_deg.Handle()) + "_deg";
	}
#endif // edo_debug


//{ Aliases

	/// Alias for float Deg.
	using Degf = Deg<float>;

	/// Alias for double Deg.
	using Degd = Deg<double>;

	/// Template alias of Deg
	template <typename T>
	using Degree = Deg<T>;

//}

// ##############################################################


// ##############################################################
// #					VEC 2									#
// ##############################################################

	/**
	*	\brief \e Vector 2 class.
	*
	*	\tparam T	Type of the vector.
	*/
	template <typename T>
	struct Vec2
	{
		/// Scalar type of the Vector.
		using Type = T;


		/// Vector's X component (axis value).
		T x = T();

		/// Vector's Y component (axis value).
		T y = T();


//{ Constants

		/// Zero vector constant { 0, 0 }.
		static const Vec2 Zero;

		/// One vector constant { 1, 1 }.
		static const Vec2 One;

		/// Right vector constant { 1, 0 }.
		static const Vec2 Right;

		/// Left vector constant { -1, 0 }.
		static const Vec2 Left;

		/// Up vector constant { 0, 1 }.
		static const Vec2 Up;

		/// Down vector constant { 0, -1 }.
		static const Vec2 Down;

//}


//{ Constructors

		/// \e Default constructor.
		Vec2() = default;


		/**
		*	\brief \e Value constructor.
		*
		*	\param[in] _x	X axis value.
		*	\param[in] _y	Y axis value.
		*/
		constexpr Vec2(T _x, T _y) noexcept :
			x{ _x },
			y{ _y }
		{
		}

		/**
		*	\brief \b Scale \e Value constructor.
		*
		*	\param[in] _scale	Axis value to apply on all axis.
		*/
		constexpr Vec2(T _scale) noexcept :
			x{ _scale },
			y{ _scale }
		{
		}


		/// Default move constructor.
		Vec2(Vec2&&) = default;

		/// Default copy constructor.
		Vec2(const Vec2&) = default;

		/**
		*	\brief \e Value constructor from another Vec2 type.
		*
		*	\tparam TIn			Type of the input Vec2.
		*
		*	\param[in] _other	Vec2 to construct from.
		*/
		template <typename TIn>
		constexpr Vec2(const Vec2<TIn>& _other) noexcept :
			x{ static_cast<T>(_other.x) },
			y{ static_cast<T>(_other.y) }
		{
		}

		/**
		*	\brief \e Value constructor from Vec3.
		*
		*	\tparam TIn			Type of the input Vec3.
		*
		*	\param[in] _other	Vec3 to construct from.
		*/
		template <typename TIn>
		constexpr Vec2(const Vec3<TIn>& _other) noexcept :
			x{ static_cast<T>(_other.x) },
			y{ static_cast<T>(_other.y) }
		{
		}

//}


//{ Equals

		/**
		*	\brief Whether this vector is a zero vector.
		*
		*	\return True if this is a zero vector.
		*/
		constexpr bool IsZero() const noexcept
		{
			return Equals0(x) && Equals0(y);
		}

		/**
		*	\brief \e Compare 2 vector.
		*
		*	\param[in] _other		Other vector to compare to.
		*	\param[in] _epsilon		Epsilon value for threshold comparison.
		*
		*	\return Whether this and _other are equal.
		*/
		constexpr bool Equals(const Vec2& _other, T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept
		{
			return edo::Equals(x, _other.x, _epsilon) &&
				edo::Equals(y, _other.y, _epsilon);
		}


		/**
		*	\brief \e Compare 2 vector equality.
		*
		*	\param[in] _rhs		Other vector to compare to.
		*
		*	\return Whether this and _rhs are equal.
		*/
		constexpr bool operator==(const Vec2& _rhs) const noexcept
		{
			return Equals(_rhs);
		}

		/**
		*	\brief \e Compare 2 vector inequality.
		*
		*	\param[in] _rhs		Other vector to compare to.
		*
		*	\return Whether this and _rhs are non-equal.
		*/
		constexpr bool operator!=(const Vec2& _rhs) const noexcept
		{
			return !(*this == _rhs);
		}

//}


//{ Accessors

		/**
		*	\brief \e Getter of vector data
		*
		*	\return this vector as a T*.
		*/
		T* Data() noexcept
		{
			return &x;
		}

		/**
		*	\brief <em> Const Getter </em> of vector data
		*
		*	\return this vector as a const T*.
		*/
		const T* Data() const noexcept
		{
			return &x;
		}


		/**
		*	\brief \e Access operator by index: x, y using 0, 1.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		T& operator[](uint32_t _index)
		{
			EDO_ASSERT(_index < 2u, Edo.Maths.Vec2, L"Index access out of range!");

			return Data()[_index];
		}

		/**
		*	\brief <em> Const Access </em> operator by index: x, y using 0, 1.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		const T& operator[](uint32_t _index) const
		{
			EDO_ASSERT(_index < 2u, Edo.Maths.Vec2, L"Index access out of range!");

			return Data()[_index];
		}

//}


//{ Length

		/**
		*	\brief \e Getter of the /b length of this vector.
		*
		*	\return Length of this vector.
		*/
		T Length() const
		{
			const T l2 = SqrLength();

			return std::sqrt(l2);
		}

		/**
		*	\brief \e Getter of the <b> Squared Length </b> of this vector.
		*
		*	\return Squared length of this vector.
		*/
		constexpr T SqrLength() const noexcept
		{
			return x * x + y * y;
		}


		/**
		*	\brief \b Normalize this vector.
		*
		*	\return self vector normalized.
		*/
		Vec2& Normalize() noexcept
		{
			const T norm = Length();

			EDO_ERROR(!Equals0(norm), Edo.Maths.Vec2, L"Normalize null vector!");

			x /= norm;
			y /= norm;

			return *this;
		}

		/**
		*	\brief \b Normalize this vector.
		*
		*	\return new normalized vector.
		*/
		Vec2 GetNormalized() const noexcept
		{
			Vec2 res = *this;
			res.Normalize();

			return res;
		}

		/**
		*	\brief Whether this vector is normalized.
		*
		*	\param[in] _epsilon	Allowed threshold to accept equality.
		* 
		*	\return True if this vector is normalized, otherwise false.
		*/
		constexpr bool IsNormalized(T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept
		{
			return edo::Equals1(SqrLength(), _epsilon);
		}

//}


//{ Proj

		/**
		*	\brief \b Reflect this vector over the normal.
		*
		*	\param[in] _normal		Normal used for reflection.
		*	\param[in] _elasticity		Elasticity reflection coefficient (use 1.0f for full reflection).
		*
		*	\return new vector reflected.
		*/
		Vec2 Reflect(const Vec2& _normal, float _elasticity = 1.0f) const noexcept
		{
			return *this - ProjectOnToNormal(_normal) * (1.0f + _elasticity);
		}

		/**
		*	\brief \b Project this vector onto an other vector.
		*
		*	Reference: https://en.wikipedia.org/wiki/Vector_projection
		*
		*	\param[in] _other	Vector used for projection.
		*
		*	\return new  vector projected.
		*/
		Vec2 ProjectOnTo(const Vec2& _other) const noexcept
		{
			return Dot(*this, _other) / _other.SqrLength() * _other;
		}

		/**
		*	\brief \b Project this vector onto s normal.
		*
		*	Assume _normal is normalized.
		*	Use ProjectOnTo() for non normalized vector.
		*	Reference: https://en.wikipedia.org/wiki/Vector_projection
		*
		*	\param[in] _normal		Normal used for projection.
		*
		*	\return new vector projected.
		*/
		Vec2 ProjectOnToNormal(const Vec2& _normal) const noexcept
		{
			EDO_WARN(_normal.IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Vec2,
				L"Normal should be normalized or use ProjectOnTo() instead!");

			return Dot(*this, _normal) * _normal;
		}

		/**
		*	\brief \e Compute the perpendicular vector to this vector.
		*
		*	Rotate this vector 90 degrees in trigonomety direction (counter-clockwise).
		*
		*	\return new vector rotated.
		*/
		Vec2 Perpendicular() const noexcept
		{
			return Vec2(y, -x);
		}

//}


//{ Dot/Cross

		/**
		*	\brief \e Compute the <b> Dot product </b> between _lhs and _rhs.
		*
		*	\param[in] _lhs		Left hand side operand to compute dot product with.
		*	\param[in] _rhs		Right hand side operand to compute dot product with.
		*
		*	\return <b> Dot product </b> between _lhs and _rhs.
		*/
		static constexpr T Dot(const Vec2& _lhs, const Vec2& _rhs) noexcept
		{
			return _lhs.x * _rhs.x + _lhs.y * _rhs.y;
		}

		/**
		*	\brief \e Compute the <b> Cross product </b> between _lhs and _rhs.
		*
		*	\param[in] _lhs		Left hand side operand to compute cross product with.
		*	\param[in] _rhs		Right hand side operand to compute cross product with.
		*
		*	\return <b> Cross product </b> between _lhs and _rhs.
		*/
		static constexpr T Cross(const Vec2& _lhs, const Vec2& _rhs) noexcept
		{
			return _lhs.x * _rhs.y - _lhs.y * _rhs.x;
		}

//}


//{ Angle

		/**
		*	\brief \e Compute the <b> Signed Angle </b> between _start and _end.
		*
		*	\param[in] _start		Starting point to compute angle from.
		*	\param[in] _end			Ending point to compute angle to.
		*
		*	\return <b> Signed Angle </b> between _start and _end.
		*/
		static Rad<T> Angle(const Vec2& _start, const Vec2& _end) noexcept
		{
			return ATan2(_end.y, _end.x) - ATan2(_start.y, _start.x);
		}

		/**
		*	\brief \e Compute the <b> Unsigned Angle </b> between _start and _end.
		*
		*	\param[in] _start		Starting point to compute angle from.
		*	\param[in] _end			Ending point to compute angle to.
		*
		*	\return <b> Unsigned Angle </b> between _start and _end.
		*/
		static Rad<T> AngleUnsigned(const Vec2& _start, const Vec2& _end) noexcept
		{
			return ACos(Dot(_start, _end));
		}

//}


//{ Dist/Dir

		/**
		*	\brief \e Compute the <b> Distance </b> between _start and _end.
		*
		*	\param[in] _start		Left hand side operand to compute distance with.
		*	\param[in] _end			Right hand side operand to compute distance with.
		*
		*	\return <b> Distance </b> between _start and _end.
		*/
		static constexpr T Dist(const Vec2& _start, const Vec2& _end) noexcept
		{
			return (_start - _end).Length();
		}

		/**
		*	\brief \e Compute the <b> Squared Distance </b> between _start and _end.
		*
		*	\param[in] _start		Left hand side operand to compute squared distance with.
		*	\param[in] _end			Right hand side operand to compute squared distance with.
		*
		*	\return <b> Squared Distance </b> between _start and _rhs.
		*/
		static constexpr T SqrDist(const Vec2& _start, const Vec2& _end) noexcept
		{
			return (_start - _end).SqrLength();
		}

		/**
		*	\brief \e Compute the <b> Non-Normalized Direction </b> from _start to _end.
		*
		*	Direction get not normalized. Use DirN instead.
		*
		*	\param[in] _start		Starting point to compute direction from.
		*	\param[in] _end			ending point to compute direction to.
		*
		*	\return <b> Non-Normalized Direction </b> from _start to _end.
		*/
		static constexpr Vec2 Dir(const Vec2& _start, const Vec2& _end) noexcept
		{
			return (_end - _start);
		}

		/**
		*	\brief \e Compute the <b> Normalized Direction </b> from _start to _end.
		*
		*	\param[in] _start		Starting point to compute direction from.
		*	\param[in] _end			ending point to compute direction to.
		*
		*	\return <b> Normalized Direction </b> from _start to _end.
		*/
		static constexpr Vec2 DirN(const Vec2& _start, const Vec2& _end) noexcept
		{
			return Dir(_start, _end).GetNormalized();
		}

//}


//{ Lerp

		/**
		*	\brief <b> Clamped Lerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Vec2 Lerp(const Vec2& _start, const Vec2& _end, AlphaT _alpha) noexcept
		{
			return edo::Lerp(_start, _end, _alpha);
		}

		/**
		*	\brief <b> Unclamped Lerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Vec2 LerpUnclamped(const Vec2& _start, const Vec2& _end, AlphaT _alpha) noexcept
		{
			return edo::LerpUnclamped(_start, _end, _alpha);
		}

		/**
		*	\brief <b> Clamped SLerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Slerp
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Vec2 SLerp(const Vec2& _start, const Vec2& _end, AlphaT _alpha) noexcept
		{
			return edo::SLerp(_start, _end, _alpha);
		}

		/**
		*	\brief <b> Unclamped SLerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Slerp
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Vec2 SLerpUnclamped(const Vec2& _start, const Vec2& _end, AlphaT _alpha) noexcept
		{
			return edo::SLerpUnclamped(_start, _end, _alpha);
		}

//}


//{ Operators

		/**
		*	\brief \e Default assignment move operator.
		*
		*	\return self vector assigned.
		*/
		Vec2& operator=(Vec2&&) = default;

		/**
		*	\brief \e Default assignment copy operator.
		*
		*	\return self vector assigned.
		*/
		Vec2& operator=(const Vec2&) = default;


		/**
		*	\brief \e Getter of the opposite signed vector.
		*
		*	\return new opposite signed vector.
		*/
		constexpr Vec2 operator-() const noexcept
		{
			return Vec2(-x, -y);
		}

		/**
		*	\brief \b Scale each vector axis by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Scale value to apply on all axis.
		*
		*	\return new vector scaled.
		*/
		template <typename TIn>
		constexpr Vec2 operator*(TIn _scale) const noexcept
		{
			return Vec2(
				x * _scale,
				y * _scale
			);
		}

		/**
		*	\brief <b> Inverse Scale </b> each vector axis by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Inverse scale value to apply on all axis.
		*
		*	\return new vector inverse-scaled.
		*/
		template <typename TIn>
		Vec2 operator/(TIn _scale) const noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Vec2, L"Divide vector by 0!");

			return Vec2(
				x / _scale,
				y / _scale
			);
		}

		/**
		*	\brief \b Add term by term vector values.
		*
		*	\param[in] _rhs		Vector to add.
		*
		*	\return new vector result.
		*/
		constexpr Vec2 operator+(const Vec2& _rhs) const noexcept
		{
			return Vec2(x + _rhs.x, y + _rhs.y);
		}

		/**
		*	\brief \b Subtract term by term vector values.
		*
		*	\param[in] _rhs		Vector to substract.
		*
		*	\return new vector result.
		*/
		constexpr Vec2 operator-(const Vec2& _rhs) const noexcept
		{
			return Vec2(x - _rhs.x, y - _rhs.y);
		}

		/**
		*	\brief \b Multiply term by term vector values.
		*
		*	\param[in] _rhs		Vector to multiply.
		*
		*	\return new vector result.
		*/
		constexpr Vec2 operator*(const Vec2& _rhs) const noexcept
		{
			return Vec2(x * _rhs.x, y * _rhs.y);
		}

		/**
		*	\brief \b Divide term by term vector values.
		*
		*	\param[in] _rhs		Vector to divide.
		*
		*	\return new vector result.
		*/
		Vec2 operator/(const Vec2& _rhs) const noexcept
		{
			EDO_ERROR(!Equals0(_rhs.x), Edo.Maths.Vec2, L"Divide X Axis by 0!");
			EDO_ERROR(!Equals0(_rhs.y), Edo.Maths.Vec2, L"Divide Y Axis by 0!");

			return Vec2(x / _rhs.x, y / _rhs.y);
		}

		/**
		*	\brief \e Compute the <b> Dot product </b> between this and _rhs.
		*
		*	\param[in] _rhs			Right hand side operand vector to compute dot product with.
		*
		*	\return <b> Dot product </b> between this vector and _other.
		*/
		constexpr T operator|(const Vec2& _rhs) const noexcept
		{
			return Dot(*this, _rhs);
		}

		/**
		*	\brief \e Compute the <b> Cross product </b> between this and _rhs.
		*
		*	\param[in] _rhs			Right hand side operand vector to compute cross product with.
		*
		*	\return <b> Cross product </b> between this vector and _other.
		*/
		constexpr T operator^(const Vec2& _rhs) const noexcept
		{
			return Cross(*this, _rhs);
		}


		/**
		*	\brief \b Scale each vector axis by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Scale value to apply on all axis.
		*
		*	\return self vector scaled.
		*/
		template <typename TIn>
		Vec2& operator*=(TIn _scale) noexcept
		{
			x *= _scale;
			y *= _scale;

			return *this;
		}

		/**
		*	\brief <b> Inverse Scale </b> each vector axis by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Scale value to apply on all axis.
		*
		*	\return self vector inverse-scaled.
		*/
		template <typename TIn>
		Vec2& operator/=(TIn _scale) noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Vec2, L"Divide vector by 0!");

			x /= _scale;
			y /= _scale;

			return *this;
		}

		/**
		*	\brief \b Add term by term vector values.
		*
		*	\param[in] _rhs		Vector to add.
		*
		*	\return self vector result.
		*/
		Vec2& operator+=(const Vec2& _rhs) noexcept
		{
			x += _rhs.x;
			y += _rhs.y;

			return *this;
		}

		/**
		*	\brief \b Substract term by term vector values.
		*
		*	\param[in] _rhs		Vector to substract.
		*
		*	\return self vector result.
		*/
		Vec2& operator-=(const Vec2& _rhs) noexcept
		{
			x -= _rhs.x;
			y -= _rhs.y;

			return *this;
		}

		/**
		*	\brief \b Multiply term by term vector values.
		*
		*	\param[in] _rhs		Vector to multiply.
		*
		*	\return self vector result.
		*/
		Vec2& operator*=(const Vec2& _rhs) noexcept
		{
			x *= _rhs.x;
			y *= _rhs.y;

			return *this;
		}

		/**
		*	\brief \b Divide term by term vector values.
		*
		*	\param[in] _rhs		Vector to divide.
		*
		*	\return self vector result.
		*/
		Vec2& operator/=(const Vec2& _rhs) noexcept
		{
			EDO_ERROR(!Equals0(_rhs.x), Edo.Maths.Vec2, L"Divide X Axis by 0!");
			EDO_ERROR(!Equals0(_rhs.y), Edo.Maths.Vec2, L"Divide Y Axis by 0!");

			x /= _rhs.x;
			y /= _rhs.y;

			return *this;
		}

//}
	};


//{ Constants

	template <typename T>
	const Vec2<T> Vec2<T>::Zero{ T(0), T(0) };

	template <typename T>
	const Vec2<T> Vec2<T>::One{ T(1), T(1) };

	template <typename T>
	const Vec2<T> Vec2<T>::Right{ T(1), T(0) };

	template <typename T>
	const Vec2<T> Vec2<T>::Left{ T(-1), T(0) };

	template <typename T>
	const Vec2<T> Vec2<T>::Up{ T(0), T(1) };

	template <typename T>
	const Vec2<T> Vec2<T>::Down{ T(0), T(-1) };

//}


	/**
	*	\brief \b Scale each vector axis by _lhs.
	*
	*	\tparam TIn			Type of the input scale.
	* 
	*	\param[in] _lhs		Scale value to apply on all axis.
	*	\param[in] _rhs		Vector to scale.
	*
	*	\return new vector scaled.
	*/
	template <typename T, typename TIn>
	constexpr Vec2<T> operator*(TIn _lhs, const Vec2<T>& _rhs) noexcept
	{
		return _rhs * _lhs;
	}

	/**
	*	\brief <b> Inverse Scale </b> each vector axis by _lhs.
	*
	*	\tparam TIn			Type of the input scale.
	* 
	*	\param[in] _lhs		Inverse scale value to apply on all axis.
	*	\param[in] _rhs		Vector to scale.
	*
	*	\return new vector inverse-scaled.
	*/
	template <typename T, typename TIn>
	Vec2<T> operator/(TIn _lhs, const Vec2<T>& _rhs) noexcept
	{
		EDO_ERROR(!Equals0(_rhs.x), Edo.Maths.Vec2, L"Inverse scale X Axis by 0!");
		EDO_ERROR(!Equals0(_rhs.y), Edo.Maths.Vec2, L"Inverse scale Y Axis by 0!");

		return Vec2<T>(
			_lhs / _rhs.x,
			_lhs / _rhs.y
		);
	}


#if __has_include(<edo_debug.hpp>)
	template <typename T>
	std::string ToString(const Vec2<T> _vec) noexcept
	{
		return "Vec2{ X: " + edo::ToString(_vec.x) +
			"\tY: " + edo::ToString(_vec.y) + " }";
	}

#endif // edo_debug

//{ Aliases

	/// Alias for int32 Vec2.
	using Vec2i = Vec2<int32_t>;

	/// Alias for uint32 Vec2.
	using Vec2ui = Vec2<uint32_t>;

	/// Alias for float Vec2.
	using Vec2f = Vec2<float>;

	/// Alias for double Vec2.
	using Vec2d = Vec2<double>;


	/// Template alias of Vec2
	template <typename T>
	using Vector2 = Vec2<T>;

	/// Alias for int32 Vector2.
	using Vector2i = Vector2<int32_t>;

	/// Alias for uint32 Vector2.
	using Vector2ui = Vector2<uint32_t>;

	/// Alias for float Vector2.
	using Vector2f = Vector2<float>;

	/// Alias for double Vector2.
	using Vector2d = Vector2<double>;

//}

// ##############################################################


// ##############################################################
// #					VEC 3									#
// ##############################################################

	/**
	*	\brief \e Vector 3 class.
	*
	*	\tparam T	Type of the vector.
	*/
	template <typename T>
	struct Vec3
	{
		/// Type of the Vector.
		using Type = T;

		/// Vector's X component (axis value).
		T x = T();

		/// Vector's Y component (axis value).
		T y = T();

		/// Vector's Z component (axis value).
		T z = T();

//{ Constants

		/// Zero vector constant {0, 0, 0}.
		static const Vec3 Zero;

		/// One vector constant {1, 1, 1}.
		static const Vec3 One;

		/// Right vector constant {1, 0, 0}.
		static const Vec3 Right;

		/// Left vector constant {-1, 0, 0}.
		static const Vec3 Left;

		/// Up vector constant {0, 1, 0}.
		static const Vec3 Up;

		/// Down vector constant {0, -1, 0}.
		static const Vec3 Down;

		/// Down vector constant {0, 0, 1}.
		static const Vec3 Forward;

		/// Down vector constant {0, 0, -1}.
		static const Vec3 Backward;

//}


//{ Constructors

		/// \e Default constructor.
		Vec3() = default;


		/**
		*	\brief \e Value constructor.
		*
		*	\param[in] _x	X axis value.
		*	\param[in] _y	Y axis value.
		*	\param[in] _z	Z axis value.
		*/
		constexpr Vec3(T _x, T _y, T _z) noexcept :
			x{ _x },
			y{ _y },
			z{ _z }
		{
		}

		/**
		*	\brief \b Scale \e Value constructor.
		*
		*	\param[in] _scale	Axis value to apply on all axis.
		*/
		constexpr Vec3(T _scale) noexcept :
			x{ _scale },
			y{ _scale },
			z{ _scale }
		{
		}


		/// Default move constructor.
		Vec3(Vec3&&) = default;

		/// Default copy constructor.
		Vec3(const Vec3&) = default;

		/**
		*	\brief \e Value constructor from another Vec3 type.
		*
		*	\tparam TIn			Type of the input Vec3.
		*
		*	\param[in] _other	Vec3 to construct from.
		*/
		template <typename TIn>
		constexpr Vec3(const Vec3<TIn>& _other) noexcept :
			x{ static_cast<T>(_other.x) },
			y{ static_cast<T>(_other.y) },
			z{ static_cast<T>(_other.z) }
		{
		}

		/**
		*	\brief \e Value constructor from Vec2.
		*
		*	\tparam TIn			Type of the in Vec2.
		*
		*	\param[in] _other	Vec2 to construct from.
		*	\param[in] _z	Z axis value.
		*/
		template <typename TIn>
		constexpr Vec3(const Vec2<TIn>& _other, T _z = T(0)) noexcept :
			x{ static_cast<T>(_other.x) },
			y{ static_cast<T>(_other.y) },
			z{ _z }
		{
		}

		/**
		*	\brief \e Value constructor from Vec4.
		*
		*	\tparam TIn			Type of the in Vec4.
		*
		*	\param[in] _other	Vec4 to construct from.
		*/
		template <typename TIn>
		constexpr Vec3(const Vec4<TIn>& _other) noexcept :
			x{ static_cast<T>(_other.x) },
			y{ static_cast<T>(_other.y) },
			z{ static_cast<T>(_other.z) }
		{
		}

//}


//{ Equals

		/**
		*	\brief Whether this vector is a zero vector.
		*
		*	\return True if this is a zero vector.
		*/
		constexpr bool IsZero() const noexcept
		{
			return edo::Equals0(x) &&
				edo::Equals0(y) &&
				edo::Equals0(z);
		}

		/**
		*	\brief \e Compare 2 vector.
		*
		*	\param[in] _other		Other vector to compare to.
		*	\param[in] _epsilon		Epsilon value for threshold comparison.
		*
		*	\return Whether this and _other are equal.
		*/
		constexpr bool Equals(const Vec3& _other, T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept
		{
			return edo::Equals(x, _other.x, _epsilon) &&
				edo::Equals(y, _other.y, _epsilon) &&
				edo::Equals(z, _other.z, _epsilon);
		}


		/**
		*	\brief \e Compare 2 vector equality.
		*
		*	\param[in] _rhs		Other vector to compare to.
		*
		*	\return Whether this and _rhs are equal.
		*/
		constexpr bool operator==(const Vec3 & _rhs) const noexcept
		{
			return Equals(_rhs);
		}

		/**
		*	\brief \e Compare 2 vector inequality.
		*
		*	\param[in] _rhs		Other vector to compare to.
		*
		*	\return Whether this and _rhs are non-equal.
		*/
		constexpr bool operator!=(const Vec3 & _rhs) const noexcept
		{
			return !(*this == _rhs);
		}

//}


//{ Accessors

		/**
		*	\brief \e Getter of vector data
		*
		*	\return this vector as a T*.
		*/
		T* Data() noexcept
		{
			return &x;
		}

		/**
		*	\brief <em> Const Getter </em> of vector data
		*
		*	\return this vector as a const T*.
		*/
		const T* Data() const noexcept
		{
			return &x;
		}


		/**
		*	\brief \e Access operator by index: x, y, z using 0, 1, 2.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		T& operator[](uint32_t _index)
		{
			EDO_ASSERT(_index < 3u, Edo.Maths.Vec3, L"Index access out of range!");

			return Data()[_index];
		}

		/**
		*	\brief <em> Const Access </em> operator by index: x, y, z using 0, 1, 2.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		const T& operator[](uint32_t _index) const
		{
			EDO_ASSERT(_index < 3u, Edo.Maths.Vec3, L"Index access out of range!");

			return Data()[_index];
		}

//}


//{ Length

		/**
		*	\brief \e Getter of the \b length of this vector.
		*
		*	\return Length of this vector.
		*/
		constexpr T Length() const noexcept
		{
			const T l2 = SqrLength();

			return std::sqrt(l2);
		}

		/**
		*	\brief \e Getter of the <b> Squared Length </b> of this vector.
		*
		*	\return Squared Length of this vector.
		*/
		constexpr T SqrLength() const noexcept
		{
			return x * x + y * y + z * z;
		}

		/**
		*	\brief \b Normalize this vector.
		*
		*	\return self vector normalized.
		*/
		Vec3& Normalize() noexcept
		{
			const T norm = Length();
			
			EDO_ERROR(!Equals0(norm), Edo.Maths.Vec3, L"Normalize null vector!");

			x /= norm;
			y /= norm;
			z /= norm;

			return *this;
		}

		/**
		*	\brief \b Normalize this vector.
		*
		*	\return new normalized vector.
		*/
		Vec3 GetNormalized() const noexcept
		{
			Vec3 res = *this;
			res.Normalize();

			return res;
		}

		/**
		*	\brief Whether this vector is normalized.
		* 
		*	\param[in] _epsilon	Allowed threshold to accept equality.
		*
		*	\return True if this vector is normalized, otherwise false.
		*/
		constexpr bool IsNormalized(T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept
		{
			return edo::Equals1(SqrLength(), _epsilon);
		}

//}


//{ Project

		/**
		*	\brief \b Reflect this vector over the normal.
		*
		*	\param[in] _normal		Normal used for reflection.
		*	\param[in] _elasticity		Elasticity reflection coefficient (use 1.0f for full reflection).
		*
		*	\return new vector reflected.
		*/
		Vec3 Reflect(const Vec3& _normal, float _elasticity = 1.0f) const noexcept
		{
			return *this - ProjectOnToNormal(_normal) * (1.0f + _elasticity);
		}

		/**
		*	\brief \b Project this vector onto an other vector.
		*
		*	Reference: https://en.wikipedia.org/wiki/Vector_projection
		*
		*	\param[in] _other	Vector used for projection.
		*
		*	\return new  vector projected.
		*/
		Vec3 ProjectOnTo(const Vec3& _other) const noexcept
		{
			return Dot(*this, _other) / _other.SqrLength() * _other;
		}

		/**
		*	\brief \b Project this vector onto s normal.
		*
		*	Assume _normal is normalized.
		*	Use GetProjectOnTo() for non normalized vector.
		*	Reference: https://en.wikipedia.org/wiki/Vector_projection
		*
		*	\param[in] _normal		Normal used for projection.
		*
		*	\return new vector projected.
		*/
		Vec3 ProjectOnToNormal(const Vec3& _normal) const noexcept
		{
			EDO_WARN(_normal.IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Vec3,
				L"Normal should be normalized or use ProjectOnTo() instead!");

			return Dot(*this, _normal) * _normal;
		}

//}


//{ Dot/Cross

		/**
		*	\brief \e Compute the <b> Dot product </b> between _lhs and _rhs.
		*
		*	\param[in] _lhs		Left hand side operand to compute dot product with.
		*	\param[in] _rhs		Right hand side operand to compute dot product with.
		*
		*	\return <b> Dot product </b> between _lhs and _rhs.
		*/
		static constexpr T Dot(const Vec3& _lhs, const Vec3& _rhs) noexcept
		{
			return _lhs.x * _rhs.x +
				_lhs.y * _rhs.y +
				_lhs.z * _rhs.z;
		}

		/**
		*	\brief \e Compute the <b> Cross product </b> between _lhs and _rhs.
		*
		*	\param[in] _lhs		Left hand side operand to compute cross product with.
		*	\param[in] _rhs		Right hand side operand to compute cross product with.
		*
		*	\return <b> Cross product </b> between _lhs and _rhs.
		*/
		static constexpr Vec3<T> Cross(const Vec3& _lhs, const Vec3& _rhs) noexcept
		{
			return Vec3(
				_lhs.y * _rhs.z - _lhs.z * _rhs.y,
				_lhs.z * _rhs.x - _lhs.x * _rhs.z,
				_lhs.x * _rhs.y - _lhs.y * _rhs.x
			);
		}

//}


//{ Angle

		/**
		*	\brief \e Compute the <b> Signed Angle </b> between _lhs and _rhs.
		*
		*	\param[in] _start		Left hand side operand to compute angle with.
		*	\param[in] _end			Right hand side operand to compute angle with.
		*	\param[in] _normal		Normal of the plan between _lhs and _rhs, used to determine angle's sign.
		*
		*	\return <b> Signed Angle </b> between _start and _end.
		*/
		static Rad<T> Angle(const Vec3& _start, const Vec3& _end, const Vec3& _normal = Vec3::Up) noexcept
		{
			Rad<T> angle = AngleUnsigned(_start, _end);

			Vec3 cross = Cross(_start, _end);

			if (Dot(cross, _normal) < 0.0f)
				angle = -angle;

			return angle;
		}

		/**
		*	\brief \e Compute the <b> Unsigned Angle </b> between _lhs and _rhs.
		*
		*	\param[in] _start		Left hand side operand to compute angle with.
		*	\param[in] _end			Right hand side operand to compute angle with.
		*
		*	\return <b> Unsigned Angle </b> between _start and _end.
		*/
		static Rad<T> AngleUnsigned(const Vec3& _start, const Vec3& _end) noexcept
		{
			return ACos(Dot(_start, _end));
		}

//}


//{ Dist/Dir

		/**
		*	\brief \e Compute the <b> Distance </b> between _lhs and _rhs.
		*
		*	\param[in] _start		Left hand side operand to compute distance with.
		*	\param[in] _end			Right hand side operand to compute distance with.
		*
		*	\return <b> Distance </b> between _start and _end.
		*/
		static constexpr T Dist(const Vec3& _start, const Vec3& _end) noexcept
		{
			return (_start - _end).Length();
		}

		/**
		*	\brief \e Compute the <b> Squared Distance </b> between _lhs and _rhs.
		*
		*	\param[in] _start		Left hand side operand to compute squared distance with.
		*	\param[in] _end			Right hand side operand to compute squared distance with.
		*
		*	\return <b> Squared Distance </b> between _start and _end.
		*/
		static constexpr T SqrDist(const Vec3& _start, const Vec3& _end) noexcept
		{
			return (_start - _end).SqrLength();
		}

		/**
		*	\brief \e Compute the <b> Non-Normalized Direction </b> from _lhs and _rhs.
		*
		*	Direction get not normalized. Use DirN instead.
		*
		*	\param[in] _start		Left hand side operand to compute direction from.
		*	\param[in] _end			Right hand side operand to compute direction to
		*
		*	\return <b> Non-Normalized Direction </b> from _start and _end.
		*/
		static constexpr Vec3 Dir(const Vec3& _start, const Vec3& _end) noexcept
		{
			return _end - _start;
		}

		/**
		*	\brief \e Compute the <b> Normalized Direction </b> from _start to _end.
		*
		*	\param[in] _start		Starting point to compute direction from.
		*	\param[in] _end			ending point to compute direction to.
		*
		*	\return <b> Normalized Direction </b> from _start to _end.
		*/
		static constexpr Vec3 DirN(const Vec3& _start, const Vec3& _end) noexcept
		{
			return Dir(_start, _end).GetNormalized();
		}

//}


//{ Lerp

		/**
		*	\brief <b> Clamped Lerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Vec3 Lerp(const Vec3& _start, const Vec3& _end, AlphaT _alpha) noexcept
		{
			return edo::Lerp(_start, _end, _alpha);
		}

		/**
		*	\brief <b> Unclamped Lerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Vec3 LerpUnclamped(const Vec3& _start, const Vec3& _end, AlphaT _alpha) noexcept
		{
			return edo::LerpUnclamped(_start, _end, _alpha);
		}

		/**
		*	\brief <b> Clamped SLerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Slerp
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Vec3 SLerp(const Vec3& _start, const Vec3& _end, AlphaT _alpha) noexcept
		{
			return edo::SLerp(_start, _end, _alpha);
		}

		/**
		*	\brief <b> Unclamped SLerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Slerp
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Vec3 SLerpUnclamped(const Vec3& _start, const Vec3& _end, AlphaT _alpha) noexcept
		{
			return edo::SLerpUnclamped(_start, _end, _alpha);
		}

//}


//{ Operators

		/**
		*	\brief \e Default assignment move operator.
		*
		*	\return self vector assigned.
		*/
		Vec3& operator=(Vec3&&) = default;

		/**
		*	\brief \e Default assignment copy operator.
		*
		*	\return self vector assigned.
		*/
		Vec3& operator=(const Vec3&) = default;


		/**
		*	\brief \e Getter of the opposite signed vector.
		*
		*	\return new opposite signed vector.
		*/
		constexpr Vec3 operator-() const noexcept
		{
			return Vec3(-x, -y, -z);
		}

		/**
		*	\brief \b Scale each vector axis by _scale.
		* 
		*	\tparam TIn			Type of the input scale.
		*
		*	\param[in] _scale	Scale value to apply on all axis.
		*
		*	\return new vector scaled.
		*/
		template <typename TIn>
		Vec3 operator*(TIn _scale) const noexcept
		{
			return Vec3(
				x * _scale,
				y * _scale,
				z * _scale
			);
		}

		/**
		*	\brief <b> Inverse Scale </b> each vector axis by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Inverse scale value to apply on all axis.
		*
		*	\return new vector inverse-scaled.
		*/
		template <typename TIn>
		Vec3 operator/(TIn _scale) const noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Vec3, L"Divide vector by 0!");

			return Vec3(
				x / _scale,
				y / _scale,
				z / _scale
			);
		}

		/**
		*	\brief \b Add term by term vector values.
		*
		*	\param[in] _rhs		Vector to add.
		*
		*	\return new vector result.
		*/
		constexpr Vec3 operator+(const Vec3& _rhs) const noexcept
		{
			return Vec3(
				x + _rhs.x,
				y + _rhs.y,
				z + _rhs.z
			);
		}

		/**
		*	\brief \b Subtract term by term vector values.
		*
		*	\param[in] _rhs		Vector to substract.
		*
		*	\return new vector result.
		*/
		constexpr Vec3 operator-(const Vec3& _rhs) const noexcept
		{
			return Vec3(
				x - _rhs.x,
				y - _rhs.y,
				z - _rhs.z
			);
		}

		/**
		*	\brief \b Multiply term by term vector values.
		*
		*	\param[in] _rhs		Vector to multiply.
		*
		*	\return new vector result.
		*/
		constexpr Vec3 operator*(const Vec3& _rhs) const noexcept
		{
			return Vec3(
				x * _rhs.x,
				y * _rhs.y,
				z * _rhs.z
			);
		}

		/**
		*	\brief \b Divide term by term vector values.
		*
		*	\param[in] _rhs		Vector to divide.
		*
		*	\return new vector result.
		*/
		Vec3 operator/(const Vec3& _rhs) const noexcept
		{
			EDO_ERROR(!Equals0(_rhs.x), Edo.Maths.Vec3, L"Divide X Axis value by 0!");
			EDO_ERROR(!Equals0(_rhs.y), Edo.Maths.Vec3, L"Divide Y Axis value by 0!");
			EDO_ERROR(!Equals0(_rhs.z), Edo.Maths.Vec3, L"Divide Z Axis value by 0!");

			return Vec3(
				x / _rhs.x,
				y / _rhs.y,
				z / _rhs.z
			);
		}

		/**
		*	\brief \e Compute the <b> Dot product </b> between this and _rhs.
		*
		*	\param[in] _rhs		Right hand side operand vector to compute dot product with.
		*
		*	\return <b> Dot product </b> between this vector and _other.
		*/
		constexpr T operator|(const Vec3& _rhs) const noexcept
		{
			return Dot(*this, _rhs);
		}

		/**
		*	\brief \e Compute the <b> Cross product </b> between this and _rhs.
		*
		*	\param[in] _rhs		Right hand side operand vector to compute cross product with.
		*
		*	\return <b> Cross product </b> between this vector and _other.
		*/
		constexpr Vec3 operator^(const Vec3& _rhs) const noexcept
		{
			return Cross(*this, _rhs);
		}


		/**
		*	\brief \b Scale each vector axis by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Scale value to apply on all axis.
		*
		*	\return self vector scaled.
		*/
		template <typename TIn>
		Vec3& operator*=(TIn _scale) noexcept
		{
			x *= _scale;
			y *= _scale;
			z *= _scale;

			return *this;
		}

		/**
		*	\brief <b> Inverse Scale </b> each vector axis by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Scale value to apply on all axis.
		*
		*	\return self vector inverse-scaled.
		*/
		template <typename TIn>
		Vec3& operator/=(TIn _scale) noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Vec3, L"Divide vector by 0!");

			x /= _scale;
			y /= _scale;
			z /= _scale;

			return *this;
		}

		/**
		*	\brief \b Add term by term vector values.
		*
		*	\param[in] _rhs		Vector to add.
		*
		*	\return self vector result.
		*/
		Vec3& operator+=(const Vec3& _rhs) noexcept
		{
			x += _rhs.x;
			y += _rhs.y;
			z += _rhs.z;

			return *this;
		}

		/**
		*	\brief \b Substract term by term vector values.
		*
		*	\param[in] _rhs		Vector to substract.
		*
		*	\return self vector result.
		*/
		Vec3& operator-=(const Vec3& _rhs) noexcept
		{
			x -= _rhs.x;
			y -= _rhs.y;
			z -= _rhs.z;

			return *this;
		}

		/**
		*	\brief \b Multiply term by term vector values.
		*
		*	\param[in] _rhs		Vector to multiply.
		*
		*	\return self vector result.
		*/
		Vec3& operator*=(const Vec3& _rhs) noexcept
		{
			x *= _rhs.x;
			y *= _rhs.y;
			z *= _rhs.z;

			return *this;
		}

		/**
		*	\brief \b Divide term by term vector values.
		*
		*	\param[in] _rhs		Vector to divide.
		*
		*	\return self vector result.
		*/
		Vec3& operator/=(const Vec3& _rhs) noexcept
		{
			EDO_ERROR(!Equals0(_rhs.x), Edo.Maths.Vec3, L"Divide X Axis value by 0!");
			EDO_ERROR(!Equals0(_rhs.y), Edo.Maths.Vec3, L"Divide Y Axis value by 0!");
			EDO_ERROR(!Equals0(_rhs.z), Edo.Maths.Vec3, L"Divide Z Axis value by 0!");

			x /= _rhs.x;
			y /= _rhs.y;
			z /= _rhs.z;

			return *this;
		}

//}
	};


//{ Constants

	template <typename T>
	const Vec3<T> Vec3<T>::Zero{ 0, 0, 0 };

	template <typename T>
	const Vec3<T> Vec3<T>::One{ 1, 1, 1 };

	template <typename T>
	const Vec3<T> Vec3<T>::Right{ 1, 0, 0 };

	template <typename T>
	const Vec3<T> Vec3<T>::Left{ -1, 0, 0 };

	template <typename T>
	const Vec3<T> Vec3<T>::Up{ 0, 1, 0 };

	template <typename T>
	const Vec3<T> Vec3<T>::Down{ 0, -1, 0 };

	template <typename T>
	const Vec3<T> Vec3<T>::Forward{ 0, 0, 1 };

	template <typename T>
	const Vec3<T> Vec3<T>::Backward{ 0, 0, -1 };

//}


	/**
	*	\brief \b Scale each vector axis by _lhs.
	*
	*	\tparam TIn			Type of the input scale.
	* 
	*	\param[in] _lhs		Scale value to apply on all axis.
	*	\param[in] _rhs		Vector to scale.
	*
	*	\return new vector scaled.
	*/
	template <typename T, typename TIn>
	constexpr Vec3<T> operator*(TIn _lhs, const Vec3<T>& _rhs) noexcept
	{
		return _rhs * _lhs;
	}

	/**
	*	\brief <b> Inverse Scale </b> each vector axis by _lhs.
	*
	*	\tparam TIn			Type of the input scale.
	* 
	*	\param[in] _lhs		Inverse scale value to apply on all axis.
	*	\param[in] _rhs		Vector to scale.
	*
	*	\return new vector inverse-scaled.
	*/
	template <typename T, typename TIn>
	Vec3<T> operator/(TIn _lhs, const Vec3<T>& _rhs) noexcept
	{
		EDO_ERROR(!Equals0(_rhs.x), Edo.Maths.Vec3, L"Inverse scale X Axis value by 0!");
		EDO_ERROR(!Equals0(_rhs.y), Edo.Maths.Vec3, L"Inverse scale Y Axis value by 0!");
		EDO_ERROR(!Equals0(_rhs.z), Edo.Maths.Vec3, L"Inverse scale Z Axis value by 0!");

		return Vec3<T>(
			_lhs / _rhs.x,
			_lhs / _rhs.y,
			_lhs / _rhs.z
		);
	}


#if __has_include(<edo_debug.hpp>)
	template <typename T>
	std::string ToString(const Vec3<T> _vec) noexcept
	{
		return "Vec3{ X: " + edo::ToString(_vec.x) +
			"\tY: " + edo::ToString(_vec.y) +
			"\tZ: " + edo::ToString(_vec.z) + " }";
	}
#endif // edo_debug


//{ Aliases

	/// Alias for int32 Vec3.
	using Vec3i = Vec3<int32_t>;

	/// Alias for uint32 Vec3.
	using Vec3ui = Vec3<uint32_t>;

	/// Alias for float Vec3.
	using Vec3f = Vec3<float>;

	/// Alias for double Vec3.
	using Vec3d = Vec3<double>;


	/// Template alias of Vec3
	template <typename T>
	using Vector3 = Vec3<T>;

	/// Alias for int32 Vector3.
	using Vector3i = Vector3<int32_t>;

	/// Alias for uint32 Vector3.
	using Vector3ui = Vector3<uint32_t>;

	/// Alias for float Vector3.
	using Vector3f = Vector3<float>;

	/// Alias for double Vector3.
	using Vector3d = Vector3<double>;

//}

// ##############################################################


// ##############################################################
// #					VEC 4									#
// ##############################################################

	/**
	*	\brief \e Vector 4 class.
	*
	*	\tparam T	Type of the vector.
	*/
	template <typename T>
	struct Vec4
	{
		/// Type of the Vector.
		using Type = T;

		/// Vector's X component (axis value).
		T x = T();

		/// Vector's Y component (axis value).
		T y = T();

		/// Vector's Z component (axis value).
		T z = T();

		/// Vector's W component (stored after xyz).
		T w = T();


//{ Constructors

		/// \e Default constructor.
		Vec4() = default;

		/**
		*	\brief \e Value constructor.
		*
		*	\param[in] _x	X axis value.
		*	\param[in] _y	Y axis value.
		*	\param[in] _z	Z axis value.
		*	\param[in] _w	W axis value.
		*/
		constexpr Vec4(T _x, T _y, T _z, T _w) noexcept :
			x{ _x },
			y{ _y },
			z{ _z },
			w{ _w }
		{
		}

		/**
		*	\brief \b Scale \e Value constructor.
		*
		*	\param[in] _scale	Axis value to apply on all axis.
		*/
		constexpr Vec4(T _scale) noexcept :
			x{ _scale },
			y{ _scale },
			z{ _scale },
			w{ _scale }
		{
		}


		/// Default move constructor.
		Vec4(Vec4&&) = default;

		/// Default copy constructor.
		Vec4(const Vec4&) = default;

		/**
		*	\brief \e Value constructor from another Vec4 type.
		*
		*	\tparam TIn			Type of the input Vec3.
		*
		*	\param[in] _other	Vec4 to construct from.
		*/
		template <typename TIn>
		constexpr Vec4(const Vec4<TIn>&_other) noexcept :
			x{ static_cast<T>(_other.x) },
			y{ static_cast<T>(_other.y) },
			z{ static_cast<T>(_other.z) },
			w{ static_cast<T>(_other.w) }
		{
		}

		/**
		*	\brief \e Value constructor from Vec2.
		*
		*	\tparam TIn			Type of the in Vec2.
		*
		*	\param[in] _other	Vec2 to construct from.
		*	\param[in] _z		Z axis value.
		*	\param[in] _w		W axis value.
		*/
		template <typename TIn>
		constexpr Vec4(const Vec2<TIn>&_other, T _z = T(0), T _w = T(0)) noexcept :
			x{ static_cast<T>(_other.x) },
			y{ static_cast<T>(_other.y) },
			z{ _z },
			w{ _w }
		{
		}

		/**
		*	\brief \e Value constructor from 2 Vec2.
		*
		*	\tparam TIn			Type of the in Vec2.
		*
		*	\param[in] _v1		First Vec2 to construct from.
		*	\param[in] _v2		Second Vec2 to construct from.
		*/
		template <typename TIn>
		constexpr Vec4(const Vec2<TIn>&_v1, const Vec2<TIn>& _v2) noexcept :
			x{ static_cast<T>(_v1.x) },
			y{ static_cast<T>(_v1.y) },
			z{ static_cast<T>(_v2.x) },
			w{ static_cast<T>(_v2.y) }
		{
		}

		/**
		*	\brief \e Value constructor from Vec3.
		*
		*	\tparam TIn			Type of the in Vec3.
		*
		*	\param[in] _other	Vec4 to construct from.
		*	\param[in] _w		W axis value.
		*/
		template <typename TIn>
		constexpr Vec4(const Vec3<TIn>&_other, T _w = T(0)) noexcept :
			x{ static_cast<T>(_other.x) },
			y{ static_cast<T>(_other.y) },
			z{ static_cast<T>(_other.z) },
			w{ _w }
		{
		}

//}


//{ Equals

		/**
		*	\brief Whether this vector is a zero vector.
		*
		*	\return True if this is a zero vector.
		*/
		constexpr bool IsZero() const noexcept
		{
			return edo::Equals0(x) &&
				edo::Equals0(y) &&
				edo::Equals0(z) &&
				edo::Equals0(w);
		}

		/**
		*	\brief \e Compare 2 vector.
		*
		*	\param[in] _other		Other vector to compare to.
		*	\param[in] _epsilon		Epsilon value for threshold comparison.
		*
		*	\return Whether this and _other are equal.
		*/
		constexpr bool Equals(const Vec4& _other, T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept
		{
			return edo::Equals(x, _other.x, _epsilon) &&
				edo::Equals(y, _other.y, _epsilon) &&
				edo::Equals(z, _other.z, _epsilon) &&
				edo::Equals(w, _other.w, _epsilon);
		}


		/**
		*	\brief \e Compare 2 vector equality.
		*
		*	\param[in] _rhs		Other vector to compare to.
		*
		*	\return Whether this and _rhs are equal.
		*/
		constexpr bool operator==(const Vec4 & _rhs) const noexcept
		{
			return Equals(_rhs);
		}

		/**
		*	\brief \e Compare 2 vector inequality.
		*
		*	\param[in] _rhs		Other vector to compare to.
		*
		*	\return Whether this and _rhs are non-equal.
		*/
		constexpr bool operator!=(const Vec4 & _rhs) const noexcept
		{
			return !(*this == _rhs);
		}
//}


//{ Acccessors

		/**
		*	\brief \e Getter of vector data
		*
		*	\return this vector as a T*.
		*/
		T* Data() noexcept
		{
			return &x;
		}

		/**
		*	\brief <em> Const Getter </em> of vector data
		*
		*	\return this vector as a const T*.
		*/
		const T* Data() const noexcept
		{
			return &x;
		}


		/**
		*	\brief \e Access operator by index: x, y, z, w using 0, 1, 2, 3.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		T& operator[](uint32_t _index)
		{
			EDO_ASSERT(_index < 4u, Edo.Maths.Vec4, L"Index access out of range!");

			return Data()[_index];
		}

		/**
		*	\brief <em> Const Access </em> operator by index: x, y, z,w  using 0, 1, 2, 3.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		const T& operator[](uint32_t _index) const
		{
			EDO_ASSERT(_index < 4u, Edo.Maths.Vec4, L"Index access out of range!");

			return Data()[_index];
		}

//}


//{ Operators

		/**
		*	\brief \e Default assignment move operator.
		*
		*	\return self vector assigned.
		*/
		Vec4& operator=(Vec4&&) = default;

		/**
		*	\brief \e Default assignment copy operator.
		*
		*	\return self vector assigned.
		*/
		Vec4& operator=(const Vec4&) = default;


		/**
		*	\brief \e Getter of the opposite signed vector.
		*
		*	\return new opposite signed vector.
		*/
		constexpr Vec4 operator-() const noexcept
		{
			return Vec4(-x, -y, -z, -w);
		}

		/**
		*	\brief \b Scale each vector axis by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Scale value to apply on all axis.
		*
		*	\return new vector scaled.
		*/
		template <typename TIn>
		Vec4 operator*(TIn _scale) const noexcept
		{
			return Vec4(
				x * _scale,
				y * _scale,
				z * _scale,
				w * _scale
			);
		}

		/**
		*	\brief <b> Inverse Scale </b> each vector axis by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Inverse scale value to apply on all axis.
		*
		*	\return new vector inverse-scaled.
		*/
		template <typename TIn>
		Vec4 operator/(TIn _scale) const noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Vec4, L"Divide vector by 0!");

			return Vec4(
				x / _scale,
				y / _scale,
				z / _scale,
				w / _scale
			);
		}

		/**
		*	\brief \b Add term by term vector values.
		*
		*	\param[in] _rhs		Vector to add.
		*
		*	\return new vector result.
		*/
		constexpr Vec4 operator+(const Vec4& _rhs) const noexcept
		{
			return Vec4(
				x + _rhs.x,
				y + _rhs.y,
				z + _rhs.z,
				w + _rhs.w
			);
		}

		/**
		*	\brief \b Subtract term by term vector values.
		*
		*	\param[in] _rhs		Vector to substract.
		*
		*	\return new vector result.
		*/
		constexpr Vec4 operator-(const Vec4& _rhs) const noexcept
		{
			return Vec4(
				x - _rhs.x,
				y - _rhs.y,
				z - _rhs.z,
				w - _rhs.w
			);
		}

		/**
		*	\brief \b Multiply term by term vector values.
		*
		*	\param[in] _rhs		Vector to multiply.
		*
		*	\return new vector result.
		*/
		constexpr Vec4 operator*(const Vec4& _rhs) const noexcept
		{
			return Vec4(
				x * _rhs.x,
				y * _rhs.y,
				z * _rhs.z,
				w * _rhs.w
			);
		}

		/**
		*	\brief \b Divide term by term vector values.
		*
		*	\param[in] _rhs		Vector to divide.
		*
		*	\return new vector result.
		*/
		Vec4 operator/(const Vec4& _rhs) const noexcept
		{
			EDO_ERROR(!Equals0(_rhs.x), Edo.Maths.Vec4, L"Divide X Axis value by 0!");
			EDO_ERROR(!Equals0(_rhs.y), Edo.Maths.Vec4, L"Divide Y Axis value by 0!");
			EDO_ERROR(!Equals0(_rhs.z), Edo.Maths.Vec4, L"Divide Z Axis value by 0!");
			EDO_ERROR(!Equals0(_rhs.w), Edo.Maths.Vec4, L"Divide W Axis value by 0!");

			return Vec4(
				x / _rhs.x,
				y / _rhs.y,
				z / _rhs.z,
				w / _rhs.w
			);
		}


		/**
		*	\brief \b Scale each vector axis by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Scale value to apply on all axis.
		*
		*	\return self vector scaled.
		*/
		template <typename TIn>
		Vec4& operator*=(TIn _scale) noexcept
		{
			x *= _scale;
			y *= _scale;
			z *= _scale;
			w *= _scale;

			return *this;
		}

		/**
		*	\brief <b> Inverse Scale </b> each vector axis by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Scale value to apply on all axis.
		*
		*	\return self vector inverse-scaled.
		*/
		template <typename TIn>
		Vec4& operator/=(TIn _scale) noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Vec4, L"Divide vector by 0!");

			x /= _scale;
			y /= _scale;
			z /= _scale;
			w /= _scale;

			return *this;
		}

		/**
		*	\brief \b Add term by term vector values.
		*
		*	\param[in] _rhs		Vector to add.
		*
		*	\return self vector result.
		*/
		Vec4& operator+=(const Vec4& _rhs) noexcept
		{
			x += _rhs.x;
			y += _rhs.y;
			z += _rhs.z;
			w += _rhs.w;

			return *this;
		}

		/**
		*	\brief \b Substract term by term vector values.
		*
		*	\param[in] _rhs		Vector to substract.
		*
		*	\return self vector result.
		*/
		Vec4& operator-=(const Vec4& _rhs) noexcept
		{
			x -= _rhs.x;
			y -= _rhs.y;
			z -= _rhs.z;
			w -= _rhs.w;

			return *this;
		}

		/**
		*	\brief \b Multiply term by term vector values.
		*
		*	\param[in] _rhs		Vector to multiply.
		*
		*	\return self vector result.
		*/
		Vec4& operator*=(const Vec4& _rhs) noexcept
		{
			x *= _rhs.x;
			y *= _rhs.y;
			z *= _rhs.z;
			w *= _rhs.w;

			return *this;
		}

		/**
		*	\brief \b Divide term by term vector values.
		*
		*	\param[in] _rhs		Vector to divide.
		*
		*	\return self vector result.
		*/
		Vec4& operator/=(const Vec4& _rhs) noexcept
		{
			EDO_ERROR(!Equals0(_rhs.x), Edo.Maths.Vec4, L"Divide X Axis value by 0!");
			EDO_ERROR(!Equals0(_rhs.y), Edo.Maths.Vec4, L"Divide Y Axis value by 0!");
			EDO_ERROR(!Equals0(_rhs.z), Edo.Maths.Vec4, L"Divide Z Axis value by 0!");
			EDO_ERROR(!Equals0(_rhs.w), Edo.Maths.Vec4, L"Divide W Axis value by 0!");

			x /= _rhs.x;
			y /= _rhs.y;
			z /= _rhs.z;
			w /= _rhs.w;

			return *this;
		}
//}
	};


	/**
	*	\brief \b Scale each vector axis by _lhs.
	*
	*	\tparam TIn			Type of the input scale.
	* 
	*	\param[in] _lhs		Scale value to apply on all axis.
	*	\param[in] _rhs		Vector to scale.
	*
	*	\return new vector scaled.
	*/
	template <typename T, typename TIn>
	constexpr Vec4<T> operator*(TIn _lhs, const Vec4<T>& _rhs) noexcept
	{
		return _rhs * _lhs;
	}

	/**
	*	\brief <b> Inverse Scale </b> each vector axis by _lhs.
	*
	*	\tparam TIn			Type of the input scale.
	* 
	*	\param[in] _lhs		Inverse scale value to apply on all axis.
	*	\param[in] _rhs		Vector to scale.
	*
	*	\return new vector inverse-scaled.
	*/
	template <typename T, typename TIn>
	Vec4<T> operator/(TIn _lhs, const Vec4<T>& _rhs) noexcept
	{
		EDO_ERROR(!Equals0(_rhs.x), Edo.Maths.Vec4, L"Inverse scale X Axis value by 0!");
		EDO_ERROR(!Equals0(_rhs.y), Edo.Maths.Vec4, L"Inverse scale Y Axis value by 0!");
		EDO_ERROR(!Equals0(_rhs.z), Edo.Maths.Vec4, L"Inverse scale Z Axis value by 0!");
		EDO_ERROR(!Equals0(_rhs.w), Edo.Maths.Vec4, L"Inverse scale W Axis value by 0!");

		return Vec4<T>(
			_lhs / _rhs.x,
			_lhs / _rhs.y,
			_lhs / _rhs.z,
			_lhs / _rhs.w
		);
	}


#if __has_include(<edo_debug.hpp>)
	template <typename T>
	std::string ToString(const Vec4<T> _vec) noexcept
	{
		return "Vec4{ X: " + edo::ToString(_vec.x) +
			"\tY: " + edo::ToString(_vec.y) +
			"\tZ: " + edo::ToString(_vec.z) +
			"\tW: " + edo::ToString(_vec.w) + " }";
	}
#endif // edo_debug


//{ Aliases

	/// Alias for int32 Vec4.
	using Vec4i = Vec4<int32_t>;

	/// Alias for uint32 Vec4.
	using Vec4ui = Vec4<uint32_t>;

	/// Alias for float Vec4.
	using Vec4f = Vec4<float>;

	/// Alias for double Vec4.
	using Vec4d = Vec4<double>;


	/// Template alias of Vec4
	template <typename T>
	using Vector4 = Vec4<T>;

	/// Alias for int32 Vector4.
	using Vector4i = Vector4<int32_t>;

	/// Alias for uint32 Vector4.
	using Vector4ui = Vector4<uint32_t>;

	/// Alias for float Vector4.
	using Vector4f = Vector4<float>;

	/// Alias for double Vector4.
	using Vector4d = Vector4<double>;

//}

// ##############################################################


// ##############################################################
// #					QUAT									#
// ##############################################################

	/**
	*	\brief \e Quaternion class.
	*
	*	\tparam T	Type of the Quaternion.
	*/
	template <typename T>
	struct Quat
	{
		/// Type of the Quaternion.
		using Type = T;


		/// Quaternion's W component (Real value).
		T w = T(1);

		/// Quaternion's X component (i axis).
		T x = T();

		/// Quaternion's Y component (j axis).
		T y = T();

		/// Quaternion's Z component (k axis).
		T z = T();


//{ Constants

		/// Zero quaternion constant { 0, 0, 0, 0 }
		static const Quat Zero;

		/// Identity quaternion constant { 1, 0, 0, 0 }
		static const Quat Identity;

//}


//{ Constructors

		/// \e Default constructor.
		Quat() = default;

		/**
		*	\brief \e Value constructor.
		*
		*	\param[in] _w	W value.
		*	\param[in] _x	X value.
		*	\param[in] _y	Y value.
		*	\param[in] _z	Z value.
		*/
		constexpr Quat(T _w, T _x, T _y, T _z) noexcept :
			w{ _w },
			x{ _x },
			y{ _y },
			z{ _z }
		{
		}


		/// Default move constructor.
		Quat(Quat&&) = default;

		/// Default copy constructor.
		Quat(const Quat&) = default;

		/**
		*	\brief \e Value constructor from another quaternion type.
		*
		*	\tparam TIn			Type of the input quaternion.
		*
		*	\param[in] _other	Quat to construct from.
		*/
		template <typename TIn>
		constexpr Quat(const Quat<TIn>& _other) noexcept :
			w{ static_cast<T>(_other.w) },
			x{ static_cast<T>(_other.x) },
			y{ static_cast<T>(_other.y) },
			z{ static_cast<T>(_other.z) }
		{
		}


		/**
		*	\brief \e Value constructor angle and axis.
		*
		*	\param[in] _angle	Angle rotation in Degree.
		*	\param[in] _axis	Axis rotation.
		*/
		Quat(Deg<T> _angle, const Vec3<T>& _axis) noexcept
		{
			const Rad<T> halfAngle = _angle / T(2.0);

			w = Cos(halfAngle);

			EDO_WARN(_axis.IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Quat, L"Axis should be normalized!");

			// Quaternion imaginary axis.
			Vec3<T>& imgAxis = ImgAxis();
			imgAxis = _axis * Sin(halfAngle);
		}

//}


//{ Equals

		/**
		*	\brief Whether this quaternion is a zero quaternion.
		*
		*	\return True if this is a zero quaternion.
		*/
		constexpr bool IsZero() const noexcept
		{
			return edo::Equals0(w) &&
				edo::Equals0(x) &&
				edo::Equals0(y) &&
				edo::Equals0(z);
		}

		/**
		*	\brief Whether this quaternion is an identity quaternion.
		*
		*	\return True if this is an identity quaternion.
		*/
		constexpr bool IsIdentity() const noexcept
		{
			return edo::Equals1(w) &&
				edo::Equals0(x) &&
				edo::Equals0(y) &&
				edo::Equals0(z);
		}

		/**
		*	\brief \e Compare 2 quaternion.
		*
		*	\param[in] _other		Other quaternion to compare to.
		*	\param[in] _epsilon		Epsilon value for threshold comparison.
		*
		*	\return Whether this and _other are equal.
		*/
		constexpr bool Equals(const Quat& _other, T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept
		{
			return edo::Equals(w, _other.w, _epsilon) &&
				edo::Equals(x, _other.x, _epsilon) &&
				edo::Equals(y, _other.y, _epsilon) &&
				edo::Equals(z, _other.z, _epsilon);
		}


		/**
		*	\brief \e Compare 2 quaternion equality.
		*
		*	\param[in] _rhs		Other quaternion to compare to.
		*
		*	\return Whether this and _rhs are equal.
		*/
		constexpr bool operator==(const Quat<T>& _rhs) const noexcept
		{
			return Equals(_rhs);
		}

		/**
		*	\brief \e Compare 2 quaternion inequality.
		*
		*	\param[in] _rhs		Other quaternion to compare to.
		*
		*	\return Whether this and _rhs are non-equal.
		*/
		constexpr bool operator!=(const Quat<T>& _rhs) const noexcept
		{
			return !(*this == _rhs);
		}

//}


//{ Accessors

		/**
		*	\brief \e Getter of quaternion data
		*
		*	\return this quaternion as a T*.
		*/
		T* Data() noexcept
		{
			return &w;
		}

		/**
		*	\brief <em> Const Getter </em> of quaternion data
		*
		*	\return this quaternion as a const T*.
		*/
		const T* Data() const noexcept
		{
			return &w;
		}


		/**
		*	\brief \e Access operator by index.
		*
		*	\param[in] _index	Index to access: 0 == w, 1 == x, 2 == y, 3 == z.
		*
		*	\return T value at index.
		*/
		T& operator[](uint32_t _index)
		{
			EDO_ASSERT(_index < 4u, Edo.Maths.Quat, L"Index access out of range!");

			return Data()[_index];
		}

		/**
		*	\brief <em> Const Access </em> operator by index.
		*
		*	\param[in] _index	Index to access: 0 == w, 1 == x, 2 == y, 3 == z.
		*
		*	\return T value at index.
		*/
		T operator[](uint32_t _index) const
		{
			EDO_ASSERT(_index < 4u, Edo.Maths.Quat, L"Index access out of range!");

			return Data()[_index];
		}

//}


//{ Length

		/**
		*	\brief \e Getter of the \b length of this quaternion.
		*
		*	\return Length of this quaternion.
		*/
		T Length() const noexcept
		{
			const T l2 = SqrLength();

			return std::sqrt(l2);
		}

		/**
		*	\brief \e Getter of the <b> Squared Length </b> of this quaternion.
		*
		*	\return Squared Length of this quaternion.
		*/
		T SqrLength() const noexcept
		{
			return w * w + x * x + y * y + z * z;
		}


		/**
		*	\brief \b Normalize this quaternion.
		*
		*	\return self quaternion normalized.
		*/
		Quat& Normalize() noexcept
		{
			const T norm = Length();

			EDO_ERROR(!Equals0(norm), Edo.Maths.Quat, L"Normalize null quaternion!");

			w /= norm;
			x /= norm;
			y /= norm;
			z /= norm;

			return *this;
		}

		/**
		*	\brief \b Normalize this quaternion.
		*
		*	\return new normalized quaternion.
		*/
		Quat GetNormalized() const noexcept
		{
			const T norm = Length();

			EDO_ERROR(!Equals0(norm), Edo.Maths.Quat, L"Normalize null quaternion!");

			return Quat(
				w / norm,
				x / norm,
				y / norm,
				z / norm
			);
		}

		/**
		*	\brief Whether this quaternion is normalized.
		* 
		*	\param[in] _epsilon		Epsilon value for threshold comparison.
		*
		*	\return True if this quaternion is normalized, otherwise false.
		*/
		bool IsNormalized(T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept
		{
			return edo::Equals1(SqrLength(), _epsilon);
		}

//}


//{ Inverse

		/**
		*	\brief \b Inverse this quaternion.
		*	Quaternion should be normalized.
		*
		*	\return self quaternion inversed.
		*/
		Quat& Inverse() noexcept
		{
			EDO_WARN(IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Quat, L"Quaternion should be normalized!");

			// Inverse of normalized quaternion is conjugate.

			x = -x;
			y = -y;
			z = -z;

			return *this;
		}

		/**
		*	\brief \b Inverse this quaternion.
		*	Quaternion should be normalized.
		*
		*	\return new quaternion inversed.
		*/
		constexpr Quat GetInversed() const noexcept
		{
			EDO_WARN(IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Quat, L"Quaternion should be normalized!");

			// Inverse of normalized quaternion is conjugate.

			return Quat(w, -x, -y, -z);
		}

//}


//{ Angle/Axis

		/**
		*	\brief \e Getter of quaternion's imaginary axis.
		*
		*	Get the values of i, j and k axis (x, y, z).
		*
		*	\return Vec3<T> imaginary axis of this quaternion.
		*/
		Vec3<T>& ImgAxis() noexcept
		{
			return reinterpret_cast<Vec3<T>&>(x);
		}

		/**
		*	\brief \e <em> Const Getter </em> of quaternion's imaginary axis.
		*
		*	Get the values of i, j and k axis (x, y, z).
		*
		*	\return const Vec3<T> imaginary axis of this quaternion.
		*/
		const Vec3<T>& ImgAxis() const noexcept
		{
			return reinterpret_cast<const Vec3<T>&>(x);
		}

		/**
		*	\brief \e Getter of the angle handled by this quaternion.
		*
		*	\return Angle of the quaternion.
		*/
		constexpr Rad<T> GetAngle() const noexcept
		{
			return ACos(w) * T(2.0);
		}

		/**
		*	\brief \e Getter of the axis handled by this quaternion.
		*
		*	\return Axis of the quaternion.
		*/
		constexpr Vec3<T> GetAxis() const noexcept
		{
			EDO_WARN(!IsIdentity(), Edo.Maths.Quat, L"Get axis of an idendity quaternion (Vec3::Zero).");

			const Rad<T> halfAngle = ACos(w);

			return (ImgAxis() / Sin(halfAngle)).GetNormalized();
		}

//}


//{ Rotate

		/**
		*	\brief \b Rotate _other quaternion by this quaternion.
		*
		*	Multiply two quaternions.
		*	Quaternion must be normalized.
		*
		*	\param[in] _other		Quaternion to rotate.
		*
		*	\return new rotated quaternion.
		*/
		Quat<T> Rotate(const Quat<T>& _other) const noexcept
		{
			EDO_WARN(IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Quat,
				L"Quaternion should be normalized for multiplication. `this` quaternion is not normalized!");
			EDO_WARN(_other.IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Quat,
				L"Quaternion should be normalized for multiplication. `other` quaternion is not normalized!");

			T resW = w * _other.w - x * _other.x - y * _other.y - z * _other.z;
			T resX = w * _other.x + x * _other.w + y * _other.z - z * _other.y;
			T resY = w * _other.y - x * _other.z + y * _other.w + z * _other.x;
			T resZ = w * _other.z + x * _other.y - y * _other.x + z * _other.w;

			return Quat(resW, resX, resY, resZ);
		}

		/**
		*	\brief \b Rotate _vec vector by this quaternion.
		*
		*	Apply quaternion rotation to vector.
		*	Quaternion must be normalized.
		*
		*	\param[in] _vec		Vector to rotate.
		*
		*	\return new rotated vector.
		*/
		constexpr Vec3<T> Rotate(const Vec3<T>& _vec) const noexcept
		{
			EDO_WARN(IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Quat,
				L"Quaternion should be normalized for multiplication. `this` quaternion is not normalized!");

			// Quaternion-vector multiplication optimization:
			// http://people.csail.mit.edu/bkph/articles/Quaternions.pdf

			// v' = q * p * q-1
			// Pure imaginary optimization:
			// v' = v + q * 2.0f * (q X v) + q * 2.0f * (q X v).
			// v' = v + q * (     A     ) + q * (      A      ).

			const Vec3<T>& imgAxis = ImgAxis();

			// Compute A = 2.0f * (q X v).
			const Vec3<T> A = T(2.0) * Vec3<T>::Cross(imgAxis, _vec);

			return _vec + (w * A) + Vec3<T>::Cross(imgAxis, A);
		}

		/**
		*	\brief \b Un-Rotate _other quaternion by this quaternion.
		*
		*	Apply the inverse rotation multiplication.
		*	Quaternion must be normalized.
		*
		*	\param[in] _other		Quaternion to un-rotate.
		*
		*	\return new un-rotated quaternion.
		*/
		Quat<T> UnRotate(const Quat<T>& _other) const noexcept
		{
			return GetInversed().Rotate(_other);
		}

		/**
		*	\brief \b Un-Rotate _vec vector by this quaternion.
		*
		*	Apply the inverse rotation to vector.
		*	Quaternion must be normalized.
		*
		*	\param[in] _vec		Vector to un-rotate.
		*
		*	\return new un-rotated vector.
		*/
		constexpr Vec3<T> UnRotate(const Vec3<T>& _vec) const noexcept
		{
			return GetInversed().Rotate(_vec);
		}

		/**
		*	\brief \e Getter of Right vector (X axis) rotated by this quaternion.
		*
		*	\return rotated right vector normalized.
		*/
		constexpr Vec3<T> RightVector() const noexcept
		{
			return Rotate(Vec3<T>::Right);
		}

		/**
		*	\brief \e Getter of Up vector (Y axis) rotated by this quaternion.
		*
		*	\return rotated up vector normalized.
		*/
		constexpr Vec3<T> UpVector() const noexcept
		{
			return Rotate(Vec3<T>::Up);
		}

		/**
		*	\brief \e Getter of Forward vector (Z axis) rotated by this quaternion.
		*
		*	\return rotated forward vector normalized.
		*/
		constexpr Vec3<T> ForwardVector() const noexcept
		{
			return Rotate(Vec3<T>::Forward);
		}

//}


//{ Euler

		/**
		*	\brief \e Convert this quaternion into euler angles.
		* 
		*	Euler norm:
		*	X-Axis: Pitch
		*	Y-Axis: Yaw
		*	Z-Axis: Roll
		*
		*	\return Euler angles.
		*/
		Vec3<Rad<T>> ToEuler() const noexcept
		{
			/**
			*	Pitch, Yaw, Roll principle applied to Edo's coordinates system.
			*
			*	Pitch: X-Axis.
			*	Origin at the center of gravity and is directed to the right.
			*	A positive pitching motion raises the nose of the aircraft and lowers the tail.
			*
			*	Yaw: -1 * Y-Axis.
			*	Origin at the center of gravity and is directed towards the bottom of the aircraft.
			*	A positive yawing motion moves the nose of the aircraft to the right.
			*
			*	Roll: Z-Axis.
			*	Origin at the center of gravity and is directed forward, parallel to the fuselage reference line.
			*	A positive rolling motion lifts the left wing and lowers the right wing.
			*
			*	Source: https://en.wikipedia.org/wiki/Aircraft_principal_axes
			*/

			/**
			*	Pitch, Yaw, Roll formula  applied to Edo's coordinates system.
			*	Source: https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
			*/

			Vec3<Rad<T>> result;

			// Pitch - X axis
			{
				T cosPitch = 1 - 2 * (x * x + y * y);
				const T sinPitch = 2 * (w * x + y * z);

				// Handle floating-point precision.
				if (edo::Equals0(cosPitch))
					cosPitch = T(0.0);


				result.x = ATan2(sinPitch, cosPitch);
			}


			// Yaw - Y axis
			{
				T sinYaw = 2 * (w * y - z * x);

				// Handle floating-point precision.
				if (edo::Equals1(sinYaw))
					sinYaw = T(1.0);


				if (std::abs(sinYaw) > 1) // 90 degrees if out of range.
					result.y = std::copysign(edo::PiOv4<T> * edo::RadToDeg<T>, sinYaw);
				else
					result.y = ASin(sinYaw);
			}


			// Roll - Z axis
			{
				T cosRoll = 1 - 2 * (y * y + z * z);
				const T sinRoll = 2 * (w * z + x * y);

				// Handle floating-point precision.
				if (edo::Equals0(cosRoll))
					cosRoll = T(0.0);


				result.z = ATan2(sinRoll, cosRoll);
			}

			return result;
		}

		/**
		*	\brief \e Create quaternion from euler angles in degrees.
		*
		*	\param[in] _angles	Euler angles in degree (using Engine euler norm).
		* 
		*	Euler norm:
		*	X-Axis: Pitch
		*	Y-Axis: Yaw
		*	Z-Axis: Roll
		*
		*	\return Quaternion from angles.
		*/
		static Quat FromEuler(const Vec3<Rad<T>>& _angles) noexcept
		{
			/**
			*	Pitch, Yaw, Roll principle applied to Edo's coordinates system.
			*
			*	Pitch: X-Axis.
			*	Origin at the center of gravity and is directed to the right.
			*	A positive pitching motion raises the nose of the aircraft and lowers the tail.
			*
			*	Yaw: -1 * Y-Axis.
			*	Origin at the center of gravity and is directed towards the bottom of the aircraft.
			*	A positive yawing motion moves the nose of the aircraft to the right.
			*
			*	Roll: Z-Axis.
			*	Origin at the center of gravity and is directed forward, parallel to the fuselage reference line.
			*	A positive rolling motion lifts the left wing and lowers the right wing.
			*
			*	Source: https://en.wikipedia.org/wiki/Aircraft_principal_axes
			*/

			/**
			*	Pitch, Yaw, Roll formula  applied to Edo's coordinates system.
			*	Source: https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
			*/

			Vec3<Rad<T>> halfRadAngles = _angles * 0.5;

			const T cosPitch = Cos(halfRadAngles.x);
			const T sinPitch = Sin(halfRadAngles.x);

			const T cosYaw = Cos(halfRadAngles.y);
			const T sinYaw = Sin(halfRadAngles.y);

			const T cosRoll = Cos(halfRadAngles.z);
			const T sinRoll = Sin(halfRadAngles.z);

			return Quat(
				cosPitch * cosYaw * cosRoll + sinPitch * sinYaw * sinRoll,
				sinPitch * cosYaw * cosRoll - cosPitch * sinYaw * sinRoll,
				cosPitch * sinYaw * cosRoll + sinPitch * cosYaw * sinRoll,
				cosPitch * cosYaw * sinRoll - sinPitch * sinYaw * cosRoll
			);
		}

//}


//{ Dot

		/**
		*	\brief \e Compute the <b> Dot product </b> between _lhs and _rhs.
		*
		*	\param[in] _lhs		Left hand side operand to compute dot product with.
		*	\param[in] _rhs		Right hand side operand to compute dot product with.
		*
		*	\return <b> Dot product </b> between _lhs and _rhs.
		*/
		static T Dot(const Quat& _lhs, const Quat& _rhs) noexcept
		{
			return _lhs.w * _rhs.w +
				_lhs.x * _rhs.x +
				_lhs.y * _rhs.y +
				_lhs.z * _rhs.z;
		}

//}


//{ Lerp

		/**
		*	\brief <b> Clamped Lerp </b> from _start to _end at _alpha.
		*
		*	_start and _end should be normalized.
		*	Result quaternion is normalized.
		*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Quat Lerp(const Quat& _start, const Quat& _end, AlphaT _alpha)
		{
			EDO_WARN(_start.IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Quat,
				L"Quaternion should be normalized for multiplication. `start` quaternion is not normalized!");
			EDO_WARN(_end.IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Quat,
				L"Quaternion should be normalized for multiplication. `end` quaternion is not normalized!");

			return edo::Lerp(_start, _end, _alpha).GetNormalized();
		}

		/**
		*	\brief <b> Unclamped Lerp </b> from _start to _end at _alpha.
		*
		*	_start and _end should be normalized.
		*	Result quaternion is normalized.
		*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Quat LerpUnclamped(const Quat& _start, const Quat& _end, AlphaT _alpha)
		{
			EDO_WARN(_start.IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Quat,
				L"Quaternion should be normalized for multiplication. `start` quaternion is not normalized!");
			EDO_WARN(_end.IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Quat,
				L"Quaternion should be normalized for multiplication. `end` quaternion is not normalized!");

			return edo::LerpUnclamped(_start, _end, _alpha).GetNormalized();
		}

		/**
		*	\brief <b> Clamped SLerp </b> from _start to _end at _alpha.
		*
		*	_start and _end should be normalized.
		*	Result quaternion is normalized.
		*	Reference: https://en.wikipedia.org/wiki/Slerp
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Quat SLerp(const Quat& _start, const Quat& _end, AlphaT _alpha)
		{
			EDO_WARN(_start.IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Quat,
				L"Quaternion should be normalized for multiplication. `start` quaternion is not normalized!");
			EDO_WARN(_end.IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Quat,
				L"Quaternion should be normalized for multiplication. `end` quaternion is not normalized!");

			return edo::SLerp(_start, _end, _alpha).GetNormalized();
		}

		/**
		*	\brief <b> Unclamped SLerp </b> from _start to _end at _alpha.
		*
		*	_start and _end should be normalized.
		*	Result quaternion is normalized.
		*	Reference: https://en.wikipedia.org/wiki/Slerp
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Quat SLerpUnclamped(const Quat& _start, const Quat& _end, AlphaT _alpha)
		{
			EDO_WARN(_start.IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Quat,
				L"Quaternion should be normalized for multiplication. `start` quaternion is not normalized!");
			EDO_WARN(_end.IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Quat,
				L"Quaternion should be normalized for multiplication. `end` quaternion is not normalized!");

			return edo::SLerpUnclamped(_start, _end, _alpha).GetNormalized();
		}

//}


//{ Operators

		/**
		*	\brief \e Default assignment move operator.
		* 
		*	\return self vector assigned.
		*/
		Quat& operator=(Quat&&) = default;

		/**
		*	\brief \e Default assignment copy operator.
		*
		*	\return self vector assigned.
		*/
		Quat& operator=(const Quat&) = default;


		/**
		*	\brief \e Getter of the opposite signed quaternion.
		*
		*	\return new opposite signed quaternion.
		*/
		constexpr Quat operator-() const noexcept
		{
			return Quat(-w, -x, -y, -z);
		}

		/**
		*	\brief \b Scale each quaternion components by _scale.
		*
		*	\param[in] _scale	Scale value to apply on components.
		*
		*	\return new quaternion scaled.
		*/
		Quat operator*(T _scale) const noexcept
		{
			return Quat(
				w * _scale,
				x * _scale,
				y * _scale,
				z * _scale
			);
		}

		/**
		*	\brief <b> Inverse Scale </b> each quaternion components by _scale.
		*
		*	\param[in] _scale	Inverse scale value to apply on all components.
		*
		*	\return new quaternion inverse-scaled.
		*/
		Quat operator/(T _scale) const noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Quat, L"Divide quaternion by 0!");

			return Quat(
				w / _scale,
				x / _scale,
				y / _scale,
				z / _scale
			);
		}

		/**
		*	\brief \b Add term by term quaternion values.
		*
		*	\param[in] _rhs		Quaternion to add.
		*
		*	\return new quaternion result.
		*/
		Quat operator+(const Quat& _rhs) const noexcept
		{
			return Quat(
				w + _rhs.w,
				x + _rhs.x,
				y + _rhs.y,
				z + _rhs.z
			);
		}

		/**
		*	\brief \b Subtract term by term quaternion values.
		*
		*	\param[in] _rhs		Quaternion to substract.
		*
		*	\return new quaternion result.
		*/
		Quat operator-(const Quat& _rhs) const noexcept
		{
			return Quat(
				w - _rhs.w,
				x - _rhs.x,
				y - _rhs.y,
				z - _rhs.z
			);
		}

		/**
		*	\brief \b Multiply quaternion to compute rotation.
		*
		*	Rotate _rhs by this (ie: this.Rotate(_rhs)).
		*	Quaternion should be normalized.
		*
		*	\param[in] _rhs		Quaternion to multiply.
		*
		*	\return new quaternion result.
		*/
		Quat operator*(const Quat& _rhs) const noexcept
		{
			return Rotate(_rhs);
		}

		/**
		*	\brief \b Rotate _rhs vector by this quaternion.
		*
		*	Apply quaternion rotation to vector.
		*	Quaternion must be normalized.
		*
		*	\param[in] _rhs		Vector to rotate.
		*
		*	\return new rotated vector.
		*/
		constexpr Vec3<T> operator*(const Vec3<T>& _rhs) const noexcept
		{
			return Rotate(_rhs);
		}

		/**
		*	\brief \b Divide quaternion to compute the inverse rotation.
		*
		*	Unrotate _rhs by this (ie: this.UnRotate(_rhs)).
		*	Quaternion should be normalized.
		*
		*	\param[in] _rhs		Quaternion to divide.
		*
		*	\return new quaternion result.
		*/
		Quat operator/(const Quat& _rhs) const noexcept
		{
			return Rotate(_rhs.GetInversed());
		}

		/**
		*	\brief \b Un-Rotate _rhs vector by this quaternion.
		*
		*	Apply quaternion inverse rotation to vector.
		*	Quaternion must be normalized.
		*
		*	\param[in] _rhs		Vector to un-rotate.
		*
		*	\return new un-rotated vector.
		*/
		constexpr Vec3<T> operator/(const Vec3<T>& _rhs) const noexcept
		{
			return UnRotate(_rhs);
		}

		/**
		*	\brief \e Compute the <b> Dot product </b> between this and _rhs.
		*
		*	\param[in] _rhs		Right hand side operand quaternion to compute dot product with.
		*
		*	\return <b> Dot product </b> between this quaternion and _other.
		*/
		constexpr T operator|(const Quat& _rhs) const noexcept
		{
			return Dot(*this, _rhs);
		}

		/**
		*	\brief \b Scale each quaternion values by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		*	\param[in] _scale	Scale value to apply on all components.
		*
		*	\return self quaternion scaled.
		*/
		Quat& operator*=(T _scale) noexcept
		{
			w *= _scale;
			x *= _scale;
			y *= _scale;
			z *= _scale;

			return *this;
		}

		/**
		*	\brief <b> Inverse Scale </b> each quaternion values by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		*	\param[in] _scale	Scale value to apply on all components.
		*
		*	\return self quaternion inverse-scaled.
		*/
		Quat& operator/=(T _scale) noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Quat, L"Divide quaternion by 0!");

			w /= _scale;
			x /= _scale;
			y /= _scale;
			z /= _scale;

			return *this;
		}

		/**
		*	\brief \b Add term by term quaternion values.
		*
		*	\param[in] _rhs		Quaternion to add.
		*
		*	\return self quaternion result.
		*/
		Quat& operator+=(const Quat& _rhs) noexcept
		{
			w += _rhs.w;
			x += _rhs.x;
			y += _rhs.y;
			z += _rhs.z;

			return *this;
		}

		/**
		*	\brief \b Substract term by term quaternion values.
		*
		*	\param[in] _rhs		Quaternion to substract.
		*
		*	\return self quaternion result.
		*/
		Quat& operator-=(const Quat& _rhs) noexcept
		{
			w -= _rhs.w;
			x -= _rhs.x;
			y -= _rhs.y;
			z -= _rhs.z;

			return *this;
		}

		/**
		*	\brief \b Multiply quaternion to compute rotation.
		*
		*	Quaternion should be normalized.
		*
		*	\param[in] _rhs		Quaternion to multiply.
		*
		*	\return self quaternion result.
		*/
		Quat& operator*=(const Quat& _rhs) noexcept
		{
			return *this = Rotate(_rhs);
		}

		/**
		*	\brief \b Divide quaternion to compute the inverse rotation.
		*
		*	Quaternion should be normalized.
		*
		*	\param[in] _rhs		Quaternion to divide.
		*
		*	\return self quaternion result.
		*/
		Quat& operator/=(const Quat& _rhs) noexcept
		{
			return *this = Rotate(_rhs.GetInversed());
		}

//}
	};


//{ Constants

	template <typename T>
	const Quat<T> Quat<T>::Zero{ 0, 0, 0, 0 };

	template <typename T>
	const Quat<T> Quat<T>::Identity{ 1, 0, 0, 0 };

//}


	/**
	*	\brief \b Scale each quaternion components by _lhs.
	*
	*	\param[in] _lhs		Scale value to apply on all axis.
	*	\param[in] _rhs		Quaternion to scale.
	*
	*	\return new vector scaled.
	*/
	template <typename T>
	constexpr Quat<T> operator*(typename std::remove_cv<T>::type _lhs, const Quat<T>& _rhs) noexcept
	{
		return _rhs * _lhs;
	}

	/**
	*	\brief <b> Inverse Scale </b> each quaternion components by _lhs.
	*
	*	\param[in] _lhs		Inverse scale value to apply on all axis.
	*	\param[in] _rhs		Quaternion to scale.
	*
	*	\return new quaternion inverse-scaled.
	*/
	template <typename T>
	Quat<T> operator/(typename std::remove_cv<T>::type _lhs, const Quat<T>& _rhs)
	{
		EDO_ERROR(!Equals0(_rhs.w), Edo.Maths.Vec4, L"Inverse scale W value by 0!");
		EDO_ERROR(!Equals0(_rhs.x), Edo.Maths.Vec4, L"Inverse scale X Axis value by 0!");
		EDO_ERROR(!Equals0(_rhs.y), Edo.Maths.Vec4, L"Inverse scale Y Axis value by 0!");
		EDO_ERROR(!Equals0(_rhs.z), Edo.Maths.Vec4, L"Inverse scale Z Axis value by 0!");

		return Quat<T>(
			_lhs / _rhs.w,
			_lhs / _rhs.x,
			_lhs / _rhs.y,
			_lhs / _rhs.z
		);
	}

	/**
	*	\brief \b Rotate _lhs vector by _rhs quaternion.
	*
	*	Apply quaternion rotation to vector.
	*	Quaternion must be normalized.
	*
	*	\param[in] _lhs		Vector to rotate.
	*	\param[in] _rhs		Quaternion used for rotation.
	*
	*	\return new rotated vector.
	*/
	template <typename T>
	constexpr Vec3<T> operator*(const Vec3<T>& _lhs, const Quat<T>& _rhs) noexcept
	{
		return _rhs * _lhs;
	}

	/**
	*	\brief <b> Inverse-Rotate </b> _lhs vector by _rhs quaternion.
	*
	*	Apply quaternion rotation to vector.
	*	Quaternion must be normalized.
	*
	*	\param[in] _lhs		Vector to rotate.
	*	\param[in] _rhs		Quaternion used for rotation.
	*
	*	\return new inverse-rotated vector.
	*/
	template <typename T>
	constexpr Vec3<T> operator/(const Vec3<T>& _lhs, const Quat<T>& _rhs) noexcept
	{
		return _rhs / _lhs;
	}


#if __has_include(<edo_debug.hpp>)
	template <typename T>
	std::string ToString(const Quat<T> _quat) noexcept
	{
		return "Quat{ W: " + edo::ToString(_quat.w) +
			"\tX: " + edo::ToString(_quat.x) +
			"\tY: " + edo::ToString(_quat.y) +
			"\tZ: " + edo::ToString(_quat.z) + " }";
	}
#endif // edo_debug


//{ Aliases

	/// Alias for float Quat.
	using Quatf = Quat<float>;

	/// Alias for double Quat.
	using Quatd = Quat<double>;


	/// Template alias of Quat
	template <typename T>
	using Quaternion = Quat<T>;

	/// Alias for float Quaternion.
	using Quaternionf = Quaternion<float>;

	/// Alias for double Quaternion.
	using Quaterniond = Quaternion<double>;

//}

// ##############################################################


// ##############################################################
// #					MAT 3									#
// ##############################################################

	namespace intl
	{
		template <typename T, MatrixMajor major>
		struct Mat3_Base;

//{ Row Major

		template <typename T>
		struct Mat3_Base<T, MatrixMajor::Row>
		{
			/// Matrix components.
			T e00{ 1 }; T e01{ 0 }; T e02{ 0 };
			T e10{ 0 }; T e11{ 1 }; T e12{ 0 };
			T e20{ 0 }; T e21{ 0 }; T e22{ 1 };

//{ Constructors

			/// Default constructor.
			Mat3_Base() = default;

			/// Default value constructor.
			constexpr Mat3_Base(
				T _e00, T _e01, T _e02,
				T _e10, T _e11, T _e12,
				T _e20, T _e21, T _e22
			) noexcept :
				e00{ _e00 }, e01{ _e01 }, e02{ _e02 },
				e10{ _e10 }, e11{ _e11 }, e12{ _e12 },
				e20{ _e20 }, e21{ _e21 }, e22{ _e22 }
			{
			}

//}
		};

//}

//{ Column Major

		template <typename T>
		struct Mat3_Base<T, MatrixMajor::Column>
		{
			/// Matrix components.
			T e00{ 1 }; T e10{ 0 }; T e20{ 0 };
			T e01{ 0 }; T e11{ 1 }; T e21{ 0 };
			T e02{ 0 }; T e12{ 0 }; T e22{ 1 };

//{ Constructors

			/// Default constructor.
			Mat3_Base() = default;

			/// Default value constructor.
			constexpr Mat3_Base(
				T _e00, T _e01, T _e02,
				T _e10, T _e11, T _e12,
				T _e20, T _e21, T _e22
			) noexcept :
				e00{ _e00 }, e10{ _e10 }, e20{ _e20 },
				e01{ _e01 }, e11{ _e11 }, e21{ _e21 },
				e02{ _e02 }, e12{ _e12 }, e22{ _e22 }
			{
			}

//}
		};

//}

	}


	/**
	*	\brief \e Matrix 3x3 class.
	*
	* 	must be align at 32 for intrinsics.
	* 
	*	\tparam T	Type of the matrix.
	*/
	template <typename T, MatrixMajor major = MatrixMajor::Default>
	struct Mat3 : private intl::Mat3_Base<T, major>
	{
		/// Type of the Matrix.
		using Type = T;

		using intl::Mat3_Base<T, major>::e00;
		using intl::Mat3_Base<T, major>::e01;
		using intl::Mat3_Base<T, major>::e02;

		using intl::Mat3_Base<T, major>::e10;
		using intl::Mat3_Base<T, major>::e11;
		using intl::Mat3_Base<T, major>::e12;

		using intl::Mat3_Base<T, major>::e20;
		using intl::Mat3_Base<T, major>::e21;
		using intl::Mat3_Base<T, major>::e22;


//{ Constants

		/**
		*	\brief Zero Mat3 constant
		* 
		*	{0, 0, 0}
		*	{0, 0, 0}
		*	{0, 0, 0}
		*/
		static const Mat3 Zero;

		/**
		*	\brief Identity Mat3 constant
		* 
		*	{1, 0, 0}
		*	{0, 1, 0}
		*	{0, 0, 1}
		*/
		static const Mat3 Identity;

//}


//{ Constructors

		using intl::Mat3_Base<T, major>::Mat3_Base;


		/**
		*	\brief \e Value constructor from another Mat3 type.
		*
		*	\tparam TIn			Type of the input Mat3.
		*	\tparam majorIn		Major of the input Mat3.
		*
		*	\param[in] _other	Mat3 to construct from.
		*/
		template <typename TIn, MatrixMajor majorIn>
		constexpr Mat3(const Mat3<TIn, majorIn>& _other) noexcept :
			intl::Mat3_Base<T, major>(
				static_cast<T>(_other.e00), static_cast<T>(_other.e01), static_cast<T>(_other.e02),
				static_cast<T>(_other.e10), static_cast<T>(_other.e11), static_cast<T>(_other.e12),
				static_cast<T>(_other.e20), static_cast<T>(_other.e21), static_cast<T>(_other.e22)
			)
		{
		}

		/**
		*	\brief \e Value constructor from another Mat4 type.
		*
		*	\tparam TIn			Type of the input Mat4.
		*	\tparam majorIn		Major of the input Mat3.
		*
		*	\param[in] _other	Mat4 to construct from.
		*/
		template <typename TIn, MatrixMajor majorIn>
		constexpr Mat3(const Mat4<TIn, majorIn>& _other) noexcept :
			intl::Mat3_Base<T, major>(
				static_cast<T>(_other.e00), static_cast<T>(_other.e01), static_cast<T>(_other.e02),
				static_cast<T>(_other.e10), static_cast<T>(_other.e11), static_cast<T>(_other.e12),
				static_cast<T>(_other.e20), static_cast<T>(_other.e21), static_cast<T>(_other.e22)
			)
		{
		}
//}


//{ Equals

		/**
		*	\brief Whether this matrix is a zero matrix.
		*
		*	\return True if this is a zero matrix.
		*/
		constexpr bool IsZero() const noexcept
		{
			return
				edo::Equals0(e00) && edo::Equals0(e01) && edo::Equals0(e02) &&
				edo::Equals0(e10) && edo::Equals0(e11) && edo::Equals0(e12) &&
				edo::Equals0(e20) && edo::Equals0(e21) && edo::Equals0(e22);
		}

		/**
		*	\brief Whether this matrix is an identity matrix.
		*
		*	\return True if this is an identity matrix.
		*/
		constexpr bool IsIdentity() const noexcept
		{
			return
				edo::Equals1(e00) && edo::Equals0(e01) && edo::Equals0(e02) &&
				edo::Equals0(e10) && edo::Equals1(e11) && edo::Equals0(e12) &&
				edo::Equals0(e20) && edo::Equals0(e21) && edo::Equals1(e22);
		}


		/**
		*	\brief \e Compare 2 Matrix.
		*
		*	\param[in] _other		Other matrix to compare to.
		*	\param[in] _epsilon		Epsilon value for threshold comparison.
		*
		*	\return Whether this and _other are equal.
		*/
		constexpr bool Equals(const Mat3& _other, T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept
		{
			return
				edo::Equals(e00, _other.e00, _epsilon) && edo::Equals(e01, _other.e01, _epsilon) && edo::Equals(e02, _other.e02, _epsilon) &&
				edo::Equals(e10, _other.e10, _epsilon) && edo::Equals(e11, _other.e11, _epsilon) && edo::Equals(e12, _other.e12, _epsilon) &&
				edo::Equals(e20, _other.e20, _epsilon) && edo::Equals(e21, _other.e21, _epsilon) && edo::Equals(e22, _other.e22, _epsilon);
		}


		/**
		*	\brief \e Compare 2 matrix equality.
		*
		*	\param[in] _rhs		Other matrix to compare to.
		*
		*	\return Whether this and _rhs are equal.
		*/
		constexpr bool operator==(const Mat3& _rhs) const noexcept
		{
			return Equals(_rhs);
		}

		/**
		*	\brief \e Compare 2 matrix inequality.
		*
		*	\param[in] _rhs		Other matrix to compare to.
		*
		*	\return Whether this and _rhs are non-equal.
		*/
		constexpr bool operator!=(const Mat3& _rhs) const noexcept
		{
			return !(*this == _rhs);
		}
//}

//{ Accessors

		/**
		*	\brief \e Getter of matrix data
		*
		*	\return this matrix as a T*.
		*/
		T* Data() noexcept
		{
			return &e00;
		}

		/**
		*	\brief <em> Const Getter </em> of matrix data
		*
		*	\return this matrix as a const T*.
		*/
		const T* Data() const noexcept
		{
			return &e00;
		}


		/**
		*	\brief \e Getter of Value at index.
		*
		*	\param[in] _index		Index to access.
		*
		*	\return element at index.
		*/
		T& At(uint32_t _index)
		{
			EDO_ASSERT(_index < 9u, Edo.Maths.Mat3, L"Index access out of range!");

			return Data()[_index];
		}

		/**
		*	\brief <em> Const Getter </em> of Value at index.
		*
		*	\param[in] _index		Index to access.
		*
		*	\return element at index.
		*/
		const T& At(uint32_t _index) const
		{
			EDO_ASSERT(_index < 9u, Edo.Maths.Mat3, L"Index access out of range!");

			return Data()[_index];
		}

		/**
		*	\brief \e Getter of Value at (x;y).
		*
		*	\param[in] _x		row index.
		*	\param[in] _y		column index.
		*
		*	\return element at index.
		*/
		T& At(uint32_t _x, uint32_t _y)
		{
			EDO_ASSERT(_x < 3u, Edo.Maths.Mat3, L"Index X access out of range!");
			EDO_ASSERT(_y < 3u, Edo.Maths.Mat3, L"Index Y access out of range!");

			return Data()[_x * 3u + _y];
		}

		/**
		*	\brief <em> Const Getter </em> of Value at (x;y).
		*
		*	\param[in] _x		row index.
		*	\param[in] _y		column index.
		*
		*	\return element at index.
		*/
		const T& At(uint32_t _x, uint32_t _y) const
		{
			EDO_ASSERT(_x < 3u, Edo.Maths.Mat3, L"Index X access out of range!");
			EDO_ASSERT(_y < 3u, Edo.Maths.Mat3, L"Index Y access out of range!");

			return Data()[_x * 3u + _y];
		}


		/**
		*	\brief \e Access operator by index.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		T& operator[](uint32_t _index)
		{
			return At(_index);
		}

		/**
		*	\brief <em> Const Access </em> operator by index.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		const T& operator[](uint32_t _index) const
		{
			return At(_index);
		}
//}


//{ Transpose

		/**
		*	\brief \b Transpose this matrix.
		*
		*	\return self transposed matrix.
		*/
		Mat3& Transpose() noexcept
		{
			std::swap(e01, e10);
			std::swap(e02, e20);
			std::swap(e12, e21);

			return *this;
		}

		/**
		*	\brief \b Transpose this matrix.
		*
		*	\return new transposed matrix.
		*/
		constexpr Mat3 GetTransposed() const noexcept
		{
			return Mat3(
				e00, e10, e20,
				e01, e11, e21,
				e02, e12, e22
			);
		}

//}


//{ Inverse

		/**
		*	\brief \e Compute the determinant of the matrix.
		*
		*	\return Determinant of this matrix.
		*/
		T Determinant() const noexcept
		{
			return
				e00 * e11 * e22 +
				e01 * e12 * e20 +
				e02 * e10 * e21 -
				e20 * e11 * e02 -
				e21 * e12 * e00 -
				e22 * e10 * e01;
		}

		/**
		*	\brief \b Inverse this matrix.
		*
		*	\return self inversed matrix.
		*/
		Mat3& Inverse() noexcept
		{
			return *this = GetInversed();
		}

		/**
		*	\brief \b Inverse this matrix.
		*
		*	\return new inversed matrix.
		*/
		Mat3 GetInversed() const noexcept
		{
			const T det = Determinant();

			EDO_ERROR(!Equals0(det), Edo.Maths.Mat3, L"Determinant must be != 0 to compute inverse matrix");

			return (T{ 1 } / det) * Mat3(
				e11 * e22 - e21 * e12, e02 * e21 - e01 * e22, e01 * e12 - e11 * e02,
				e12 * e20 - e10 * e22, e00 * e22 - e20 * e02, e02 * e10 - e00 * e12,
				e10 * e21 - e20 * e11, e01 * e20 - e00 * e21, e00 * e11 - e10 * e01
			);
		}
	
//}


//{ Lerp

		/**
		*	\brief <b> Clamped Lerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Mat3 Lerp(const Mat3& _start, const Mat3& _end, AlphaT _alpha) noexcept
		{
			return edo::Lerp(_start, _end, _alpha);
		}

		/**
		*	\brief <b> Unclamped Lerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Mat3 LerpUnclamped(const Mat3& _start, const Mat3& _end, AlphaT _alpha) noexcept
		{
			return edo::LerpUnclamped(_start, _end, _alpha);
		}

//}


//{ Transform

		/**
		*	\brief Make <b> rotation matrix </b> from quaternion.
		*
		*	\param[in] _rot	quaternion to use for rotation.
		*
		*	\return rotation matrix.
		*/
		static Mat3 MakeRotation(const Quat<T>& _rot) noexcept
		{
			EDO_WARN(_rot.IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Mat3, L"Quaternion should be normalized!");

			// Sources: https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation

			const T XW2 = T(2) * _rot.x * _rot.w;
			const T XX2 = T(2) * _rot.x * _rot.x;
			const T XY2 = T(2) * _rot.x * _rot.y;
			const T XZ2 = T(2) * _rot.x * _rot.z;

			const T YW2 = T(2) * _rot.y * _rot.w;
			const T YY2 = T(2) * _rot.y * _rot.y;
			const T YZ2 = T(2) * _rot.y * _rot.z;

			const T ZW2 = T(2) * _rot.z * _rot.w;
			const T ZZ2 = T(2) * _rot.z * _rot.z;

			return Mat3(
				T(1) - YY2 - ZZ2, XY2 - ZW2, XZ2 + YW2,
				XY2 + ZW2, T(1) - XX2 - ZZ2, YZ2 - XW2,
				XZ2 - YW2, YZ2 + XW2, T(1) - XX2 - YY2
			);
		}

		/**
		*	\brief Make <b> scale matrix </b> from vector3.
		*
		*	\param[in] _scale	Vector for scaling.
		*
		*	\return scale matrix.
		*/
		static Mat3 MakeScale(const Vec3<T>& _scale) noexcept
		{
			Mat3 result = Mat3::Identity;

			result.e00 = _scale.x;
			result.e11 = _scale.y;
			result.e22 = _scale.z;

			return result;
		}

//}


//{ Operators
		
		/**
		*	\brief \e Assignment operator from another Mat3 type.
		*
		*	\tparam TIn			Type of the input Mat3.
		*	\tparam majorIn		Major of the input Mat3.
		*
		*	\param[in] _rhs		Mat3 to assign from.
		*/
		template <typename TIn, MatrixMajor majorIn>
		Mat3& operator=(const Mat3<TIn, majorIn> _rhs) noexcept
		{
			e00 = static_cast<T>(_rhs.e00);
			e01 = static_cast<T>(_rhs.e01);
			e02 = static_cast<T>(_rhs.e02);

			e10 = static_cast<T>(_rhs.e10);
			e11 = static_cast<T>(_rhs.e11);
			e12 = static_cast<T>(_rhs.e12);

			e20 = static_cast<T>(_rhs.e20);
			e21 = static_cast<T>(_rhs.e21);
			e22 = static_cast<T>(_rhs.e22);

			return *this;
		}

		/**
		*	\brief \e Getter of the opposite signed matrix.
		*
		*	\return new opposite signed matrix.
		*/
		constexpr Mat3 operator-() const noexcept
		{
			return Mat3(
				-e00, -e01, -e02,
				-e10, -e11, -e12,
				-e20, -e21, -e22
			);
		}

		/**
		*	\brief \b Scale each matrix component by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Scale value to apply on all components.
		*
		*	\return new matrix scaled.
		*/
		template <typename TIn>
		Mat3 operator*(TIn _scale) const noexcept
		{
			return Mat3(
				static_cast<T>(e00 * _scale), static_cast<T>(e01 * _scale), static_cast<T>(e02 * _scale),
				static_cast<T>(e10 * _scale), static_cast<T>(e11 * _scale), static_cast<T>(e12 * _scale),
				static_cast<T>(e20 * _scale), static_cast<T>(e21 * _scale), static_cast<T>(e22 * _scale)
			);
		}

		/**
		*	\brief <b> Inverse Scale </b> each matrix component by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Inverse scale value to apply on all components.
		*
		*	\return new matrix inverse-scaled.
		*/
		template <typename TIn>
		Mat3 operator/(TIn _scale) const noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Mat3, L"Divide matrix by 0!");

			return Mat3(
				static_cast<T>(e00 / _scale), static_cast<T>(e01 / _scale), static_cast<T>(e02 / _scale),
				static_cast<T>(e10 / _scale), static_cast<T>(e11 / _scale), static_cast<T>(e12 / _scale),
				static_cast<T>(e20 / _scale), static_cast<T>(e21 / _scale), static_cast<T>(e22 / _scale)
			);
		}

		/**
		*	\brief \b Add term by term matrix values.
		*
		*	\param[in] _rhs		Matrix to add.
		*
		*	\return new matrix result.
		*/
		Mat3 operator+(const Mat3& _rhs) const noexcept
		{
			return Mat3(
				e00 + _rhs.e00, e01 + _rhs.e01, e02 + _rhs.e02,
				e10 + _rhs.e10, e11 + _rhs.e11, e12 + _rhs.e12,
				e20 + _rhs.e20, e21 + _rhs.e21, e22 + _rhs.e22
			);
		}

		/**
		*	\brief \b Subtract term by term matrix values.
		*
		*	\param[in] _rhs		Matrix to substract.
		*
		*	\return new matrix result.
		*/
		Mat3 operator-(const Mat3& _rhs) const noexcept
		{
			return Mat3(
				e00 - _rhs.e00, e01 - _rhs.e01, e02 - _rhs.e02,
				e10 - _rhs.e10, e11 - _rhs.e11, e12 - _rhs.e12,
				e20 - _rhs.e20, e21 - _rhs.e21, e22 - _rhs.e22
			);
		}

		/**
		*	\brief \b Multiply matrices.
		*
		*	\param[in] _rhs		Matrix to multiply to.
		*
		*	\return new matrix result.
		*/
		Mat3 operator*(const Mat3& _rhs) const noexcept
		{
			return Mat3(
				e00 * _rhs.e00 + e01 * _rhs.e10 + e02 * _rhs.e20,
				e00 * _rhs.e01 + e01 * _rhs.e11 + e02 * _rhs.e21,
				e00 * _rhs.e02 + e01 * _rhs.e12 + e02 * _rhs.e22,

				e10 * _rhs.e00 + e11 * _rhs.e10 + e12 * _rhs.e20,
				e10 * _rhs.e01 + e11 * _rhs.e11 + e12 * _rhs.e21,
				e10 * _rhs.e02 + e11 * _rhs.e12 + e12 * _rhs.e22,

				e20 * _rhs.e00 + e21 * _rhs.e10 + e22 * _rhs.e20,
				e20 * _rhs.e01 + e21 * _rhs.e11 + e22 * _rhs.e21,
				e20 * _rhs.e02 + e21 * _rhs.e12 + e22 * _rhs.e22
			);
		}

		/**
		*	\brief \b Inverse multiply matrices.
		*
		*	\param[in] _rhs		Matrix to inverse multiply to.
		*
		*	\return new matrix result.
		*/
		Mat3 operator/(const Mat3& _rhs) const noexcept
		{
			return *this * _rhs.GetInversed();
		}


		/**
		*	\brief transform this vector by this matrix.
		*
		*	\param[in] _rhs		Vector to transform.
		*
		*	\return Transformed vector.
		*/
		Vec3<T> operator*(const Vec3<T>&_rhs) const noexcept
		{
			return Vec3(
				e00 * _rhs.x + e01 * _rhs.y + e02 * _rhs.z,
				e10 * _rhs.x + e11 * _rhs.y + e12 * _rhs.z,
				e20 * _rhs.x + e21 * _rhs.y + e22 * _rhs.z
			);
		}


		/**
		*	\brief \b Scale each matrix component by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Scale value to apply on all components.
		*
		*	\return self matrix scaled.
		*/
		template <typename TIn>
		Mat3& operator*=(TIn _scale) noexcept
		{
			e00 *= _scale;
			e01 *= _scale;
			e02 *= _scale;

			e10 *= _scale;
			e11 *= _scale;
			e12 *= _scale;

			e20 *= _scale;
			e21 *= _scale;
			e22 *= _scale;

			return *this;
		}

		/**
		*	\brief <b> Inverse Scale </b> each matrix component by _scale.
		* 
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Inverse scale value to apply on all components.
		*
		*	\return self matrix inverse-scaled.
		*/
		template <typename TIn>
		Mat3& operator/=(TIn _scale) noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Mat3, L"Divide matrix by 0!");

			e00 /= _scale;
			e01 /= _scale;
			e02 /= _scale;

			e10 /= _scale;
			e11 /= _scale;
			e12 /= _scale;

			e20 /= _scale;
			e21 /= _scale;
			e22 /= _scale;

			return *this;
		}

		/**
		*	\brief \b Add term by term matrix values.
		*
		*	\param[in] _rhs		Matrix to add.
		*
		*	\return self matrix result.
		*/
		Mat3& operator+=(const Mat3& _rhs) noexcept
		{
			e00 += _rhs.e00;
			e01 += _rhs.e01;
			e02 += _rhs.e02;

			e10 += _rhs.e10;
			e11 += _rhs.e11;
			e12 += _rhs.e12;

			e20 += _rhs.e20;
			e21 += _rhs.e21;
			e22 += _rhs.e22;

			return *this;
		}

		/**
		*	\brief \b Subtract term by term matrix values.
		*
		*	\param[in] _rhs		Matrix to substract.
		*
		*	\return self matrix result.
		*/
		Mat3& operator-=(const Mat3& _rhs) noexcept
		{
			e00 -= _rhs.e00;
			e01 -= _rhs.e01;
			e02 -= _rhs.e02;

			e10 -= _rhs.e10;
			e11 -= _rhs.e11;
			e12 -= _rhs.e12;

			e20 -= _rhs.e20;
			e21 -= _rhs.e21;
			e22 -= _rhs.e22;

			return *this;
		}

		/**
		*	\brief \b Multiply matrices.
		*
		*	\param[in] _rhs		Matrix to multiply to.
		*
		*	\return self matrix result.
		*/
		Mat3& operator*=(const Mat3& _rhs) noexcept
		{
			return *this = *this * _rhs;
		}

		/**
		*	\brief \b Inverse multiply matrices.
		*
		*	\param[in] _rhs		Matrix to inverse multiply to.
		*
		*	\return self matrix result.
		*/
		Mat3& operator/=(const Mat3& _rhs) noexcept
		{
			return *this = *this / _rhs;
		}

//}
	};


//{ Constants

	template <typename T, MatrixMajor major>
	const Mat3<T, major> Mat3<T, major>::Zero
	{
		T(0), T(0), T(0),
		T(0), T(0), T(0),
		T(0), T(0), T(0)
	};

	template <typename T, MatrixMajor major>
	const Mat3<T, major> Mat3<T, major>::Identity
	{
		T(1), T(0), T(0),
		T(0), T(1), T(0),
		T(0), T(0), T(1)
	};

//}


	/**
	*	\brief \b Scale each matrix components by _lhs.
	*
	*	\tparam TIn			Type of the input scale.
	* 
	*	\param[in] _lhs		Scale value to apply on all components.
	*	\param[in] _rhs		Matrix to scale.
	*
	*	\return new matrix scaled.
	*/
	template <typename T, MatrixMajor major, typename TIn>
	Mat3<T, major> operator*(TIn _lhs, const Mat3<T, major>& _rhs) noexcept
	{
		return _rhs * _lhs;
	}

	/**
	*	\brief <b> Inverse Scale </b> each matrix components by _lhs.
	*
	*	\tparam TIn			Type of the input scale.
	* 
	*	\param[in] _lhs		Inverse scale value to apply on all components.
	*	\param[in] _rhs		Matrix to scale.
	*
	*	\return new matrix inverse-scaled.
	*/
	template <typename T, MatrixMajor major, typename TIn>
	Mat3<T, major> operator/(TIn _lhs, const Mat3<T, major>& _rhs) noexcept
	{
		EDO_ERROR(!Equals0(_rhs.e00), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e01), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e02), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e10), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e11), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e12), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e20), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e21), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e22), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");

		return Mat3<T>(
			_lhs / _rhs.e00, _lhs / _rhs.e01, _lhs / _rhs.e02,
			_lhs / _rhs.e10, _lhs / _rhs.e11, _lhs / _rhs.e12,
			_lhs / _rhs.e20, _lhs / _rhs.e21, _lhs / _rhs.e22
		);
	}


#if __has_include(<edo_debug.hpp>)
	template <typename T, MatrixMajor major>
	std::string ToString(const Mat3<T, major> _mat) noexcept
	{
		// Keep memory order (Raw / column major).
		const T* const data = _mat.Data();

		return "Mat3{\n " +
			edo::ToString(data[0]) + ",\t" +
			edo::ToString(data[1]) + ",\t" +
			edo::ToString(data[2]) + ",\n " +

			edo::ToString(data[3]) + ",\t" +
			edo::ToString(data[4]) + ",\t" +
			edo::ToString(data[5]) + ",\n " +

			edo::ToString(data[6]) + ",\t" +
			edo::ToString(data[7]) + ",\t" +
			edo::ToString(data[8]) + "\n}";
	}
#endif // edo_debug


//{ Aliases

	/// Alias for int32 Mat3.
	using Mat3i = Mat3<int32_t>;

	/// Alias for float Mat3.
	using Mat3f = Mat3<float>;

	/// Alias for double Mat3.
	using Mat3d = Mat3<double>;


	/// Template alias of Mat3
	template <typename T, MatrixMajor major = MatrixMajor::Default>
	using Matrix3 = Mat3<T, major>;

	/// Alias for int32 Matrix3.
	using Matrix3i = Matrix3<int32_t>;

	/// Alias for float Matrix3.
	using Matrix3f = Matrix3<float>;

	/// Alias for double Matrix3.
	using Matrix3d = Matrix3<double>;


	/// Alias for row major int32 Mat3.
	using RMat3i = Mat3<int32_t, MatrixMajor::Row>;

	/// Alias for row major float Mat3.
	using RMat3f = Mat3<float, MatrixMajor::Row>;

	/// Alias for row major double Mat3.
	using RMat3d = Mat3<double, MatrixMajor::Row>;


	/// Alias for column major int32 Mat3.
	using CMat3i = Mat3<int32_t, MatrixMajor::Column>;

	/// Alias for column major float Mat3.
	using CMat3f = Mat3<float, MatrixMajor::Column>;

	/// Alias for column major double Mat3.
	using CMat3d = Mat3<double, MatrixMajor::Column>;

//}

// ##############################################################


// ##############################################################
// #					MAT 4									#
// ##############################################################

	namespace intl
	{
		template <typename T, MatrixMajor major>
		struct Mat4_Base;

//{ Row Major

		template <typename T>
		struct Mat4_Base<T, MatrixMajor::Row>
		{
			/// Matrix components.
			T e00{ 1 }; T e01{ 0 }; T e02{ 0 }; T e03{ 0 };
			T e10{ 0 }; T e11{ 1 }; T e12{ 0 }; T e13{ 0 };
			T e20{ 0 }; T e21{ 0 }; T e22{ 1 }; T e23{ 0 };
			T e30{ 0 }; T e31{ 0 }; T e32{ 0 }; T e33{ 1 };


//{ Constructors

			/// Default constructor.
			Mat4_Base() = default;

			/// Default value constructor.
			constexpr Mat4_Base(
				T _e00, T _e01, T _e02, T _e03,
				T _e10, T _e11, T _e12, T _e13,
				T _e20, T _e21, T _e22, T _e23,
				T _e30, T _e31, T _e32, T _e33
			) noexcept :
				e00{ _e00 }, e01{ _e01 }, e02{ _e02 }, e03{ _e03 },
				e10{ _e10 }, e11{ _e11 }, e12{ _e12 }, e13{ _e13 },
				e20{ _e20 }, e21{ _e21 }, e22{ _e22 }, e23{ _e23 },
				e30{ _e30 }, e31{ _e31 }, e32{ _e32 }, e33{ _e33 }
			{
			}

//}
		};

//}

//{ Column Major

		template <typename T>
		struct Mat4_Base<T, MatrixMajor::Column>
		{
			/// Matrix components.
			T e00{ 1 }; T e10{ 0 }; T e20{ 0 }; T e30{ 0 };
			T e01{ 0 }; T e11{ 1 }; T e21{ 0 }; T e31{ 0 };
			T e02{ 0 }; T e12{ 0 }; T e22{ 1 }; T e32{ 0 };
			T e03{ 0 }; T e13{ 0 }; T e23{ 0 }; T e33{ 1 };

//{ Constructors

			/// Default constructor.
			Mat4_Base() = default;

			/// Default value constructor.
			constexpr Mat4_Base(
				T _e00, T _e01, T _e02, T _e03,
				T _e10, T _e11, T _e12, T _e13,
				T _e20, T _e21, T _e22, T _e23,
				T _e30, T _e31, T _e32, T _e33
			) noexcept :
				e00{ _e00 }, e10{ _e10 }, e20{ _e20 }, e30{ _e30 },
				e01{ _e01 }, e11{ _e11 }, e21{ _e21 }, e31{ _e31 },
				e02{ _e02 }, e12{ _e12 }, e22{ _e22 }, e32{ _e32 },
				e03{ _e03 }, e13{ _e13 }, e23{ _e23 }, e33{ _e33 }
			{
			}

//}
		};
	}


	template <typename T, MatrixMajor major = MatrixMajor::Default>
	struct Mat4 : private intl::Mat4_Base<T, major>
	{
		/// Type of the Matrix.
		using Type = T;

		using intl::Mat4_Base<T, major>::e00;
		using intl::Mat4_Base<T, major>::e01;
		using intl::Mat4_Base<T, major>::e02;
		using intl::Mat4_Base<T, major>::e03;

		using intl::Mat4_Base<T, major>::e10;
		using intl::Mat4_Base<T, major>::e11;
		using intl::Mat4_Base<T, major>::e12;
		using intl::Mat4_Base<T, major>::e13;

		using intl::Mat4_Base<T, major>::e20;
		using intl::Mat4_Base<T, major>::e21;
		using intl::Mat4_Base<T, major>::e22;
		using intl::Mat4_Base<T, major>::e23;

		using intl::Mat4_Base<T, major>::e30;
		using intl::Mat4_Base<T, major>::e31;
		using intl::Mat4_Base<T, major>::e32;
		using intl::Mat4_Base<T, major>::e33;

//{ Constants

		/**
		*	\brief Zero Mat4 constant
		* 
		*	{0, 0, 0, 0}
		*	{0, 0, 0, 0}
		*	{0, 0, 0, 0}
		*	{0, 0, 0, 0}
		*/
		static const Mat4 Zero;

		/**
		*	\brief Identity Mat4 constant
		* 
		*	{1, 0, 0, 0}
		*	{0, 1, 0, 0}
		*	{0, 0, 1, 0}
		*	{0, 0, 0, 1}
		*/
		static const Mat4 Identity;

//}


//{ Constructors

		using intl::Mat4_Base<T, major>::Mat4_Base;

		/**
		*	\brief \e Value constructor from another Mat4 type.
		*
		*	\tparam TIn			Type of the input Mat4.
		*	\tparam majorIn		Major of the input Mat4.
		*
		*	\param[in] _other	Mat4 to construct from.
		*/
		template <typename TIn, MatrixMajor majorIn>
		constexpr Mat4(const Mat4<TIn, majorIn>& _other) noexcept :
			intl::Mat4_Base<T, major>(
				static_cast<T>(_other.e00), static_cast<T>(_other.e01), static_cast<T>(_other.e02), static_cast<T>(_other.e03),
				static_cast<T>(_other.e10), static_cast<T>(_other.e11), static_cast<T>(_other.e12), static_cast<T>(_other.e13),
				static_cast<T>(_other.e20), static_cast<T>(_other.e21), static_cast<T>(_other.e22), static_cast<T>(_other.e23),
				static_cast<T>(_other.e30), static_cast<T>(_other.e31), static_cast<T>(_other.e32), static_cast<T>(_other.e33)
			)
		{
		}

		/**
		*	\brief \e Value constructor from another Mat3 type.
		*
		*	\tparam TIn			Type of the input Mat3.
		*	\tparam majorIn		Major of the input Mat4.
		*
		*	\param[in] _other	Mat3 to construct from.
		*/
		template <typename TIn, MatrixMajor majorIn>
		constexpr Mat4(const Mat3<TIn, majorIn>& _other) noexcept :
			intl::Mat4_Base<T, major>(
				static_cast<T>(_other.e00), static_cast<T>(_other.e01), static_cast<T>(_other.e02), T(0),
				static_cast<T>(_other.e10), static_cast<T>(_other.e11), static_cast<T>(_other.e12), T(0),
				static_cast<T>(_other.e20), static_cast<T>(_other.e21), static_cast<T>(_other.e22), T(0),
				T(0), T(0), T(0), T(1)
			)
		{
		}

//}


//{ Equals

		/**
		*	\brief Whether this matrix is a zero matrix.
		*
		*	\return True if this is a zero matrix.
		*/
		constexpr bool IsZero() const noexcept
		{
			return
				edo::Equals0(e00) && edo::Equals0(e01) && edo::Equals0(e02) && edo::Equals0(e03) &&
				edo::Equals0(e10) && edo::Equals0(e11) && edo::Equals0(e12) && edo::Equals0(e13) &&
				edo::Equals0(e20) && edo::Equals0(e21) && edo::Equals0(e22) && edo::Equals0(e23) &&
				edo::Equals0(e30) && edo::Equals0(e31) && edo::Equals0(e32) && edo::Equals0(e33);
		}

		/**
		*	\brief Whether this matrix is an identity matrix.
		*
		*	\return True if this is an identity matrix.
		*/
		constexpr bool IsIdentity() const noexcept
		{
			return
				edo::Equals1(e00) && edo::Equals0(e01) && edo::Equals0(e02) && edo::Equals0(e03) &&
				edo::Equals0(e10) && edo::Equals1(e11) && edo::Equals0(e12) && edo::Equals0(e13) &&
				edo::Equals0(e20) && edo::Equals0(e21) && edo::Equals1(e22) && edo::Equals0(e23) &&
				edo::Equals0(e30) && edo::Equals0(e31) && edo::Equals0(e32) && edo::Equals1(e33);
		}


		/**
		*	\brief \e Compare 2 Matrix.
		*
		*	\param[in] _other		Other matrix to compare to.
		*	\param[in] _epsilon		Epsilon value for threshold comparison.
		*
		*	\return Whether this and _other are equal.
		*/
		constexpr bool Equals(const Mat4& _other, T _epsilon = std::numeric_limits<T>::epsilon()) const noexcept
		{
			return
				edo::Equals(e00, _other.e00, _epsilon) &&
				edo::Equals(e01, _other.e01, _epsilon) &&
				edo::Equals(e02, _other.e02, _epsilon) &&
				edo::Equals(e03, _other.e03, _epsilon) &&
				edo::Equals(e10, _other.e10, _epsilon) &&
				edo::Equals(e11, _other.e11, _epsilon) &&
				edo::Equals(e12, _other.e12, _epsilon) &&
				edo::Equals(e13, _other.e13, _epsilon) &&
				edo::Equals(e20, _other.e20, _epsilon) &&
				edo::Equals(e21, _other.e21, _epsilon) &&
				edo::Equals(e22, _other.e22, _epsilon) &&
				edo::Equals(e23, _other.e23, _epsilon) &&
				edo::Equals(e30, _other.e30, _epsilon) &&
				edo::Equals(e31, _other.e31, _epsilon) &&
				edo::Equals(e32, _other.e32, _epsilon) &&
				edo::Equals(e33, _other.e33, _epsilon);
		}


		/**
		*	\brief \e Compare 2 matrix equality.
		*
		*	\param[in] _rhs		Other matrix to compare to.
		*
		*	\return Whether this and _rhs are equal.
		*/
		constexpr bool operator==(const Mat4& _rhs) const noexcept
		{
			return Equals(_rhs);
		}

		/**
		*	\brief \e Compare 2 matrix inequality.
		*
		*	\param[in] _rhs		Other matrix to compare to.
		*
		*	\return Whether this and _rhs are non-equal.
		*/
		constexpr bool operator!=(const Mat4& _rhs) const noexcept
		{
			return !(*this == _rhs);
		}

//}


//{ Accessors

		/**
		*	\brief \e Getter of matrix data
		*
		*	\return this matrix as a T*.
		*/
		T* Data() noexcept
		{
			return &e00;
		}

		/**
		*	\brief <em> Const Getter </em> of matrix data
		*
		*	\return this matrix as a const T*.
		*/
		const T* Data() const noexcept
		{
			return &e00;
		}


		/**
		*	\brief \e Getter of Value at index.
		*
		*	\param[in] _index		Index to access.
		*
		*	\return element at index.
		*/
		T& At(uint32_t _index)
		{
			EDO_ASSERT(_index < 16u, Edo.Maths.Mat4, L"Index access out of range!");

			return Data()[_index];

		}

		/**
		*	\brief <em> Const Getter </em> of Value at index.
		*
		*	\param[in] _index		Index to access.
		*
		*	\return element at index.
		*/
		const T& At(uint32_t _index) const
		{
			EDO_ASSERT(_index < 16u, Edo.Maths.Mat4, L"Index access out of range!");

			return Data()[_index];

		}

		/**
		*	\brief \e Getter of Value at (x;y).
		*
		*	\param[in] _x		row index.
		*	\param[in] _y		column index.
		*
		*	\return element at index.
		*/
		T& At(uint32_t _x, uint32_t _y)
		{
			EDO_ASSERT(_x < 4u, Edo.Maths.Mat4, L"Index X access out of range!");
			EDO_ASSERT(_y < 4u, Edo.Maths.Mat4, L"Index Y access out of range!");

			return Data()[_x * 4u + _y];
		}

		/**
		*	\brief <em> Const Getter </em> of Value at (x;y).
		*
		*	\param[in] _x		row index.
		*	\param[in] _y		column index.
		*
		*	\return element at index.
		*/
		const T& At(uint32_t _x, uint32_t _y) const
		{
			EDO_ASSERT(_x < 4u, Edo.Maths.Mat4, L"Index X access out of range!");
			EDO_ASSERT(_y < 4u, Edo.Maths.Mat4, L"Index Y access out of range!");

			return Data()[_x * 4u + _y];
		}


		/**
		*	\brief \e Access operator by index.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		T& operator[](uint32_t _index)
		{
			return At(_index);
		}

		/**
		*	\brief <em> Const Access </em> operator by index.
		*
		*	\param[in] _index	Index to access.
		*
		*	\return T value at index.
		*/
		const T& operator[](uint32_t _index) const
		{
			return At(_index);
		}

//}


//{ Transpose

		/**
		*	\brief \b Transpose this matrix.
		*
		*	\return self transposed matrix.
		*/
		Mat4& Transpose() noexcept
		{
			std::swap(e01, e10);
			std::swap(e02, e20);
			std::swap(e03, e30);

			std::swap(e12, e21);
			std::swap(e13, e31);

			std::swap(e23, e32);

			return *this;
		}

		/**
		*	\brief \b Transpose this matrix.
		*
		*	\return new transposed matrix.
		*/
		constexpr Mat4 GetTransposed() const noexcept
		{
			return Mat4(
				e00, e10, e20, e30,
				e01, e11, e21, e31,
				e02, e12, e22, e32,
				e03, e13, e23, e33
			);
		}

//}


//{ Inverse

		/**
		*	\brief \e Compute the determinant of the matrix.
		*
		*	\return Determinant of this matrix.
		*/
		T Determinant() const noexcept
		{
			const T det22_33_23_32 = e22 * e33 - e23 * e32;
			const T det12_33_13_32 = e12 * e33 - e13 * e32;
			const T det12_23_13_22 = e12 * e23 - e13 * e22;
			const T det02_33_03_32 = e02 * e33 - e03 * e32;
			const T det02_23_03_22 = e02 * e23 - e03 * e22;
			const T det02_13_03_12 = e02 * e13 - e03 * e12;

			return
				e00 * (e11 * det22_33_23_32 - e21 * det12_33_13_32 + e31 * det12_23_13_22) -
				e10 * (e01 * det22_33_23_32 - e21 * det02_33_03_32 + e31 * det02_23_03_22) +
				e20 * (e01 * det12_33_13_32 - e11 * det02_33_03_32 + e31 * det02_13_03_12) -
				e30 * (e01 * det12_23_13_22 - e11 * det02_23_03_22 + e21 * det02_13_03_12);
		}

		/**
		*	\brief \b Inverse this matrix.
		*
		*	\return self inversed matrix.
		*/
		Mat4& Inverse()  noexcept
		{
			return *this = GetInversed();
		}

		/**
		*	\brief \b Inverse this matrix.
		*
		*	\return new inversed matrix.
		*/
		Mat4 GetInversed() const noexcept
		{
			const T det = Determinant();

			EDO_ERROR(!Equals0(det), Edo.Maths.Mat4, L"Determinant must be != 0 to compute inverse matrix");

			Mat4 result;

			const T _01x12 = e01 * e12;
			const T _01x13 = e01 * e13;
			const T _01x22 = e01 * e22;
			const T _01x23 = e01 * e23;
			const T _01x32 = e01 * e32;
			const T _01x33 = e01 * e33;

			const T _02x11 = e02 * e11;
			const T _02x13 = e02 * e13;
			const T _02x21 = e02 * e21;
			const T _02x23 = e02 * e23;
			const T _02x31 = e02 * e31;
			const T _02x33 = e02 * e33;

			const T _03x11 = e03 * e11;
			const T _03x12 = e03 * e12;
			const T _03x21 = e03 * e21;
			const T _03x22 = e03 * e22;
			const T _03x31 = e03 * e31;
			const T _03x32 = e03 * e32;

			const T _11x22 = e11 * e22;
			const T _11x23 = e11 * e23;
			const T _11x32 = e11 * e32;
			const T _11x33 = e11 * e33;

			const T _12x21 = e12 * e21;
			const T _12x23 = e12 * e23;
			const T _12x31 = e12 * e31;
			const T _12x33 = e12 * e33;

			const T _13x21 = e13 * e21;
			const T _13x22 = e13 * e22;
			const T _13x31 = e13 * e31;
			const T _13x32 = e13 * e32;

			const T _21x32 = e21 * e32;
			const T _21x33 = e21 * e33;

			const T _22x31 = e22 * e31;
			const T _22x33 = e22 * e33;

			const T _23x31 = e23 * e31;
			const T _23x32 = e23 * e32;

			// Row 0.
			result.e00 =
				e11 * _22x33 -
				e11 * _23x32 -
				e21 * _12x33 +
				e21 * _13x32 +
				e31 * _12x23 -
				e31 * _13x22;

			result.e01 =
				-e01 * _22x33 +
				e01 * _23x32 +
				e21 * _02x33 -
				e21 * _03x32 -
				e31 * _02x23 +
				e31 * _03x22;

			result.e02 =
				e01 * _12x33 -
				e01 * _13x32 -
				e11 * _02x33 +
				e11 * _03x32 +
				e31 * _02x13 -
				e31 * _03x12;

			result.e03 =
				-e01 * _12x23 +
				e01 * _13x22 +
				e11 * _02x23 -
				e11 * _03x22 -
				e21 * _02x13 +
				e21 * _03x12;


			// Row 1
			result.e10 =
				-e10 * _22x33 +
				e10 * _23x32 +
				e20 * _12x33 -
				e20 * _13x32 -
				e30 * _12x23 +
				e30 * _13x22;

			result.e11 =
				e00 * _22x33 -
				e00 * _23x32 -
				e20 * _02x33 +
				e20 * _03x32 +
				e30 * _02x23 -
				e30 * _03x22;

			result.e12 =
				-e00 * _12x33 +
				e00 * _13x32 +
				e10 * _02x33 -
				e10 * _03x32 -
				e30 * _02x13 +
				e30 * _03x12;

			result.e13 =
				e00 * _12x23 -
				e00 * _13x22 -
				e10 * _02x23 +
				e10 * _03x22 +
				e20 * _02x13 -
				e20 * _03x12;


			// Row 2.
			result.e20 =
				e10 * _21x33 -
				e10 * _23x31 -
				e20 * _11x33 +
				e20 * _13x31 +
				e30 * _11x23 -
				e30 * _13x21;

			result.e21 =
				-e00 * _21x33 +
				e00 * _23x31 +
				e20 * _01x33 -
				e20 * _03x31 -
				e30 * _01x23 +
				e30 * _03x21;

			result.e22 =
				e00 * _11x33 -
				e00 * _13x31 -
				e10 * _01x33 +
				e10 * _03x31 +
				e30 * _01x13 -
				e30 * _03x11;

			result.e23 =
				-e00 * _11x23 +
				e00 * _13x21 +
				e10 * _01x23 -
				e10 * _03x21 -
				e20 * _01x13 +
				e20 * _03x11;


			// Row 3.
			result.e30 =
				-e10 * _21x32 +
				e10 * _22x31 +
				e20 * _11x32 -
				e20 * _12x31 -
				e30 * _11x22 +
				e30 * _12x21;

			result.e31 =
				e00 * _21x32 -
				e00 * _22x31 -
				e20 * _01x32 +
				e20 * _02x31 +
				e30 * _01x22 -
				e30 * _02x21;

			result.e32 =
				-e00 * _11x32 +
				e00 * _12x31 +
				e10 * _01x32 -
				e10 * _02x31 -
				e30 * _01x12 +
				e30 * _02x11;

			result.e33 =
				e00 * _11x22 -
				e00 * _12x21 -
				e10 * _01x22 +
				e10 * _02x21 +
				e20 * _01x12 -
				e20 * _02x11;


			result /= det;

			return result;
		}

//}


//{ Lerp

		/**
		*	\brief <b> Clamped Lerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Mat4 Lerp(const Mat4& _start, const Mat4& _end, AlphaT _alpha) noexcept
		{
			return edo::Lerp(_start, _end, _alpha);
		}

		/**
		*	\brief <b> Unclamped Lerp </b> from _start to _end at _alpha.
		*
		*	Reference: https://en.wikipedia.org/wiki/Linear_interpolation
		*
		*	\tparam AlphaT		Input Alpha type.
		* 
		*	\param _start		Starting point of the lerp.
		*	\param _end			Ending point of the lerp.
		*	\param _alpha		Alpha of the lerp.
		*
		*	\return interpolation between _start and _end. return _start when _alpha == 0.0f and _end when _alpha == 1.0f.
		*/
		template<typename AlphaT = T>
		static Mat4 LerpUnclamped(const Mat4& _start, const Mat4& _end, AlphaT _alpha) noexcept
		{
			return edo::LerpUnclamped(_start, _end, _alpha);
		}

//}


//{ Transform


		/**
		*	\brief Make <b> translation matrix </b> from vector3.
		*
		*	\param[in] _transl	Vector to translate
		*
		*	\return translation matrix.
		*/
		static Mat4 MakeTranslation(const Vec3<T>& _transl) noexcept
		{
			Mat4 res = Mat4::Identity;

			res.e03 = _transl.x;
			res.e13 = _transl.y;
			res.e23 = _transl.z;

			return res;
		}

		/**
		*	\brief Make <b> rotation matrix </b> from quaternion.
		*
		*	\param[in] _rot	quaternion to use for rotation.
		*
		*	\return rotation matrix.
		*/
		static Mat4 MakeRotation(const Quat<T>& _rot) noexcept
		{
			EDO_WARN(_rot.IsNormalized(5 * std::numeric_limits<T>::epsilon()), Edo.Maths.Mat4, L"Quaternion should be normalized!");

			// Sources: https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation

			const T XW2 = T(2) * _rot.x * _rot.w;
			const T XX2 = T(2) * _rot.x * _rot.x;
			const T XY2 = T(2) * _rot.x * _rot.y;
			const T XZ2 = T(2) * _rot.x * _rot.z;

			const T YW2 = T(2) * _rot.y * _rot.w;
			const T YY2 = T(2) * _rot.y * _rot.y;
			const T YZ2 = T(2) * _rot.y * _rot.z;

			const T ZW2 = T(2) * _rot.z * _rot.w;
			const T ZZ2 = T(2) * _rot.z * _rot.z;

			return Mat4(
				T(1) - YY2 - ZZ2, XY2 - ZW2, XZ2 + YW2, T(0),
				XY2 + ZW2, T(1) - XX2 - ZZ2, YZ2 - XW2, T(0),
				XZ2 - YW2, YZ2 + XW2, T(1) - XX2 - YY2, T(0),
				T(0), T(0), T(0), T(1)
			);
		}

		/**
		*	\brief Make <b> scale matrix </b> from vector3.
		*
		*	\param[in] _scale	Vector for scaling.
		*
		*	\return scale matrix.
		*/
		static Mat4 MakeScale(const Vec3<T>& _scale) noexcept
		{
			Mat4 result = Mat4::Identity;

			result.e00 = _scale.x;
			result.e11 = _scale.y;
			result.e22 = _scale.z;

			return result;
		}

		/**
		 *	\brief Make <b> LookAt matrix </b> from center, target and up.
		 * 
		 *	\param[in] _eye		Center (camera).
		 *	\param[in] _target	Target to look at.
		 *	\param[in] _up		Up vector (camera).
		 *
		 * 	\returns LookAt matrix.
		*/
		static Mat4 MakeLookAt(const Vec3<T>& _eye, const Vec3<T>& _target, const Vec3<T>& _up) noexcept
		{
			const Vec3<T> forward = (_target - _eye).Normalize();

			return MakeInverseView(_eye, forward, _up);
		}

		/**
		 * \brief Make <b> view matrix </b> for camera.
		 * 
		 * @param _eye 			Camera's world position
		 * @param _forward 		Camera forward vector
		 * @param _up 			Camera's up vector.
		 * 
		 * @return Inverse View matrix. 
		 */
		// static Mat4 MakeView(const Vec3<T>& _eye, const Vec3<T>& _forward, const Vec3<T>& _up);

		/**
		 * \brief Make <b> inverse view matrix </b> for camera.
		 * 
		 * @param _eye 			Camera's world position
		 * @param _forward 		Camera forward vector
		 * @param _up 			Camera's up vector.
		 * 
		 * @return Inverse View matrix. 
		 */
		static Mat4 MakeInverseView(const Vec3<T>& _eye, const Vec3<T>& _forward, const Vec3<T>& _up) noexcept
		{
			const Vec3<T> right = Vec3<T>::Cross(_up, _forward).Normalize();

			const Vec3<T> translation = Vec3(
				Vec3<T>::Dot(_eye, right),
				Vec3<T>::Dot(_eye, _up),
				Vec3<T>::Dot(_eye, _forward)
			);

			return Mat4(
				right.x,	right.y,	right.z,	-translation.x,
				_up.x,		_up.y,		_up.z,		-translation.y,
				_forward.x,	_forward.y,	_forward.z,	-translation.z,
				T(0),		 T(0),		T(0),		T(1)
			);
		}

		/**
		*	\brief Make <b> perspective matrix </b>.
		*
		*	\param[in] _fov			Perspective FOV.
		*	\param[in] _aspect		Aspect ratio (width/height).
		*	\param[in] _near		Near frustum.
		*	\param[in] _far			Far frustum.
		*
		*	\return perspective matrix.
		*/
		static Mat4 MakePerspective(Deg<T> _fov = T(90.0), T _aspect = T(1.0), T _near = T(0.35), T _far = T(10.0)) noexcept
		{
			EDO_ERROR(!Equals0(_far - _near), Edo.Maths.Mat4, L"(far - near) produces division by 0!");

			const T focalLength = T(1) / Tan(_fov / T(2));

			/**
			*	Vulkan/DX12 matrix
			*	Sources: https://youtu.be/U0_ONQQ5ZNM
			*	https://computergraphics.stackexchange.com/questions/12448/vulkan-perspective-matrix-vs-opengl-perspective-matrix
			*/

			return Mat4(
				focalLength / _aspect,	0,					0,									0,
				0,						focalLength,		0,									0,
				0,						0,					_far / (_far - _near),				-(_far * _near) / (_far - _near),
				0,						0,					1,									0
			);
		}

//}

//{ Operators
		
		/**
		*	\brief \e Assignment operator from another Mat4 type.
		*
		*	\tparam TIn			Type of the input Mat4.
		*	\tparam majorIn		Major of the input Mat4.
		*
		*	\param[in] _rhs		Mat4 to assign from.
		*/
		template <typename TIn, MatrixMajor majorIn>
		Mat4& operator=(const Mat4<TIn, majorIn> _rhs) noexcept
		{
			e00 = static_cast<T>(_rhs.e00);
			e01 = static_cast<T>(_rhs.e01);
			e02 = static_cast<T>(_rhs.e02);
			e03 = static_cast<T>(_rhs.e03);

			e10 = static_cast<T>(_rhs.e10);
			e11 = static_cast<T>(_rhs.e11);
			e12 = static_cast<T>(_rhs.e12);
			e13 = static_cast<T>(_rhs.e13);

			e20 = static_cast<T>(_rhs.e20);
			e21 = static_cast<T>(_rhs.e21);
			e22 = static_cast<T>(_rhs.e22);
			e23 = static_cast<T>(_rhs.e23);

			e30 = static_cast<T>(_rhs.e30);
			e31 = static_cast<T>(_rhs.e31);
			e32 = static_cast<T>(_rhs.e32);
			e33 = static_cast<T>(_rhs.e33);

			return *this;
		}

		/**
		*	\brief \e Getter of the opposite signed matrix.
		*
		*	\return new opposite signed matrix.
		*/
		constexpr Mat4 operator-() const noexcept
		{
			return Mat4(
				-e00, -e01, -e02, -e03,
				-e10, -e11, -e12, -e13,
				-e20, -e21, -e22, -e23,
				-e30, -e31, -e32, -e33
			);
		}

		/**
		*	\brief \b Scale each matrix component by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Scale value to apply on all components.
		*
		*	\return new matrix scaled.
		*/
		template <typename TIn>
		Mat4 operator*(TIn _scale) const noexcept
		{
			return Mat4(
				static_cast<T>(e00 * _scale), static_cast<T>(e01 * _scale), static_cast<T>(e02 * _scale), static_cast<T>(e03 * _scale),
				static_cast<T>(e10 * _scale), static_cast<T>(e11 * _scale), static_cast<T>(e12 * _scale), static_cast<T>(e13 * _scale),
				static_cast<T>(e20 * _scale), static_cast<T>(e21 * _scale), static_cast<T>(e22 * _scale), static_cast<T>(e23 * _scale),
				static_cast<T>(e30 * _scale), static_cast<T>(e31 * _scale), static_cast<T>(e32 * _scale), static_cast<T>(e33 * _scale)
			);
		}

		/**
		*	\brief <b> Inverse Scale </b> each matrix component by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Inverse scale value to apply on all components.
		*
		*	\return new matrix inverse-scaled.
		*/
		template <typename TIn>
		Mat4 operator/(TIn _scale) const noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Mat4, L"Divide matrix by 0!");

			return Mat4(
				static_cast<T>(e00 / _scale), static_cast<T>(e01 / _scale), static_cast<T>(e02 / _scale), static_cast<T>(e03 / _scale),
				static_cast<T>(e10 / _scale), static_cast<T>(e11 / _scale), static_cast<T>(e12 / _scale), static_cast<T>(e13 / _scale),
				static_cast<T>(e20 / _scale), static_cast<T>(e21 / _scale), static_cast<T>(e22 / _scale), static_cast<T>(e23 / _scale),
				static_cast<T>(e30 / _scale), static_cast<T>(e31 / _scale), static_cast<T>(e32 / _scale), static_cast<T>(e33 / _scale)
			);
		}

		/**
		*	\brief \b Add term by term matrix values.
		*
		*	\param[in] _rhs		Matrix to add.
		*
		*	\return new matrix result.
		*/
		Mat4 operator+(const Mat4& _rhs) const noexcept
		{
			return Mat4(
				e00 + _rhs.e00, e01 + _rhs.e01, e02 + _rhs.e02, e03 + _rhs.e03,
				e10 + _rhs.e10, e11 + _rhs.e11, e12 + _rhs.e12, e13 + _rhs.e13,
				e20 + _rhs.e20, e21 + _rhs.e21, e22 + _rhs.e22, e23 + _rhs.e23,
				e30 + _rhs.e30, e31 + _rhs.e31, e32 + _rhs.e32, e33 + _rhs.e33
			);
		}

		/**
		*	\brief \b Subtract term by term matrix values.
		*
		*	\param[in] _rhs		Matrix to substract.
		*
		*	\return new matrix result.
		*/
		Mat4 operator-(const Mat4& _rhs) const noexcept
		{
			return Mat4(
				e00 - _rhs.e00, e01 - _rhs.e01, e02 - _rhs.e02, e03 - _rhs.e03,
				e10 - _rhs.e10, e11 - _rhs.e11, e12 - _rhs.e12, e13 - _rhs.e13,
				e20 - _rhs.e20, e21 - _rhs.e21, e22 - _rhs.e22, e23 - _rhs.e23,
				e30 - _rhs.e30, e31 - _rhs.e31, e32 - _rhs.e32, e33 - _rhs.e33
			);
		}

		/**
		*	\brief \b Multiply matrices.
		*
		*	\param[in] _rhs		Matrix to multiply to.
		*
		*	\return new matrix result.
		*/
		Mat4 operator*(const Mat4& _rhs) const noexcept
		{
			return Mat4(
				e00 * _rhs.e00 + e01 * _rhs.e10 + e02 * _rhs.e20 + e03 * _rhs.e30,
				e00 * _rhs.e01 + e01 * _rhs.e11 + e02 * _rhs.e21 + e03 * _rhs.e31,
				e00 * _rhs.e02 + e01 * _rhs.e12 + e02 * _rhs.e22 + e03 * _rhs.e32,
				e00 * _rhs.e03 + e01 * _rhs.e13 + e02 * _rhs.e23 + e03 * _rhs.e33,

				e10 * _rhs.e00 + e11 * _rhs.e10 + e12 * _rhs.e20 + e13 * _rhs.e30,
				e10 * _rhs.e01 + e11 * _rhs.e11 + e12 * _rhs.e21 + e13 * _rhs.e31,
				e10 * _rhs.e02 + e11 * _rhs.e12 + e12 * _rhs.e22 + e13 * _rhs.e32,
				e10 * _rhs.e03 + e11 * _rhs.e13 + e12 * _rhs.e23 + e13 * _rhs.e33,

				e20 * _rhs.e00 + e21 * _rhs.e10 + e22 * _rhs.e20 + e23 * _rhs.e30,
				e20 * _rhs.e01 + e21 * _rhs.e11 + e22 * _rhs.e21 + e23 * _rhs.e31,
				e20 * _rhs.e02 + e21 * _rhs.e12 + e22 * _rhs.e22 + e23 * _rhs.e32,
				e20 * _rhs.e03 + e21 * _rhs.e13 + e22 * _rhs.e23 + e23 * _rhs.e33,

				e30 * _rhs.e00 + e31 * _rhs.e10 + e32 * _rhs.e20 + e33 * _rhs.e30,
				e30 * _rhs.e01 + e31 * _rhs.e11 + e32 * _rhs.e21 + e33 * _rhs.e31,
				e30 * _rhs.e02 + e31 * _rhs.e12 + e32 * _rhs.e22 + e33 * _rhs.e32,
				e30 * _rhs.e03 + e31 * _rhs.e13 + e32 * _rhs.e23 + e33 * _rhs.e33
			);
		}

		/**
		*	\brief \b Inverse multiply matrices.
		*
		*	\param[in] _rhs		Matrix to inverse multiply to.
		*
		*	\return new matrix result.
		*/
		Mat4 operator/(const Mat4& _rhs) const noexcept
		{
			return *this * _rhs.GetInversed();
		}


		/**
		*	\brief transform this vector by this matrix.
		*
		*	Ignore 4th row/column component.
		*
		*	\param[in] _rhs		Vector to transform.
		*
		*	\return Transformed vector.
		*/
		Vec3<T> operator*(const Vec3<T>&_rhs) const noexcept
		{
			return Vec3<T>(
				e00 * _rhs.x + e01 * _rhs.y + e02 * _rhs.z,
				e10 * _rhs.x + e11 * _rhs.y + e12 * _rhs.z,
				e20 * _rhs.x + e21 * _rhs.y + e22 * _rhs.z
			);
		}

		/**
		*	\brief transform this vector by this matrix.
		*
		*	\param[in] _rhs		Vector to transform.
		*
		*	\return Transformed vector.
		*/
		Vec4<T> operator*(const Vec4<T>&_rhs) const noexcept
		{
			return Vec4<T>(
				e00 * _rhs.x + e01 * _rhs.y + e02 * _rhs.z + e03 * _rhs.w,
				e10 * _rhs.x + e11 * _rhs.y + e12 * _rhs.z + e13 * _rhs.w,
				e20 * _rhs.x + e21 * _rhs.y + e22 * _rhs.z + e23 * _rhs.w,
				e30 * _rhs.x + e31 * _rhs.y + e32 * _rhs.z + e33 * _rhs.w
			);
		}


		/**
		*	\brief \b Scale each matrix component by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Scale value to apply on all components.
		*
		*	\return self matrix scaled.
		*/
		template <typename TIn>
		Mat4& operator*=(TIn _scale) noexcept
		{
			e00 *= _scale;
			e01 *= _scale;
			e02 *= _scale;
			e03 *= _scale;

			e10 *= _scale;
			e11 *= _scale;
			e12 *= _scale;
			e13 *= _scale;

			e20 *= _scale;
			e21 *= _scale;
			e22 *= _scale;
			e23 *= _scale;

			e30 *= _scale;
			e31 *= _scale;
			e32 *= _scale;
			e33 *= _scale;

			return *this;
		}

		/**
		*	\brief <b> Inverse Scale </b> each matrix component by _scale.
		*
		*	\tparam TIn			Type of the input scale.
		* 
		*	\param[in] _scale	Inverse scale value to apply on all components.
		*
		*	\return self matrix inverse-scaled.
		*/
		template <typename TIn>
		Mat4& operator/=(TIn _scale) noexcept
		{
			EDO_ERROR(!Equals0(_scale), Edo.Maths.Mat4, L"Divide matrix by 0!");

			e00 /= _scale;
			e01 /= _scale;
			e02 /= _scale;
			e03 /= _scale;

			e10 /= _scale;
			e11 /= _scale;
			e12 /= _scale;
			e13 /= _scale;

			e20 /= _scale;
			e21 /= _scale;
			e22 /= _scale;
			e23 /= _scale;

			e30 /= _scale;
			e31 /= _scale;
			e32 /= _scale;
			e33 /= _scale;

			return *this;
		}

		/**
		*	\brief \b Add term by term matrix values.
		*
		*	\param[in] _rhs		Matrix to add.
		*
		*	\return self matrix result.
		*/
		Mat4& operator+=(const Mat4& _rhs) noexcept
		{
			e00 += _rhs.e00;
			e01 += _rhs.e01;
			e02 += _rhs.e02;
			e03 += _rhs.e03;

			e10 += _rhs.e10;
			e11 += _rhs.e11;
			e12 += _rhs.e12;
			e13 += _rhs.e13;

			e20 += _rhs.e20;
			e21 += _rhs.e21;
			e22 += _rhs.e22;
			e23 += _rhs.e23;

			e30 += _rhs.e30;
			e31 += _rhs.e31;
			e32 += _rhs.e32;
			e33 += _rhs.e33;

			return *this;
		}

		/**
		*	\brief \b Subtract term by term matrix values.
		*
		*	\param[in] _rhs		Matrix to substract.
		*
		*	\return self matrix result.
		*/
		Mat4& operator-=(const Mat4& _rhs) noexcept
		{
			e00 -= _rhs.e00;
			e01 -= _rhs.e01;
			e02 -= _rhs.e02;
			e03 -= _rhs.e03;

			e10 -= _rhs.e10;
			e11 -= _rhs.e11;
			e12 -= _rhs.e12;
			e13 -= _rhs.e13;

			e20 -= _rhs.e20;
			e21 -= _rhs.e21;
			e22 -= _rhs.e22;
			e23 -= _rhs.e23;

			e30 -= _rhs.e30;
			e31 -= _rhs.e31;
			e32 -= _rhs.e32;
			e33 -= _rhs.e33;

			return *this;
		}

		/**
		*	\brief \b Multiply matrices.
		*
		*	\param[in] _rhs		Matrix to multiply to.
		*
		*	\return self matrix result.
		*/
		Mat4& operator*=(const Mat4& _rhs) noexcept
		{
			return *this = *this * _rhs;
		}

		/**
		*	\brief \b Inverse multiply matrices.
		*
		*	\param[in] _rhs		Matrix to inverse multiply to.
		*
		*	\return self matrix result.
		*/
		Mat4& operator/=(const Mat4& _rhs) noexcept
		{
			return *this = *this / _rhs;
		}

//}
	};


//{ Constants

	template <typename T, MatrixMajor major>
	const Mat4<T, major> Mat4<T, major>::Zero
	{
		T(0), T(0), T(0), T(0),
		T(0), T(0), T(0), T(0),
		T(0), T(0), T(0), T(0),
		T(0), T(0), T(0), T(0)
	};

	template <typename T, MatrixMajor major>
	const Mat4<T, major> Mat4<T, major>::Identity
	{
		T(1), T(0), T(0), T(0),
		T(0), T(1), T(0), T(0),
		T(0), T(0), T(1), T(0),
		T(0), T(0), T(0), T(1)
	};

//}


	/**
	*	\brief \b Scale each matrix components by _lhs.
	* 
	*	\tparam TIn			Type of the input scale.
	*
	*	\param[in] _lhs		Scale value to apply on all components.
	*	\param[in] _rhs		Matrix to scale.
	*
	*	\return new matrix scaled.
	*/
	template <typename T, MatrixMajor major, typename TIn>
	Mat4<T, major> operator*(TIn _lhs, const Mat4<T, major>& _rhs) noexcept
	{
		return _rhs * _lhs;
	}

	/**
	*	\brief <b> Inverse Scale </b> each matrix components by _lhs.
	*
	*	\tparam TIn			Type of the input scale.
	* 
	*	\param[in] _lhs		Inverse scale value to apply on all components.
	*	\param[in] _rhs		Matrix to scale.
	*
	*	\return new matrix inverse-scaled.
	*/
	template <typename T, MatrixMajor major, typename TIn>
	Mat4<T, major> operator/(TIn _lhs, const Mat4<T, major>& _rhs)
	{
		EDO_ERROR(!Equals0(_rhs.e00), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e01), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e02), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e03), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e10), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e11), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e12), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e13), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e20), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e21), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e22), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e23), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e30), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e31), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e32), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");
		EDO_ERROR(!Equals0(_rhs.e33), Edo.Maths.Mat3, L"Inverse scale matrix by 0!");

		return Mat4<T, major>(
			_lhs / _rhs.e00, _lhs / _rhs.e01, _lhs / _rhs.e02, _lhs / _rhs.e03,
			_lhs / _rhs.e10, _lhs / _rhs.e11, _lhs / _rhs.e12, _lhs / _rhs.e13,
			_lhs / _rhs.e20, _lhs / _rhs.e21, _lhs / _rhs.e22, _lhs / _rhs.e23,
			_lhs / _rhs.e30, _lhs / _rhs.e31, _lhs / _rhs.e32, _lhs / _rhs.e33
		);
	}


#if __has_include(<edo_debug.hpp>)
	template <typename T, MatrixMajor major>
	std::string ToString(const Mat4<T, major> _mat) noexcept
	{
		// Keep memory order (Raw / column major).
		const T* const data = _mat.Data();

		return "Mat4{\n " +
			edo::ToString(data[0]) + ",\t" +
			edo::ToString(data[1]) + ",\t" +
			edo::ToString(data[2]) + ",\t" +
			edo::ToString(data[3]) + ",\n " +

			edo::ToString(data[4]) + ",\t" +
			edo::ToString(data[5]) + ",\t" +
			edo::ToString(data[6]) + ",\t" +
			edo::ToString(data[7]) + ",\n " +

			edo::ToString(data[8]) + ",\t" +
			edo::ToString(data[9]) + ",\t" +
			edo::ToString(data[10]) + ",\t" +
			edo::ToString(data[11]) + ",\n " +

			edo::ToString(data[12]) + ",\t" +
			edo::ToString(data[13]) + ",\t" +
			edo::ToString(data[14]) + ",\t" +
			edo::ToString(data[15]) + "\n}";
	}
#endif // edo_debug


//{ Aliases

	/// Alias for int32 Mat4.
	using Mat4i = Mat4<int32_t>;

	/// Alias for float Mat4.
	using Mat4f = Mat4<float>;

	/// Alias for double Mat4.
	using Mat4d = Mat4<double>;


	/// Template alias of Mat4
	template <typename T, MatrixMajor major = MatrixMajor::Default>
	using Matrix4 = Mat4<T>;

	/// Alias for int32 Matrix4.
	using Matrix4i = Matrix4<int32_t>;

	/// Alias for float Matrix4.
	using Matrix4f = Matrix4<float>;

	/// Alias for double Matrix4.
	using Matrix4d = Matrix4<double>;


	/// Alias for row major int32 Mat4.
	using RMat4i = Mat4<int32_t, MatrixMajor::Row>;

	/// Alias for row major float Mat4.
	using RMat4f = Mat4<float, MatrixMajor::Row>;

	/// Alias for row major double Mat4.
	using RMat4d = Mat4<double, MatrixMajor::Row>;


	/// Alias for column major int32 Mat4.
	using CMat4i = Mat4<int32_t, MatrixMajor::Column>;

	/// Alias for column major float Mat4.
	using CMat4f = Mat4<float, MatrixMajor::Column>;

	/// Alias for column major double Mat4.
	using CMat4d = Mat4<double, MatrixMajor::Column>;

//}

// ##############################################################
}

#endif // EDO_SH_MATHS_GUARD