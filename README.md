Reference - 
- https://github.com/arduino/ArduinoTensorFlowLiteTutorials.git
- https://github.com/arduino/ArduinoTensorFlowLiteTutorials/blob/master/GestureToEmoji/ArduinoSketches

# Table Tennis Shot predictor

This is a deep learning project, that gives output in the form of probability (softmax function).
**Arduino Nano 33 BLE** is used. It is preferred as it has a 9 axis inertial measurement unit (IMU) which means that it includes an accelerometer, a gyroscope, and a magnetometer with 3-axis resolution each. Here in the project, we have only used gyroscope and accelerometer.


IMU_Capture is used to record the data for the gestures.
It is used for recording the gesture data for four simple table tennis movements.

IMU_Classifier predicts the gesture for which the model is trained.
It is used twice - to blink on good shots and show the output in serial monitor.

Link of python code in Google Colab - https://colab.research.google.com/drive/1F2hPw5tTrvfqM9x2fogeiEzbJwia0R8S?usp=sharing
(Also saved as ModelMaking.ipynb)

First two plots are made to visualize the gesture on graph.

The dataset for each gesture is some 3600 lines with 6 columns (3 for gyroscope, 3 for accelerometer). Each dataset contains 30 repetitions of a single gesture. That gives us 120 x 6 matrix (DataFrame) for one movement (120 rows per gesture is set into Arduino Nano 33 BLE).
Data is converted from 3600 x 6 matrix to 30 x 720 matrix to fit the idea of one movement per row. In the 720 columns, 120 x 6 values of a single movement are recorded.
Model is trained on the processed data. 600 epochs were used, which was not really necessary as can be seen from the plots of loss and errors.

Model created is then converted to TensorFlow Lite format with ".tflite" extension.
Since we have to use it in Arduino, the TensorFlow Lite file is then converted into Arduino Header file with ".h" extension.

The "model.h" file is our model, trained on the 4 gestures (30 times each), that is to be uploaded in Arduino with the help if the code IMU_Classifier.

## Generalization of the project
The project here is specific to table tennis as the data of gesture is that of table tennis movements. This project is not limited to table tennis only. 

The IMU_Capture captures the gesture, which can be anything. We have captured 30 good movements of table tennis to with IMU_Capture. These shots are our desired outputs while predicting. As for the generalization, you can take any kind of gesture and make it so that the model recognizes it as some gesture.

Here, only four gestures are taken, and on that, we are predicting the probablity of the four. That can be made into five, six, seven or even more. 

For the data processing part, in the python notebook, you will have to adjust your "GESTURES" list according to the gestures you have captured using Arduino.
