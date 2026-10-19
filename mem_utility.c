/**
 * @file mem_utility.c
 * @author Sledoff (norscreecs@gmail.com)
 * @brief Utility 
 * @version 1.0.0
 * @date 2026-10-19
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

uint64_t beging_reg = 0xA1000000;
uint64_t end_reg = 0xA1000100;
uint8_t reg_size = 32;
ssize_t map_size = 0;
uint8_t byte_size = 4;

void print_help(char* name) {
    printf("=====================================\n");
    printf("Utility for displaying register values\n");
    printf("Author: K.Sledevskiy (norscreecs@gmail.com)\n");
    printf("\n-------------------------------------\n");
    printf(" -h : --help - show this message;\n");
    printf(" -b - initial register;\n");
    printf(" -e - end register;\n");
    printf(" -s - size of register;\n");
    printf("USAGE: %s -b 0xA1000000 -e 0xA1000100 [-s 8/16/32/64]\n", name);
}

int parse_args(int argc, char* argv[]) {
    if (argc <= 1) {
        print_help(argv[0]);
        return -1;
    }
    int opt;
    uint8_t beging_f = 0;
    uint8_t end_f = 0;


    while ((opt = getopt(argc, argv, "b:e:s:h")) != -1) {
        switch (opt) {
            case 'b':
                beging_f = 1;
                beging_reg = strtoull(optarg, NULL, 16);
                break;
            case 'e':
                end_f = 1;
                end_reg = strtoull(optarg, NULL, 16);
                break;
            case 's':
                reg_size = strtod(optarg, NULL);
                break;
            case 'h':
                print_help(argv[0]);
                return -1;
                break;
            default:
                return 0;
        }
    }
    if (beging_f == 0 || end_f == 0) {
        printf("The start and end address arguments are mandatory!\n");
        return -1;
    }
    byte_size = reg_size / 8;
    map_size = (end_reg - beging_reg) / byte_size;
    if (beging_reg + map_size*byte_size != end_reg) {
        printf("Addresses are not aligned\n");
        return -1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    int error = parse_args(argc, argv);
    if (error < 0)
        return -1;

    int fd = open("/dev/mem", O_RDONLY);
    if (fd < 0) {
        perror("Can not open /dev/mem! ");
        return -1;
    }
 
    uint8_t* vmap = mmap(NULL, map_size*byte_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (vmap == MAP_FAILED) {
        perror("Can not create mmap!");
        return -1;
    }

    printf("Data from regs: %08lX - %08lX with reg size: %d\n", beging_reg, end_reg, reg_size);

    for (int i = 0; i < map_size*byte_size; i += byte_size) {
        printf("[%08lX] - 0x", beging_reg + i);
        for (int j = 0; j < byte_size; j++) {
            printf("%02X", vmap[i+j]);
        }
        printf("\n");
    }

    munmap(vmap, map_size);
    close(fd);
    return 0;
}
