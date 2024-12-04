#include <stdio.h>
#include <stdlib.h>

int search(const char *input, int i, int j, size_t width, size_t height)
{
    if (input[i + width * j] != 'X')
        return 0;

    int count = 0;

    // EAST
    if (i < width - 3 &&
        input[i + 1 + width * j] == 'M' &&
        input[i + 2 + width * j] == 'A' &&
        input[i + 3 + width * j] == 'S')
        count++;

    // WEST
    if (i >= 3 &&
        input[i - 1 + width * j] == 'M' &&
        input[i - 2 + width * j] == 'A' &&
        input[i - 3 + width * j] == 'S')
        count++;

    // SOUTH
    if (j < height - 3 &&
        input[i + width * (j + 1)] == 'M' &&
        input[i + width * (j + 2)] == 'A' &&
        input[i + width * (j + 3)] == 'S')
        count++;

    // NORTH
    if (j >= 3 &&
        input[i + width * (j - 1)] == 'M' &&
        input[i + width * (j - 2)] == 'A' &&
        input[i + width * (j - 3)] == 'S')
        count++;

    // SOUTH-EAST
    if (i < width - 3 && j < height - 3 &&
        input[i + 1 + width * (j + 1)] == 'M' &&
        input[i + 2 + width * (j + 2)] == 'A' &&
        input[i + 3 + width * (j + 3)] == 'S')
        count++;

    // SOUTH-WEST
    if (i >= 3 && j < height - 3 &&
        input[i - 1 + width * (j + 1)] == 'M' &&
        input[i - 2 + width * (j + 2)] == 'A' &&
        input[i - 3 + width * (j + 3)] == 'S')
        count++;

    // NORTH-WEST
    if (i >= 3 && j >= 3 &&
        input[i - 1 + width * (j - 1)] == 'M' &&
        input[i - 2 + width * (j - 2)] == 'A' &&
        input[i - 3 + width * (j - 3)] == 'S')
        count++;

    // NORTH-EAST
    if (i < width - 3 && j >= 3 &&
        input[i + 1 + width * (j - 1)] == 'M' &&
        input[i + 2 + width * (j - 2)] == 'A' &&
        input[i + 3 + width * (j - 3)] == 'S')
        count++;

    return count;
}

int search2(const char *input, int i, int j, size_t width, size_t height)
{
    if (input[i + width * j] != 'A')
        return 0;

    int count = 0;

    if (i >= 1 && i < width - 1 && j >= 1 && j < height - 1)
    {
        // SOUTH-EAST && SOUTH-WEST
        if (input[i + 1 + width * (j + 1)] == 'M' &&
            input[i - 1 + width * (j - 1)] == 'S' &&
            input[i - 1 + width * (j + 1)] == 'M' &&
            input[i + 1 + width * (j - 1)] == 'S')
            count++;

        // SOUTH-EAST && NORTH-WEST
        if (input[i + 1 + width * (j + 1)] == 'M' &&
            input[i - 1 + width * (j - 1)] == 'S' &&
            input[i - 1 + width * (j - 1)] == 'M' &&
            input[i + 1 + width * (j + 1)] == 'S')
            count++;

        // SOUTH-EAST && NORTH-EAST
        if (input[i + 1 + width * (j + 1)] == 'M' &&
            input[i - 1 + width * (j - 1)] == 'S' &&
            input[i + 1 + width * (j - 1)] == 'M' &&
            input[i - 1 + width * (j + 1)] == 'S')
            count++;

        // SOUTH-WEST && NORTH-WEST
        if (input[i - 1 + width * (j + 1)] == 'M' &&
            input[i + 1 + width * (j - 1)] == 'S' &&
            input[i - 1 + width * (j - 1)] == 'M' &&
            input[i + 1 + width * (j + 1)] == 'S')
            count++;

        // SOUTH-WEST && NORTH-EAST
        if (input[i - 1 + width * (j + 1)] == 'M' &&
            input[i + 1 + width * (j - 1)] == 'S' &&
            input[i + 1 + width * (j - 1)] == 'M' &&
            input[i - 1 + width * (j + 1)] == 'S')
            count++;

        // NORTH-WEST && NORTH-EAST
        if (input[i - 1 + width * (j - 1)] == 'M' &&
            input[i + 1 + width * (j + 1)] == 'S' &&
            input[i + 1 + width * (j - 1)] == 'M' &&
            input[i - 1 + width * (j + 1)] == 'S')
            count++;
    }

    return count;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage : day4 [input file]\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == 0)
    {
        printf("Could not open file : %s\n", argv[1]);
        return 0;
    }

    size_t width = 0;
    size_t height = 0;
    char c;

    while (!feof(file))
    {
        c = fgetc(file);

        if (c == '\n')
            height++;

        if (height == 0)
            width++;
    }

    rewind(file);

    char *input = malloc(width * height);
    int i = 0;
    int j = 0;
    while (!feof(file))
    {
        c = fgetc(file);

        if (c == '\n')
        {
            i = 0;
            j++;
        }
        else
        {
            input[i + width * j] = c;
            i++;
        }
    }

    fclose(file);

    // Part 1 ////////////////////////////////////////////////////////////
    int count = 0;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            count += search(input, i, j, width, height);
        }
    }

    printf("%d\n", count);
    //////////////////////////////////////////////////////////////////////

    // Part 2 ////////////////////////////////////////////////////////////
    count = 0;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            count += search2(input, i, j, width, height);
        }
    }

    printf("%d\n", count);
    //////////////////////////////////////////////////////////////////////

    free(input);

    return 0;
}