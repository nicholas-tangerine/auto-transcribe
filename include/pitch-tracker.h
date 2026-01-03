#ifndef PITCH_TRACKER_H_
#define PITCH_TRACKER_H_

#include <stdbool.h>
#include <stdint.h>

/**
 * This struct keeps track of frequency domain graph over time. Treated as a
 * ring buffer.
 */
typedef struct {
    double **note_buffer;   //  note[frame][n] -> amplitude 
    bool *note_active;      //  note_active[n] -> on/off
    uint64_t frame_count;   //  number of frames to keep histories of; treated as circular buffer
    uint64_t curr;          //  index of oldest frame
    uint32_t num_notes;     //  number of notes in a frame
} pitch_tracker_t;

/**
 * Allocates a clean pitch_tracker_t struct
 *
 * @param frame_count       the number of frames to keep in tracker history
 * @param num_notes         the number of notes in each frame from (and
 *                          including) A0
 */
pitch_tracker_t *pitch_tracker_init(uint64_t frame_count, uint32_t num_notes);

/**
 * Add a notes representation array to the pitch tracker. 
 *
 * @param pitch_tracker     pitch_tracker_t struct containing previous history
 * @param notes             notes/musical representation of waveform
 */
void add_frame(pitch_tracker_t *pitch_tracker, double *notes);

/**
 * Takes the buffer and marks the notes that are active and not active. For a
 * note to be considered "active", it must be present in at least k frames.
 * Output is stored in the note_active array in pitch_tracker struct
 *
 * @param pitch_tracker     a struct storing all the frames
 * @param k                 the number of times a note has to be heard to be
 *                          considered "active"
 */
void extract_true_notes(pitch_tracker_t *pitch_tracker, uint32_t k);

#endif //   PITCH_TRACKER_H_
