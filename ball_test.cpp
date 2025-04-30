// ball_test.cpp
#include <memory> 
#include "PongThreading/BallLogic.h"
#include "PongThreading/paddle.h" // Use real Paddle
#include "gtest/gtest.h"

// Setup fixture for Ball tests
class BallLogicTest : public ::testing::Test {
    protected:
        PaddleLogic leftPaddle;
        PaddleLogic rightPaddle;
        std::unique_ptr<BallLogic> logic;

        BallLogicTest()
            : leftPaddle(-0.95f, 0.0f, 0.03f, 0.3f, 0.01f),
              rightPaddle(0.95f, 0.0f, 0.03f, 0.3f, 0.01f) {}

        void SetUp() override {
            logic = std::make_unique<BallLogic>(0.0f, 0.0f, 0.05f, 0.01f);
        }

    };

    // Movement prediction tests
    // Test: computeNextPosition should move ball horizontally correctly
    TEST_F(BallLogicTest, ComputeNextPositionBasic) {
        logic->setPosition(0.0f, 0.0f);
        logic->setDirection(1.0f, 0.0f);
        logic->setSpeed(5.0f);
    
        logic->computeNextPosition(0.016f);
        EXPECT_NEAR(logic->getX(), 0.08f, 1e-5);
        EXPECT_NEAR(logic->getY(), 0.0f, 1e-5);
    }
    
    // Test: computeNextPosition should move ball diagonally correctly
    TEST_F(BallLogicTest, ComputeNextPositionDiagonal) {
        logic->setPosition(0.0f, 0.0f);
        logic->setDirection(0.7071f, 0.7071f);
        logic->setSpeed(5.0f);
    
        logic->computeNextPosition(0.016f);
        EXPECT_NEAR(logic->getX(), 0.056568f, 1e-4);
        EXPECT_NEAR(logic->getY(), 0.056568f, 1e-4);
    }

    // Screen collision detection tests
    // Test: ball should detect top collision correctly near the top boundary
    TEST_F(BallLogicTest, CheckTopCollision) {
        EXPECT_TRUE(logic->checkTopCollision(1.0f - 0.01f, 0.02f)); // barely touching
        EXPECT_TRUE(logic->checkTopCollision(1.0f, 0.0f));           // exactly at top
        EXPECT_FALSE(logic->checkTopCollision(0.9f, 0.05f));         // below top
    }

    // Test: ball should detect bottom collision correctly near the bottom boundary
    TEST_F(BallLogicTest, CheckBottomCollision) {
        EXPECT_TRUE(logic->checkBottomCollision(-1.0f + 0.01f, 0.02f)); // barely touching bottom
        EXPECT_TRUE(logic->checkBottomCollision(-1.0f, 0.0f));          // exactly at bottom
        EXPECT_FALSE(logic->checkBottomCollision(-0.8f, 0.05f));        // well above bottom
    }

    // Test: ball should detect when player 1 scores (right side)
    TEST_F(BallLogicTest, CheckRightScore) {
        EXPECT_TRUE(logic->checkRightScore(1.0f - 0.01f, 0.02f)); // barely past right edge
        EXPECT_TRUE(logic->checkRightScore(1.0f, 0.0f));          // exactly at right edge
        EXPECT_FALSE(logic->checkRightScore(0.8f, 0.05f));        // comfortably within bounds
    }

    // Test: ball should detect when player 2 scores (left side)
    TEST_F(BallLogicTest, CheckLeftScore) {
        EXPECT_TRUE(logic->checkLeftScore(-1.0f + 0.01f, 0.02f)); // barely past left edge
        EXPECT_TRUE(logic->checkLeftScore(-1.0f, 0.0f));          // exactly at left edge
        EXPECT_FALSE(logic->checkLeftScore(-0.8f, 0.05f));        // comfortably within bounds
    }

    // Vertex generation tests
    // Test: calculateVertices should return correct number of vertices
    TEST_F(BallLogicTest, CalculateVerticesCount) {
        int segments = 10;
        auto vertices = logic->calculateVertices(segments);
        EXPECT_EQ(vertices.size(), segments + 2); // center + segments + 1 (closing the circle)
    }
    /*
    // Test: first vertex should always be the center of the ball
    TEST_F(BallTest, CalculateVerticesFirstVertexIsCenter) {
        auto vertices = ball->calculateVertices(10);
        EXPECT_FLOAT_EQ(vertices[0].first, ball->getX());
        EXPECT_FLOAT_EQ(vertices[0].second, ball->getY());
    }
   
    // Test: vertices should be placed correctly around the ball
    TEST_F(BallTest, CalculateVerticesAreCorrectlyOffset) {
        int segments = 4; // 90 degree steps for easy checking
        auto vertices = ball->calculateVertices(segments);

        float aspectRatio = 1200.0f / 800.0f; // 1.5
        float radius = ball->getSize();

        // At 0 degrees (right side)
        EXPECT_NEAR(vertices[1].first, ball->getX() + radius, 1e-4);
        EXPECT_NEAR(vertices[1].second, ball->getY(), 1e-4);

        // At 90 degrees (top side)
        EXPECT_NEAR(vertices[2].first, ball->getX(), 1e-4);
        EXPECT_NEAR(vertices[2].second, ball->getY() + radius * aspectRatio, 1e-4);

        // At 180 degrees (left side)
        EXPECT_NEAR(vertices[3].first, ball->getX() - radius, 1e-4);
        EXPECT_NEAR(vertices[3].second, ball->getY(), 1e-4);

        // At 270 degrees (bottom side)
        EXPECT_NEAR(vertices[4].first, ball->getX(), 1e-4);
        EXPECT_NEAR(vertices[4].second, ball->getY() - radius * aspectRatio, 1e-4);
    }
        */
