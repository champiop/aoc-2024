#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int charToDir(char d)
{
    switch (d)
    {
    case '^':
        return 0;
        break;

    case '>':
        return 1;
        break;

    case 'v':
        return 2;
        break;

    case '<':
        return 3;
        break;

    default:
        return -1;
        break;
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage : day6 [input file]\n");
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

    char *startInput = malloc(width * height);
    char *input = malloc(width * height);
    int starti = 0;
    int startj = 0;
    int gi = 0;
    int gj = 0;
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
            if (c == '^' || c == 'v' || c == '<' || c == '>')
            {
                starti = i;
                startj = j;
            }

            startInput[i + width * j] = c;
            i++;
        }
    }

    fclose(file);

    int blocki[width * height];
    int blockj[width * height];
    memset(blocki, -1, width * height * sizeof(int));
    memset(blockj, -1, width * height * sizeof(int));

    // Part 1 ////////////////////////////////////////////////////////////
    memcpy(input, startInput, width * height);
    gi = starti;
    gj = startj;

    int count = 1;
    while (1)
    {
        int ni = gi;
        int nj = gj;
        char nd = input[gi + width * gj];

        switch (nd)
        {
        case '^':
            nj--;
            nd = '>';
            break;

        case '>':
            ni++;
            nd = 'v';
            break;

        case 'v':
            nj++;
            nd = '<';
            break;

        case '<':
            ni--;
            nd = '^';
            break;

        default:
            break;
        }

        if (ni < 0 || ni >= width || nj < 0 || nj >= height)
            break;

        switch (input[ni + width * nj])
        {
        case '.':
            count++;
            input[ni + width * nj] = input[gi + width * gj];
            input[gi + width * gj] = 'X';
            gi = ni;
            gj = nj;
            blocki[gi + width * gj] = gi;
            blockj[gi + width * gj] = gj;
            break;

        case '#':
            input[gi + width * gj] = nd;
            break;

        default:
            input[ni + width * nj] = input[gi + width * gj];
            gi = ni;
            gj = nj;
            blocki[gi + width * gj] = gi;
            blockj[gi + width * gj] = gj;
            break;
        }
    }

    printf("%d\n", count);
    //////////////////////////////////////////////////////////////////////

    memcpy(input, startInput, width * height);
    gi = starti;
    gj = startj;

    // Part 2 ////////////////////////////////////////////////////////////
    count = 0;
    int visited[4 * width * height];
    memset(visited, 0, 4 * width * height * sizeof(int));
    for (int k = 0; k < width * height; k++)
    {
        if (blocki[k] == -1 && blockj[k] == -1)
            continue;

        if (input[k] == '#' || input[k] == '^' ||
            input[k] == '>' || input[k] == 'v' ||
            input[k] == '<')
            continue;

        input[k] = '#';

        while (1)
        {
            if (visited[4 * (gi + width * gj) + charToDir(input[gi + width * gj])])
            {
                count++;
                break;
            }

            int ni = gi;
            int nj = gj;
            char nd = input[gi + width * gj];

            switch (nd)
            {
            case '^':
                nj--;
                nd = '>';
                break;

            case '>':
                ni++;
                nd = 'v';
                break;

            case 'v':
                nj++;
                nd = '<';
                break;

            case '<':
                ni--;
                nd = '^';
                break;

            default:
                break;
            }

            if (ni < 0 || ni >= width || nj < 0 || nj >= height)
                break;

            switch (input[ni + width * nj])
            {
            case '#':
                input[gi + width * gj] = nd;
                break;

            default:
                visited[4 * (gi + width * gj) + charToDir(input[gi + width * gj])] = 1;
                input[ni + width * nj] = input[gi + width * gj];
                gi = ni;
                gj = nj;
                break;
            }
        }

        memcpy(input, startInput, width * height);
        gi = starti;
        gj = startj;
        memset(visited, 0, 4 * width * height * sizeof(int));
    }

    printf("%d\n", count);
    //////////////////////////////////////////////////////////////////////

    free(input);
    free(startInput);
    return 0;
}