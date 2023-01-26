#ifndef MATRIX_2D
#define MATRIX_2D

//#define NDEBUG

#include <iostream>
#include <cassert>
#include <algorithm>

/**
  @file matrix_2d.h
  @brief matrix_2d template class declaration and implementation.
*/


/**
  @brief Class for representing a two-dimensional array

  Class that encapsulates a two-dimensional array. It is used a single array
  to simulate the presence of the two-dimensional array.
*/

template <typename T> class matrix_2d {
	public:

	/**
		@brief Data type to represent the dimensions of the two-dimensional matrix
	*/
		typedef unsigned int size_type;

	private:

		T* _matrix;

		size_type _rows;
		size_type _col;

	public:

		/**
    	@brief Default constructor

    	Initialize the object to a null two-dimensional array.

   		@post _buffer = nullptr
   		@post _rows = 0
   		@post _col = 0
  	*/
		matrix_2d(void) : _rows(0), _col(0), _matrix(nullptr) {

			#ifndef NDEBUG
			std::cout << "matrix_2d::matrix_2d()" << std::endl;
			#endif
		}


		/**
		 * @brief Parameterized constructor
		 * 
		 * 
		 *	Parameterized constructor to create a matrix with the given dimensions. Matrix 
		 *  cells are not initialized. If x = 0 or y = 0, a null matrix_2d is created.
		 * 
		 * @param y number of rows
		 * @param x number of columns
		 * 
		 * @pre x >= 0
		 * @pre y >= 0
		 * 
		 * @post _matrix != nullptr
		 * @post _rows = x
		 * @post _col = y; 
  	*/
		matrix_2d(size_type y, size_type x) : _rows(0), _col(0), _matrix(nullptr) {
			assert(x >= 0);
			assert(y >= 0);

			if(x > 0 && y > 0) {
				_matrix = new T[x * y];
				_rows = y;
				_col = x;
			}

			#ifndef NDEBUG
			std::cout << "matrix_2d::matrix_2d(size_type, size_type)" << std::endl;
			#endif
		}
		
		/**
			@brief Conversion copy constructor
			
			Constructor from another matrix_2d on a different template parameter
			U. If in the casting procedure generates an exception, a null matrix_2d is 
			created and the exception is rethrown to the caller.
			
			@param source matrix_2d to build the new matrix_2d
		*/
		template <typename U>
		matrix_2d(const matrix_2d<U>& other) : _rows(0), _col(0), _matrix(nullptr) {

			this->_matrix = new T[other.size()];
			this->_rows = other.rows();
			this->_col = other.columns();
			
			try {
				for(size_type i=0; i < this->_rows; ++i)
					for(size_type j=0; j < this->_col; ++j) {
						(*this)(i, j) = static_cast<T>(other(i, j));
					}
			}
			catch(...) {
				delete[] _matrix;
				this->_matrix = nullptr;
				this->_rows = 0;
				this->_col = 0;
				throw;
			}

			#ifndef NDEBUG
			std::cout << "matrix_2d::matrix_2d(const matrix_2d<U>&)" << std::endl;
			#endif
		}

		/**
    	@brief Destructor

    	Class destructor. Deallocates the simulating array from heap.

    	@post _matrix = nullptr
	    @post _rows = 0
	    @post _col = 0
  	*/
		~matrix_2d()  {
			delete[] _matrix;
			_matrix = nullptr;
		 	_rows = 0;
		 	_col = 0;

		  #ifndef NDEBUG
		 	std::cout << "matrix_2d::~matrix_2d()"<< std::endl;
			#endif
		}
		
		/**
    	@brief Copy Constructor

    	Class copy constructor. Creates a new matrix_2d from the given one as a parameter.
    	The two matrix_2d are independent.

    	@param other matrix_2d to copy
    
    	@post _matrix != nullptr
    	@post _rows = other._rows
    	@post _col = other._col
  	*/
		matrix_2d(const matrix_2d& other) : _matrix(nullptr), _rows(0), _col(0) {
		  	_matrix = new T[other.size()];
		  	_rows = other._rows;
		  	_col = other._col;
		  	
		  	try {
		   		for(size_type i = 0; i < other.size(); ++i)
		      		_matrix[i] = other._matrix[i];
		  	}
		  	catch(...) {
		    	delete[] _matrix;
		    	_matrix = nullptr;
		    	_rows = 0;
		    	_col = 0;
		    	throw;
		  }
		  
		  #ifndef NDEBUG
		  std::cout << "matrix_2d::matrix_2d(const matrix_2d&)"<< std::endl;
		  #endif
		}
		
		/**
		 * 
		 * @brief Assignment operator
		 * 
		 * Refefinition of assignment operator. Copies the contents of another matrix_2d object.
		 * 
		 * @param other source matrix_2d to copy
		 * 
		 * @post _matrix != nullptr
		 * @post _rows = other._rows
		 * @post _col = other._col 
		 * 
		 * @return current object reference
	  */
		matrix_2d& operator=(const matrix_2d& other) {
			
			if(&other != this) {
				matrix_2d tmp(other);
				this->swap(tmp);
			}
			
			#ifndef NDEBUG
		  std::cout << "matrix_2d::operator=(const matrix_2d& other)" << std::endl;
		  #endif
			
			return *this;
		}
		
		/**
		 * 
		 * @brief [y, x] cell getter/setter
		 * 
		 * Redefinition of operator(). Allows to both read or write the cell in
		 * position [y, x].
		 * 
		 * @param y row of the cell
		 * 
		 * @param x column of the cell
		 * 
		 * @pre y >= 0
		 * @pre y < _rows
		 * @pre x >= 0
		 * @pre x < _col

	    @return cell reference
	  */
		T& operator()(size_type y, size_type x) {

			assert(y >= 0);
			assert(x >= 0);
			assert(y < _rows);
			assert(x < _col);

			return _matrix[(y * _col) + x];
		}

		/**
    	* @brief [y, x] cell getter
			*
	    * Redefinition of operator(). Allows to read the cell in
	    * position [y, x].
			*
	    * @param y row of the cell
	    * @param x column of the cell
			*
	    * @pre x >= 0
	    * @pre x < _col
			* @pre y >= 0
			* @pre y < _rows
			* 
	    * @return cell read-only reference
	  */
		const T& operator()(size_type y, size_type x) const {

			assert(y >= 0);
			assert(x >= 0);
			assert(y < _rows);
			assert(x < _col);

			return _matrix[(y * _col) + x];
		}

		/**
		 * @brief Class swap method
		 * 
		 * Method to swap the contents of two matrix_2d.
	
	    @param other the matrix_2d to exchange content with
	  */
		void swap(matrix_2d& other) {
			std::swap(this->_matrix, other._matrix);
			std::swap(this->_rows, other._rows);
			std::swap(this->_col, other._col);
		}

		/**
    *	@brief Rows getter
    * 
    * Returns the number of rows of the matrix.
		*
	  * @return number of rows
	  */
		inline size_type rows() const {return _rows;}

		/**
		 * @brief Columns getter
		 * 
		 * Returns the number of columns of the matrix.
		 *
	   * @return number of columns
	  */
		inline size_type columns() const {return _col;}

		/**
		 * @brief Total dimension getter
		 * 
		 * Returns the matrix total dimension.
		 *
	   * @return matrix dimension
	  */
		inline size_type size() const {return _rows * _col;}
		

		/**
	    @brief Comparison function
	
	    Returns true if the two matrix_2d are equal, false otherwise.
	    Two matrix_2d are considered equal if they have the same shape and
			the same element for each cell. The comparison between elements is
			performed by a functor passed as the second parameter.	
	
	    @param other the matrix_2d to compare with the current instance
	    @param equality the functor to use for the comparison

	    @pre E : T x T -> {0, 1}

	    @return true if the two matrix_2d are equal, false otherwise
	  */
		template <typename E>
		bool equals(const matrix_2d& other, const E equality) const {

			if(this->_rows != other._rows || this->_col != other._col)
				return false;
			
			for(size_type i=0; i < this->size(); ++i)
				if(!equality(this->_matrix[i], other._matrix[i]))
					return false;
					
			return true;
		}

		/**
		  @brief Redefinition of operator==
		
			Returns true if the two matrix_2d are equal, false otherwise.
			Two matrix_2d are considered equal if they have the same shape e
			the same element for each cell. The comparison between elements is
			performed by the operator== for any data type T.
		
		  @param other the matrix_2d to compare with the current instance

		  @return true if the two matrix_2d are equal, false otherwise
	  */
		bool operator==(const matrix_2d& other) const {
			return this->equals(other, [] (T& p1, T& p2) -> bool {return p1 == p2;});
		}

		/**
	    @brief Redefinition of operator!=
	
	    Returns the negation of operator==.
	
	    @param other the matrix_2d to compare with the current instance
	  */
		bool operator!=(const matrix_2d& other) const {
			return !((*this) == other);
		}
		
		/**
	    @brief 2-dimensional submatrix extraction
	
	    Returns a matrix_2d extracted from the current matrix_2d instance. 
	    Indexes start from 0 and both lower and upper limits are included. 
	    If the submatrix extraction fails, the exception is rethrown to the caller.
	
	    @param y1 starting row
	    @param y2 final row
	    @param x1 starting column
	    @param x2 final column

	    @pre y1 >= 0
	    @pre y1 < _rows
	    @pre x1 >= 0
	    @pre x1 < _col
	    @pre y2 >= 0	   
	    @pre y2 < _rows
	    @pre x2 >= 0
	    @pre x2 < _col
	    @pre y1 <= y2
	    @pre x1 <= x2

	    @return pointer to submatrix [y1:y2, x1:x2]
	  */
		matrix_2d* slice(size_type y1, size_type y2,
								size_type x1, size_type x2) const {
							
			assert(y1 >= 0 && y1 < this->_rows);
			assert(y2 >= 0 && y2 < this->_rows);
			assert(y1 <= y2);
			
			assert(x1 >= 0 && x1 < this->_col);
			assert(x2 >= 0 && x2 < this->_col);
			assert(x1 <= x2);
			
			matrix_2d* submatrix = new matrix_2d(y2 - y1 + 1, x2 - x1 + 1);

			try {
				for(size_type i = y1; i <= y2; ++i)
					for(size_type j = x1; j <= x2; ++j)
						(*submatrix)(i - y1, j - x1) = (*this)(i, j);
			}
			catch(...) {
				delete submatrix;
				throw;
			}
					
			return submatrix;
		}

	/**
		@brief Fill method

		Method that fills the current matrix_2d with the values obtained from two 
		generics iterators. The values previously contained in the array are overwritten.
		If the iterator reaches the end before completely filling the matrix_2d,
		the remaining elements remain intact. If at any point an excpetion is thrown, changes
		are discarded and the exception is rethrown to the caller.

		@param start start sequence iterator
		@param end end sequence iterator
	*/
		template <typename I>
		void fill(I start, I end) {
			
			size_type i = 0;

			T* tmp = new T[this->size()];

			try {
				while(i < this->size() && start != end) {
					tmp[i] = static_cast<T>(*start);	
					++start;
					++i;
				} 

				while(i < this->size()) {
					tmp[i] = this->_matrix[i];
					++i;
				}
			}

			catch(...) {
				delete[] tmp;
				throw;
			}

			std::swap(this->_matrix, tmp);
			delete[] tmp;
		}

	/**
		@brief Fill method 

		Method that fills the current matrix_2d with the values obtained from two 
		generics iterators. The values previously contained in the array are overwritten.
		If the iterator reaches the end before completely filling the matrix_2d,
		the remaining elements remain intact. Iterators are passed to the method by reference.
		A dummy third parameter is used to distinguish this method from the one that passes 
		iterators by value. If at any point an excpetion is thrown, changes are discarded 
		and the exception is rethrown to the caller.

		@param start start sequence iterator
		@param end end sequence iterator
	*/
		template <typename I>
		void fill(I& start, I& end, int) {
			
			size_type i = 0;

			T* tmp = new T[this->size()];

			try {
				while(i < this->size() && start != end) {
					tmp[i] = static_cast<T>(*start);	
					++start;
					++i;
				} 

				while(i < this->size()) {
					tmp[i] = this->_matrix[i];
					++i;
				}
			}

			catch(...) {
				delete[] tmp;
				throw;
			}

			std::swap(this->_matrix, tmp);
			delete[] tmp; 		
		}

	/**
	 * @brief Random access iterator
	 
  	Random access iterator for the matrix_2d class. The iterator is mapped
   	into a pointer to the data type T.
	*/
		typedef T* iterator;

	/**
	 * @brief Read-only random access iterator

  	Random access iterator for the matrix_2d class. The iterator is mapped
   	into a constant pointer to the data type T. 
	*/
		typedef const T* const_iterator;

 	/**
		@brief Sequence start iterator

		Returns the start-sequence read/write iterator of a matrix_2d.
	*/
		iterator begin() {
			return _matrix;
		}

	/**
		@brief Sequence end iterator

		Returns the end-sequence read/write iterator of a matrix_2d.
	*/
		iterator end() {
			return _matrix + this->size();
		}

	/**
		@brief Read-only sequence start iterator

		Returns the start-sequence read-only iterator of a matrix_2d.
	*/
		const_iterator begin() const {
			return _matrix;
		}

	/**
		@brief Read-only sequence end iterator

		Returns the end-of-sequence read-only iterator of a matrix_2d.
	*/
		const_iterator end() const {
			return _matrix + this->size();
		}
};


/**
	@brief Print function

	Function that prints a matrix_2d on an ostream passed as a parameter.

	@param os output stream
	@param matrix matrix_2d to print

	@return ostream reference
*/
template <typename T>
std::ostream& operator<<(std::ostream& os, const matrix_2d<T>& matrix) {

		for(typename matrix_2d<T>::size_type i = 0; i < matrix.rows(); ++i) {
			for(typename matrix_2d<T>::size_type j = 0; j < matrix.columns(); ++j)
				std::cout << matrix(i, j) << " ";
			std::cout << std::endl;
		}

		return os;
}


/**
		@brief Transformation function

		Returns a new matrix_2d from the source matrix_2d given as parameter, 
		obtained by applying the functor func to each element of the source array.
	
		@pre func : W -> T

		@param source source matrix_2d
		@param func functor to applicate

		@return pointer to the transformed matrix_2d
*/
template <typename T, typename W, typename F>
matrix_2d<T>* transform(const matrix_2d<W>& source, const F func) {
		
	matrix_2d<T>* transformed = new matrix_2d<T>(source.rows(), 
																							source.columns());

	try {
		for(typename matrix_2d<W>::size_type i = 0; i < source.rows(); ++i)
			for(typename matrix_2d<W>::size_type j = 0; j < source.columns(); ++j) {
				(*transformed)(i, j) = func(source(i, j));
			}
		}
	catch(...) {
		delete transformed;
		throw;
	}
				
	return transformed;
}

#endif


