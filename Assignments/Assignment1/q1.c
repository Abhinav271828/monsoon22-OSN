#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <math.h>

void reverse(char*, char*);

int main(int argc, char* argv[])
{
    //Retrieve input filename,
    char* input_file_path = argv[1];
    //open it,
    int input_fd = open(input_file_path, O_RDONLY);
    //find its length and the appropriate chunk size
    off_t input_file_length = lseek(input_fd, 0, SEEK_END);
    int chunk_length = ceil(input_file_length / 500.0);
    int chunk_size = chunk_length * sizeof(char);
    int iters = (ceil) ((float)input_file_length / chunk_length);

    //Find the output filename
    mkdir("Assignment", 00700);
    char* output_file_path = (char *) malloc((13 + strlen(input_file_path)) * sizeof(char));
    strcpy(output_file_path, "Assignment/1_");
    strcat(output_file_path, input_file_path);
    //and create the file
    int output_fd = open(output_file_path, O_CREAT | O_RDWR | O_TRUNC, 00600);
    lseek(output_fd, 0, SEEK_SET);

    //Pointers to the strings that will be used
    char* stored_chunk = (char *) malloc(chunk_size);
    char* to_write = (char *) malloc(chunk_size);
    char* digit = (char *) malloc(sizeof(char));

    float frac_done = 0.0;
    write(1, "progress: 0.00%", 15 * sizeof(char));
    int no_read = 0;
    for (int i = iters-1; i >= 0; i--)
    {
        //Go to beginning of i'th chunk
        lseek(input_fd, i * chunk_size, SEEK_SET);
        //Read and terminate
        no_read = read(input_fd, stored_chunk, chunk_size);
        stored_chunk[no_read] = '\0';
        //Reverse
        reverse(stored_chunk, to_write);
        //And write
        write(output_fd, to_write, no_read);

        //Print progress bar
        frac_done = (float)((iters-i-1) * chunk_length) / (float)(input_file_length);
        write(1, "\rprogress: 0.", 13 * sizeof(char));
        *digit = (int)floor(frac_done * 10) % 10 + '0';
        write(1, digit, sizeof(char));
        *digit = (int)floor(frac_done * 100) % 10 + '0';
        write(1, digit, sizeof(char));
        write(1, "%", sizeof(char));
    }
    write(1, "\rprogress: 1.00%\n", 17 * sizeof(char));

    //Close files
    close(input_fd);
    close(output_fd);

}

void reverse(char* str1, char* str2)
{
    for (int i = 0, j = strlen(str1) -1; i < strlen(str1); i++, j--)
        str2[i] = str1[j];
    str2[strlen(str1)] = '\0';
}