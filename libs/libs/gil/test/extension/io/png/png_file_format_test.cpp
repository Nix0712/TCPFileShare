//
// Copyright 2013 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#define BOOST_GIL_IO_ENABLE_GRAY_ALPHA
#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>

#include <boost/core/lightweight_test.hpp>

#include "paths.hpp"

namespace fs  = boost::gil::detail::filesystem;
namespace gil = boost::gil;

#ifdef BOOST_GIL_IO_USE_PNG_TEST_SUITE_IMAGES

// Test will loop through the "in" folder to read and convert
// the png's to rgb8_image_t's. Which then will be written in
// the "out" folder.
//
// The file name structure is as followed:
//
// g04i2c08.png
// || |||+---- bit-depth
// || ||+----- color-type (descriptive)
// || |+------ color-type (numerical)
// || +------- interlaced or non-interlaced
// |+--------- parameter of test (in this case gamma-value)
// +---------- test feature (in this case gamma)

void test_file_format()
{
    std::string in(png_in + "PngSuite\\");
    fs::path in_path = fs::system_complete(fs::path(in));

    if (fs::is_directory(in_path))
    {
        fs::directory_iterator end_iter;
        for (fs::directory_iterator dir_itr(in_path); dir_itr != end_iter; ++dir_itr)
        {
            if (fs::is_regular_file(dir_itr->status()) && (dir_itr->path().extension().string() == ".PNG"))
            {
                gil::rgb8_image_t img;
                std::string filename = in + dir_itr->path().filename().string();
                gil::read_and_convert_image(filename, img, gil::png_tag());

#ifdef BOOST_GIL_IO_TEST_ALLOW_WRITING_IMAGES
                gil::write_view(png_out + dir_itr->path().stem().string() + ".png",
                    gil::view(img), gil::png_tag());
#endif  // BOOST_GIL_IO_TEST_ALLOW_WRITING_IMAGES
            }
        }
    }
}

int main()
{
    test_file_format();

    return boost::report_errors();
}

#else
int main() {}
#endif // BOOST_GIL_IO_USE_PNG_TEST_SUITE_IMAGES
