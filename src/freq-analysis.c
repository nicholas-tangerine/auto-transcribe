#include "freq-analysis.h"

#include <fftw3.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

fftw_complex *real_to_complex(double *samples, uint64_t length) {
    fftw_complex *out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * length);
    for (uint64_t i = 0; i < length; i++) {
        out[i][0] = samples[i];
        out[i][1] = 0.0;
    }

    return out;
}

double *complex_to_real_magnitude(fftw_complex *freq, uint64_t length) {
    double *out = (double *) malloc(sizeof(double) * length);
    for (uint64_t i = 0; i < length; i++) {
        double re = freq[i][0];
        double im = freq[i][1];
        out[i] = sqrt(re*re + im*im);
    }

    return out;
}

void extract_freq_phase(double *samples, uint64_t length, uint64_t window_size,
        double *freq, double *phase) {
    fftw_complex *out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * ((window_size >> 1) + 1));

    fftw_plan plan = fftw_plan_dft_r2c_1d(window_size, samples, out, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);

    double *new_freq = complex_to_real_magnitude(out, window_size);
    memcpy(freq, new_freq, sizeof(double) * ((window_size >> 1) + 1));
    free(new_freq);

    return;
}
