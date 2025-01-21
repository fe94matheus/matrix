# FLIB - High-Precision Matrix Library

FLIB is a C++ template library that provides high-precision matrix operations using MPFR (Multiple Precision Floating-Point Reliable Library). It offers both full matrix operations and efficient matrix views for working with submatrices.

## Features

- Arbitrary-precision floating-point arithmetic using MPFR
- Template-based precision control via bit specification
- Basic matrix operations (addition, subtraction, multiplication)
- Matrix transposition
- Efficient matrix views for working with submatrices
- Random matrix initialization
- Zero matrix initialization
- Pretty-printing support

## Dependencies

- MPFR Library
- GMP (GNU Multiple Precision Arithmetic Library)
- C++11 or later

## Installation

1. Install the required dependencies:
   ```bash
   # Ubuntu/Debian
   sudo apt-get install libmpfr-dev libgmp-dev

   # macOS
   brew install mpfr gmp
   ```

2. Include the header files in your project:
   ```cpp
   #include "matrix.hpp"
   ```

## Usage

### Creating a Matrix

```cpp
#include "matrix.hpp"

// Create a matrix with 256-bit precision
flib::matrix<256> mat(3, 3);  // 3x3 matrix

// Initialize with random values
mat.initialize_random();

// Or initialize with zeros
mat.initialize_zeros();
```

### Basic Operations

```cpp
flib::matrix<256> A(2, 3);
flib::matrix<256> B(3, 2);
flib::matrix<256> C(2, 2);

// Matrix multiplication
C = A * B;

// Matrix addition
C = A + B;  // (when A and B have same dimensions)

// Matrix subtraction
C = A - B;  // (when A and B have same dimensions)

// Matrix transposition
auto AT = A.transpose();
```

### Using Matrix Views

Matrix views provide efficient access to submatrices without copying data:

```cpp
flib::matrix<256> large_matrix(10, 10);
large_matrix.initialize_random();

// Create a view of a 3x3 submatrix starting at position (1,1)
flib::matrix_view<256> submatrix(large_matrix, 1, 1, 3, 3);

// Work with the submatrix
std::cout << submatrix << std::endl;
```

### Printing Matrices

```cpp
flib::matrix<256> mat(2, 2);
mat.initialize_random();

// Print the matrix
std::cout << mat << std::endl;
```

## Implementation Details

- The library uses MPFR for arbitrary-precision arithmetic operations
- Matrix elements are stored in row-major order
- Matrix views provide zero-overhead access to submatrices
- All operations use MPFR's round-to-nearest mode (MPFR_RNDN)
- Memory management is handled automatically through RAII

## Best Practices

1. Choose an appropriate precision (bits template parameter) based on your needs
2. Use matrix views when working with submatrices to avoid unnecessary copying
3. Initialize matrices before use (either with zeros or random values)
4. Be mindful of matrix dimensions when performing operations

## Limitations

- No support for matrix inversion or decomposition methods yet
- Matrix views are non-owning and require the parent matrix to outlive them
- Fixed seed for random initialization (can be modified in the source)

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for:
- Bug fixes
- New features
- Performance improvements
- Documentation updates

## Contact

Please add your contact information here if you'd like users to be able to reach out with questions or feedback.

## License

This project is licensed under the MIT License - see the LICENSE file for details.