#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

bool reverse(char*, char*);
void writeYN(int);

int main(int argc, char* argv[])
{
    //Retrieve input filename,
    char *new_file_path = argv[1], *old_file_path = argv[2], *dir_path = argv[3];
    int perms, owner, group, others;

    //open it,
    int input_fd = open(new_file_path, O_RDONLY);
    //find its length and the appropriate chunk size
    off_t new_file_length = lseek(input_fd, 0, SEEK_END);
    int chunk_length = ceil(new_file_length / 500.0);
    int chunk_size = chunk_length * sizeof(char);
    int iters = (ceil) ((float)new_file_length / chunk_length);

    int output_fd = open(old_file_path, O_RDONLY);
    lseek(output_fd, 0, SEEK_SET);

    //Pointers to the strings that will be used
    char* stored_chunk = (char *) malloc(chunk_size);
    char* to_write = (char *) malloc(chunk_size);

    //Checking permissions
    struct stat statbuf;
    int x = stat(dir_path, &statbuf);
    write(1, "Directory is created: ", 22 * sizeof(char));
    writeYN(x);

    //float frac_done = 0.0;
    //printf("progress: 0.00%%");
    //fflush(stdout);
    int no_read = 0; int is_reversed = 1;
    for (int i = iters-1; i >= 0; i--)
    {
        //Go to beginning of i'th chunk
        lseek(input_fd, i * chunk_size, SEEK_SET);
        //Read and terminate
        no_read = read(input_fd, stored_chunk, chunk_size);
        stored_chunk[no_read] = '\0';
        no_read = read(output_fd, to_write, chunk_size);
        to_write[no_read] = '\0';

        //Check if reversed
        is_reversed = is_reversed & (int)reverse(stored_chunk, to_write);

        //Print progress bar
        //frac_done = (float)((iters-i-1) * chunk_length) / (float)(new_file_length);
        //printf("\rprogress: %1.2f%%", frac_done);
        //fflush(stdout);
    }
    //printf("\rprogress: 1.00%%\n");
    write(1, "Whether file contents are reversed in newfile: ", 47 * sizeof(char));
    writeYN((int)is_reversed);

    //Close files
    close(input_fd);
    close(output_fd);

    stat(new_file_path, &statbuf); perms = statbuf.st_mode % 512;
    owner = perms / 64;
    write(1, "User has read permissions on newfile: ", 38 * sizeof(char)); writeYN((int)((owner / 4) == 1));
    write(1, "User has write permissions on newfile: ", 39 * sizeof(char)); writeYN((int)(((owner % 4) / 2) == 1));
    write(1, "User has execute permissions on newfile: ", 41 * sizeof(char)); writeYN((int)((owner % 2) == 1));
    group = (perms % 64) / 8;
    write(1, "Groups has read permissions on newfile: ", 39 * sizeof(char)); writeYN((int)((group / 4) == 1));
    write(1, "Group has write permissions on newfile: ", 40 * sizeof(char)); writeYN((int)(((group % 4) / 2) == 1));
    write(1, "Group has execute permissions on newfile: ", 42 * sizeof(char)); writeYN((int)((group % 2) == 1));
    others = perms % 8;
    write(1, "Other has read permissions on newfile: ", 39 * sizeof(char)); writeYN((int)((others / 4) == 1));
    write(1, "Other has write permissions on newfile: ", 40 * sizeof(char)); writeYN((int)(((others % 4) / 2) == 1));
    write(1, "Other has execute permissions on newfile: ", 42 * sizeof(char)); writeYN((int)((others % 2) == 1));

    stat(old_file_path, &statbuf); perms = statbuf.st_mode % 512;
    owner = perms / 64;
    write(1, "User has read permissions on oldfile: ", 38 * sizeof(char)); writeYN((int)((owner / 4) == 1));
    write(1, "User has write permissions on oldfile: ", 39 * sizeof(char)); writeYN((int)(((owner % 4) / 2) == 1));
    write(1, "User has execute permissions on oldfile: ", 41 * sizeof(char)); writeYN((int)((owner % 2) == 1));
    group = (perms % 64) / 8;
    write(1, "Groups has read permissions on oldfile: ", 39 * sizeof(char)); writeYN((int)((group / 4) == 1));
    write(1, "Group has write permissions on oldfile: ", 40 * sizeof(char)); writeYN((int)(((group % 4) / 2) == 1));
    write(1, "Group has execute permissions on oldfile: ", 42 * sizeof(char)); writeYN((int)((group % 2) == 1));
    others = perms % 8;
    write(1, "Other has read permissions on oldfile: ", 39 * sizeof(char)); writeYN((int)((others / 4) == 1));
    write(1, "Other has write permissions on oldfile: ", 40 * sizeof(char)); writeYN((int)(((others % 4) / 2) == 1));
    write(1, "Other has execute permissions on oldfile: ", 42 * sizeof(char)); writeYN((int)((others % 2) == 1));

    stat(dir_path, &statbuf); perms = statbuf.st_mode % 512;
    owner = perms / 64;
    write(1, "User has read permissions on directory: ", 40 * sizeof(char)); writeYN((int)((owner / 4) == 1));
    write(1, "User has write permissions on directory: ", 41 * sizeof(char)); writeYN((int)(((owner % 4) / 2) == 1));
    write(1, "User has execute permissions on directory: ", 43 * sizeof(char)); writeYN((int)((owner % 2) == 1));
    group = (perms % 64) / 8;
    write(1, "Groups has read permissions on directory: ", 41 * sizeof(char)); writeYN((int)((group / 4) == 1));
    write(1, "Group has write permissions on directory: ", 42 * sizeof(char)); writeYN((int)(((group % 4) / 2) == 1));
    write(1, "Group has execute permissions on directory: ", 44 * sizeof(char)); writeYN((int)((group % 2) == 1));
    others = perms % 8;
    write(1, "Other has read permissions on directory: ", 41 * sizeof(char)); writeYN((int)((others / 4) == 1));
    write(1, "Other has write permissions on directory: ", 42 * sizeof(char)); writeYN((int)(((others % 4) / 2) == 1));
    write(1, "Other has execute permissions on directory: ", 44 * sizeof(char)); writeYN((int)((others % 2) == 1));

}

bool reverse(char* str1, char* str2)
{
    bool is_reversed = true;
    for (int i = 0, j = strlen(str1) -1; i < strlen(str1); i++, j--)
        is_reversed = is_reversed && (str2[i] == str1[j]);
    is_reversed = is_reversed && (str2[strlen(str1)] == '\0');
    return is_reversed;
}

void writeYN(int x)
{
    if (x == 0)
        write(1, "Yes\n", 4 * sizeof(char));
    else
        write(1, "No\n", 3 * sizeof(char));
}