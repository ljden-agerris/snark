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

#include "accumulated.h"

#include <comma/base/exception.h>
#include <iostream>
#include <vector>
#include <map>
#include <boost/bind.hpp>
#include <boost/thread/pthread/pthread_mutex_scoped_lock.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include "../depth_traits.h"
// #include <Eigen/Core>
// #include <boost/date_time/posix_time/ptime.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
// #include <opencv2/highgui/highgui.hpp>

namespace snark{ namespace cv_mat {  namespace impl {
    
template< int DepthIn >
static void iterate_pixels( const tbb::blocked_range< std::size_t >& r, const cv::Mat& m, cv::Mat& average, comma::uint64 count )
{
    typedef typename depth_traits< DepthIn >::value_t value_in_t;
    typedef double value_out_t;
    const unsigned int channels = m.channels();
    const unsigned int cols = m.cols * channels;
    for( unsigned int i = r.begin(); i < r.end(); ++i )
    {
        const value_in_t* in = m.ptr< value_in_t >(i);
        value_out_t* avg = average.ptr< value_out_t >(i);
        for( unsigned int j = 0; j < cols; ++j ) 
        {
            *avg += (*in - *avg) / count; 
            ++avg;
            ++in;
        }
    }
}

template< typename H, int DepthIn >
static void divide_by_rows( const typename accumulated_impl_< H >::value_type m, cv::Mat& average, comma::uint64 count )
{
    tbb::parallel_for( tbb::blocked_range< std::size_t >( 0, m.second.rows ), 
                       boost::bind( &iterate_pixels< DepthIn >, _1, m.second, boost::ref( average ), count ) );
}

template< typename H >
static void iterate_by_input_type( const typename accumulated_impl_< H >::value_type& m, cv::Mat& average, comma::uint64 count)
{
    int otype = m.second.depth(); // This will work?
    switch( otype )
    {
        case CV_8U : divide_by_rows< H, CV_8U  >( m, average, count ); break;
        case CV_8S : divide_by_rows< H, CV_8S  >( m, average, count ); break;
        case CV_16U: divide_by_rows< H, CV_16U >( m, average, count ); break;
        case CV_16S: divide_by_rows< H, CV_16S >( m, average, count ); break;
        case CV_32S: divide_by_rows< H, CV_32S >( m, average, count ); break;
        case CV_32F: divide_by_rows< H, CV_32F >( m, average, count ); break;
        case CV_64F: divide_by_rows< H, CV_64F >( m, average, count ); break;
        default: COMMA_THROW( comma::exception, "accumulated: unrecognised output image type " << otype );
    }
}

// TODO pipeline is serial, but filter is not!!! threading=1 needed or locking
    
template < typename H >
typename accumulated_impl_< H >::value_type accumulated_impl_< H >::operator()( const typename accumulated_impl_< H >::value_type& n )
{
    ++count_;
    if( average_.size() == cv::Size(0,0) )  // This filter is not run in parallel, no locking required
    {
        std::cerr << "Found empty average_" << std::endl;
        
        average_.create( n.second.rows, n.second.cols, CV_MAKETYPE(CV_64F, n.second.channels()) );
        std::cerr << "average_ " << average_.rows << "x" << average_.cols << " type: " << average_.type() << std::endl;
    }
    
    iterate_by_input_type< H >(n, average_, count_);
    
    cv::Mat result;
    average_.convertTo(result, n.second.type());
    return value_type( n.first, result );
}

} } }  // namespace snark { namespace cv_mat { namespace impl {

template class snark::cv_mat::impl::accumulated_impl_< boost::posix_time::ptime >;
template class snark::cv_mat::impl::accumulated_impl_< std::vector< char > >;