#include "fract.h"

point_container::point_container( const std::vector<float> &dat, size_t w, size_t h )
{
    data = dat;
    width = w;
    height = h;
    if( data.size() < w * h ) {
        throw "Not enough data, needs to be at least width*height";
    }
}

point_container single_iter( const point_container &points, float s = 0.0f )
{
    single_iter( points, s, s, s, s );
}

point_container single_iter( const point_container &points, float s11, float s12, float s21, float s22 )
{
    size_t sectors_w = points.w() - 1;
    size_t sectors_h = points.h() - 1;
    size_t new_width = sectors_w * sectors_w;
    size_t new_height = sectors_h * sectors_h;
    std::vector<float> new_data;
    new_data.resize( new_width * new_height );

    const float xm = 1.0f;
    const float ym = 1.0f;

    const float zm = 

    const float dx = 1.0f / sectors_w;
    const float dy = 1.0f / sectors_h;
    dz = z(i) - z(i - 1);

    for( size_t i = 0; i < sectors_w; i++ ) {
        const float x = (float)i / sectors_w;
        for( size_t j = 0; j < sectors_h; j++ ) {
            const float y = (float)j / sectors_h;

            

            a = dx / xm;
            b = (x(n)*x(i-1)-x(1)*x(i)) / xm;
            c = dy / xm - s11(i)*ym/xm - s12(i)*zm/xm;
            e = dz / xm - s21(i)*ym/xm - s22(i)*zm/xm;
            d = y(1) - c*x(1) - s11(i)*y(1) - s12(i)*z(1);
            f = z(1) - e*x(1) - s21(i)*y(1) - s22(i)*x(1);
        }
    }
}
