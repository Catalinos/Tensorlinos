<div align="center">
<h1>TensorLinos</h1>

![Logo](/images/logo.png)

</div>

# :pencil: Description
:construction: This is a work in progress :construction:

This is my custom machine learning shared library in C languuage

# :rocket: Getting Started

## :gear: Dependencies

You just need make, gcc and a linux

## :chart_with_upwards_trend: Progress so far
- Created a shared library called _linreg_
- Ability to initialize a custom liniar regression model
- Ability to load a dataset that is read from a file inside the _'artificial_data'_ directory
- FeedForward process
- Few loss functions like MeanSquaredError and MeanAbsoluteError
- Added the full training ability

## :hammer_and_wrench: To do next
- Add more loss functions
- Implement activation functions
- Implement optimizers
- Cleanup the code

# :computer: Functions Documentation

## Dataset Format

For the linear regression model to function correctly, the dataset should adhere to the following format:

    First Line: The total number of data entries (rows) in the dataset.

    Subsequent Lines: Each line represents a single data entry consisting of an input feature (x) and the corresponding target variable (y), separated by a comma.
### Example
```
22
97,231.218
167,398.373
117,283.222
...
122,289.842
59,162.754
```

### `loadDataset`

**Purpose**: Loads the dataset from a specific file.

**Inputs**:
- `filename` (char * ): String that contains the name of the file to read the data.

**Outputs**: Returns an instance of `DataSet` with properties initialized.

**Example Call**:
```c
DataSet dataset = loadDataset(filename);
```

### `initializeModel`

**Purpose**: Initializes a linear model with random weights.

**Inputs**:
- `grade` (int): The degree of the polynomial to be used in the model.
- `activation` (enum ActivationFunction): The type of activation function to use.

! The choice of the activation function are the following:
```c
enum ActivationFunction{
    ReLU,
    Sigmoid,
    Softmax,
    Linear,
};
```
**Outputs**: Returns an instance of `LiniarModel` with properties initialized.

**Example Call**:
```c
LiniarModel model = initializeModel(2, Sigmoid);
