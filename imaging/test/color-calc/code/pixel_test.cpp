// This file is part of snark, a generic and flexible library for robotics research
// Copyright (c) 2011 The University of Sydney
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. Neither the name of the University of Sydney nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
// GRANTED BY THIS LICENSE.  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
// HOLDERS AND CONTRIBUTORS \"AS IS\" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
// IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "../../../../imaging/color/pixel.h"

#include <gtest/gtest.h>

#include <boost/assign.hpp>

#include <iostream>

TEST( pixel, ctor )
{
    using namespace snark::imaging;
    {
        pixel< unsigned char, ub > p0;
        pixel< comma::uint16, ub > p1;
        pixel< comma::uint32, ub > p2;
        pixel< float,         ub > p3;
        pixel< double,        ub > p4;
    }
    {
        // pixel< unsigned char, uw > p0;
        pixel< comma::uint16, uw > p1;
        pixel< comma::uint32, uw > p2;
        pixel< float,         uw > p3;
        pixel< double,        uw > p4;
    }
    {
        // pixel< unsigned char, ui > p0;
        // pixel< comma::uint16, ui > p1;
        pixel< comma::uint32, ui > p2;
        pixel< float,         ui > p3;
        pixel< double,        ui > p4;
    }
    {
        // pixel< unsigned char,  f > p0;
        // pixel< comma::uint16,  f > p1;
        // pixel< comma::uint32,  f > p2;
        pixel< float,          f > p3;
        pixel< double,         f > p4;
    }
    {
        // pixel< unsigned char,  d > p0;
        // pixel< comma::uint16,  d > p1;
        // pixel< comma::uint32,  d > p2;
        pixel< float,          d > p3;
        pixel< double,         d > p4;
    }
}

TEST( pixel, string )
{
    using namespace snark::imaging;
    {
        std::string s = stringify::from( ub );
        EXPECT_EQ( s, "ub" );
    }
    {
        std::string s = stringify::from( ui );
        EXPECT_EQ( s, "ui" );
    }
    {
        std::string s = stringify::from( d );
        EXPECT_EQ( s, "d" );
    }
    {
        range r = stringify::to( "ub" );
        EXPECT_EQ( r, ub );
    }
    {
        range r = stringify::to( "f" );
        EXPECT_EQ( r, f );
    }
    {
        ASSERT_THROW( stringify::to( "a" ), comma::exception );
    }
}


TEST( pixel, convert )
{
    using namespace snark::imaging;
    {
        pixel< unsigned char, ub > p( 10, 20, 30 );
        {
            pixel< unsigned char, ub > p0( pixel< unsigned char, ub >::convert( p ) );
            EXPECT_EQ( p0.channel0, p.channel0 ); EXPECT_EQ( p0.channel1, p.channel1 ); EXPECT_EQ( p0.channel2, p.channel2 );
            pixel< comma::uint16, ub > p1( pixel< comma::uint16, ub >::convert( p ) );
            EXPECT_EQ( p1.channel0, p.channel0 ); EXPECT_EQ( p1.channel1, p.channel1 ); EXPECT_EQ( p1.channel2, p.channel2 );
            pixel< comma::uint32, ub > p2( pixel< comma::uint32, ub >::convert( p ) );
            EXPECT_EQ( p2.channel0, p.channel0 ); EXPECT_EQ( p2.channel1, p.channel1 ); EXPECT_EQ( p2.channel2, p.channel2 );
            pixel< float,         ub > p3( pixel< float        , ub >::convert( p ) );
            EXPECT_EQ( p3.channel0, p.channel0 ); EXPECT_EQ( p3.channel1, p.channel1 ); EXPECT_EQ( p3.channel2, p.channel2 );
            pixel< double,        ub > p4( pixel< double       , ub >::convert( p ) );
            EXPECT_EQ( p4.channel0, p.channel0 ); EXPECT_EQ( p4.channel1, p.channel1 ); EXPECT_EQ( p4.channel2, p.channel2 );
        }
        {
            double scale = std::numeric_limits< range_traits< uw >::value_t >::max() / std::numeric_limits< range_traits< ub >::value_t >::max();
            pixel< comma::uint16, uw > p1( pixel< comma::uint16, uw >::convert( p ) );
            EXPECT_EQ( p1.channel0, scale * p.channel0 ); EXPECT_EQ( p1.channel1, scale * p.channel1 ); EXPECT_EQ( p1.channel2, scale * p.channel2 );
            pixel< comma::uint32, uw > p2( pixel< comma::uint32, uw >::convert( p ) );
            EXPECT_EQ( p2.channel0, scale * p.channel0 ); EXPECT_EQ( p2.channel1, scale * p.channel1 ); EXPECT_EQ( p2.channel2, scale * p.channel2 );
            pixel< float,         uw > p3( pixel< float        , uw >::convert( p ) );
            EXPECT_EQ( p3.channel0, scale * p.channel0 ); EXPECT_EQ( p3.channel1, scale * p.channel1 ); EXPECT_EQ( p3.channel2, scale * p.channel2 );
            pixel< double,        uw > p4( pixel< double       , uw >::convert( p ) );
            EXPECT_EQ( p4.channel0, scale * p.channel0 ); EXPECT_EQ( p4.channel1, scale * p.channel1 ); EXPECT_EQ( p4.channel2, scale * p.channel2 );
        }
        {
            double scale = std::numeric_limits< range_traits< ui >::value_t >::max() / std::numeric_limits< range_traits< ub >::value_t >::max();
            pixel< comma::uint32, ui > p2( pixel< comma::uint32, ui >::convert( p ) );
            EXPECT_EQ( p2.channel0, scale * p.channel0 ); EXPECT_EQ( p2.channel1, scale * p.channel1 ); EXPECT_EQ( p2.channel2, scale * p.channel2 );
            // floats cannot store ui precisely
            pixel< float,         ui > p3( pixel< float        , ui >::convert( p ) );
            EXPECT_NEAR( p3.channel0, scale * p.channel0, 15 ); EXPECT_NEAR( p3.channel1, scale * p.channel1, 15 ); EXPECT_NEAR( p3.channel2, scale * p.channel2, 15 );
            // but doubles can
            pixel< double,        ui > p4( pixel< double       , ui >::convert( p ) );
            EXPECT_EQ( p4.channel0, scale * p.channel0 ); EXPECT_EQ( p4.channel1, scale * p.channel1 ); EXPECT_EQ( p4.channel2, scale * p.channel2 );
        }
        {
            double scale = 1.0 / std::numeric_limits< range_traits< ub >::value_t >::max();
            // conversions are done in doubles, floats are imprecise
            pixel< float,         f > p3( pixel< float        , f >::convert( p ) );
            EXPECT_NEAR( p3.channel0, scale * p.channel0, 1.0e-8 ); EXPECT_NEAR( p3.channel1, scale * p.channel1, 1.0e-8 ); EXPECT_NEAR( p3.channel2, scale * p.channel2, 1.0e-8 );
            pixel< double,        f > p4( pixel< double       , f >::convert( p ) );
            EXPECT_EQ( p4.channel0, scale * p.channel0 ); EXPECT_EQ( p4.channel1, scale * p.channel1 ); EXPECT_EQ( p4.channel2, scale * p.channel2 );
        }
        {
            double scale = 1.0 / std::numeric_limits< range_traits< ub >::value_t >::max();
            // conversions are done in doubles, floats are imprecise
            pixel< float,         d > p3( pixel< float        , d >::convert( p ) );
            EXPECT_NEAR( p3.channel0, scale * p.channel0, 1.0e-8 ); EXPECT_NEAR( p3.channel1, scale * p.channel1, 1.0e-8 ); EXPECT_NEAR( p3.channel2, scale * p.channel2, 1.0e-8 );
            pixel< double,        d > p4( pixel< double       , d >::convert( p ) );
            EXPECT_EQ( p4.channel0, scale * p.channel0 ); EXPECT_EQ( p4.channel1, scale * p.channel1 ); EXPECT_EQ( p4.channel2, scale * p.channel2 );
        }
    }
    {
        pixel< comma::uint16, uw > p( 20000, 30000, 50000 );
        {
            pixel< comma::uint16, uw > p1( pixel< comma::uint16, uw >::convert( p ) );
            EXPECT_EQ( p1.channel0, p.channel0 ); EXPECT_EQ( p1.channel1, p.channel1 ); EXPECT_EQ( p1.channel2, p.channel2 );
            pixel< comma::uint32, uw > p2( pixel< comma::uint32, uw >::convert( p ) );
            EXPECT_EQ( p2.channel0, p.channel0 ); EXPECT_EQ( p2.channel1, p.channel1 ); EXPECT_EQ( p2.channel2, p.channel2 );
            pixel< float,         uw > p3( pixel< float        , uw >::convert( p ) );
            EXPECT_EQ( p3.channel0, p.channel0 ); EXPECT_EQ( p3.channel1, p.channel1 ); EXPECT_EQ( p3.channel2, p.channel2 );
            pixel< double,        uw > p4( pixel< double       , uw >::convert( p ) );
            EXPECT_EQ( p4.channel0, p.channel0 ); EXPECT_EQ( p4.channel1, p.channel1 ); EXPECT_EQ( p4.channel2, p.channel2 );
        }
        {
            double scale = std::numeric_limits< range_traits< ui >::value_t >::max() / std::numeric_limits< range_traits< uw >::value_t >::max();
            pixel< comma::uint32, ui > p2( pixel< comma::uint32, ui >::convert( p ) );
            EXPECT_EQ( p2.channel0, scale * p.channel0 ); EXPECT_EQ( p2.channel1, scale * p.channel1 ); EXPECT_EQ( p2.channel2, scale * p.channel2 );
            // floats cannot store ui precisely
            pixel< float,         ui > p3( pixel< float        , ui >::convert( p ) );
            EXPECT_NEAR( p3.channel0, scale * p.channel0, 100 ); EXPECT_NEAR( p3.channel1, scale * p.channel1, 100 ); EXPECT_NEAR( p3.channel2, scale * p.channel2, 100 );
            // but doubles can
            pixel< double,        ui > p4( pixel< double       , ui >::convert( p ) );
            EXPECT_EQ( p4.channel0, scale * p.channel0 ); EXPECT_EQ( p4.channel1, scale * p.channel1 ); EXPECT_EQ( p4.channel2, scale * p.channel2 );
        }
        {
            double scale = 1.0 / std::numeric_limits< range_traits< uw >::value_t >::max();
            // conversions are done in doubles, floats are imprecise
            pixel< float,         f > p3( pixel< float        , f >::convert( p ) );
            EXPECT_NEAR( p3.channel0, scale * p.channel0, 2.0e-8 ); EXPECT_NEAR( p3.channel1, scale * p.channel1, 2.0e-8 ); EXPECT_NEAR( p3.channel2, scale * p.channel2, 2.0e-8 );
            pixel< double,        f > p4( pixel< double       , f >::convert( p ) );
            EXPECT_EQ( p4.channel0, scale * p.channel0 ); EXPECT_EQ( p4.channel1, scale * p.channel1 ); EXPECT_EQ( p4.channel2, scale * p.channel2 );
        }
        {
            double scale = 1.0 / std::numeric_limits< range_traits< uw >::value_t >::max();
            // conversions are done in doubles, floats are imprecise
            pixel< float,         d > p3( pixel< float        , d >::convert( p ) );
            EXPECT_NEAR( p3.channel0, scale * p.channel0, 2.0e-8 ); EXPECT_NEAR( p3.channel1, scale * p.channel1, 2.0e-8 ); EXPECT_NEAR( p3.channel2, scale * p.channel2, 2.0e-8 );
            pixel< double,        d > p4( pixel< double       , d >::convert( p ) );
            EXPECT_EQ( p4.channel0, scale * p.channel0 ); EXPECT_EQ( p4.channel1, scale * p.channel1 ); EXPECT_EQ( p4.channel2, scale * p.channel2 );
        }
    }
    {
        comma::uint32 m = std::numeric_limits< comma::uint32 >::max();
        pixel< comma::uint32, ui > p( 0.2 * m, 0.3 * m, 0.5 * m );
        {
            pixel< comma::uint32, ui > p2( pixel< comma::uint32, ui >::convert( p ) );
            EXPECT_EQ( p2.channel0, p.channel0 ); EXPECT_EQ( p2.channel1, p.channel1 ); EXPECT_EQ( p2.channel2, p.channel2 );
            // floats cannot store ui precisely
            pixel< float,         ui > p3( pixel< float        , ui >::convert( p ) );
            EXPECT_NEAR( p3.channel0, p.channel0, 100 ); EXPECT_NEAR( p3.channel1, p.channel1, 100 ); EXPECT_NEAR( p3.channel2, p.channel2, 100 );
            // but doubles can
            pixel< double,        ui > p4( pixel< double       , ui >::convert( p ) );
            EXPECT_EQ( p4.channel0, p.channel0 ); EXPECT_EQ( p4.channel1, p.channel1 ); EXPECT_EQ( p4.channel2, p.channel2 );
        }
        {
            double scale = 1.0 / std::numeric_limits< range_traits< ui >::value_t >::max();
            // conversions are done in doubles, floats are imprecise
            pixel< float,         f > p3( pixel< float        , f >::convert( p ) );
            EXPECT_NEAR( p3.channel0, scale * p.channel0, 2.0e-8 ); EXPECT_NEAR( p3.channel1, scale * p.channel1, 2.0e-8 ); EXPECT_NEAR( p3.channel2, scale * p.channel2, 2.0e-8 );
            pixel< double,        f > p4( pixel< double       , f >::convert( p ) );
            EXPECT_EQ( p4.channel0, scale * p.channel0 ); EXPECT_EQ( p4.channel1, scale * p.channel1 ); EXPECT_EQ( p4.channel2, scale * p.channel2 );
        }
        {
            double scale = 1.0 / std::numeric_limits< range_traits< ui >::value_t >::max();
            // conversions are done in doubles, floats are imprecise
            pixel< float,         d > p3( pixel< float        , d >::convert( p ) );
            EXPECT_NEAR( p3.channel0, scale * p.channel0, 2.0e-8 ); EXPECT_NEAR( p3.channel1, scale * p.channel1, 2.0e-8 ); EXPECT_NEAR( p3.channel2, scale * p.channel2, 2.0e-8 );
            pixel< double,        d > p4( pixel< double       , d >::convert( p ) );
            EXPECT_EQ( p4.channel0, scale * p.channel0 ); EXPECT_EQ( p4.channel1, scale * p.channel1 ); EXPECT_EQ( p4.channel2, scale * p.channel2 );
        }
    }
    {
        pixel< float,          f > p( 0.2, 0.3, 0.5 );
        {
            {
                double scale = std::numeric_limits< range_traits< ub >::value_t >::max();
                pixel< unsigned char, ub > p0( pixel< unsigned char, ub >::convert( p ) );
                EXPECT_NEAR( p0.channel0, scale * p.channel0, 1 ); EXPECT_NEAR( p0.channel1, scale * p.channel1, 1 ); EXPECT_NEAR( p0.channel2, scale * p.channel2, 1 );
            }
            {
                double scale = std::numeric_limits< range_traits< uw >::value_t >::max();
                pixel< comma::uint16, uw > p1( pixel< comma::uint16, uw >::convert( p ) );
                EXPECT_NEAR( p1.channel0, scale * p.channel0, 1 ); EXPECT_NEAR( p1.channel1, scale * p.channel1, 1 ); EXPECT_NEAR( p1.channel2, scale * p.channel2, 1 );
            }
            {
                double scale = std::numeric_limits< range_traits< ui >::value_t >::max();
                pixel< comma::uint32, ui > p2( pixel< comma::uint32, ui >::convert( p ) );
                EXPECT_NEAR( p2.channel0, scale * p.channel0, 1 ); EXPECT_NEAR( p2.channel1, scale * p.channel1, 1 ); EXPECT_NEAR( p2.channel2, scale * p.channel2, 1 );
            }
            pixel< float,         f > p3( pixel< float        , f >::convert( p ) );
            EXPECT_EQ( p3.channel0, p.channel0 ); EXPECT_EQ( p3.channel1, p.channel1 ); EXPECT_EQ( p3.channel2, p.channel2 );
            pixel< double,        d > p4( pixel< double       , d >::convert( p ) );
            EXPECT_EQ( p4.channel0, p.channel0 ); EXPECT_EQ( p4.channel1, p.channel1 ); EXPECT_EQ( p4.channel2, p.channel2 );
        }
    }
    {
        pixel< double,         d > p( 0.2, 0.3, 0.5 );
        {
            {
                double scale = std::numeric_limits< range_traits< ub >::value_t >::max();
                pixel< unsigned char, ub > p0( pixel< unsigned char, ub >::convert( p ) );
                EXPECT_NEAR( p0.channel0, scale * p.channel0, 1 ); EXPECT_NEAR( p0.channel1, scale * p.channel1, 1 ); EXPECT_NEAR( p0.channel2, scale * p.channel2, 1 );
            }
            {
                double scale = std::numeric_limits< range_traits< uw >::value_t >::max();
                pixel< comma::uint16, uw > p1( pixel< comma::uint16, uw >::convert( p ) );
                EXPECT_NEAR( p1.channel0, scale * p.channel0, 1 ); EXPECT_NEAR( p1.channel1, scale * p.channel1, 1 ); EXPECT_NEAR( p1.channel2, scale * p.channel2, 1 );
            }
            {
                double scale = std::numeric_limits< range_traits< ui >::value_t >::max();
                pixel< comma::uint32, ui > p2( pixel< comma::uint32, ui >::convert( p ) );
                EXPECT_NEAR( p2.channel0, scale * p.channel0, 1 ); EXPECT_NEAR( p2.channel1, scale * p.channel1, 1 ); EXPECT_NEAR( p2.channel2, scale * p.channel2, 1 );
            }
            pixel< float,         f > p3( pixel< float        , f >::convert( p ) );
            EXPECT_NEAR( p3.channel0, p.channel0, 2.0e-8 ); EXPECT_NEAR( p3.channel1, p.channel1, 2.0e-8 ); EXPECT_NEAR( p3.channel2, p.channel2, 2.0e-8 );
            pixel< double,        d > p4( pixel< double       , d >::convert( p ) );
            EXPECT_EQ( p4.channel0, p.channel0 ); EXPECT_EQ( p4.channel1, p.channel1 ); EXPECT_EQ( p4.channel2, p.channel2 );
        }
    }
}