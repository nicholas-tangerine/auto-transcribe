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
    memcpy(new_freq, freq, length * sizeof(double));

    double window_avg = 0.0;
    uint64_t l = 0, r = window_size, m = window_size >> 1;

    //  initialize window avg, up to but not including r
    for (uint64_t i = l; i < r; i++){ window_avg += freq[i] / (double) window_size; }

    //  account for the left border, from 0...(window_size/2)
    for (uint64_t i = l; i < r; i++) {
        if (freq[i] < (window_avg + freq[r])) new_freq[i] = 0.0;
    }

    while (r < length) {
        window_avg += freq[r] / (double) window_size;
        if (freq[m] < window_avg) new_freq[m] = 0.0;

        window_avg -= freq[l] / (double) window_size;
        l++; m++; r++;  // increment all pointers by 1
    }
    //  account for the right border, from (length-window_size)/2...length-1
    r--; l--;
    for (uint64_t i = l; i < r; i++) {
        if (freq[i] < (window_avg + freq[l])) new_freq[i] = 0.0;
    }

    memcpy(freq, new_freq, length * sizeof(double));
    free(new_freq);
}

void extract_freq(double *samples, uint64_t length, uint64_t window_size,
        double *freq) {
    fftw_complex *out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * ((window_size >> 1) + 1));

    fftw_plan plan = fftw_plan_dft_r2c_1d(window_size, samples, out, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);

    double *new_freq = complex_to_real_magnitude(out, window_size);
    memcpy(freq, new_freq, sizeof(double) * ((window_size >> 1) + 1));
    free(new_freq);

    return;
}
