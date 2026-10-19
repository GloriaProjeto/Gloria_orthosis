#pragma once

class LedModel {
private:
    int redPin;
    int greenPin;
    int bluePin;
public:
    void setRed(int value);
    void setGreen(int value);
    void setBlue(int value);

    int getRed();
    int getGreen();
    int getBlue();
};
