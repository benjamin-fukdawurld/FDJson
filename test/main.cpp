#include <gtest/gtest.h>

#include "test_primitive.h"
#include "test_array.h"
#include "test_list.h"
#include "test_tuple.h"
#include "test_set.h"
#include "test_map.h"

#include "test_custom.h"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

