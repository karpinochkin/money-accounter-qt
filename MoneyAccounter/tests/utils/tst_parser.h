#ifndef TST_PARSER_H
#define TST_PARSER_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../src/utils/qparser.h"
#include "../src/core/base.h"
#include <qt5/QtWidgets/QApplication>

TEST(parser_test, parse) {
    auto parser = std::make_unique<QParser>(nullptr);
    auto result = parser->ParseKID("../../MoneyAccounter/data/test-kid-file.kid");

    auto object11 = result.at(0).objects.at(0).info;
    auto object12 = result.at(0).objects.at(1).info;
    auto a11 = result.at(0).array_objects.at(0).at(0).info;
    auto a12 = result.at(0).array_objects.at(0).at(1).info;
    auto a13 = result.at(0).array_objects.at(0).at(2).info;

    auto object21 = result.at(1).objects.at(0).info;
    auto object22 = result.at(1).objects.at(1).info;
    auto a21 = result.at(1).array_objects.at(0).at(0).info;
    auto a22 = result.at(1).array_objects.at(0).at(1).info;
    auto a23 = result.at(1).array_objects.at(1).at(0).info;
    auto a24 = result.at(1).array_objects.at(1).at(1).info;
    auto a25 = result.at(1).array_objects.at(1).at(2).info;

    ASSERT_EQ(object11, "object11");
    ASSERT_EQ(object12, "object12");
    ASSERT_EQ(object21, "object21");
    ASSERT_EQ(object22, "object22");
    ASSERT_EQ(a11, "a11");
    ASSERT_EQ(a12, "a12");
    ASSERT_EQ(a13, "a13");
    ASSERT_EQ(a21, "a21");
    ASSERT_EQ(a22, "a22");
    ASSERT_EQ(a23, "a23");
    ASSERT_EQ(a24, "a24");
    ASSERT_EQ(a25, "a25");

    //        for (auto row : kid) {
    //            for (auto obj : row.objects) {
    //                qDebug() << obj.info;
    //            }
    //            for (auto arr : row.array_objects) {
    //                for (auto item : arr) {
    //                    qDebug() << item.info;
    //                }
    //            }
    //        }
}

#endif // TST_PARSER_H
