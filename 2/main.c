#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isSafe(char *report)
{
    int current = 0;
    int previous = -1;
    int sign = 0;
    int characterCount = 0;
    char *cursor = report;
    while (sscanf(cursor, "%d%n", &current, &characterCount) == 1)
    {
        cursor += characterCount;

        if (previous == -1)
        {
            previous = current;
            continue;
        }

        int diff = current - previous;
        if (sign == 0)
        {
            if (diff < 0)
            {
                sign = -1;
                if (diff < -3)
                    return 0;
            }
            else if (diff > 0)
            {
                sign = 1;
                if (diff > 3)
                    return 0;
            }
            else
            {
                return 0;
            }
        }
        else if (sign == -1)
        {
            if (diff >= 0)
                return 0;
            else if (diff < -3)
                return 0;
        }
        else
        {
            if (diff <= 0)
                return 0;
            else if (diff > 3)
                return 0;
        }

        previous = current;
    }
}

int isSafe2(char *report)
{
    if (isSafe(report))
    {
        return 1;
    }
    else
    {
        int cursor = 0;
        int current = 0;
        int characterCount = 0;
        size_t len = strlen(report);
        char *substr = malloc(len + 1);
        while (sscanf(report + cursor, "%d%n", &current, &characterCount) == 1)
        {
            strncpy(substr, report, cursor);
            substr[cursor] = '\0';
            cursor += characterCount;
            strcat(substr, report + cursor);

            if (isSafe(substr))
                return 1;
        }
        free(substr);
    }

    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage : day2 [input file]\n");
        return 0;
    }

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

    char **reports = malloc(size * sizeof(char *));
    int bufferSize = 128;
    for (int i = 0; i < size; i++)
    {
        reports[i] = malloc(bufferSize * sizeof(char));

        int j = 0;
        while ((c = fgetc(file)) != '\n' && j < bufferSize - 1)
        {
            reports[i][j] = c;
            j++;
        }
        reports[i][j] = '\0';
    }

    fclose(file);

    // Part 1 ////////////////////////////////////////////////////////////
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (isSafe(reports[i]))
            count++;
    }

    printf("%d\n", count);
    //////////////////////////////////////////////////////////////////////

    // Part 2////////////////////////////////////////////////////////////
    count = 0;
    for (int i = 0; i < size; i++)
    {
        if (isSafe2(reports[i]))
            count++;
    }

    printf("%d\n", count);
    //////////////////////////////////////////////////////////////////////

    for (int i = 0; i < size; i++)
    {
        free(reports[i]);
    }
    free(reports);

    return 0;
}