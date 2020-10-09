#include "database/controllers/tst_cntrls.h"
#include "database/tables/tst_tbls.h"
#include "models/tst_models.h"
#include "utils/tst_parser.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
