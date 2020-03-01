#include <gtest/gtest.h>

#include "test/test_primitive.h"
#include "test/test_array.h"
#include "test/test_list.h"
#include "test/test_tuple.h"
#include "test/test_set.h"
#include "test/test_map.h"

#include "test_custom.h"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

