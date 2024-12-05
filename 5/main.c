#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage : day5 [input file]\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == 0)
    {
        printf("Could not open file : %s\n", argv[1]);
        return 0;
    }

    size_t orderingSize = 0;
    char c;
    int start = 0;

    while (!feof(file))
    {
        c = fgetc(file);

        if (c == '\n')
        {
            if (start)
                break;

            start = 1;
            orderingSize++;
        }
        else
        {
            start = 0;
        }
    }

    size_t pagesSize = 0;
    size_t maxPageCount = 0;
    size_t pageCount = 0;

    while (!feof(file))
    {
        c = fgetc(file);

        if (c == '\n')
        {
            if (pageCount > maxPageCount)
                maxPageCount = pageCount;

            pageCount = 0;
            pagesSize++;
        }
        else
        {
            int tmp;
            fscanf(file, "%d", &tmp);

            pageCount++;
        }
    }

    rewind(file);

    int *ordering = malloc(2 * orderingSize * sizeof(int));
    for (int i = 0; i < 2 * orderingSize; i += 2)
    {
        fscanf(file, "%d|%d\n", ordering + i, ordering + i + 1);
    }

    int **pages = malloc(pagesSize * sizeof(int *));
    for (int j = 0; j < pagesSize; j++)
    {
        pages[j] = malloc(maxPageCount * sizeof(int));

        fscanf(file, "%d", pages[j]);

        int i = 1;
        while ((c = fgetc(file)) != '\n')
        {
            fscanf(file, "%d", pages[j] + i);
            i++;
        }

        pages[j][i] = -1;
    }

    fclose(file);

    // Part 1 ////////////////////////////////////////////////////////////
    int count = 0;
    for (int j = 0; j < pagesSize; j++)
    {
        for (int i = 1; i < maxPageCount; i++)
        {
            if (pages[j][i] == -1)
            {
                count += pages[j][(i - 1) / 2];
                break;
            }

            int end = 0;
            for (int k = 0; k < orderingSize; k++)
            {
                if (ordering[2 * k] == pages[j][i] &&
                    ordering[2 * k + 1] == pages[j][i - 1])
                    end = 1;
            }

            if (end)
                break;

            if (i == maxPageCount - 1)
            {
                count += pages[j][i / 2];
            }
        }
    }

    printf("%d\n", count);
    //////////////////////////////////////////////////////////////////////

    // Part 2 ////////////////////////////////////////////////////////////
    count = 0;
    for (int j = 0; j < pagesSize; j++)
    {
        int inOrder = 1;
        for (int i = 1; i < maxPageCount; i++)
        {
            if (pages[j][i] == -1)
            {
                if (!inOrder)
                {
                    count += pages[j][(i - 1) / 2];
                }
                break;
            }

            // Bubble sort
            for (int i1 = 0; i1 < maxPageCount - i; i1++)
            {
                int tmp;
                for (int k = 0; k < orderingSize; k++)
                {
                    if (ordering[2 * k] == pages[j][i1 + 1] &&
                        ordering[2 * k + 1] == pages[j][i1])
                    {
                        tmp = pages[j][i1];
                        pages[j][i1] = pages[j][i1 + 1];
                        pages[j][i1 + 1] = tmp;
                        inOrder = 0;
                    }
                }
            }

            if (i == maxPageCount - 1)
            {
                if (!inOrder)
                {
                    count += pages[j][i / 2];
                }
            }
        }
    }

    printf("%d\n", count);
    //////////////////////////////////////////////////////////////////////

    free(ordering);
    for (int j = 0; j < pagesSize; j++)
        free(pages[j]);
    free(pages);

    return 0;
}