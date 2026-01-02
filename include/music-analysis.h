#ifndef MUSIC_ANALYSIS_H_
#define MUSIC_ANALYSIS_H_

#include <stdint.h>

/**
 * Takes a frequency and converts it to a note. The note is given as the
 * distance from A0. Assumes 88 key layout, and A = 440 Hz
 *
 * @param freq          the frequency to translate into a musical note
 * @param threshold     threshold for a frequency to be an actual note. must be
 *                      in range [0.0, 1.0)
 * @param error         changes the value of error to be how far off the freq
 *                      is from a note
 *
 * @return the distance from A0 of the note. A0 = 0 and A#/Bb0 = 1,... etc.
 */
int freq_to_note(double freq, double threshold, double *error);

/**
 * Converts frequency domain representation to musical note domain. Returns an
 * array with the i'th index corresponding to the i'th note from A0. The value
 * stored at the i'th index is its corresponding amplitude. Assumes frequency
 * representation is linearly scaled. To be freed by user.
 *
 * @param freq          the frequency array
 * @param freq_min      the lowest frequency in freq
 * @param freq_max      the highest frequency in freq
 * @param freq_len      the number of elements in the freq array
 * @param threshold     how close a frequency must be to a note to count from
 *                      [0.0, 1.0) (low->high tolerance)
 * @param num_notes     the length of the output array; how many notes (from
 *                      and including A0)
 *
 * @return the corresponding musical representation of the frequency array
 */

double *freq_to_note_arr(double *freq, double freq_min, double freq_max,
        uint32_t freq_len, double threshold, uint32_t num_notes);

#endif //   MUSIC_ANALYSIS_H_
