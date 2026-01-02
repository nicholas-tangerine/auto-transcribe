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

/**
 * Allocates audio_buffer_t struct with empty fields. To be freed by user
 *
 * @return new audio_buffer_t struct
 */
audio_buffer_t *audio_buffer_init();

/**
 * Extracts the waveform data from audio file. If multiple channels, the waveforms are interleaved (i.e. to be read as left_amplitude followed by right_amplitude
 *
 * @param file_name     name of audio file to read from
 * @param audio_buffer  audio_buffer_t struct to hold the audio information
 *
 * @return 0 on success
 */
int sample_file(char *file_name, audio_buffer_t *audio_buffer);

/**
 * Converts interleaved audio channels into a mono stereo
 *
 * @param audio_buffer  audio_buffer_t struct to hold the audio information with interleaved channel data
 * 
 * @return  0 on success
 */
int convert_to_mono(audio_buffer_t *audio_buffer);

#endif //   INPUT_HANDLER_H
