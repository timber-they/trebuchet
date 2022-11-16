#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

// Trebuchet values to be parsed
#define TREBUCHET_VALUES 9
#define MAX_NAME_LENGTH 13
#define PI 3.14159265
#define G 9.81

#define ERROR_PARSING 1

typedef struct
{
    // SI values are used -> meters and kilograms
    double weight;
    double counterweight;
    double arm;
    double sling;
    double lever;
    double counterlength;
    double height;
    double angle;
    // Simulation values
    double timeStep;
    // Non-initial values
    double angularVelocity;
    double torque;
    double momentOfInertia;
    double weightAngle;
} Trebuchet;

int solve(FILE *in);
Trebuchet parse(FILE *in);
void print(Trebuchet trebuchet);

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
    print(trebuchet);

    while (trebuchet.angle < 180.0)
    {
        // First some helpful values to be used
        double armWeight = 
            // Law of cosines
            trebuchet.arm*trebuchet.arm +
            trebuchet.sling*trebuchet.sling -
            2*trebuchet.arm*trebuchet.sling *
            cos(PI/180 * (
                180 - trebuchet.angle + trebuchet.weightAngle));
        double armCounterweight =
            // Law of cosines
            trebuchet.lever*trebuchet.lever +
            trebuchet.counterlength*trebuchet.counterlength -
            2*trebuchet.lever*trebuchet.counterlength *
            cos(PI/180 * trebuchet.angle);

        // Calculate moment of inertia
        trebuchet.momentOfInertia =
            // Weight
            trebuchet.weight * armWeight +
            // Counterweight
            trebuchet.counterweight * armCounterweight;

        // Calculate torque
        double gravitationalForceWeight = trebuchet.weight * G
        double gravitationalForceCounterweight = trebuchet.counterweight * G;
        double angularForceCounterWeight =
            cos(PI/180 * (180-trebuchet.angle)) *
            gravitationalForceCounterweight;
    }

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
        else if (!strcmp(name, "counterlength"))
            res.counterlength = value;
        else if (!strcmp(name, "height"))
            res.height = value;
        else if (!strcmp(name, "angle"))
            res.angle = value;
        else if (!strcmp(name, "timeStep"))
            res.timeStep = value;
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

void print(Trebuchet trebuchet)
{
    printf("Weight: %lf\n", trebuchet.weight);
    printf("Counterweight: %lf\n", trebuchet.counterweight);
    printf("Arm: %lf\n", trebuchet.arm);
    printf("Sling: %lf\n", trebuchet.sling);
    printf("Lever: %lf\n", trebuchet.lever);
    printf("Counterlength: %lf\n", trebuchet.counterlength);
    printf("Height: %lf\n", trebuchet.height);
    printf("Angle: %lf\n", trebuchet.angle);
    printf("Angular velocity: %lf\n", trebuchet.angularVelocity);
    printf("Torque: %lf\n", trebuchet.torque);
    printf("Moment of inertia: %lf\n", trebuchet.momentOfInertia);
}

