#ifndef FREQ_ANALYSIS_H_
#define FREQ_ANALYSIS_H_

#include <fftw3.h>
#include <stdint.h>

/**
 * Takes in `double` array and translates it to `fftw_complex` array
 * To be freed by user with fftw_free
 *
 * @param samples       array of samples
 * @param length        number of elements in samples array
 *
 * @return a new array of type fftw_complex to use for fftw3 input
 */
fftw_complex *generate_input(double *samples, uint64_t length);

/**
 * Extracts the frequencies and phases of the signal
 * Requires that freq and phase are of the proper length, not checked in this
 * function
 *
 * @param samples       array of samples
 * @param length        number of elements in samples array
 * @param window_size   size of window upon which FFT is performed, equivalent
 *                      to N in fftw docs
 * @param freq          pointer to output array, to be updated with freq
 * @param phase         pointer to output array, to be filled with the phase of
 *                      various frequencies
 */
void extract_freq_phase(double *samples, uint64_t length, uint64_t window_size,
        double *freq, double *phase);

#endif //   FREQ_ANALYSIS_H_
