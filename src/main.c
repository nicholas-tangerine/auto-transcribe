#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "input-handler.h"
#include "freq-analysis.h"
#include "music-analysis.h"

const char *NOTE_NAMES[] = {"A", "A#/Bb", "B", "C", "C#/Db", "D", "D#/Eb", "E", "F", "F#/Gb", "G", "G#/Ab"};

const uint64_t FFTW_WINDOW_SIZE = 44100;
const uint64_t FFTW_WINDOW_HOP = 2048;

const double NOTE_MIN_ENERGY = 1e-6;

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
    uint64_t freq_len = (FFTW_WINDOW_SIZE >> 1) + 1;
    double *freq = malloc(sizeof(double) * freq_len);

    /* Main loop */
    uint64_t samples_offset = 0;
    for (uint64_t frame = 0; frame < audio_buffer->frame_count - FFTW_WINDOW_SIZE; frame++) {
        double freq_min = 0.0;
        double freq_max = (double) (audio_buffer->sample_rate >> 1);
        extract_freq_window(
            audio_buffer->samples_double + samples_offset,  // ptr to samples
            audio_buffer->frame_count - samples_offset,     // number of items until end of samples
            FFTW_WINDOW_SIZE,                               // size of array to fft
            freq                                            // fft output
        );
        denoise_freq(
            freq,                                           // freq domain representation of window        
            5,                                              // sliding window size
            freq_len,                                          // length of freq array
            NOTE_MIN_ENERGY                                 // lowest energy needed to be note
        );
        remove_harmonics(
            freq,                                           // freq domain representation of window
            freq_min,                                       // smallest frequency captured
            freq_max,                                       // highest frequency captured
            freq_len,                                       // length of freq array
            0.2,                                            // how loud (%) to be a real note
            0.0,                                            // harmonic downweight factor
            0.2                                             // something like size of neighborhood to check
        );
        double *notes = freq_to_note_arr(freq, freq_min, freq_max, freq_len, 0.3, 88);
        for (int i = 0; i < 88; i++) {
            if (notes[i] == 0.0) continue;
            double curr_freq = 440.0 * pow(2, (double) (i - 48) / 12);
            printf("Note: %8s \t Note num: %3d \t Freq: %5.5f \t Amplitude: %f\n", NOTE_NAMES[i % 12], i, curr_freq, notes[i]);
        }
        free(notes);

        samples_offset += FFTW_WINDOW_HOP;
        break;
    }

    free(audio_buffer);

    return 0;
}
