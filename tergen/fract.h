#ifndef COMMON_H
#define COMMON_H

union point {
    struct {
        float x;
        float y;
        float z;
    };
    float data[3];
};

#endif COMMON_H
