//
// Created by pierreantoine on 11/01/2020.
//

#include <boost/test/unit_test.hpp>
#include "src/reference.h"


using symbol::reference;

BOOST_AUTO_TEST_CASE(ReferenceEquality)
{
    reference r1("filename", 1, 1, 0);
    reference r2("filename", 1, 1, 0);
    reference r3("other filename", 1, 1, 0);
    BOOST_CHECK_EQUAL(r1, r2);
    BOOST_CHECK(r1 != r3);
}