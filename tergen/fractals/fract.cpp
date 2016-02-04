#include "fract.h"
#include <cstdio>
#include <cmath>

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
    const int size = 5;
    point_container test( size, size );
    test.set( size/2, size/2, 1.0f );
    print_container( test );
    printf( "\n\n" );
    point_container test2 = multi_iter( test, 2, 0.5 );
    //print_container( test2 );
    printf( "\n\n" );
    box_dimension( test2, 9 );
    return 0;
}

point_container multi_iter( const point_container &points, size_t iters, float s )
{
    point_container pts = points;

    while( true ) {
        if( iters == 0 ) {
            return pts;
        }

        pts = std::move( single_iter( pts, s ) );
        iters--;
    }
}

point_container single_iter( const point_container &points, float s )
{
    size_t sectors_w = points.w() - 1;
    size_t sectors_h = points.h() - 1;
    size_t new_width = sectors_w * sectors_w + 1;
    size_t new_height = sectors_h * sectors_h + 1;
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
//printf( "Sector %lu,%lu\n", i, j );
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

//printf( "First e:%.2f f:%.2f h: %.2f\n", e, f, h );

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

            if( true )
            {
                // The second triangle of the quad
                // Kinda inverted
                const float dzx = -(ur - ul);
                const float dzy = -(ur - lr);

                const float e = dzx * (1 - s) / w;
                const float f = dzy * (1 - s) / h;

                const float h = ur;

//printf( "Second e:%.2f f:%.2f h: %.2f\n", e, f, h );

                for( size_t ii = points.w() / 2 + 1; ii < points.w(); ii++ ) {
                    const float lx = 1.0f - (float)ii / points.w();
                    for( size_t jj = points.h() / 2 + 1; jj < points.h(); jj++ ) {
                        const float ly = 1.0f - (float)ii / points.h();
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

inline size_t index_from_3d( int x, int y, int z, int side_len )
{
    if( x < 0 || y < 0 || z < 0 || side_len < 0 ) {
        printf("err");
        return 0;
    }
    size_t ret = ((x * side_len) + y) * side_len + z;
    if( ret >= side_len * side_len * side_len ) {
        return 0;
    }

    return (size_t)ret;
}

inline void draw( int x, int y, int z, int side_len,
                  std::vector<bool> &boxed, size_t &count )
{
    size_t index = index_from_3d( x, y, z, side_len );
    if( !boxed[index] ) {
        count++;
        boxed[index] = true;
    }
}

void line( int x1, int y1, int z1,
           const int x2, const int y2, const int z2,
           int side_len, std::vector<bool> &boxed, size_t &count )
{
    
    int i, dx, dy, dz, l, m, n, x_inc, y_inc, z_inc, err_1, err_2, dx2, dy2, dz2;

    int x = x1;
    int y = y1;
    int z = z1;
    dx = x2 - x1;
    dy = y2 - y1;
    dz = z2 - z1;
    x_inc = (dx < 0) ? -1 : 1;
    l = abs(dx);
    y_inc = (dy < 0) ? -1 : 1;
    m = abs(dy);
    z_inc = (dz < 0) ? -1 : 1;
    n = abs(dz);
    dx2 = l << 1;
    dy2 = m << 1;
    dz2 = n << 1;
    
    if ((l >= m) && (l >= n)) {
        err_1 = dy2 - l;
        err_2 = dz2 - l;
        for (i = 0; i < l; i++) {
            draw( x, y, z, side_len, boxed, count );
            if (err_1 > 0) {
                y += y_inc;
                err_1 -= dx2;
            }
            if (err_2 > 0) {
                z += z_inc;
                err_2 -= dx2;
            }
            err_1 += dy2;
            err_2 += dz2;
            x += x_inc;
        }
    } else if ((m >= l) && (m >= n)) {
        err_1 = dx2 - m;
        err_2 = dz2 - m;
        for (i = 0; i < m; i++) {
            draw( x, y, z, side_len, boxed, count );
            if (err_1 > 0) {
                x += x_inc;
                err_1 -= dy2;
            }
            if (err_2 > 0) {
                z += z_inc;
                err_2 -= dy2;
            }
            err_1 += dx2;
            err_2 += dz2;
            y += y_inc;
        }
    } else {
        err_1 = dy2 - n;
        err_2 = dx2 - n;
        for (i = 0; i < n; i++) {
            draw( x, y, z, side_len, boxed, count );
            if (err_1 > 0) {
                y += y_inc;
                err_1 -= dz2;
            }
            if (err_2 > 0) {
                x += x_inc;
                err_2 -= dz2;
            }
            err_1 += dy2;
            err_2 += dx2;
            z += z_inc;
        }
    }
    draw( x, y, z, side_len, boxed, count );
}

inline void set_indices( size_t i, size_t j,
                         size_t &xindex, size_t &yindex, size_t &zindex,
                         size_t side_len,
                         const point_container &points )
{
    const float x = (float)i / points.w();
    const float y = (float)j / points.h();
    const float z = points.get( i, j );
    xindex = (size_t)( x * side_len );
    yindex = (size_t)( y * side_len );
    zindex = (size_t)( z * side_len );
}

float box_dimension( const point_container &points, const size_t subdiv )
{
    int last_side_len = 2 << subdiv;
    int cur_side_len = last_side_len / 2;
    std::vector<bool> last;
    std::vector<bool> cur;
    std::vector<size_t> counts;
    std::vector<size_t> lens;
    size_t cur_count = 0;
    // 3 sides of the cube
    last.resize( last_side_len * last_side_len * last_side_len );
    cur.resize( cur_side_len * cur_side_len * cur_side_len );

    for( size_t i = 1; i < points.w() - 1; i++ ) {
        for( size_t j = 1; j < points.h() - 1; j++ ) {
            size_t xindex = 0;
            size_t yindex = 0;
            size_t zindex = 0;
            size_t xindex_n = 0;
            size_t yindex_n = 0;
            size_t zindex_n = 0;
            set_indices( i, j, xindex, yindex, zindex, last_side_len, points );

            set_indices( i - 1, j, xindex_n, yindex_n, zindex_n, last_side_len, points );
            line( xindex, yindex, zindex, xindex_n, yindex_n, zindex_n, last_side_len, last, cur_count );
            set_indices( i + 1, j, xindex_n, yindex_n, zindex_n, last_side_len, points );
            line( xindex, yindex, zindex, xindex_n, yindex_n, zindex_n, last_side_len, last, cur_count );
            set_indices( i, j - 1, xindex_n, yindex_n, zindex_n, last_side_len, points );
            line( xindex, yindex, zindex, xindex_n, yindex_n, zindex_n, last_side_len, last, cur_count );
            set_indices( i, j + 1, xindex_n, yindex_n, zindex_n, last_side_len, points );
            line( xindex, yindex, zindex, xindex_n, yindex_n, zindex_n, last_side_len, last, cur_count );
        }
    }

    counts.push_back( cur_count );
    lens.push_back( last_side_len );
    for( size_t cur_div = subdiv - 1; cur_div > 2; cur_div-- ) {
        cur.clear();
        cur.resize( cur_side_len * cur_side_len * cur_side_len );

        cur_count = 0;

        for( size_t i = 0; i < last_side_len; i++ ) {
            for( size_t j = 0; j < last_side_len; j++ ) {
                for( size_t k = 0; k < last_side_len; k++ ) {
                    const size_t old_index = index_from_3d( i, j, k, last_side_len );
                    if( !last[old_index] ) {
                        continue;
                    }

                    const size_t new_index = index_from_3d( i / 2, j / 2, k / 2, cur_side_len );
                    if( !cur[new_index] ) {
                        cur_count++;
                    }

                    cur[new_index] = true;
                }
            }
        }

        counts.push_back( cur_count );
        lens.push_back( cur_side_len );
        last = std::move( cur );
        last_side_len /= 2;
        cur_side_len /= 2;
    }

    for( size_t i = 0; i < counts.size(); i++ ) {
        const float boxlen = 1.0f / lens[i];
        const float mink = counts[i] > 0 ? log( counts[i] ) / log( 1.0 / boxlen ) : 0.0f;
        printf( "%lu na %lu, minkowski %.2f\n", counts[i], lens[i] * lens[i] * lens[i], mink );
    }

    return 0;
}
