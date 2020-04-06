//
// Created by xMellox on 03-Apr-20.
//

#define BOOST_TEST_MODULE test_version

#include "lib.h"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(BOOST_TEST_MODULE)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
    BOOST_CHECK(version() > 0);
}

}