#include <sys/types.h> // For `open`, `lseek`
#include <sys/stat.h>  // For `open`
#include <fcntl.h>     // For `fcntl` & `open`
#include <unistd.h>    // For `write`, `lseek` & `fcntl`
#include <stdio.h>     // For `perror` & `printf`

#define RECORD_COUNT 3
#define RECORD_SIZE sizeof(struct record)

struct record {
    int recordNumber;
    int someNumber;
};

void initialize_records(int fd) {
    struct record records[RECORD_COUNT] = {
        {1, 0},
        {2, 0},
        {3, 0}
    };
    lseek(fd, 0, SEEK_SET);
    write(fd, records, RECORD_SIZE*RECORD_COUNT);
}

void lock_record(int fd, off_t record_offset) {
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = record_offset;
    lock.l_len = RECORD_SIZE;
    lock.l_pid = getpid();

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error while locking record");
        _exit(1);
    }
}

void unlock_record(int fd, off_t record_offset) {
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = record_offset;
    lock.l_len = RECORD_SIZE;
    lock.l_pid = getpid();

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error while unlocking record");
        _exit(1);
    }
}

int main() {
    char *filePath = "./support_folder/18-file.txt";
    int fd = open(filePath, O_CREAT | O_RDWR, S_IRWXU);
    if (fd == -1) {
        perror("Error while opening the file");
        return 1;
    }
    if (lseek(fd, 0, SEEK_END) == 0) {
        initialize_records(fd);
    }
    for (int i = 0; i < RECORD_COUNT; ++i) {
        off_t record_offset = i * RECORD_SIZE;

        lock_record(fd, record_offset);

        struct record r;
        lseek(fd, record_offset, SEEK_SET);
        read(fd, &r, RECORD_SIZE);
        printf("Record %d: Number=%d\n", r.recordNumber, r.someNumber);

        r.someNumber += 1;
        lseek(fd, record_offset, SEEK_SET);
        write(fd, &r, RECORD_SIZE);

        unlock_record(fd, record_offset);
    }
    return 0;
}
