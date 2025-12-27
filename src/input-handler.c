#include "input-handler.h"

float *sample_file(char *file_name) {
    //  DECODER INIT
    ma_decoder decoder;
    ma_decoder_config decoder_config = ma_decoder_config_init(ma_format_32, 1, 44100); 
    ma_result result = ma_decoder_init_file(file_name, &decoder_config, &decoder);
    if (result != MA_SUCCESS) {
        fprintf(stderr, "DEBUG: miniaudio couldn't init file %s\n", file_name);
        return NULL;
    }



    ma_decoder_init_file(&decoder);
}
