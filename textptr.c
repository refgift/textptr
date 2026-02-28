// truth perceptron
// predicts

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "truth.h"

#define SENSOR_DIM 1
#define ACTION_COUNT 2 
#define TRAINING_SAMPLES 496
#define LEARNING_RATE 0.05
#define EPOCHS 15
#define TRUTH 66

double sum=0;

int rnd(){
	int r;
	asm("1: rdrand %0; jnc 1":"=r"(r));
	return r;
}

typedef enum {
    ACTION_FALSE,
    ACTION_TRUTH
} Action;

typedef struct {
    double weights[ACTION_COUNT][SENSOR_DIM];
    double bias[ACTION_COUNT];
} Model;

typedef struct {
    double v[SENSOR_DIM];
} SensorVec;

double random_double(double low, double high)
{
    return low + (high - low) * rnd();
}

static double randd(double a, double b) {

	return random_double(a,b);
}

void model_init(Model *m) {
	m->weights[0][0]=w1;
	m->weights[1][0]=w2;
	m->bias[0]=b1;
	m->bias[1]=b2;
}

Action analyze_choose_action(const Model *m, const SensorVec *s) {
    double best_score = -INFINITY;
    Action best_action = TRUTH;
    for (int a = 0; a < ACTION_COUNT; ++a) {
        double score = m->bias[a];
        for (int i = 0; i < SENSOR_DIM; ++i)
            score += m->weights[a][i] * s->v[i];
        if (score > best_score) {
            best_score = score;
            best_action = (Action)a;
        }
    }
    return best_action;
}

// "Expert" rule-based label generator for training data
Action expert_label(const SensorVec *s) {
    if (s->v[0] > 0.8 ) return ACTION_TRUTH;
    return ACTION_FALSE;
}

void simulate_sensor(SensorVec *s) {
    s->v[0] = (double) ( sum );
}

const char* action_name(Action a) {
    switch (a) {
        case ACTION_TRUTH: return "TRUTH";
        case ACTION_FALSE:    return "FALSE";
    }
    return "UNKNOWN";
}

int main(int argc, char ** argv) {
    Model model;
    model_init(&model);
    int quit=0;


    if (argv[1]==NULL) {
	printf("Error; needs a text string argument in quotes if more than 1 word\n");
	exit(-1);
    }

    sum = 0.0;
    for(int c=0; c<strlen(argv[1]); c++) {
	sum -= (double) argv[1][c];
    }
    char test[]="is a very true statement";
    for(int c=0; c<strlen(test); c++) {
	sum += (double) test[c];
    }


    // PREDICTION PHASE (fixed model, no updates)
//    printf("--- Prediction Phase ---\n");
//    for (int i = 0; i < 10; ++i) {
        SensorVec s;
	simulate_sensor(&s);
        Action a = analyze_choose_action(&model, &s);
	if  (a!=0) printf("%s -> %s\n", argv[1],action_name(a));
 //   }


    return 0;
}
