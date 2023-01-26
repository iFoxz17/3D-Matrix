#ifndef MATRIX_3D
#define MATRIX_3D

#include <iterator> // std::forward_iterator_tag
#include <cstddef> // std::ptrdiff_t
#include "matrix_2d.h"

//#define NDEBUG

/**
  @file matrix_3d.h
  @brief matrix_3d template class declaration and implementation.
*/


/**
  @brief Class for representing a three-dimensional array

  Class that encapsulates a three-dimensional array. It used a one-dimensional
  array of two-dimensional matrix (matrix_2d) to simulate the presence of
  the three-dimensional array.
*/

template <typename T> class matrix_3d {
	
	public:

		/**
			@brief Data type to represent the dimensions of the three-dimensional matrix
		*/
		typedef typename matrix_2d<T>::size_type size_type;
	
	private:

		matrix_2d<T>* _vect;
		size_type _size;

	public:
		
		/**
	    	@brief Default constructor

    		Initialize the object to a null three-dimensional array.

	   		@post _vect = nullptr
	   		@post _size = 0
  		*/
		matrix_3d(void) : _vect(nullptr), _size(0) {
			
			#ifndef NDEBUG
			std::cout << "matrix_3d::matrix_3d()" << std::endl;
			#endif
		}
		
		/**
	    	@brief Parameterized constructor

    		Parameterized constructor to create a matrix with the given dimensions.
    		Matrix cells are not initialized. 
    		If x = 0 or y = 0 or z = 0, a null matrix_3d is created.
			
			@param z number of plans
			@param y number of rows
	    	@param x number of columns
	    	
			@pre z >= 0
			@pre y >= 0
	    	@pre x >= 0

	    	@post _vect != nullptr
	    	@post _size = z
	    	@post _vect[i] != nullptr
	  	*/
		matrix_3d(size_type z, size_type y, size_type x) : _vect(nullptr), _size(0) {

			assert(z >= 0);
			assert(x >= 0);
			assert(y >= 0);

			if(x > 0 && y > 0) {

				_vect = new matrix_2d<T>[z];
				_size = z;

				matrix_2d<T>* tmp = nullptr;
				
				try {
					for(size_type i = 0; i < _size; ++i) {
						tmp = new matrix_2d<T>(y, x);
						tmp->swap(_vect[i]);
						delete tmp;
						tmp = nullptr;
					}
				}
				catch(...) {
					delete[] _vect;
					_vect = nullptr;
					_size = 0;
					throw;
				}
			}

			#ifndef NDEBUG
			std::cout << "matrix_3d::matrix_3d(size_type, size_type, size_type)" << std::endl;
			#endif
		}

		/**
			@brief Conversion copy constructor
			
			Constructor from another matrix_3d on a different template parameter
			U. If in the casting procedure generates an exception, a null matrix_3d is 
			created and the exception is rethrown to the caller.
			
			@param source matrix_2d to build the new matrix_2d
		*/
		template <typename U>
		matrix_3d(const matrix_3d<U>& other) : _vect(nullptr), _size(0) {

			this->_vect = new matrix_2d<T>[other.plans()];
			this->_size = other.plans();

			matrix_2d<T>* tmp = nullptr;
			
			try {
				for(size_type i=0; i < other.plans(); ++i) {
					tmp = new matrix_2d<T>(other[i]);
					tmp->swap(this->_vect[i]); 
					delete tmp;
					tmp = nullptr;
				}
			}
			catch(...) {
				delete[] _vect;
				this->_vect = nullptr;
				this->_size = 0;
				throw;
			}

			#ifndef NDEBUG
			std::cout << "matrix_3d::matrix_3d(const matrix_3d<U>&)" << std::endl;
			#endif
		}

		/**
	    	@brief Destructor

    		Class destructor. Deallocates the simulating array from heap.

	    	@post _vect = nullptr
	    	@post _size = 0
  		*/
		~matrix_3d() {
			
			delete[] _vect;
			_vect = nullptr;
			_size = 0;
			
			#ifndef NDEBUG
		 	std::cout << "matrix_3d::~matrix_3d()"<< std::endl;
			#endif
		}
		
		/**
	    	@brief Copy Constructor

    		Class copy constructor. Creates a new matrix_3d from the given one as a parameter.
    		The two matrix_3d are independent.

	    	@param other matrix_3d to copy
	    
	    	@post _vect != nullptr
	    	@post _size = other._size
  		*/
		matrix_3d(const matrix_3d& other) : _vect(nullptr), _size(0) {
			
			_vect = new matrix_2d<T>[other._size];
			_size = other._size;
			
			try {
				for(size_type i = 0; i < _size; ++i)
					_vect[i] = other._vect[i];
			}
			catch(...) {
				delete[] _vect;
				_size = 0;
				throw;
			}
	
			#ifndef NDEBUG
			std::cout << "matrix_3d::matrix_3d(const matrix_3d& other)" << std::endl;
			#endif
		}
		
		/**
		    @brief Assignment operator
	
	    	Refefinition of assignment operator. Copies the contents of another matrix_2d object.
	
	    	@param other source matrix_3d to copy
			
			@post _matrix != nullptr
		    @post _size = other._size

		    @return current object reference
	  	*/
		matrix_3d& operator=(const matrix_3d& other) {
			
			if(this != &other) {
				matrix_3d tmp(other);
				this->swap(tmp);
			}
			
			#ifndef NDEBUG
		  	std::cout << "matrix_3d::operator=(const matrix_3d& other)" << std::endl;
		 	#endif

			return *this;
		}

		/**
	    	@brief z-th plan getter

			Returns a read-only reference
			to the z-th plane of the three-dimensional matrix.
			
			@param z plan to read
			
			@pre z >= 0
		    @pre z < _size

		    @return read-only reference to the z-th plan
	  	*/
		const matrix_2d<T>& operator[](size_type i) const {
			assert(i >= 0);
			assert(i < _size);
			
			return _vect[i];
		}

		/**
	    	@brief [z, y, x] cell getter/setter

		    Redefinition of operator(). Allows to read or write the cell in
	    	position [z, y, x]. 
			
			@param z plan of the cell
		    @param y row of the cell
	    	@param x column of the cell
			
			@pre y >= 0
		    @pre y < _vect[z].rows()
		    @pre x >= 0
		    @pre x < _vect[z].columns()
			@pre z >= 0
		    @pre z < _size

		    @return reference to [z, y, x] cell
	  	*/
		T& operator()(size_type z, size_type y, size_type x) {

			assert(z >= 0);
			assert(z < _size);

			return _vect[z](y, x);
		}

		/**
	    	@brief [z, y, x] cell getter

		    Redefinition of operator(). Allows to read the cell in
	    	position [z, y, x]. 
			
			@param z plan of the cell
		    @param y row of the cell
	    	@param x column of the cell
			
			@pre y >= 0
		    @pre y < _vect[z].rows()
		    @pre x >= 0
		    @pre x < _vect[z].columns()
			@pre z >= 0
		    @pre z < _size

		    @return read-only reference to [z, y, x] cell
	  	*/
		const T& operator()(size_type z, size_type y, size_type x) const {

			assert(z >= 0);
			assert(z < _size);

			return _vect[z](y, x);
		}

		/**
	    	@brief Class swap method
		
			Method to swap the contents of two matrix_3d.
	
	    	@param other the matrix_3d to exchange content with
	  	*/
		void swap(matrix_3d& other) {
			std::swap(this->_vect, other._vect);
			std::swap(this->_size, other._size);
		}

		/**
    		@brief Rows getter
			
			Method that returns the number of rows of the matrix.

	    	@return number of rows
	  	*/
		inline size_type rows() const {
			return this->_size == 0 ? 0 : this->_vect[0].rows();
		}

		/**
    		@brief Columns getter
			
			Method that returns the number of columns of the matrix.

	    	@return number of columns
	  	*/
		inline size_type columns() const {
			return this->_size == 0 ? 0 : this->_vect[0].columns();
		}

		/**
    		@brief Plans getter
			
			Method that returns the number of plans of the matrix.

	    	@return number of plans
	  	*/
		inline size_type plans() const {
			return this->_size;
		}

		/**
    		@brief Total dimension getter
			
			Method that returns the matrix total dimension.

	    	@return matrix dimension
	  	*/		
	  	inline size_type size() const {
			return this->_size == 0 ? 0 : this->_size * _vect[0].size(); 
		}

		/**
		    @brief Comparison function
		
		    Returns true if the two matrix_3d are equal, false otherwise.
	    	Two matrix_3d are considered equal if they have the same shape and
			the same element for each cell. The comparison between elements is
			performed by a functor passed as the second parameter.
		
		    @param other the matrix_3d to compare with the current instance
			
			@pre E : T x T -> {0, 1}

		    @return true if the two matrix_3d are equal, false otherwise
	  	*/
		template <typename E>
		bool equals(const matrix_3d<T>& other, const E equality) const {

			if(this->_size != other._size)
				return false;
			
			for(size_type i=0; i < this->_size; ++i)
				if(!(this->_vect[i].equals(other._vect[i], equality)))
					return false;
					
			return true;
		}

		/**
		    @brief Redefinition of operator==
		
			Returns true if the two matrix_2d are equal, false otherwise.
			Two matrix_3d are considered equal if they have the same shape e
			the same element for each cell. The comparison between elements is
			performed by the operator== for any data type T.
		
		  	@param other the matrix_3d to compare with the current instance

		  	@return true if the two matrix_3d are equal, false otherwise
	  */
		bool operator==(const matrix_3d& other) const {
			if(this->_size != other._size)
				return false;
				
			for(size_type i=0; i < this->_size; ++i)
				if (!(this->_vect[i] == other._vect[i]))
					return false;
					
			return true;
		}

		/**
		    @brief Redefinition of operator!=
	
	    	Returns the negation of operator==.
	
	    	@param other the matrix_2d to compare with the current instance
	  	*/
		bool operator!=(const matrix_3d& other) const {
			return !((*this) == other);
		}
		
		/**
		    @brief 3-dimensional submatrix extraction
		
		    Returns a matrix_3d extracted from the current matrix_3d instance. 
	    	Indexes start from 0 and both lower and upper limits are included. 
	    	If the submatrix extraction fails, the exception is rethrown to the caller.
			
			@param z1 starting plan
		    @param z2 final plan
		    @param y1 starting row
		    @param y2 final row
		    @param x1 starting column
		    @param x2 final column
			
			@pre z1 >= 0
		    @pre z1 < _size
		    @pre y1 >= 0
		    @pre y1 < vect[z1].rows()
		    @pre x1 >= 0
		    @pre x1 < vect[z1].columns()
		    @pre z2 >= 0
		    @pre z2 < _size
		    @pre y2 >= 0	   
		    @pre y2 < vect[z1].rows()
		    @pre x2 >= 0
		    @pre x2 < vect[z1].columns()
		    @pre y1 <= y2
		    @pre x1 <= x2
		    @pre z1 <= z2

		   	@return pointer to submatrix [z1:z2, y1:y2, x1:x2]
	  	*/
		matrix_3d* slice(size_type z1, size_type z2,
					size_type y1, size_type y2,
					size_type x1, size_type x2) const {
							
			assert(z1 >= 0 && z1 < this->_size);
			assert(z2 >= 0 && z2 < this->_size);
			assert(z1 <= z2);

			matrix_3d<T>* submatrix = new matrix_3d<T>(z2 - z1 + 1,
												 y2 - y1 + 1,
												 x2 - x1 + 1);

			matrix_2d<T>* tmp = nullptr;

			for(size_type i = 0; i < submatrix->_size; ++i) {
				tmp = this->_vect[z1 + i].slice(y1, y2, x1, x2); 
				submatrix->_vect[i].swap(*tmp);
				delete tmp;
				tmp = nullptr;
			}

			return submatrix;
		}

		/**
			@brief Fill method

			Method that fills the current matrix_3d with the values obtained from two 
			generics iterators. The values previously contained in the array are overwritten.
			If the iterator reaches the end before completely filling the matrix_3d,
			the remaining elements remain intact. If at any point an excpetion is thrown, changes
			are discarded and the exception is rethrown to the caller.

			@param start start sequence iterator
			@param end end sequence iterator
		*/
		template <typename I>
		void fill(I start, I end) {
			
			size_type i = 0;
			
			while(i < this->_size && start != end) {
				_vect[i].fill(start, end, 0);	
				++i;
			} 		
		}

		/**
			@brief Print function

			Function that prints a matrix_3d on an ostream passed as a parameter.

			@param os output stream
			@param matrix matrix_3d to print

			@return ostream reference
		*/
		friend std::ostream& operator<<(std::ostream& os, const matrix_3d<T>& matrix) {

			for(size_type i = 0; i < matrix._size; ++i) {
				std::cout << matrix._vect[i] << std::endl; 
			}

			return os;
		}
		

		class const_iterator;
		
		/**
			@brief Class to represent a bidirectional iterator

	  		Class for representing a bidirectional iterator for the matrix_3d class.
			The class relies on the iterators of the matrix_2d class, used as main data structure
			for the matrix_3d class. 
		*/ 
	 	class iterator {

	 		private:

	 			matrix_2d<T>* ptr;
	    		matrix_3d<T>::size_type z;
	    		matrix_3d<T>::size_type size;
	    		typename matrix_2d<T>::iterator sub_iter;

	    		friend class matrix_3d<T>; 

	    		/**
			    	@brief Private initialization constructor used by the matrix_3d class
			    */ 
	    		iterator(matrix_2d<T>* ptr, matrix_3d<T>::size_type z, 
	    				 matrix_3d<T>::size_type size, 
	    				 typename matrix_2d<T>::iterator sub_iter) : ptr(nullptr), sub_iter(nullptr), z(0), size(0) {
	    			
	    			this->ptr = ptr; 
	    			this->z = z;
	    			this->size = size; 
			    	this->sub_iter = sub_iter;
			    }

		  	public:

		    	typedef std::bidirectional_iterator_tag iterator_category;
		    	typedef T                        value_type;
		    	typedef ptrdiff_t                difference_type;
		    	typedef T*                       pointer;
		    	typedef T&                       reference;

	  
			    iterator() : ptr(nullptr), size(0), sub_iter(nullptr), z(0) {}
			    
			    iterator(const iterator& other) : ptr(nullptr), sub_iter(nullptr), size(0), z(0) {
			    	this->ptr = other.ptr;
			    	this->sub_iter = other.sub_iter;
			    	this->z = other.z;
			    	this->size = other.size;
			    }

			    iterator& operator=(const iterator& other) {
			    	
			    	if(this != &other) {
			    		iterator tmp(other);
			    		std::swap(this->ptr, tmp.ptr);
			    		std::swap(this->sub_iter, tmp.sub_iter);
			    		std::swap(this->z, tmp.z);
			    		std::swap(this->size, tmp.size);

			    	}
			      
			    	return *this;
			    }

			    ~iterator() {}

			    reference operator*() const {
		      		return *sub_iter;
			    }

			    pointer operator->() const {
			     	return sub_iter;
			    }
		 
			    iterator operator++(int) {
		      		iterator tmp(*this);
		      		++(*this);
		      		return tmp;
			    }

			    iterator& operator++() {
			    	if(size == 0)
			    		return *this;

			    	if(z == size - 1) {
			    		if(sub_iter != ptr[z].end())
			    			++sub_iter;
			    	}
			    	else 
			    		if(sub_iter + 1 == ptr[z].end())
				    		sub_iter = ptr[++z].begin();
			    		else {
			    			++sub_iter;
			    		}
			    		
			      	return *this;
			    }

			    iterator operator--(int) {
			      	iterator tmp(*this);
			      	--(*this);
			    	return tmp;
			    }

			    iterator& operator--() {

			    	if(size == 0)
			    		return *this;

			      	if(sub_iter == ptr[z].begin()) {
			    		if(z > 0) {
			    			sub_iter = ptr[--z].end();
			    			--sub_iter;
			    		}
			    	}
		    		else
		    			--sub_iter;

			      	return *this;
			    }
			  
			    bool operator==(const iterator &other) const {
			    	return ptr == other.ptr &&
			    		   z == other.z &&
			    		   size == other.size && 
			      		   sub_iter == other.sub_iter;
			    }

			    bool operator!=(const iterator &other) const {
			    	return !((*this) == other);
			    }
	 
			    friend class const_iterator;

			    bool operator==(const const_iterator &other) const {
			    	return ptr == other.ptr &&
			    		   z == other.z &&
			    		   size == other.size && 
			      		   sub_iter == other.sub_iter;
			    }

			    bool operator!=(const const_iterator &other) const {
			    	return !((*this) == other);
			    }
		   
		};
		 
		/**
			@brief Sequence start iterator

			Returns the start-sequence read/write iterator of a matrix_3d.
		*/
		iterator begin() {
			if(this->_size == 0)
				return iterator();

			return iterator(_vect, 0, _size, _vect[0].begin());
		}
		
		/**
			@brief Sequence end iterator

			Returns the end-sequence read/write iterator of a matrix_3d.
		*/ 
		iterator end() {
			if(this->_size == 0)
				return iterator();

			return iterator(_vect, _size - 1, _size, _vect[_size - 1].end());
		}

		/**
			@brief Class to represent a read-only bidirectional iterator

	  		Class for representing a read-only bidirectional iterator for the matrix_3d class.
			The class relies on the read-only iterators of the matrix_2d class, used as main data structure
			for the matrix_3d class. 
		*/  
	  	class const_iterator {
		
		  	private:
				
				const matrix_2d<T>* ptr;
	    		matrix_3d<T>::size_type z;
	    		matrix_3d<T>::size_type size;
	    		typename matrix_2d<T>::const_iterator sub_iter;

	    		friend class matrix_3d<T>; 

			    /**
			    	@brief Private initialization constructor used by the matrix_3d class
			    */ 
			    const_iterator(const matrix_2d<T>* ptr, matrix_3d<T>::size_type z, 
		    				 matrix_3d<T>::size_type size, 
		    				 typename matrix_2d<T>::const_iterator sub_iter) : ptr(nullptr), sub_iter(nullptr), z(0), size(0) {
		    			
	    			this->ptr = ptr; 
	    			this->z = z;
	    			this->size = size; 
			    	this->sub_iter = sub_iter;
			    }

			public:

				typedef std::bidirectional_iterator_tag iterator_category;
				typedef T                        value_type;
				typedef ptrdiff_t                difference_type;
				typedef const T*                 pointer;
				typedef const T&                 reference;

			  	const_iterator() : ptr(nullptr), size(0), sub_iter(nullptr), z(0) {}
			    
			    const_iterator(const const_iterator& other) : ptr(nullptr), sub_iter(nullptr), size(0), z(0) {
			    	this->ptr = other.ptr;
			    	this->sub_iter = other.sub_iter;
			    	this->z = other.z;
			    	this->size = other.size;
			    }

			    const_iterator& operator=(const const_iterator& other) {
			    	
			    	if(this != &other) {
			    		const_iterator tmp(other);
			    		std::swap(this->ptr, tmp.ptr);
			    		std::swap(this->sub_iter, tmp.sub_iter);
			    		std::swap(this->z, tmp.z);
			    		std::swap(this->size, tmp.size);

			    	}
			      
			    	return *this;
			    }

			    ~const_iterator() {}

			    reference operator*() const {
		      		return *sub_iter;
			    }

			    pointer operator->() const {
			    	return sub_iter;
			    }
			    
			    const_iterator operator++(int) {
			    	const_iterator tmp(*this);
			    	++(*this);
			    	return tmp;
			    }

			    const_iterator& operator++() {

			    	if(size == 0)
			    		return *this;

			    	if(z == size - 1) {
			    		if(sub_iter != ptr[z].end())
			    			++sub_iter;
			    	}
			    	else 
			    		if(sub_iter + 1 == ptr[z].end())
				    		sub_iter = ptr[++z].begin();
			    		else
			    			++sub_iter;
			    		
			      	return *this;
			    }

			    const_iterator operator--(int) {
			    	const_iterator tmp(*this);
			    	--(*this);
			    	return tmp;
			    }

			    const_iterator& operator--() {

			    	if(size == 0)
			    		return *this;

			      	if(sub_iter == ptr[z].begin()) {
			    		if(z > 0) {
			    			sub_iter = ptr[--z].end();
			    			--sub_iter;
			    		}
			    	}
		    		else
		    			--sub_iter;

			      	return *this;
			    }
			  
			    bool operator==(const const_iterator &other) const {
			    	return ptr == other.ptr &&
				    		z == other.z &&
				    		size == other.size && 
				      		sub_iter == other.sub_iter;
			    }

			    bool operator!=(const const_iterator &other) const {
			    	return !((*this) == other);
			    }
			    
			    friend class iterator;

			    bool operator==(const iterator &other) const {
			    	return ptr == other.ptr &&
				    		z == other.z &&
				    		size == other.size && 
				      		sub_iter == other.sub_iter;
			    }

			    bool operator!=(const iterator &other) const {
			    	return !((*this) == other);
			    }

			    /**
					@brief Iterator to const_iterator conversion constructor
			    */
			    const_iterator(const iterator &other) {
			    	this->ptr = other.ptr;
			    	this->sub_iter = other.sub_iter;
			    	this->z = other.z;
			    	this->size = other.size;
			    }

			    /**
					@brief Assignment of an iterator to a const_iterator
			    */
			    const_iterator &operator=(const iterator &other) {
			    	this->ptr = other.ptr;
			    	this->sub_iter = other.sub_iter;
			    	this->z = other.z;
			    	this->size = other.size;
			      
			    	return *this;
			    }

		};
			  
		/**
			@brief Read-only sequence start iterator

			Returns the start-sequence read-only iterator of a matrix_3d.
		*/	  
		const_iterator begin() const {
			if(this->_size == 0)
				return const_iterator();

		    return const_iterator(_vect, 0, _size, _vect[0].begin());
		}
		  
		/**
			@brief Read-only sequence end iterator

			Returns the end-sequence read-only iterator of a matrix_3d.
		*/ 
		const_iterator end() const {
			if(this->_size == 0)
				return const_iterator();

			return const_iterator(_vect, _size - 1, _size, _vect[_size - 1].end());
		}

		/**
			@brief Transformation function

			Returns a new matrix_3d from the source matrix_3d given as parameter, 
			obtained by applying the functor func to each element of the source array.
			
			@pre func : W -> Q

			@param source source matrix_3d
			@param func functor to applicate

			@return pointer to the transformed matrix_3d
		*/

		template <typename Q, typename W, typename F>
		friend matrix_3d<Q>* transform(const matrix_3d<W>& source, F func);
};

template <typename Q, typename W, typename F>
matrix_3d<Q>* transform(const matrix_3d<W>& source, const F func) {
				
	matrix_3d<Q>* transformed = new matrix_3d<Q>(source.plans(), 
												 source.rows(),
												 source.columns());


	matrix_2d<Q>* tmp = nullptr; 

	for(typename matrix_3d<W>::size_type z=0; z < source.plans(); ++z) {
		tmp = transform<Q>(source[z], func);
		transformed->_vect[z].swap(*tmp);
		delete tmp;
		tmp = nullptr;
	}
			
	return transformed;
}



#endif

