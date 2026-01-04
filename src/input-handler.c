#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_FLAC
#define MA_NO_WAV

#include <stdlib.h>
#include <stdio.h>

#include "miniaudio.h"
#include "input-handler.h"

audio_buffer_t *audio_buffer_init() {
    audio_buffer_t *out = malloc(1 * sizeof(audio_buffer_t));

    return out;
}

void audio_buffer_free(audio_buffer_t *buffer) {
    free(buffer->samples_float);
    free(buffer->samples_double);
    free(buffer);
}

int sample_file(char *file_name, audio_buffer_t *audio_buffer) {
    //  DECODER INIT
    ma_decoder decoder;
    ma_decoder_config decoder_config = ma_decoder_config_init(ma_format_f32, 0, 0); 

    if (ma_decoder_init_file(file_name, &decoder_config, &decoder) != MA_SUCCESS) {
        fprintf(stderr, "DEBUG: miniaudio couldn't init file %s\n", file_name);
        return 1;
    }

    //  COLLECT WAVEFORM DATA
    ma_uint64 frames;
    ma_uint32 channels;
    ma_decoder_get_length_in_pcm_frames(&decoder, &frames);
    channels = decoder.outputChannels;

    float *samples_float = malloc(frames * decoder.outputChannels * sizeof(float));
    double *samples_double = malloc(frames * decoder.outputChannels * sizeof(double));

    if (!samples_float || !samples_double) {
        ma_decoder_uninit(&decoder);
        fprintf(stderr, "DEBUG: couldn't allocate memory for samples\n");
        return 1;
    }

    ma_decoder_read_pcm_frames(&decoder, samples_float, frames, NULL);
    ma_decoder_uninit(&decoder);

    //  TRANSLATE FLOAT DATA TO DOUBLE
    for (ma_uint64 i = 0; i < frames * channels; i++) {
        samples_double[i] = (double) samples_float[i];
    }

    //  UPDATE AUDIO BUFFER
    audio_buffer->samples_float = samples_float;
    audio_buffer->samples_double = samples_double;
    audio_buffer->frame_count = frames;
    audio_buffer->channel_count = decoder.outputChannels;
    audio_buffer->sample_rate = decoder.outputSampleRate;

    return 0;
}

int convert_to_mono(audio_buffer_t *audio_buffer) {
    float *new_float = malloc(audio_buffer->frame_count * sizeof(float));
    double *new_double = malloc(audio_buffer->frame_count * sizeof(double));

    for (uint64_t i = 0; i < audio_buffer->frame_count; i++) {
        float sum_float = 0.0f;
        double sum_double = 0.0;
        for (uint32_t c = 0; c < audio_buffer->channel_count; c++) {
            sum_float += audio_buffer->samples_float[i * audio_buffer->channel_count + c];
            sum_double += audio_buffer->samples_double[i * audio_buffer->channel_count + c];
        }
        new_float[i] = sum_float / audio_buffer->channel_count;
        new_double[i] = sum_double / audio_buffer->channel_count;
    }

    free(audio_buffer->samples_float);
    free(audio_buffer->samples_double);
    audio_buffer->samples_float = new_float;
    audio_buffer->samples_double = new_double;

    audio_buffer->channel_count = 1;

    return 0;
}
