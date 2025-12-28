#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <stdint.h>

typedef struct {
    float *samples_float;
    double *samples_double;
    uint64_t frame_count;
    uint32_t channel_count;
    uint32_t sample_rate;
} audio_buffer_t;

audio_buffer_t *audio_buffer_init();

int sample_file(char *file_name, audio_buffer_t *audio_buffer);

int convert_to_mono(audio_buffer_t *audio_buffer);

#endif // INPUT_HANDLER_H
