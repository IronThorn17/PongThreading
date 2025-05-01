#include <gtest/gtest.h>
#include "PongThreading/PaddleLogic.h"

// Test canMoveUp static method
TEST(PaddleLogic_StaticTests, CanMoveUp_WithinBounds) {
    EXPECT_TRUE(PaddleLogic::canMoveUp(0.0f, 0.2f, 0.1f));
}

TEST(PaddleLogic_StaticTests, CanMoveUp_OutOfBounds) {
    EXPECT_FALSE(PaddleLogic::canMoveUp(0.9f, 0.2f, 0.2f));
}

TEST(PaddleLogic_StaticTests, MoveUpIfPossible_Moves) {
    float newY = PaddleLogic::moveUpIfPossible(0.0f, 0.2f, 0.1f);
    EXPECT_FLOAT_EQ(newY, 0.1f);
}

TEST(PaddleLogic_StaticTests, MoveUpIfPossible_DoesNotMove) {
    float newY = PaddleLogic::moveUpIfPossible(0.95f, 0.2f, 0.1f);
    EXPECT_FLOAT_EQ(newY, 0.95f);
}

// Test instance methods
TEST(PaddleLogic_InstanceTests, TryMoveUp_Succeeds) {
    PaddleLogic paddle(0.0f, 0.0f, 0.2f, 0.2f, 0.1f);
    EXPECT_TRUE(paddle.tryMoveUp());
    EXPECT_FLOAT_EQ(paddle.getY(), 0.1f);
}

TEST(PaddleLogic_InstanceTests, TryMoveUp_Fails) {
    PaddleLogic paddle(0.0f, 0.95f, 0.2f, 0.2f, 0.1f);  // should go out of bounds
    EXPECT_FALSE(paddle.tryMoveUp());
    EXPECT_FLOAT_EQ(paddle.getY(), 0.95f);
}

TEST(PaddleLogic_InstanceTests, TryMoveDown_Succeeds) {
    PaddleLogic paddle(0.0f, 0.0f, 0.2f, 0.2f, 0.1f);
    EXPECT_TRUE(paddle.tryMoveDown());
    EXPECT_FLOAT_EQ(paddle.getY(), -0.1f);
}

TEST(PaddleLogic_InstanceTests, TryMoveDown_Fails) {
    PaddleLogic paddle(0.0f, -0.95f, 0.2f, 0.2f, 0.1f);  // would go out of bounds
    EXPECT_FALSE(paddle.tryMoveDown());
    EXPECT_FLOAT_EQ(paddle.getY(), -0.95f);
}
