#ifndef PITCH_TRACKER_H_
#define PITCH_TRACKER_H_

#include <stdbool.h>
#include <stdint.h>

/**
 * This struct keeps track of frequency domain graph over time. Treated as a
 * circular buffer, with a LRU replacement policy
 */
typedef struct {
    double **freq;          //  freq[frame][f] -> amplitude
    double **note;          //  note[frame][n] -> amplitude 
    bool *note_active;      //  note_active[frame][n] -> on/off
    uint64_t frame_count;   //  number of frames to keep histories of; treated as circular buffer
    uint64_t curr;          //  index of oldest frame
} pitch_tracker_t;

/**
 * Allocates a clean pitch_tracker_t struct
 *
 * @param frame_count       the number of frames to keep in tracker history
 * @param freq_len          the number of frequency bins
 * @param freq_min          the frequency of the 0th frequency bin
 * @param freq_max          the frequency of the last frequency bin
 */
pitch_tracker_t *pitch_tracker_init(uint64_t frame_count, uint64_t freq_len,
        uint32_t freq_min, uint32_t freq_max);

/**
 * Add a frequency representation array to the pitch tracker. 
 *
 * @param pitch_tracker     pitch_tracker_t struct containing previous history
 * @param freq              frequency representation of waveform
 */
void add_freq(pitch_tracker_t *pitch_tracker, double *freq);

#endif //   PITCH_TRACKER_H_
