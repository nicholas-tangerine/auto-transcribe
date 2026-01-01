#include "music-analysis.h"

#include <math.h>

int freq_to_note(double freq) {
    if (log2(freq / 440.0) == HUGE_VAL) return -1;

    double log_val = log2(freq / 440.0);
    int n = 48 + round(12 * log_val);

    return n;
}
