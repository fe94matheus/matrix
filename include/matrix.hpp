#pragma once
#include <mpfr.h>
#include <gmp.h>
#include <iostream>
#include <cstdint>
#include <iomanip>
#include <cassert>

namespace flib
{
    template <int bits>
    class matrix
    {

    private:
        mpfr_t *data_;
        uint64_t rows_;
        uint64_t cols_;
        uint64_t alloc_;

    public:
        matrix() : data_(nullptr), rows_(0), cols_(0), alloc_(0) {}

        matrix(uint64_t rows, uint64_t cols) : rows_(rows), cols_(cols), alloc_((rows + 1) * (cols + 1))
        {
            data_ = new mpfr_t[alloc_];
            for (uint i = 0; i < alloc_; i++)
            {
                mpfr_init2(data_[i], bits);
            }
        }

        // Copy assignment
        matrix &operator=(const matrix<bits> &mat)
        {
            if (this != &mat)
            {
                // Release old memory
                for (uint64_t i = 0; i < alloc_; i++)
                {
                    mpfr_clear(data_[i]);
                }
                delete[] data_;

                // Allocate new memory
                rows_ = mat.rows_;
                cols_ = mat.cols_;
                alloc_ = mat.alloc_;
                data_ = new mpfr_t[alloc_];
                for (uint64_t i = 0; i < alloc_; i++)
                {
                    mpfr_init2(data_[i], bits);
                    mpfr_set(data_[i], mat.data_[i], MPFR_RNDN);
                }
            }
            return *this;
        }

        ~matrix()
        {
            if (data_)
            {
                for (uint64_t i = 0; i < alloc_; i++)
                {
                    mpfr_clear(data_[i]);
                }
                delete[] data_;
            }
        }

        uint64_t rows() const { return rows_; }
        uint64_t cols() const { return cols_; }

        mpfr_t &operator()(uint64_t row, uint64_t col)
        {
            return data_[row * cols_ + col];
        }

        const mpfr_t &operator()(uint64_t row, uint64_t col) const
        {
            return data_[row * cols_ + col];
        }

        friend matrix operator*(const matrix<bits> &m1, const matrix<bits> &m2)
        {
            assert(m1.cols_ == m2.rows_);

            matrix<bits> result(m1.rows_, m2.cols_);

            result.initialize_zeros();

            for (uint64_t i = 0; i < m1.rows_; ++i)
            {
                for (uint64_t j = 0; j < m2.cols_; ++j)
                {
                    for (uint64_t k = 0; k < m1.cols_; ++k)
                    {
                        mpfr_t temp;
                        mpfr_init2(temp, bits);
                        mpfr_mul(temp, m1(i, k), m2(k, j), MPFR_RNDN);         // Multiply elements
                        mpfr_add(result(i, j), result(i, j), temp, MPFR_RNDN); // Accumulate in result
                        mpfr_clear(temp);
                    }
                }
            }

            return result;
        }

        friend matrix operator+(const matrix<bits> &m1, const matrix<bits> &m2)
        {
            assert(m1.rows_ == m2.rows_ && m1.cols_ == m2.cols_);

            matrix<bits> result(m1.rows_, m1.cols_);

            for (uint64_t i = 0; i < m1.rows_; i++)
            {
                for (uint64_t j = 0; j < m1.cols_; j++)
                {
                    mpfr_add(result(i, j), m1(i, j), m2(i, j), MPFR_RNDN);
                }
            }

            return result;
        }

        friend matrix operator-(const matrix<bits> &m1, const matrix<bits> &m2)
        {
            assert(m1.rows_ == m2.rows_ && m1.cols_ == m2.cols_);

            matrix<bits> result(m1.rows_, m1.cols_);

            for (uint64_t i = 0; i < m1.rows_; i++)
            {
                for (uint64_t j = 0; j < m1.cols_; j++)
                {
                    mpfr_sub(result(i, j), m1(i, j), m2(i, j), MPFR_RNDN);
                }
            }

            return result;
        }

        matrix transpose() const
        {
            matrix transposed(cols_, rows_);

            for (uint64_t i = 0; i < rows_; ++i)
            {
                for (uint64_t j = 0; j < cols_; ++j)
                {
                    mpfr_set(transposed(j, i), (*this)(i, j), MPFR_RNDN);
                }
            }

            return transposed;
        }

        void initialize_random()
        {
            gmp_randstate_t rstate;
            gmp_randinit_default(rstate); // Initialize GMP random state
            mpz_t seed;
            mpz_init_set_ui(seed, 12345); // Set a fixed seed, or adjust as needed
            gmp_randseed(rstate, seed);   // Seed the random state with the given seed

            for (uint64_t i = 0; i < alloc_; i++)
            {
                mpfr_urandom(data_[i], rstate, MPFR_RNDN); // Generate random number in [0,1)
            }

            mpz_clear(seed);
            gmp_randclear(rstate); // Clear random state
        }

        void initialize_zeros()
        {
            for (uint64_t i = 0; i < rows_; ++i)
            {
                for (uint64_t j = 0; j < cols_; ++j)
                {
                    mpfr_set_d((*this)(i, j), 0.0, MPFR_RNDN);
                }
            }
        }

        friend std::ostream &operator<<(std::ostream &os, const matrix &mat)
        {
            for (uint64_t i = 0; i < mat.rows_; ++i)
            {
                for (uint64_t j = 0; j < mat.cols_; ++j)
                {
                    char buffer[128];
                    mpfr_snprintf(buffer, sizeof(buffer), "%.15Rf", mat(i, j));  
                    os << std::setw(15) << buffer << " ";                       
                }
                os << '\n';  
            }
            return os;
        }
    };

};