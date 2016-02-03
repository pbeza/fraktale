#include "fract.h"
#include <cstdio>

point_container::point_container( size_t w, size_t h )
{
    width = w;
    height = h;
    data.resize( w * h );
}

point_container::point_container( const std::vector<float> &dat, size_t w, size_t h )
{
    data = dat;
    width = w;
    height = h;
    if( data.size() < w * h ) {
        throw "Not enough data, needs to be at least width*height";
    }
}

float point_container::get( size_t x, size_t y ) const
{
    return data[x * height + y];
}

void point_container::set( size_t x, size_t y, float val )
{
    data[x * height + y] = val;
}

void print_container( const point_container &pc )
{
    for( size_t y = 0; y < pc.h(); y++ ) {
        for( size_t x = 0; x < pc.w(); x++ ) {
            printf( "%.1f ", pc.get( x, y ) );
        }
        printf( "\n" );
    }
}

int main( int argc, char **argv )
{
    point_container test( 4, 3 );
    test.set( 1, 1, 1.0f );
    print_container( test );
    printf( "\n\n" );
    point_container test2 = single_iter( test, 0.0 );
    print_container( test2 );
    return 0;
}

point_container single_iter( const point_container &points, float s )
{
    size_t sectors_w = points.w() - 1;
    size_t sectors_h = points.h() - 1;
    size_t new_width = sectors_w * sectors_w;
    size_t new_height = sectors_h * sectors_h;
    point_container new_data( new_width, new_height );

    const float w = 1.0f;
    const float h = 1.0f;

    const float dx = 1.0f / sectors_w;
    const float dy = 1.0f / sectors_h;

    //const float a = dx / xm;
    //const float c = dy / ym;

    for( size_t i = 0; i < sectors_w - 1; i++ ) {
        //const float x = (float)i / sectors_w;
        //const float b = x;
        for( size_t j = 0; j < sectors_h - 1; j++ ) {
            //const float y = (float)j / sectors_h;
            //const float d = y;

            // Lower left, lower right, upper left, upper right
            const float ll = points.get( i, j );
            const float lr = points.get( i + 1, j );
            const float ul = points.get( i, j + 1 );
            const float ur = points.get( i + 1, j + 1 );

            {
                // The first triangle of the quad
                const float dzx = lr - ll;
                const float dzy = ul - ll;

                const float e = dzx * (1 - s) / w;
                const float f = dzy * (1 - s) / h;

                const float h = ll;
                for( size_t ii = 0; ii < points.w() / 2 + 1; ii++ ) {
                    const float lx = (float)ii / points.w();
                    for( size_t jj = 0; jj < points.h() / 2 + 1; jj++ ) {
                        const float ly = (float)ii / points.h();

                        const float lz = points.get( ii, jj );

                        //const float newx = (lx * a) + b;
                        //const float newy = (ly * c) + d;
                        const float newz = (e * lx) + (f * ly) + (s * lz) + h;
                        new_data.set( i * points.w() + ii,  j * points.h() + jj, newz );
                    }
                }
            }

            if( false )
            {
                // The second triangle of the quad
                // Kinda inverted
                const float dzx = ur - ul;
                const float dzy = ur - lr;

                const float e = dzx * (1 - s) / w;
                const float f = dzy * (1 - s) / h;

                const float h = ur;
                for( size_t ii = points.w() / 2 + 1; ii < points.w(); ii++ ) {
                    const float lx = (float)ii / points.w();
                    for( size_t jj = points.h() / 2 + 1; jj < points.h(); jj++ ) {
                        const float ly = (float)ii / points.h();
                        const float lz = points.get( ii, jj );
                        const float newz = (e * lx) + (f * ly) + (s * lz) + h;
                        new_data.set( i * points.w() + ii,  j * points.h() + jj, newz );
                    }
                }
            }
        }
    }

    return new_data;
}
