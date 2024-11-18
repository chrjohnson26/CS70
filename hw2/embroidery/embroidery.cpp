#include <cs70/turtle.hpp>
#include "embroidery.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cstddef>
using namespace std;

// Draws a rectangle based on the user's input
void rect(Turtle& t, float width , float height) {
    // We need to put the pen down in order to draw
    t.pendown();
    t.forward(width);
    t.left(90);
    t.forward(height);
    t.left(90);
    t.forward(width);
    t.left(90);
    t.forward(height);
    t.penup();
}

// Draws a rectangle with predetermined attributes and a message
void meetTurtle() {
    // Sets turtle object's attributes
    constexpr float PATCH_WIDTH = 50;
    constexpr float PATCH_HEIGHT = 40;
    constexpr int EDGE_STEP = 2;
    constexpr int TEXT_STEP = 1;
    constexpr float FONT_SCALE = 1.0;
    constexpr float SATIN_DELTA = 0.3;
    // Initializes turtle object in order to embroider
    Turtle t;
    t.setStepSize(EDGE_STEP);
    t.satinon(SATIN_DELTA);
    rect(t, PATCH_WIDTH, PATCH_HEIGHT);
    t.setStepSize(TEXT_STEP);
    // Assigns placement for first message
    t.gotopoint(PATCH_WIDTH/4, PATCH_HEIGHT-20);
    t.pendown();
    t.displayMessage("CJ", FONT_SCALE);
    t.penup();
    // Assigns placement for second message
    t.gotopoint(PATCH_WIDTH/4, PATCH_HEIGHT-10);
    t.pendown();
    t.displayMessage("CS", FONT_SCALE);
    t.penup();
    // Assigns placement for third message
    t.gotopoint(PATCH_WIDTH/4, PATCH_HEIGHT-30);
    t.pendown();
    t.displayMessage("SD", FONT_SCALE);
    t.penup();
    t.end();
    // Saves our results into a file
    t.save("meet_turtle.dst");
}

// Plots example data
void plotExampleData() {
    // Assigns constants and file names
    constexpr int PLOT_STEP = 1;
    constexpr int NUM_DATA_POINTS = 59;
    const string INPUT_NAME = "/home/student/data/hw2/us_population_growth.txt";
    const string OUTPUT_NAME = "example_data.dst";
    constexpr float PATCH_WIDTH = 50;
    constexpr float PATCH_HEIGHT = 40.0;
    constexpr int EDGE_STEP = 8;
    constexpr float SATIN_DELTA = 0.3;
    constexpr float FONT_SCALE = 1.0;
    // Creates an array in order to store the data
    float data[NUM_DATA_POINTS];
    // Creates a variable that will track the largest value
    float max = 0;
    ifstream input{INPUT_NAME};
    // Iterates through array
    for (int i = 0; i < NUM_DATA_POINTS; i++) {
        // Reads each line of data
        input >> data[i];
        // Finds largest value
        if (data[i] > max) {
            max = data[i];
        }
    }
    // Lets system know we are done reading the file
    input.close();

    // Initializes turtle object to draw rectangle that will show the data
    Turtle t;
    t.setStepSize(EDGE_STEP);
    t.satinon(SATIN_DELTA);
    rect(t, PATCH_WIDTH, PATCH_HEIGHT);
    t.setStepSize(PLOT_STEP);
    // Calculates width for graph
    float availableWidth = (PATCH_WIDTH - EDGE_STEP)/NUM_DATA_POINTS;

    // Calculates height in order to normalize data with respect to max
    float availableHeight = (PATCH_HEIGHT - EDGE_STEP)/max;
    float offset = 1.5;
    t.gotopoint(offset, data[0]*availableHeight);
    t.pendown();
    // Normalizes and graphs all our data points
    for (int i = 1; i < NUM_DATA_POINTS; i++) {
        t.gotopoint((availableWidth * i) + offset, availableHeight * data[i]);
    }

    t.penup();
    // Goes to the point which when drawn will align the first 9 with the peak
    t.gotopoint(PATCH_WIDTH-30, PATCH_HEIGHT-7);
    t.pendown();
    t.displayMessage("1992", FONT_SCALE);
    t.penup();
    t.end();
    t.save(OUTPUT_NAME);
}

// Plots student data
void plotStudentData() {
    // Assigns constants and file names
    constexpr int PLOT_STEP = 1;
    constexpr int NUM_DATA_POINTS = 52;
    const string INPUT_NAME = "student_data.txt";
    const string OUTPUT_NAME = "student_data.dst";
    constexpr float PATCH_WIDTH = 50;
    constexpr float PATCH_HEIGHT = 40.0;
    constexpr int EDGE_STEP = 2;
    constexpr float SATIN_DELTA = 0.3;
    constexpr float FONT_SCALE = 0.85;
    constexpr float HEIGHT_SCALE = 10;
    // Creates an array in order to store the data
    float data[NUM_DATA_POINTS];
    // Creates a variable that will track the largest value
    float max = 0;
    ifstream input{INPUT_NAME};
    // Iterates through array
    for (int i = 0; i < NUM_DATA_POINTS; i++) {
        // Reads each line of data
        input >> data[i];
        // Finds largest value
        if (data[i] > max) {
            max = data[i];
        }
    }
    // Lets system know we are done reading the file
    input.close();

    // Initializes turtle object to draw rectangle that will show the data
    Turtle t;
    t.setStepSize(EDGE_STEP);
    t.satinon(SATIN_DELTA);
    rect(t, PATCH_WIDTH, PATCH_HEIGHT);
    t.setStepSize(PLOT_STEP);
    // Calculates width for graph
    float availableWidth = (PATCH_WIDTH - EDGE_STEP)/NUM_DATA_POINTS;

    // Calculates height in order to normalize data with respect to max
    float availableHeight = (PATCH_HEIGHT - HEIGHT_SCALE)/max;
    float offset = 1.5;
    t.gotopoint(offset, data[0]*availableHeight);
    t.pendown();
    // Normalizes and graphs all our data points
    for (int i = 1; i < NUM_DATA_POINTS; i++) {
        t.gotopoint((availableWidth * i) + offset, availableHeight * data[i]);
    }

    t.penup();
    // Goes to the point which when drawn will align the first 9 with the peak
    t.gotopoint(PATCH_WIDTH-42, PATCH_HEIGHT-7);
    t.pendown();
    t.displayMessage("Numbers!", FONT_SCALE);
    t.penup();
    t.end();
    t.save(OUTPUT_NAME);
}
