#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>

#define PART                2

#define MAX_LABEL_LENGTH    8

#if PART == 2
#define MAX_LENSES          1500
#endif

#if PART == 2
typedef struct lensList_s
{
    char label[MAX_LABEL_LENGTH];
    int focalLength;
    struct lensList_s* next;
} lensList_t;

lensList_t lensPool[MAX_LENSES];
lensList_t* freeList;

void MM_free(lensList_t*);

void MM_init()
{
    lensList_t* entry = lensPool;
    for (int i = 0; i < MAX_LENSES; ++i) {
        MM_free(entry++);
    }
}

lensList_t* MM_alloc()
{
    if (!freeList) {
        printf("out of memory...\n");
        exit(0);
    }

    lensList_t* entry = freeList;
    freeList = *((lensList_t**)freeList);
    return entry;
}

void MM_free(lensList_t* entry)
{
    *(lensList_t**)entry = freeList;
    freeList = entry;
}

#endif

unsigned char hash(const char* str)
{
    unsigned int value = 0;

    for ( ; *str; ++str) {
        value = ((value + *str) * 17) % 256;
    }

    return value;
}

main()
{
#if PART == 2
    MM_init();
#endif

    FILE* fp = fopen("day15.h", "rb");
    if (!fp) {
        return 0;
    }

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    char* data = (char*)malloc(size + 1);
    if (!data) {
        return 0;
    }

    fread(data, sizeof(char), size, fp);
    data[size] = '\0';
    fclose(fp);

#if PART == 2
    lensList_t* boxes[256];
    memset(boxes, 0, sizeof(boxes));
#endif

    int sum = 0;
    char* token = strtok(data, ",");
    while (token)
    {
#if PART == 1
        sum  += hash(token);
#else
        char label[MAX_LABEL_LENGTH];
        size_t len = strlen(token);
        if (token[len - 1] == '-')
        {
            sscanf(token, "%8[^-]-", label);

            const int boxIndex = hash(label);
            lensList_t* prev = NULL, *lens = boxes[boxIndex];
            for (; lens; lens = lens->next)
            {
                if (!strncmp(lens->label, label, sizeof(label))) {
                    break;
                }
                prev = lens;
            }

            if (lens) {
                if (prev == NULL) {
                    boxes[boxIndex] = lens->next;
                }
                else {
                    prev->next = lens->next;
                }
            }
        }
        else
        {
            int focalLength;
            sscanf(token, "%8[^=]=%d", label, &focalLength);

            const int boxIndex = hash(label);
            lensList_t* prev = NULL, *lens = boxes[boxIndex];
            for (; lens; lens = lens->next)
            {
                if (!strncmp(lens->label, label, sizeof(label))) {
                    break;
                }
                prev = lens;
            }

            if (!lens) 
            {
                lens = MM_alloc();
                strncpy(lens->label, label, sizeof(label));

                if (!prev) {
                    boxes[boxIndex] = lens;
                } else {
                    prev->next = lens;
                }
            }

            lens->focalLength = focalLength;
        }
#endif
        token = strtok(NULL, ",");
    }
#if PART == 2
    for (int boxIndex = 0; boxIndex < 256; ++boxIndex)
    {
        int slot = 1;
        for (lensList_t* lens = boxes[boxIndex]; lens; lens = lens->next, ++slot)
        {
            int focusingPower = (boxIndex + 1) * slot * lens->focalLength;
            sum += focusingPower;
        }
    }
#endif
    printf("%d\n", sum);

    free(data);
}