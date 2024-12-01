#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage : day1 [input file]\n");
        return 0;
    }

    long distance = 0;

    FILE *file = fopen(argv[1], "r");
    if (file == 0)
    {
        printf("Could not open file : %s\n", argv[1]);
        return 0;
    }

    // Counting lines
    char c;
    int size = 0;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            size++;
        }
    }

    rewind(file);

    int *left = malloc(size * sizeof(int));
    int *right = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        int e = fscanf(file, "%d %d", left + i, right + i);
    }

    fclose(file);

    // Part 1 ////////////////////////////////////////////////////////////
    // Bubble sort
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size - j - 1; i++)
        {
            int tmp;

            if (left[i] > left[i + 1])
            {
                tmp = left[i];
                left[i] = left[i + 1];
                left[i + 1] = tmp;
            }

            if (right[i] > right[i + 1])
            {
                tmp = right[i];
                right[i] = right[i + 1];
                right[i + 1] = tmp;
            }
        }

        distance += abs(left[size - j - 1] - right[size - j - 1]);
    }

    printf("Part 1 : %ld\n", distance);
    //////////////////////////////////////////////////////////////////////

    // Part 2 ////////////////////////////////////////////////////////////
    // Both list are sorted
    distance = 0;
    int j = 0;
    while (j < size)
    {
        int i = 0;
        while (right[i] <= left[j])
        {
            if (right[i] == left[j])
            {
                distance += left[j];
            }

            i++;
        }

        j++;
    }

    printf("Part 2 : %ld\n", distance);
    //////////////////////////////////////////////////////////////////////

    free(left);
    free(right);

    return 0;
}