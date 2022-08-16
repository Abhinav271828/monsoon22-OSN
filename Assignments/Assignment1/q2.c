#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <math.h>

void copy_from_to(int input_fd, int output_fd, int start_idx, int end_idx, bool reverse);

int total_printed = 0;
int main(int argc, char* argv[])
{
    //Retrieve input filename,
    char* input_file_path = argv[1];
    int start = atoi(argv[2]), end = atoi(argv[3]);
    //open it,
    int input_fd = open(input_file_path, O_RDONLY);
    //find its length and the appropriate chunk size
    off_t input_file_length = lseek(input_fd, 0, SEEK_END);

    //Find the output filename
    mkdir("Assignment", 00700);
    char* output_file_path = (char *) malloc((13 + strlen(input_file_path)) * sizeof(char));
    strcpy(output_file_path, "Assignment/2_");
    strcat(output_file_path, input_file_path);
    //and create the file
    int output_fd = open(output_file_path, O_CREAT | O_RDWR | O_TRUNC, 00600);
    lseek(output_fd, 0, SEEK_SET);

    //Copy
    copy_from_to(input_fd, output_fd, 0, start, true);
    copy_from_to(input_fd, output_fd, start, end+1, false);
    copy_from_to(input_fd, output_fd, end, input_file_length, true);
    write(1, "\rprogress: 1.00%\n", 17 * sizeof(char));

    //Pointers to the strings that will be used
    close(input_fd);
    close(output_fd);

}

//Copies [start_idx:end_idx] of input_fd
//to output_fd.
//Reverses if reverse == true
void copy_from_to(int input_fd, int output_fd, int start_idx, int end_idx, bool reverse)
{
    int length = (end_idx - start_idx);
    int total_length = lseek(input_fd, 0, SEEK_END);

    lseek(input_fd, 0, SEEK_SET);
    lseek(output_fd, 0, SEEK_CUR);

    int chunk_length = ceil(length / 500.0);
    int chunk_size = chunk_length * sizeof(char);
    int iters = (ceil) ((float) length / chunk_length);

    char* stored_chunk = (char *) malloc(chunk_size);
    char* to_write = (char *) malloc(chunk_size);
    char* digit = (char *) malloc(sizeof(char));

    float frac_done = (float) (start_idx)/(total_length);
    write(1, "\rprogress: 0.00%", 15 * sizeof(char)); 
    int no_read = 0, read_from, read_for;

    for (int j = 0, i; j < iters; j++)
    {
        i = reverse ? iters - 1 - j : j;

        read_from = start_idx + i * chunk_size;
        read_for = (i == iters - 1) ? (end_idx - read_from) : chunk_size;
        total_printed += read_for;

        //Go to beginning of i'th chunk
        lseek(input_fd, read_from, SEEK_SET);

        //Read and terminate
        no_read = read(input_fd, stored_chunk, read_for);
        stored_chunk[no_read] = '\0';

        if (reverse)
        {
            for (int i = 0, j = strlen(stored_chunk) -1; i < strlen(stored_chunk); i++, j--)
            to_write[i] = stored_chunk[j];
            to_write[strlen(stored_chunk)] = '\0';
        }
        else strcpy(to_write, stored_chunk);

        //And write
        write(output_fd, to_write, no_read);

        //Print progress bar
        frac_done = (float) (total_printed) / (float) (total_length);
        write(1, "\rprogress: 0.", 13 * sizeof(char));
        *digit = (int)floor(frac_done * 10) % 10 + '0';
        write(1, digit, sizeof(char));
        *digit = (int)floor(frac_done * 100) % 10 + '0';
        write(1, digit, sizeof(char));
        write(1, "%", sizeof(char));
    }

    frac_done = (float) (end_idx)/(total_length);
    write(1, "\rprogress: 0.", 13 * sizeof(char));
    *digit = (int)floor(frac_done * 10) % 10 + '0';
    write(1, digit, sizeof(char));
    *digit = (int)floor(frac_done * 100) % 10 + '0';
    write(1, digit, sizeof(char));
    write(1, "%", sizeof(char));
}