#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#define TREBUCHET_VALUES 5
#define MAX_NAME_LENGTH 13

#define ERROR_PARSING 1

typedef struct
{
    // SI values are used -> meters and kilograms
    double weight;
    double counterweight;
    double arm;
    double sling;
    double lever;
} Trebuchet;

int solve(FILE *in);
Trebuchet parse(FILE *in);

int main()
{
    FILE *in = fopen("inmain", "r");

    printf("Solution: %d\n", solve(in));

    fclose(in);
    return 0;
}

int solve(FILE *in)
{
    Trebuchet trebuchet = parse(in);
    printf("Arm: %lf\n", trebuchet.arm);
    return -1;
}

Trebuchet parse(FILE *in)
{
    Trebuchet res = {0};
    char *name = malloc((MAX_NAME_LENGTH+1)*sizeof(*name));
    double value = -1;
    for (int i = 0; i < TREBUCHET_VALUES; i++)
    {
        if (fscanf(in, "%s%*[\t ]%lf\n", name, &value) != 2)
        {
            fprintf(stderr, "Couldn't parse input file (invalid number of arguments)!\n");
            free(name);
            exit(ERROR_PARSING);
        }
        if (!strcmp(name, "weight"))
            res.weight = value;
        else if (!strcmp(name, "counterweight"))
            res.counterweight = value;
        else if (!strcmp(name, "arm"))
            res.arm = value;
        else if (!strcmp(name, "sling"))
            res.sling = value;
        else if (!strcmp(name, "lever"))
            res.lever = value;
        else
        {
            fprintf(stderr, "Couldn't parse option '%s'\n", name);
            free(name);
            exit(ERROR_PARSING);
        }
    }
    free(name);
    return res;
}

