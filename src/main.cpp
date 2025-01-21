#include "matrix.hpp"
#include "matrix_view.hpp"
#include <mpfr.h>

void teste()
{
    mpfr_t value1d;
    mpfr_t value1u;
    mpfr_t result1;

    mpfr_t x;

    int p = 4096;

    mpfr_init2(value1d, p);
    mpfr_init2(value1u, p);
    mpfr_init2(x, p);
    mpfr_init2(result1, p);

    mpfr_const_pi(x, MPFR_RNDD);

    mpfr_pow_si(value1d, x, 25, MPFR_RNDD);
    mpfr_pow_si(value1u, x, 25, MPFR_RNDU);

    mpfr_sub(result1, value1u, value1d, MPFR_RNDN);

    mpfr_printf("result1: %.10Re\n", result1);


    mpfr_clear(x);
    mpfr_clear(value1d);
    mpfr_clear(value1u);
    mpfr_clear(result1);
}

int main()
{
    // flib::matrix<512> mat2;

    teste();

    return 0;
}