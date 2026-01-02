#include <stdio.h>
#include <stdlib.h>

#include "input-handler.h"
#include "freq-analysis.h"
#include "music-analysis.h"

const uint64_t FFTW_WINDOW = 44100;
const char *NOTE_NAMES[] = {"A", "A#/Bb", "B", "C", "C#/Db", "D", "D#/Eb", "E", "F", "F#/Gb", "G", "G#/Ab"};

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "USAGE: ./main <music_file.mp3>\n");
        return 1;
    }

    /* Initialize audio buffer struct and fill it with wave amplitude data */
    audio_buffer_t *audio_buffer = audio_buffer_init();
    sample_file(argv[1], audio_buffer);
    convert_to_mono(audio_buffer);

    /* Extract and denoise frequencies from the first second of the mp3 */
    uint64_t nbins = (FFTW_WINDOW >> 1) + 1;
    double *freq = malloc(sizeof(double) * nbins);

    extract_freq_window(audio_buffer->samples_double, audio_buffer->frame_count,
            FFTW_WINDOW, freq);
    denoise_freq(freq, 5, nbins);
    remove_harmonics(freq, 0, (double) (audio_buffer->sample_rate), nbins, 0.5, 0.0);
    double *notes = freq_to_note_arr(freq, 0, (double) nbins, nbins, 0.3, 88);

    /* Print frequency data in a human readable format */
    printf("FRAME COUNT: %ld\n", audio_buffer->frame_count);
    printf("CHANNEL COUNT: %d\n", audio_buffer->channel_count);
    printf("SAMPLE RATE: %d\n", audio_buffer->sample_rate);

    for (int i = 0; i < 88; i++) {
        if (notes[i] == 0.0) continue;
        printf("Note: %8s \t Note num: %3d \t Amplitude: %f\n", NOTE_NAMES[i % 12], i,  notes[i]);
    }
    /*
       for (uint64_t i = 0; i < nbins; i++) {
    //if (freq[i] == 0.0) continue;
    int note_val = freq_to_note(i, 0.3, NULL);
    if (note_val < 0) continue;
    //printf("%f %f\n", (double) i, freq[i]);
    //printf("Hz: %f \t Amplitude: %f \t Note: %s\n", (double) i, freq[i], NOTE_NAMES[note_val % 12]);
    //printf("Hz: %f \t Amplitude: %f \t Note: %s\n", (double) i, freq[i], note_val < 0 ? "unknown" : NOTE_NAMES[note_val % 12]);
    }
    */

    return 0;
}
