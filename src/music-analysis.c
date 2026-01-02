#include "music-analysis.h"

#include <math.h>
#include <stdlib.h>

int freq_to_note(double freq, double threshold, double *error) {
    if (freq <= 0.0) return -1;
    //if (log2(freq / 440.0) == HUGE_VAL) return -1;

    if (threshold < 0.0) threshold = 0.0;
    if (threshold >= 1.0) threshold = 0.99999;

    if (error == NULL) {
        double temp;
        error = &temp;
    }

    double log_val = log2(freq / 440.0);
    *error = fabs(12 * log_val - round(12 * log_val));
    if (*error > threshold) return -1;
    int n = 48 + (int) round(12 * log_val);

    return n;
}

double *freq_to_note_arr(double *freq, double freq_min, double freq_max,
        uint32_t freq_len, double threshold, uint32_t num_notes) {
    double *out = (double *) calloc(num_notes, sizeof(double));

    for (uint32_t i = 0; i < freq_len; i++) {
        double analysis_freq = (double) freq_min + ((double) i * (double)
                (freq_max - freq_min) / (double) freq_len - 1.0);
        double analysis_amplitude = freq[i];

        double error = 0;
        int note_num = freq_to_note(analysis_freq, threshold, &error);
        if (note_num < 0) continue;
        if ((uint32_t) note_num >= num_notes) break;
        out[note_num] += fabs(1 - (double) error) * analysis_amplitude;
    }
    return out;
}
