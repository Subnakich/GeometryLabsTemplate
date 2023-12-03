#ifndef VECTOR4_HPP
#define VECTOR4_HPP

namespace vector4s
{

	template <typename T>
	class Vector4
	{
	public:

		Vector4();

		Vector4(T X, T Y, T Z, T W);


		template <typename U>
		explicit Vector4(const Vector4<U> &vector);

		T x; //!< X coordinate of the vector
		T y; //!< Y coordinate of the vector
		T z; //!< Z coordinate of the vector
		T w;
	};


	template <typename T>
	Vector4<T> operator-(const Vector4<T> &left);

	template <typename T>
	Vector4<T> &operator+=(Vector4<T> &left, const Vector4<T> &right);

	template <typename T>
	Vector4<T> &operator-=(Vector4<T> &left, const Vector4<T> &right);

	template <typename T>
	Vector4<T> operator+(const Vector4<T> &left, const Vector4<T> &right);

	template <typename T>
	Vector4<T> operator-(const Vector4<T> &left, const Vector4<T> &right);

	template <typename T>
	Vector4<T> operator+(const Vector4<T> &left, T right);

	template <typename T>
	Vector4<T> operator*(const Vector4<T> &left, T right);

	template <typename T>
	Vector4<T> operator*(T left, const Vector4<T> &right);

	template <typename T>
	Vector4<T> &operator*=(Vector4<T> &left, T right);

	template <typename T>
	Vector4<T> operator/(const Vector4<T> &left, T right);

	template <typename T>
	Vector4<T> &operator/=(Vector4<T> &left, T right);

	template <typename T>
	bool operator==(const Vector4<T> &left, const Vector4<T> &right);

	template <typename T>
	bool operator!=(const Vector4<T> &left, const Vector4<T> &right);


	#include "vector4.inl"
	typedef Vector4<int> Vector4i;
	typedef Vector4<float> Vector4f;


} // namespace vecs


#endif // VECTOR4_HPP
