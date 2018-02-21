/**
 * @Author: Zejiang Zeng <yzy>
 * @Date:   2018-02-20T12:16:30-05:00
 * @Email:  zzeng@terpmail.umd.edu
 * @Last modified by:   yzy
 * @Last modified time: 2018-02-20T20:54:55-05:00
 * @License: BSD
 */



#include <gtest/gtest.h>
#include "BoardNode.hpp"

struct BoardNodeTest : public ::testing::Test {
        Board testBoard_1 {1,8,0,3,2,4,6,7,5};
        Board testBoard_2 {1,2,3,4,5,6,7,8,0};
        Board testBoard_3 {0,1,2,3,4,5,6,7,8};
        Board testBoard_4 {1,3,7,6,5,0,8,2,4};
        std::shared_ptr<BoardNode> node1 = std::make_shared<BoardNode>(testBoard_1);
        std::shared_ptr<BoardNode> node2 = std::make_shared<BoardNode>(testBoard_2);
        std::shared_ptr<BoardNode> node3 = std::make_shared<BoardNode>(testBoard_3);
        std::shared_ptr<BoardNode> node4 = std::make_shared<BoardNode>(testBoard_4);
};

TEST_F(BoardNodeTest,FindspacePositionTEST) {
        EXPECT_EQ(2,node1->FindspacePoistion(node1->board));
        EXPECT_EQ(8,node2->FindspacePoistion(node2->board));
        EXPECT_EQ(0,node3->FindspacePoistion(node3->board));
        EXPECT_EQ(5,node4->FindspacePoistion(node4->board));
}

TEST_F(BoardNodeTest,hammingTEST) {
        EXPECT_EQ(7,node1->hamming(node1->board));
        EXPECT_EQ(0,node2->hamming(node2->board));
        EXPECT_EQ(8,node3->hamming(node3->board));
        EXPECT_EQ(6,node4->hamming(node4->board));

}
TEST_F(BoardNodeTest,manhattanTEST) {
        EXPECT_EQ(12,node1->manhattan(node1->board));
        EXPECT_EQ(0,node2->manhattan(node2->board));
        EXPECT_EQ(14,node3->manhattan(node3->board));
        EXPECT_EQ(13,node4->manhattan(node4->board));
}

TEST_F(BoardNodeTest,swapTEST) {
        Board goal {1,8,2,3,0,4,6,7,5};
        Board NewBoard = node1->Swap(node1->board,2,4);
        EXPECT_EQ( goal,NewBoard );
}

TEST_F(BoardNodeTest,isGoalTEST) {
        EXPECT_TRUE(node2->isGoal(node2->board));
}

TEST_F(BoardNodeTest,hashingVectorTEST) {
        EXPECT_EQ(180324675,node1->hashingVector(node1->board));
        EXPECT_EQ(123456780,node2->hashingVector(node2->board));
        EXPECT_EQ(12345678,node3->hashingVector(node3->board));
        EXPECT_EQ(137650824,node4->hashingVector(node4->board));
}

TEST_F(BoardNodeTest,fatherNodeTEST) {
        EXPECT_EQ(node1->father,nullptr);
}
