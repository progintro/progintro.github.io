#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define GET_INT32_FROM_BYTE_BUFFER(buffer, offset) (* (uint32_t*) &buffer[offset])
#define GET_INT16_FROM_BYTE_BUFFER(buffer, offset) (* (uint16_t*) &buffer[offset])
#define SET_BUFFER_INT32(buffer, offset, value) *(uint32_t*) &buffer[offset] = value

// Only 3-byte pixel color representations are supported
#define PIXEL_COLOR_DEPTH 3

// Some offsets in order to avoid the introduction of magic numbers
#define FILE_SIZE_OFFSET 2
#define RESERVED_OFFSET 6
#define PIXEL_ARRAY_OFFSET_OFFSET 10
#define IMAGE_WIDTH_OFFSET 18
#define IMAGE_HEIGHT_OFFSET 22
#define PIXEL_DEPTH_OFFSET 28
#define IMAGE_SIZE_OFFSET 34

// Exit with an error message
void exit_with_failure(const char *message)
{
    fprintf(stderr, "{error}: %s\n", message);
    exit(EXIT_FAILURE);
}

int read_next_integer_from_input(void)
{
    // Reading the integer from standard input and returning its value
    int data;
    if (fread(&data, sizeof(uint32_t), 1, stdin) != 1)
        exit_with_failure("failed to read integer from input");
    
    return data;
}

uint8_t* read_header(void)
{
    // First, check if the signature is correct
    int first_byte = getchar();
    int second_byte = getchar();

    if (first_byte != 'B' || second_byte != 'M')
        exit_with_failure("failed to locate bitmap signature");
    
    uint32_t file_size = read_next_integer_from_input();

    // The next four bytes are reserved for future use by the standardization committee
    // Just copy them as is, they won't prove any useful though
    uint32_t reserved_bytes = read_next_integer_from_input();

    // Trying to figure out how many bytes to allocate for a heap-allocated copy of the buffer
    uint32_t pixel_array_offset = read_next_integer_from_input();

    uint8_t *header = malloc(pixel_array_offset);
    if (!header)
        exit_with_failure("failed to allocate enough memory for the header");

    // Populate the header with the file's data
    header[0] = 'B';
    header[1] = 'M';
    SET_BUFFER_INT32(header, FILE_SIZE_OFFSET, file_size);
    SET_BUFFER_INT32(header, RESERVED_OFFSET, reserved_bytes);
    SET_BUFFER_INT32(header, PIXEL_ARRAY_OFFSET_OFFSET, pixel_array_offset);

    // Reading the rest of the data
    int read_offset = PIXEL_ARRAY_OFFSET_OFFSET + 4;

    if (fread(header + read_offset, sizeof(uint8_t), pixel_array_offset - read_offset, stdin) != \
        (size_t) pixel_array_offset - read_offset)
    {
        exit_with_failure("failed to read the rest of the header into memory");
    }

    return header;
}

// For this function to work, standard input should be already positioned properly
// In particular, the file cursor should be right before the pixel array of the given bitmap data
void rotate_bitmap(uint8_t *header)
{
    int file_size = GET_INT32_FROM_BYTE_BUFFER(header, FILE_SIZE_OFFSET);
    int image_width = GET_INT32_FROM_BYTE_BUFFER(header, IMAGE_WIDTH_OFFSET);
    int image_height = GET_INT32_FROM_BYTE_BUFFER(header, IMAGE_HEIGHT_OFFSET);
    int image_size = GET_INT32_FROM_BYTE_BUFFER(header, IMAGE_SIZE_OFFSET);
    int pixel_array_offset = GET_INT32_FROM_BYTE_BUFFER(header, PIXEL_ARRAY_OFFSET_OFFSET);
    int pixel_depth = GET_INT16_FROM_BYTE_BUFFER(header, PIXEL_DEPTH_OFFSET);

    // Assert that each pixel occupies the required size of bits
    if (pixel_depth != 24)
        exit_with_failure("all input images must have a pixel depth of 24 bits");
    
    // If the header is less than 54 bytes long, abort
    if (pixel_array_offset < 54)
        exit_with_failure("the header must be at least 54 bytes long");
    
    // Check if the header's file_size property is consistent with that of the actual file
    if (file_size != pixel_array_offset + image_size)
        exit_with_failure("the bitmap's file_size attribute is incorrect");
    
    int padding = image_size / image_height - image_width * PIXEL_COLOR_DEPTH;

    // Check if the padding is valid
    if (padding >= 4 || padding < 0)
        exit_with_failure("invalid image dimensions or size, the calculated padding is incorrect");
    
    // Allocating enough memory to store the actual pixel data
    uint8_t **pixel_data = malloc(sizeof(uint8_t*) * (file_size - pixel_array_offset));
    if (!pixel_data)
        exit_with_failure("failed to allocate enough space for the pixel_data array");
    
    for (int i = 0; i < image_height; i++)
    {
        // Copy the padding too, it will be filtered out later on
        // I tried to skip the bytes using fseek() but it just wouldn't work for UNIX pipes!
        pixel_data[i] = malloc(3 * image_width + padding);
        if (!pixel_data[i]) exit_with_failure("failed to allocate enough space for pixel array row");
    
        // Copying the next line into the buffer's current row
        if (fread(pixel_data[i], sizeof(uint8_t), 3 * image_width + padding, stdin) != (size_t) (3 * image_width + padding))
            exit_with_failure("failed to read pixel row into memory");
    }

    /*
     * Producing the rotated version of the image
     */
    // The new image will have its width and height transposed
    // I should first calculate the new row padding (row size must be a multiple of four)
    int new_padding = (4 - (image_height * 3) % 4) % 4;
    int new_image_size = (image_height * 3 + new_padding) * image_width;
    int new_file_size = file_size + (new_image_size - image_size);

    // Modifying the local header buffer and sending that version to standard output
    SET_BUFFER_INT32(header, FILE_SIZE_OFFSET, new_file_size);
    SET_BUFFER_INT32(header, IMAGE_WIDTH_OFFSET, image_height);
    SET_BUFFER_INT32(header, IMAGE_HEIGHT_OFFSET, image_width);
    SET_BUFFER_INT32(header, IMAGE_SIZE_OFFSET, new_image_size);
    fwrite(header, sizeof(uint8_t), pixel_array_offset, stdout);
    
    // A special buffer to help me copy zeros and form some padding
    uint8_t *padding_buffer = calloc(new_padding, sizeof(uint8_t));

    /*
     * Column i of the old image will end up as row i of the rotated version
     * The pixel values of each column should also be written in reverse order (the bottom pixel comes first)
     */
    // The first column (which will be turned into a row) should be shown up first in the final version,
    // so it needs to be actually transformed last to comply with the bitmap file format
    for (int i = image_width - 1; i >= 0; i--)
    {
        // I don't need to actually iterate in reverse here,
        // because the bitmap has already reversed each column for me
        for (int j = 0; j < image_height; j++)
        {
            // Mapping each pixel to its rotated version
            fwrite(&pixel_data[j][i * 3], sizeof(uint8_t), 3, stdout);
        }

        fwrite(padding_buffer, sizeof(uint8_t), new_padding, stdout);
    }

    // Freeing up all dynamically allocated memory
    free(padding_buffer);
    
    for (int i = 0; i < image_height; i++)
        free(pixel_data[i]);

    free(pixel_data);
}

int main()
{
    uint8_t *header = read_header();

    // Attempting to rotate the image
    // Both fuctions will just abort if something went wrong
    rotate_bitmap(header);

    free(header);
}
