#include "freq-analysis.h"

#include <fftw3.h>
#include <stdint.h>

fftw_complex *generate_input(double *samples, uint64_t length) {
    fftw_complex *out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * length);
    for (uint64_t i = 0; i < length; i++) {
        out[i][0] = samples[i];
        out[i][1] = 0.0;
    }

    return out;
}

void extract_freq_phase(double *samples, uint64_t length, uint64_t window_size,
        double *freq, double *phase) {
    fftw_complex *in = generate_input(samples, length);
    fftw_complex *out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * length);

    fftw_plan plan = fftw_plan_dft_1d(length, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    return;
}
