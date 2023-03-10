#include <gtest/gtest.h>

#include "../../src/Parser.hpp"
#include "../../src/Validator.hpp"

TEST(ValidatorTests, PDNF_ValidationTest) {
    EXPECT_TRUE(Validator::isPDNF(Parser::parse("((A/\\(B/\\C))\\/(((!A)/\\(B/\\C))\\/((A/\\((!B)/\\C))\\/((!A)/\\((!B)/\\(!C))))))")));
    EXPECT_TRUE(Validator::isPDNF(Parser::parse("(((((P/\\Q)/\\R)\\/((P/\\(!Q))/\\R))\\/(((P/\\(!Q))/\\(!R))\\/(((!P)/\\Q)/\\(!R))))\\/(((!P)/\\(!Q))/\\(!R)))")));
}