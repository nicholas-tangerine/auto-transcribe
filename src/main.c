#include <stdio.h>
#include <stdlib.h>

#include "input-handler.h"
#include "freq-analysis.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "USAGE: ./main <music_file.mp3>\n");
        return 1;
    }

    /* Initialize audio buffer struct and fill it with wave amplitude data */
    audio_buffer_t *audio_buffer = audio_buffer_init();
    sample_file(argv[1], audio_buffer);
    convert_to_mono(audio_buffer);

    printf("FRAME COUNT: %ld\nCHANNEL COUNT: %d\nSAMPLE RATE: %d\n", audio_buffer->frame_count, audio_buffer->channel_count, audio_buffer->sample_rate);
    
    int nbins = (audio_buffer->sample_rate >> 1) + 1;
    double *freq = malloc(sizeof(double) * nbins);
    double *phase = malloc(sizeof(double) * nbins);
    extract_freq_phase(audio_buffer->samples_double, audio_buffer->frame_count,
            audio_buffer->sample_rate, freq, phase);

    for (uint64_t i = 0; i < nbins; i++) {
        double analysis_freq = (double) i;
        printf("Hz: %08.4f \t Amplitude: %.4f\n", (double) i, freq[i]);
    }

    return 0;
}
