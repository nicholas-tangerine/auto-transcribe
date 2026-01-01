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

void denoise_freq(double *freq, uint64_t window_size, uint64_t length) {
    if (window_size > length) { fprintf(stderr, "DEBUG: window_size > length in denoise freq\n"); return; }

    double *new_freq = malloc(length * sizeof(double));

    new_freq[0] = 0.0;
    for (uint64_t i = window_size; i < length - window_size; i++) {
        double max_amplitude = 0.0;
        uint64_t best_freq = 0;     // frequency at which max_amplitude occurs
        for (uint64_t k = i - window_size; k < i + window_size; k++) {
            if (freq[k] < max_amplitude) {
                new_freq[k] = 0.0;
                continue;
            }
            new_freq[best_freq] = 0.0;
            max_amplitude = freq[k];
            best_freq = k;
        }
    }

    memcpy(freq, new_freq, length * sizeof(double));
    free(new_freq);
}

void extract_freq_window(double *samples, uint64_t length, uint64_t window_size,
        double *freq) {
    fftw_complex *out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * ((window_size >> 1) + 1));

    fftw_plan plan = fftw_plan_dft_r2c_1d(window_size, samples, out, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);

    double *new_freq = complex_to_real_magnitude(out, (window_size >> 1) + 1);
    memcpy(freq, new_freq, sizeof(double) * ((window_size >> 1) + 1));
    free(new_freq);
    fftw_free(out);

    return;
}
