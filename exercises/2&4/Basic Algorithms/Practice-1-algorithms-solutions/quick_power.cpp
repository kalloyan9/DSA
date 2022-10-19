
#include <iostream>

template <typename T>
T quick_power( const T& elem, uint32_t power )
{
	if ( power == 0 )
	{
		return T();
	}
	if ( power == 1 )
	{
		return elem;
	}

	if ( power & 1 ) // odd power
	{
		return elem * quick_power( elem, power -1 );
	}
	else // even power
	{
		T res = quick_power( elem, power / 2 );
		return res * res;
	}
}

template <>
double quick_power( const double& elem, uint32_t power )
{
	if ( power == 0 )
	{
		return 1.0f;
	}
	if ( power == 1 )
	{
		return elem;
	}

	if ( power & 1 ) // odd power
	{
		return elem * quick_power( elem, power / 2 );
	}
	else // even power
	{
		double res = quick_power( elem, power / 2 );
		return res * res;
	}
}



template < class T >
class Matrix
{
public:
	Matrix()
	{
		for ( short i = 0; i < 3; ++i )
		{
			for ( short j = 0; j < 3; ++j )
				mat[ i ][ j ] = ( i == j ? 1 : 0 );
		}
	}

	Matrix( const Matrix<T>& other )
	{
		for ( size_t i = 0; i < 3; i++ )
		{
			for ( size_t j = 0; j < 3; j++ )
			{
				mat[ i ][ j ] = other.mat[ i ][ j ];
			}
		}
	}

	Matrix<T>& operator=( const Matrix<T>& other )
	{
		if ( this != &other )
		{
			for ( size_t i = 0; i < 3; i++ )
			{
				for ( size_t j = 0; j < 3; j++ )
				{
					mat[ i ][ j ] = other.mat[ i ][ j ];
				}
			}
		}
		return *this;
	}

	Matrix<T>& operator*=( const Matrix<T>& rhs )
	{
		T resultMatrix[ 3 ][ 3 ];
		for ( size_t i = 0; i < 3; i++ )
		{
			for ( size_t j = 0; j < 3; j++ )
			{
				resultMatrix[ i ][ j ] = 0;
				for ( size_t k = 0; k < 3; k++ )
				{
					resultMatrix[ i ][ j ] += mat[ i ][ k ] * rhs.mat[ k ][ j ];
				}
			}
		}
		for ( size_t i = 0; i < 3; i++ )
		{
			for ( size_t j = 0; j < 3; j++ )
			{
				mat[ i ][ j ] = resultMatrix[ i ][ j ];
			}
		}
		return *this;
	}

	void print() const
	{
		for ( size_t i = 0; i < 3; i++ )
		{
			for ( size_t j = 0; j < 3; j++ )
			{
				std::cout << mat[ i ][ j ] << " ";
			}
			std::cout << std::endl;
		}
	}

public:
	struct Point3D
	{
		T x, y, z;
		Point3D( const T& _x, const T& _y, const T& _z ) : x ( _x ), y( _y ), z( _z ){ }
	};

	void setU( const Point3D& u )
	{
		mat[ 0 ][ 0 ] = u.x; mat[ 0 ][ 1 ] = u.y; mat[ 0 ][ 2 ] = u.z;
	}

	void setV( const Point3D& v )
	{
		mat[ 1 ][ 0 ] = v.x; mat[ 1 ][ 1 ] = v.y; mat[ 1 ][ 2 ] = v.z;
	}

	void setW( const Point3D& w )
	{
		mat[ 2 ][ 0 ] = w.x; mat[ 2 ][ 1 ] = w.y; mat[ 2 ][ 2 ] = w.z;
	}

private:
	T mat[ 3 ][ 3 ];
};

template <typename T>
Matrix<T> operator*( Matrix<T> lhs, const Matrix<T>& rhs )
{
	return lhs *= rhs;
}

int main()
{
	Matrix<int> m1;
	m1.setU( Matrix<int>::Point3D(  3, 2, 1 ) );
	m1.setV( Matrix<int>::Point3D( -4, 0, 5 ) );
	m1.setW( Matrix<int>::Point3D( -9, 2, 4 ) );
	m1.print();

	Matrix<int> res = quick_power<Matrix<int>>( m1, 5 );

	res.print();

	return 0;
}