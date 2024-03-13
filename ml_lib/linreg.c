#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"linreg.h"



LiniarModel initializeModel(int grade, enum ActivationFunction activation){
    
    LiniarModel liniar_model;

    liniar_model.activation = activation;
    liniar_model.grade = grade;
    liniar_model.weights = malloc(grade * sizeof(float));

    srand(time(0));
    int upper = 100;
    int lower = 0;
    for(int i = 0; i < grade; i++){
        liniar_model.weights[i] = (float)((rand() % (upper - lower + 1)) + lower);
        // liniar_model.weights[i] = (float) rand();
    }
    liniar_model.bias = (float) ((rand()%(upper-lower+1)) + lower);
    liniar_model.train=train;
    return liniar_model;
}

void showValuesW(const LiniarModel model){
    printf("Learning function is the following: \nf(x)=");

    for(int i = 0; i < model.grade; i++){
        printf("%.4f*(x)^%d + ", model.weights[i], i);
    }
    printf("%.4f", model.bias);
    printf("\n");
    printf("With the activation function of: %s \n", ActivationFunctionName[model.activation]);
}

int getRandomInt(int lower, int upper){
    return (int) ((rand()%(upper - lower + 1)) + lower);
}

float sigmoidf(float number){
    return (1 / (1 + powf(EULER_NUMBER_F, -number)));
}

float computeMSE(const float *predicted, const DataSet dataset){
    float loss = 0;
    
    for(int i=0;i<dataset.dimension; ++i){
        float error = predicted[i] - dataset.X[i][1];
        loss += pow(error,2);
    }
    loss /= 2*dataset.dimension;

    return loss;
}

float computeMAE(const float *predicted, const DataSet dataset){
    float loss = 0;
    
    for(int i=0;i<dataset.dimension; ++i){
        loss += abs(predicted[i] - dataset.X[i][1]);
    }
    loss /= dataset.dimension;

    return loss;
}

float computeLoss(enum LossFunction losstype, const float *predicted, const DataSet dataset){
    float loss = 0;
    switch(losstype){
        case 0:
            loss = computeMSE(predicted, dataset);
            break;
        case 1:
            loss = computeMAE(predicted, dataset);
            break;
        default:
            loss = -1;
    }
    return loss;
}

float *computeGradient(const DataSet dataset, float* predicted, float alpha, int grade, float *weights, float bias){
    float *returned_values = calloc((grade+1), sizeof(float));
    
    for(int i=0;i<grade;++i){
        returned_values[i] = weights[i];
        float grad = 0;

        for(int j = 0; j < dataset.dimension; ++j){
            grad +=  (predicted[j] - dataset.X[j][1]) * dataset.X[j][0];
        }

        grad /= dataset.dimension;

        returned_values[i] = weights[i] - (alpha * grad);

    }
    float bias_grad = 0;
    for(int j = 0; j < dataset.dimension; ++j){
        bias_grad +=  (predicted[j] - dataset.X[j][1]);
    }
    bias_grad /= dataset.dimension;
    returned_values[grade] = bias - (alpha * bias_grad);
    return returned_values;
}


void train(LiniarModel *model, const DataSet dataset, enum LossFunction lossfunction, float alpha, int epochs){

    int x_length = dataset.dimension;
    model->loss = lossfunction;
    float *result = calloc(x_length, sizeof(float));
    float best_loss = 0;
    for(int steps=0;steps<epochs;++steps){

        for(int i = 0; i < x_length; ++i){
            result[i] = 0;
            for(int j=0;j<model->grade; ++j){
                result[i] = model->weights[j] * dataset.X[i][0];
            }
        }
        float loss = computeLoss(lossfunction, result, dataset);
        // printf("Loss %s after first training is: %f\n", LossFunctionNAME[model->loss], loss);

        float *new_weights = computeGradient(dataset, result, alpha, model->grade, model->weights, model->bias);

        // printf("The new parameters are: ");
        for(int i=0; i < model->grade; ++i){
            model->weights[i] = new_weights[i];
            // printf("%.2f*(x)^%d + ", new_weights[i], i);
        }
        model->bias = new_weights[model->grade];
        // printf("%.2f\n", model->bias);

        if(abs(best_loss-loss) < 1){
            printf("-------------------------------------------\n");
            printf("The model finished training afted %d steps with the loss of %s = %.3f\n", steps, LossFunctionNAME[model->loss], best_loss);
            printf("-------------------------------------------\n");

            break;
        }
        best_loss = loss;

    }

    free(result);
}

float *predict(const LiniarModel model, const DataSet dataset){

    int x_length = dataset.dimension;

    float *result = calloc(x_length, sizeof(float));
    for(int i = 0; i < x_length; ++i){
        result[i] = 0;
        for(int j=0;j<model.grade; ++j){
            result[i] += model.weights[j] * dataset.X[i][0];
        }
    }

    return result;
}

void compare5Samples(const DataSet dataset, float *result){
    
    printf("----------------------Comparison---------------------\n");

    printf("Index \tTruth \t\tPredicted \tDifference\n");
    for(int i = 0; i<5; ++i){
        int index = getRandomInt(0, dataset.dimension);
        float diff = dataset.X[index][1] - result[index];
        printf("%d \t%.3f \t%.3f \t%.3f\n", index, dataset.X[index][1], result[index], diff);
    }
}

void destroyModel(const LiniarModel model){
    free(model.weights);
}

DataSet loadDataset(char *filename){

    DataSet dataset;
    int dimensions;

    FILE *fin = fopen(filename,"r");
    fscanf(fin, "%d", &dimensions);

    dataset.dimension = dimensions;
    dataset.X = (float**)malloc(sizeof(float*)*dimensions);
    
    for(int i=0;i<dimensions;++i){
        dataset.X[i] = (float*)malloc(sizeof(float));
    }

    for(int i=0;i<dimensions; ++i){
        float x,y;
        fscanf(fin,"%f,%f", &x,&y);
        dataset.X[i][0] = x;
        dataset.X[i][1] = y;
    }

    fclose(fin);
    return dataset;

}
void printData(const DataSet dataset){

    for(int i=0; i<dataset.dimension;++i){
        printf("House %d has %.1f square meters and values %.2f thousands dollars\n", i, dataset.X[i][0], dataset.X[i][1]);
    }

}

void printRandomSample(const DataSet dataset){
    srand(time(0));
    int upper = dataset.dimension;
    int lower = 0;
    int rand_index = (rand()%(upper-lower+1)) + lower;
    printf("House %d has %.1f square meters and values %.2f thousands dollars\n", rand_index, dataset.X[rand_index][0], dataset.X[rand_index][1]);
}

void destoryDataSet(DataSet dataset){
    
    for (int i = 0; i < dataset.dimension; i++) {
        free(dataset.X[i]);
    }
    free(dataset.X);
}
