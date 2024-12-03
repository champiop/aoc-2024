#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum
{
    ERROR = 0,
    MUL,
    DO,
    DONT,
    OPAR,
    COMMA,
    CPAR,
    INTEGER,
    END
};

int getToken(const char *input, int *cursor)
{
    if (input[*cursor] == 'm')
    {
        if (input[*cursor + 1] == 'u')
        {
            if (input[*cursor + 2] == 'l')
                return MUL;
        }
    }
    else if (input[*cursor] == 'd')
    {
        if (input[*cursor + 1] == 'o')
        {
            if (input[*cursor + 2] == 'n')
            {
                if (input[*cursor + 3] == '\'')
                {
                    if (input[*cursor + 4] == 't')
                        return DONT;
                    else
                        return DO;
                }
                else
                    return DO;
            }
            else
                return DO;
        }
    }
    else if (input[*cursor] == '(')
        return OPAR;
    else if (input[*cursor] == ',')
        return COMMA;
    else if (input[*cursor] == ')')
        return CPAR;
    else if (isdigit(input[*cursor]))
    {
        int i = 0;
        while (isdigit(input[*cursor + i]) && i < 3)
        {
            i++;
        }

        return INTEGER;
    }
    else if (input[*cursor] == '\0')
        return END;

    return ERROR;
}

int eatToken(const char *input, int *cursor, int token)
{
    if (token == MUL)
    {
        if (input[*cursor] == 'm')
        {
            (*cursor)++;
            if (input[*cursor] == 'u')
            {
                (*cursor)++;
                if (input[*cursor] == 'l')
                {
                    (*cursor)++;
                    return 0;
                }
                else
                    return -1;
            }
            else
                return -1;
        }
        else
            return -1;
    }
    else if (token == DO)
    {
        if (input[*cursor] == 'd')
        {
            (*cursor)++;
            if (input[*cursor] == 'o')
            {
                (*cursor)++;
                return 0;
            }
            else
                return -1;
        }
        else
            return -1;
    }
    else if (token == DONT)
    {
        if (input[*cursor] == 'd')
        {
            (*cursor)++;
            if (input[*cursor] == 'o')
            {
                (*cursor)++;
                if (input[*cursor] == 'n')
                {
                    (*cursor)++;
                    if (input[*cursor] == '\'')
                    {
                        (*cursor)++;
                        if (input[*cursor] == 't')
                        {
                            (*cursor)++;
                            return 0;
                        }
                        else
                            return -1;
                    }
                    else
                        return -1;
                }
                else
                    return -1;
            }
            else
                return -1;
        }
        else
            return -1;
    }
    else if (token == OPAR)
    {
        if (input[*cursor] == '(')
        {
            (*cursor)++;
            return 0;
        }
        else
            return -1;
    }
    else if (token == COMMA)
    {
        if (input[*cursor] == ',')
        {
            (*cursor)++;
            return 0;
        }
        else
            return -1;
    }
    else if (token == CPAR)
    {
        if (input[*cursor] == ')')
        {
            (*cursor)++;
            return 0;
        }
        else
            return -1;
    }
    else if (token == INTEGER)
    {
        if (isdigit(input[*cursor]))
        {
            int i = 0;
            int value = 0;
            while (isdigit(input[*cursor + i]) && i < 3)
            {
                if (i != 0)
                    value *= 10;

                char c = input[*cursor + i];
                value += c - '0';
                i++;
            }
            (*cursor) += i;

            return value;
        }
        else
            return -1;
    }
    else if (token == END)
    {
        if (input[*cursor] == '\0')
        {
            (*cursor)++;
            return 0;
        }
        else
            return -1;
    }
    else if (token == ERROR)
    {
        (*cursor)++;
        return 0;
    }
    else
    {
        return -1;
    }
}

int parseMul(const char *input, int *cursor)
{
    int token = getToken(input, cursor);
    if (token == MUL)
    {
        eatToken(input, cursor, MUL);
        token = getToken(input, cursor);
        if (token == OPAR)
        {
            eatToken(input, cursor, OPAR);
            token = getToken(input, cursor);
            if (token == INTEGER)
            {
                int a = eatToken(input, cursor, INTEGER);
                token = getToken(input, cursor);
                if (token == COMMA)
                {
                    eatToken(input, cursor, COMMA);
                    token = getToken(input, cursor);
                    if (token == INTEGER)
                    {
                        int b = eatToken(input, cursor, INTEGER);
                        token = getToken(input, cursor);
                        if (token == CPAR)
                        {
                            eatToken(input, cursor, CPAR);
                            return a * b;
                        }
                    }
                }
            }
        }
    }

    return -1;
}

int parseDoDont(const char *input, int *cursor)
{
    int token = getToken(input, cursor);
    if (token == DO)
    {
        eatToken(input, cursor, DO);
        token = getToken(input, cursor);
        if (token == OPAR)
        {
            eatToken(input, cursor, OPAR);
            token = getToken(input, cursor);
            if (token == CPAR)
            {
                eatToken(input, cursor, CPAR);
                return 1;
            }
        }
    }
    else if (token == DONT)
    {

        eatToken(input, cursor, DONT);
        token = getToken(input, cursor);
        if (token == OPAR)
        {
            eatToken(input, cursor, OPAR);
            token = getToken(input, cursor);
            if (token == CPAR)
            {
                eatToken(input, cursor, CPAR);
                return 0;
            }
        }
    }
    printf("DEBUG: %d\n", *cursor);
    return -1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage : day3 [input file]\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == 0)
    {
        printf("Could not open file : %s\n", argv[1]);
        return 0;
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *input = malloc(size + 1);
    fread(input, 1, size, file);
    input[size] = '\0';

    fclose(file);

    // Part 1 ////////////////////////////////////////////////////////////
    int token = 0;
    int cursor = 0;
    long sum = 0;
    while ((token = getToken(input, &cursor)) != END)
    {
        if (token == MUL)
        {
            int res = parseMul(input, &cursor);
            if (res != -1)
                sum += res;
        }
        else
        {
            eatToken(input, &cursor, token);
        }
    }

    printf("%ld\n", sum);
    //////////////////////////////////////////////////////////////////////

    // Part 2 ////////////////////////////////////////////////////////////
    token = 0;
    cursor = 0;
    sum = 0;
    int enable = 1;
    while ((token = getToken(input, &cursor)) != END)
    {
        if (token == MUL)
        {
            int res = parseMul(input, &cursor);
            if (res != -1 && enable)
                sum += res;
        }
        else if (token == DO || token == DONT)
        {
            int res = parseDoDont(input, &cursor);
            if (res != -1)
                enable = res;
        }
        else
        {
            eatToken(input, &cursor, token);
        }
    }

    printf("%ld\n", sum);
    //////////////////////////////////////////////////////////////////////

    free(input);

    return 0;
}