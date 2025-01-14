#include "solong.h"

char *get_next_line(FILE *file) {
    if (!file) {
        return NULL;
    }

    size_t buffer_size = 128;  // Initial buffer size
    size_t position = 0;
    char *buffer = malloc(buffer_size);
    if (!buffer) {
        return NULL;  // Memory allocation failed
    }

    int c;
    while ((c = fgetc(file)) != EOF && c != '\n') {
        // Check if buffer needs to be resized
        if (position >= buffer_size - 1) {
            buffer_size *= 2;
            char *new_buffer = realloc(buffer, buffer_size);
            if (!new_buffer) {
                free(buffer);
                return NULL;  // Memory allocation failed
            }
            buffer = new_buffer;
        }
        buffer[position++] = (char)c;
    }

    // Check for end of file without any data read
    if (position == 0 && c == EOF) {
        free(buffer);
        return NULL;
    }

    buffer[position] = '\0';  // Null-terminate the string
    return buffer;
}

void free_string(char **str, int str_count)
{
    int i;

    if (!str)
        return ;
    i = -1;
    while (++i < str_count)
        free(str[i]);
    free(str);
}
