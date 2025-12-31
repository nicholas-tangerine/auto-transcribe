#ifndef MUSIC_ANALYSIS_H_
#define MUSIC_ANALYSIS_H_

/**
 * Takes a frequency and converts it to a note. The note is given as the
 * distance from A0. Assumes 88 key layout, and A = 440 Hz
 *
 * @param freq      the frequency to translate into a musical note
 *
 * @return the distance from A0 of the note. A0 = 0 and Bb0 = 1, etc.
 */
int freq_to_note(double freq);

#endif //   MUSIC_ANALYSIS_H_
