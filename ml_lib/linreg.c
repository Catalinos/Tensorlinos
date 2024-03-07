#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include<time.h>
#include"linreg.h"



LiniarModel initializeModel(int grade, enum ActivationFunction activation){
    
    LiniarModel liniar_model;

    liniar_model.activation = activation;
    liniar_model.grade = grade;
    liniar_model.weights = malloc(grade * sizeof(float));

    srand(time(0));
    int upper = 400;
    int lower = 0;
    for(int i = 0; i < grade; i++){
        liniar_model.weights[i] = (float)((rand() % (upper - lower + 1)) + lower); // Initialize each element to 1
    }
    liniar_model.bias = (rand()%(upper-lower+1)) + lower;
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

float computeMSE(const float *predicted, const DataSet dataset){
    float loss = 0;
    
    for(int i=0;i<dataset.dimension; ++i){
        loss += predicted[i] - dataset.X[i][1];
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

void train(LiniarModel *model, const DataSet dataset, enum LossFunction lossfunction){

    int x_length = dataset.dimension;
    model->loss = lossfunction;
    float *result = calloc(x_length, sizeof(float));
    for(int i = 0; i < x_length; ++i){
        result[i] = 0;
        for(int j=0;j<model->grade; ++j){
            result[i] += model->weights[j] * dataset.X[i][0];
        }
    }
    float loss = computeLoss(lossfunction, result, dataset);
    printf("Loss %s after first training is: %f\n", LossFunctionNAME[model->loss], loss);
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
    
    for (int i = 0; i < dataset.dimension-1; i++) {
        free(dataset.X[i]);
    }
    free(dataset.X);
}
