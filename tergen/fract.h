#ifndef FRACT_H
#define FRACT_H

// Must be square
class point_container {
private:
    std::vector<float> data;
    size_t width;
    size_t height;
public:

    // Data must be filled with >= w*h elements!
    // Will throw otherwise
    point_container( const std::vector<float> &dat, size_t w, size_t h );
    point_container( point_container &&other ) = default;

    float &get( size_t x, size_t y );
    void set( size_t x, size_t y, float val );
    size_t w() const { return width; }
    size_t h() const { return height; }
};

// s must be >-1.0 and <1.0
point_container single_iter( const point_container &points, float s = 0.0f );

#endif FRACT_H
