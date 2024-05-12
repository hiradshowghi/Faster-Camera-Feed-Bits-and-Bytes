#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARR 5000

/*  Function: take_photo()
    Description: Simulates taking a photo as a black-and-white image represented by
                 an array of characters '1' and '0'. The photo is stored in the out[] array.

    Output: out[]   - an array of characters to store the photo data, as a string of 1 and 0 characters
    Output: rows    - an address to an integer to store the number of rows in the photo
    Output: cols    - an address to an integer to store the number of columns in the photo

    Returns: the total number of characters in the photo data OR 0 if no photo was taken
    
*/
int take_photo(unsigned char out[], int* rows, int* cols);

unsigned char get_bit(unsigned char byte, int bit);
unsigned char set_bit(unsigned char byte, int bit);
unsigned char clear_bit(unsigned char byte, int bit);

// Implement the print_raw function here
void print_raw(unsigned char raw_string[], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            // Access the character at the appropriate index in the 1D array
            char pixel = raw_string[i * cols + j];

            // Print '*' for '1' and '.' for '0'
            if (pixel == '1') {
                printf("*");
            } else if (pixel == '0') {
                printf(".");
            }
        }
        printf("\n"); // Move to the next row
    }
}

// Implement the pack_bits function here
int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]) {
    int packed_size = (num_chars + 7) / 8; // Calculate the packed size in bytes
    int packed_idx = 0; // Current byte in packed_result
    unsigned char current_byte = 0; // Current byte being packed
    int bit_idx = 0; // Current bit within the current_byte

    for (int i = 0; i < num_chars; i++) {
        unsigned char bit = unpacked_string[i];
        current_byte |= (bit << bit_idx); // Set the bit in the current_byte

        bit_idx++;
        if (bit_idx == 8 || i == num_chars - 1) {
            // If we've filled a byte or reached the end of the unpacked string
            packed_result[packed_idx] = current_byte;
            packed_idx++;
            current_byte = 0; // Reset the current_byte
            bit_idx = 0;
        }
    }

    return packed_size;
}

// Implement the print_packed function here
void print_packed(unsigned char packed[], int rows, int cols) {
    int packed_size = (rows * cols + 7) / 8;
    int packed_idx = 0;

    for (int i = 0; i < packed_size; i++) {
        unsigned char current_byte = packed[i];
        for (int j = 0; j < 8 && (i * 8 + j < rows * cols); j++) {
            unsigned char bit = (current_byte >> j) & 1;
            if (bit == 1) {
                printf("*");
            } else {
                printf(".");
            }
        }
        if ((i + 1) * 8 % cols == 0) {
            printf("\n");
        }
    }
}

int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[]) {
    int encoded_size = 0; // Initialize the size of the encoded array
    unsigned char current_bit = packed[0]; // Initialize the current bit as the first bit in packed
    int consecutive_count = 1; // Initialize the count of consecutive bits

    for (int i = 1; i < packed_size; i++) {
        if (packed[i] == current_bit) {
            // If the current bit matches the previous bit, increment the consecutive count
            consecutive_count++;
        } else {
            // If the current bit is different, add the count to the encoded array
            encoded_result[encoded_size] = consecutive_count;
            encoded_size++;
            consecutive_count = 1; // Reset the count
            current_bit = packed[i]; // Update the current bit
        }
    }

    // Add the final count to the encoded array
    encoded_result[encoded_size] = consecutive_count;
    encoded_size++;

    return encoded_size;
}

void print_encoded(unsigned char encoded[], int encoded_size) {
    int current_bit = 1; // Start with 1s
    for (int i = 0; i < encoded_size; i++) {
        int count = encoded[i];
        for (int j = 0; j < count; j++) {
            putchar(current_bit ? '*' : '.'); // Print '*' for 1 and '.' for 0
        }
        current_bit = 1 - current_bit; // Toggle between 1s and 0s
    }
}

int main() {
    int rows, cols;
    unsigned char raw[MAX_ARR];
    int raw_size;
    

    // Initialize the loop to print multiple images
    int imageCounter = 0;

    while ((raw_size = take_photo(raw, &rows, &cols)) > 0) {
        printf("Image %d:\n", imageCounter + 1);
        printf("Rows: %d\n", rows);
        printf("Columns: %d\n", cols);

        // Part 1.3: Implement the print_raw function
        printf("Raw Image:\n");
        print_raw(raw, rows, cols);

        // Part 1.6: Print the number of bytes required to represent the image
        printf("Size of Raw Image: %d bytes\n", raw_size);

        // Increase the image counter
        imageCounter++;

        // Add a newline between images
        printf("\n");
        
    }

    if (imageCounter == 0) {
        printf("No images available.\n");
    }

    return 0;
}

unsigned char get_bit(unsigned char byte, int bit) {
    return (byte >> bit) & 1;
}

unsigned char set_bit(unsigned char byte, int bit) {
    return byte | (1 << bit);
}

unsigned char clear_bit(unsigned char byte, int bit) {
    return byte & ~(1 << bit);
}