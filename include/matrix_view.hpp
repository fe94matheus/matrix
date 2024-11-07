#include <cstdint>
#include "matrix.hpp"


namespace flib
{
    template<int bits>
    class matrix_view
    {
    private:
        matrix<bits> &parent_;     
        uint64_t start_row_;   
        uint64_t start_col_;   
        uint64_t rows_, cols_;  

    public:
        matrix_view(matrix<bits> &parent, uint64_t start_row, uint64_t start_col, uint64_t rows, uint64_t cols)
            : parent_(parent), start_row_(start_row), start_col_(start_col), rows_(rows), cols_(cols)
        {
            assert(start_row + rows <= parent.rows() && start_col + cols <= parent.cols());
        }

        mpfr_t &operator()(uint64_t i, uint64_t j)
        {
            return parent_(start_row_ + i, start_col_ + j);
        }

        const mpfr_t &operator()(uint64_t i, uint64_t j) const
        {
            return parent_(start_row_ + i, start_col_ + j);
        }

        uint64_t rows() const { return rows_; }
        uint64_t cols() const { return cols_; }

        friend std::ostream &operator<<(std::ostream &os, const matrix_view &mat)
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

} // namespace flib
