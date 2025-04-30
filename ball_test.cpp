// ball_test.cpp
#include <memory> 
#include "PongThreading/ball.h"
#include "PongThreading/paddle.h" // Use real Paddle
#include "gtest/gtest.h"

// Setup fixture for Ball tests
class BallTest : public ::testing::Test {
    protected:
        Paddle leftPaddle;
        Paddle rightPaddle;
        std::unique_ptr<Ball> ball;
        float newX, newY;

        void SetUp() override {
            leftPaddle = Paddle(-0.95f, 0.0f, 0.03f, 0.3f, 0.01f);
            rightPaddle = Paddle(0.95f, 0.0f, 0.03f, 0.3f, 0.01f);
            ball = std::make_unique<Ball>(0.0f, 0.0f, 0.02f, 0.5f, leftPaddle, rightPaddle);
        }
        /*
        TearDown() handled by unique_ptr
        void TearDown() override {
            delete ball;
        }
        */
    };

    // Movement prediction tests
    // Test: computeNextPosition should move ball horizontally correctly
    TEST_F(BallTest, ComputeNextPositionBasic) {
        auto [newX, newY] = ball->computeNextPosition(0.0f, 0.0f, 1.0f, 0.0f, 5.0f, 0.016f);
        EXPECT_NEAR(newX, 0.08f, 1e-5);
        EXPECT_NEAR(newY, 0.0f, 1e-5);
    }

    // Test: computeNextPosition should move ball diagonally correctly
    TEST_F(BallTest, ComputeNextPositionDiagonal) {
        auto [newX, newY] = ball->computeNextPosition(0.0f, 0.0f, 0.7071f, 0.7071f, 5.0f, 0.016f);
        EXPECT_NEAR(newX, 0.08f * 0.7071f, 1e-4);
        EXPECT_NEAR(newY, 0.08f * 0.7071f, 1e-4);
    }

    // Screen collision detection tests
    // Test: ball should detect top collision correctly near the top boundary
    TEST_F(BallTest, CheckTopCollision) {
        EXPECT_TRUE(ball->checkTopCollision(1.0f - 0.01f, 0.02f)); // barely touching
        EXPECT_TRUE(ball->checkTopCollision(1.0f, 0.0f));           // exactly at top
        EXPECT_FALSE(ball->checkTopCollision(0.9f, 0.05f));         // below top
    }

    // Test: ball should detect bottom collision correctly near the bottom boundary
    TEST_F(BallTest, CheckBottomCollision) {
        EXPECT_TRUE(ball->checkBottomCollision(-1.0f + 0.01f, 0.02f)); // barely touching bottom
        EXPECT_TRUE(ball->checkBottomCollision(-1.0f, 0.0f));          // exactly at bottom
        EXPECT_FALSE(ball->checkBottomCollision(-0.8f, 0.05f));        // well above bottom
    }

    // Test: ball should detect when player 1 scores (right side)
    TEST_F(BallTest, CheckRightScore) {
        EXPECT_TRUE(ball->checkRightScore(1.0f - 0.01f, 0.02f)); // barely past right edge
        EXPECT_TRUE(ball->checkRightScore(1.0f, 0.0f));          // exactly at right edge
        EXPECT_FALSE(ball->checkRightScore(0.8f, 0.05f));        // comfortably within bounds
    }

    // Test: ball should detect when player 2 scores (left side)
    TEST_F(BallTest, CheckLeftScore) {
        EXPECT_TRUE(ball->checkLeftScore(-1.0f + 0.01f, 0.02f)); // barely past left edge
        EXPECT_TRUE(ball->checkLeftScore(-1.0f, 0.0f));          // exactly at left edge
        EXPECT_FALSE(ball->checkLeftScore(-0.8f, 0.05f));        // comfortably within bounds
    }

    // Vertex generation tests
    // Test: calculateVertices should return correct number of vertices
    TEST_F(BallTest, CalculateVerticesCount) {
        int segments = 10;
        auto vertices = ball->calculateVertices(segments);
        EXPECT_EQ(vertices.size(), segments + 2); // center + segments + 1 (closing the circle)
    }
    
    // Test: first vertex should always be the center of the ball
    TEST_F(BallTest, CalculateVerticesFirstVertexIsCenter) {
        auto vertices = ball->calculateVertices(10);
        EXPECT_FLOAT_EQ(vertices[0].first, ball->getX());
        EXPECT_FLOAT_EQ(vertices[0].second, ball->getY());
    }
   /*
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