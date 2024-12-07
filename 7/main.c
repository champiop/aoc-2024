#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int evaluate(long *operands, long result, int i, size_t size)
{
    if (operands[i] < 0 || operands[i] > result)
        return 0;

    if (operands[i + 1] == -1)
        return operands[i] == result ? 1 : 0;

    long cpy[size];
    memcpy(cpy, operands, size * sizeof(long));

    long cpy2[size];
    memcpy(cpy2, operands, size * sizeof(long));

    cpy[i + 1] = cpy[i] * cpy[i + 1];
    if (evaluate(cpy, result, i + 1, size))
        return 1;

    cpy2[i + 1] = cpy2[i] + cpy2[i + 1];
    return evaluate(cpy2, result, i + 1, size);
}

int evaluate2(long *operands, long result, int i, size_t size)
{
    if (operands[i] < 0 || operands[i] > result)
        return 0;

    if (operands[i + 1] == -1)
        return operands[i] == result ? 1 : 0;

    long cpy[size];
    memcpy(cpy, operands, size * sizeof(long));

    long cpy2[size];
    memcpy(cpy2, operands, size * sizeof(long));

    operands[i + 1] = operands[i] * operands[i + 1];
    if (evaluate2(operands, result, i + 1, size))
        return 1;

    cpy[i + 1] = cpy[i] + cpy[i + 1];
    if (evaluate2(cpy, result, i + 1, size))
        return 1;

    long tmp = 0;
    char tmpStr[100];
    sprintf(tmpStr, "%ld%ld", cpy2[i], cpy2[i + 1]);
    sscanf(tmpStr, "%ld", &tmp);
    cpy2[i + 1] = tmp;
    return evaluate2(cpy2, result, i + 1, size);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage : day7 [input file]\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == 0)
    {
        printf("Could not open file : %s\n", argv[1]);
        return 0;
    }

    size_t maxOperandCount = 0;
    size_t maxCharCount = 0;
    size_t equationCount = 0;
    size_t operandCount = 0;
    size_t charCount = 0;
    int startCountingOperands = 0;
    char c;

    while (!feof(file))
    {
        c = fgetc(file);
        charCount++;

        if (c == '\n')
        {
            if (operandCount > maxOperandCount)
                maxOperandCount = operandCount;

            if (charCount > maxCharCount)
                maxCharCount = charCount;

            operandCount = 0;
            startCountingOperands = 0;
            charCount = 0;
            equationCount++;
            continue;
        }
        else if (c == ':')
        {
            startCountingOperands = 1;
        }
        else if (c == ' ' && startCountingOperands)
        {
            operandCount++;
        }
    }

    rewind(file);

    long equations[equationCount][maxOperandCount + 1];
    long result[equationCount];
    for (int j = 0; j < equationCount; j++)
    {
        char equation[maxCharCount + 1];
        int i = 0;

        fgets(equation, maxCharCount + 1, file);

        int tmp = 0;
        int cursor = 0;
        sscanf(equation, "%ld:%n", &result[j], &cursor);
        while (sscanf(equation + cursor, " %ld%n", &equations[j][i], &tmp) == 1)
        {
            cursor += tmp;
            i++;
        }

        equations[j][i] = -1;
    }

    // Part 1 ////////////////////////////////////////////////////////////
    long count = 0;
    for (int j = 0; j < equationCount; j++)
    {
        if (evaluate(equations[j], result[j], 0, maxOperandCount + 1))
            count += result[j];
    }

    printf("%ld\n", count);
    //////////////////////////////////////////////////////////////////////

    // Part 2 ////////////////////////////////////////////////////////////
    count = 0;
    for (int j = 0; j < equationCount; j++)
    {
        // printf("Equation %d/%lu\n", j + 1, equationCount);
        if (evaluate2(equations[j], result[j], 0, maxOperandCount + 1))
            count += result[j];
    }

    printf("%ld\n", count);
    //////////////////////////////////////////////////////////////////////

    fclose(file);

    return 0;
}