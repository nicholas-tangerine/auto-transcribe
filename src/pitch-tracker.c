#include "pitch-tracker.h"

pitch_tracker_t *pitch_tracker_init(uint64_t frame_count, uint64_t freq_len,
        uint32_t freq_min, uint32_t freq_max) {
    pitch_tracker_t *out = (pitch_tracker_t *) malloc(sizeof(pitch_tracker_t));

    out->freq = malloc(sizeof(double *) * freq_len);
    out->note = malloc(/* NUMBER OF NOTES TO KEEP TRACK OF */);
    out->note_active = malloc(sizeof(bool) * freq_len);
    out->frame_count = frame_count;
    out->curr = 0;

    return out;
}

void add_frame(pitch_tracker_t *pitch_tracker, double *freq) {
    pitch_tracker->freq[pitch_tracker->curr] = freq;
    pitch_tracker->curr = (pitch_tracker->curr + 1) % pitch_tracker->frame_count;
}
