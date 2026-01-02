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
 * @return a new array of type fftw_complex to use for fftw3
 */
fftw_complex *real_to_complex(double *samples, uint64_t length);

/**
 * Returns an array of the magnitudes of each frequency wave. To be freed by
 * user
 *
 * @param freq          array of frequencies of type fftw_complex
 * @param length        length of the freq array
 *
 * @return an array with each element storing the magnitude of its
 * corresponding freq
 */
double *complex_to_real_magnitude(fftw_complex *freq, uint64_t length);

/**
 * Filters out all noise. Any spectral leakage, etc. will be set to 0 and only
 * the "real" notes will still have any amplitude. "Real" note amplitude is
 * unchanged. This works by zeroing out everything EXCEPT the highest amplitude
 * frequency in the window.
 *
 * @param freq          array of frequencies and their associated amplitudes
 * @param window_size   size of window for finding local maximum of amplitudes
 * @param length        the length of the frequency array
 */
void denoise_freq(double *freq, uint64_t window_size, uint64_t length);

/**
 * Removes or downweights harmonics.
 *
 * @param freq          array of frequencies and their associated amplitudes
 * @param freq_min      the lowest frequency in the freq array
 * @param freq_max      the maximum frequency in the freq array
 * @param freq_len      the length of the frequency array
 * @param real_weight   if the harmonic is at least real_weight *
 *                      analysis_amplitude, it is a real note
 *                      harmonic (default 0.0)
 * @param fake_weight   how loud the harmonic should be (default 0.0 means
 *                      remove altogether)
 */
void remove_harmonics(double *freq, double freq_min, double freq_max, uint64_t
        freq_len, double real_weight, double fake_weight);

/**
 * Extracts the frequencies and phases of the signal. Requires that freq and
 * phase are of the proper length, not checked in this function
 *
 * @param samples       array of samples
 * @param length        number of elements in samples array
 * @param window_size   size of window upon which FFT is performed, equivalent
 *                      to N in fftw docs
 * @param freq          pointer to output array, to be updated with freq
 */
void extract_freq_window(double *samples, uint64_t length, uint64_t window_size,
        double *freq);

#endif //   FREQ_ANALYSIS_H_
