#include "pitch-tracker.h"

#include <stdlib.h>

pitch_tracker_t *pitch_tracker_init(uint64_t frame_count, uint32_t num_notes) {
    pitch_tracker_t *out = (pitch_tracker_t *) malloc(sizeof(pitch_tracker_t));

    out->note_buffer = malloc(sizeof(double *) * frame_count);
    out->note_active = malloc(sizeof(bool) * num_notes);
    out->frame_count = frame_count;
    out->curr = 0;
    out->num_notes = num_notes;

    return out;
}

void add_frame(pitch_tracker_t *pitch_tracker, double *notes) {
    pitch_tracker->note_buffer[pitch_tracker->curr] = notes;
    pitch_tracker->curr = (pitch_tracker->curr + 1) % pitch_tracker->frame_count;
}

void extract_true_notes(pitch_tracker_t *pitch_tracker, uint32_t k) {
    double **buffer = pitch_tracker->note_buffer;
    uint32_t num_notes = pitch_tracker->num_notes;

    //  MARK: probably lots of cache misses here
    for (uint32_t n = 0; n < num_notes; n++) {
        uint32_t counter = 0;
        for (uint64_t i = 0; i < pitch_tracker->frame_count; i++) {
            uint64_t curr_index = (pitch_tracker->curr + i) % pitch_tracker->frame_count;
            double *notes_arr = buffer[curr_index];

            if (notes_arr[n] > 0.0) counter++;
        } // frame in frames

        pitch_tracker->note_active[n] = counter >= k ? true : false;
    } // note in notes
    return;
}
