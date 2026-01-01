#ifndef PITCH_TRACKER_H_
#define PITCH_TRACKER_H_

#include <stdbool.h>

typedef struct {
    double **freq;      // freq[frame][f] -> amplitude
    double **note;      // note[frame][n] -> amplitude 
    bool *note_active;
} tracker;

#endif //   PITCH_TRACKER_H_
