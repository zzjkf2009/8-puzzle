#include <vector>
#include <cmath>
#include <iostream>
#include <cassert>
#include <memory>
#include <queue>
// Dimentionality reduction, convert the 3-by-3 matrix to a 1-by-9 vector
typedef std::vector<int>  Board;

class BoardNode {
public:
Board board;
BoardNode* father;
int priority;
//int hash;
std::vector<std::shared_ptr<BoardNode> > neighbors;
int spacePoistion;
typedef std::vector<BoardNode> Neighbors;

/**
 * The constructor of the class BoardNode, when initialize the board info, which
 * is a vector of int,assign its position of the blank space and it fatheras NULL
 * @param initalNdoe [vector<initalNdoe>]
 */
BoardNode(Board initalNdoe) : board(initalNdoe){
        spacePoistion = FindspacePoistion(board);
        priority = manhattan(board);
        //hash = hashingVector(board);
        father = NULL;
}
/**
 * An other situation to create a BoardNode object by a BoardNode as father node
 * and new board info with new blank space located in an other palce
 * @param rootNode    [BoardNode]
 * @param NewBoard    [Board]
 * @param Newposition [int]
 */
BoardNode(BoardNode rootNode,Board NewBoard,int Newposition) : father(&rootNode),board(NewBoard),spacePoistion(Newposition){
        priority = manhattan(board);
        //  hash = hashingVector(board);
        father = NULL;
}
/**
 * Find the positoin of the blank space in the vector. Here I use 0 to represent
 * the blank space
 * @param  board [Board]
 * @return       [int]
 */
int FindspacePoistion(Board board) {
        int position;
        for (int i = 0; i<board.size(); i++) {
                if(board[i] == 0) {
                        position = i;
                        break;
                }
        }
        assert (position >= 0 && position < 9);
        return position;

}
/**
 * This is a utility function to calculate the Heuristics distance, which when
 * number is not located where it supposed to be, I mark the distance as 1, otherwise
 * it is 0
 * @param  board [Board]
 * @return       [int]
 */
int hamming(Board board) {
        int hamming = 0;
        for(int i =0; i<board.size(); i++) {
                if (board[i] != 0)
                        hamming += i+1 == board[i] ? 0 : 1;
        }
        return hamming;
}
/**
 * The other Heuristics function to calculate the distance to its goal
 * @param  board [Board]
 * @return       [int]
 */
int manhattan(Board board) {
        int manhattan = 0;
        for (int i =0; i<board.size(); i++) {
                if (board[i] != i+1 && board[i] != 0)
                        manhattan += std::abs((i+1)/3-board[i]/3)+abs((i+1)%3-board[i]%3);
        }
        return manhattan;
}
/**
 * Switch the position of two elements in a vector
 * @param  board [Board]
 * @param  i     [int]
 * @param  j     [int]
 * @return       [Board]
 */
Board Swap(const Board &board,const int &i,const int &j) {
        Board NewBoard = board;
        int tem = NewBoard[i];
        NewBoard[i] = NewBoard[j];
        NewBoard[j] = tem;
        return NewBoard;
}

/**
 * The verfity if the board state reach the goal state
 * @param  board [Board]
 * @return       [bool]
 */
bool isGoal(Board board) {
        for (int i = 0; i<board.size()-1; i++) {
                if(board[i] == i+1)
                        continue;
                else
                        return false;
        }
        return true;
}

/**
 * Comparing if tow vector<int> is same
 * @param  currNode   [Board]
 * @param  fathernode [Board]
 * @return            [bool]
 */
bool isEuqal(Board currNode, Board fathernode) {
        return currNode == fathernode;
}
/**
 * Find the neighbors board of the current board state and store them into a vector
 * child state will not move back to his parent's state
 * @param currNode [description]
 */
void FindNeighbors(BoardNode &currNode){

        int a = currNode.spacePoistion/3; int b = currNode.spacePoistion%3;
        for (int i = a-1; i <= a+1; i++) {
                if (i< 0 || i>2 || i==a) // || i*3+b == currNode.father->spacePoistion)
                        continue;
                else {
                        Board childBoard = Swap(currNode.board,currNode.spacePoistion,i*3+b);
                        //BoardNode *childNode = new childNode(currNode,childBoard,i*3+b);
                        //  std::shared_ptr<BoardNode> childNode(new BoardNode(currNode,childBoard,i*3+b));
                        auto childNode = std::make_shared<BoardNode>(currNode,childBoard,i*3+b);
                        childNode->father = &currNode;
                        currNode.neighbors.push_back(childNode);
                }

        }
        for (int j = b-1; j <= b+1; j++) {
                if (j< 0 || j>2 || j==b) // || a*3+j == currNode.father->spacePoistion)
                        continue;
                else {
                        Board childBoard = Swap(currNode.board,currNode.spacePoistion,a*3+j);
                        //  BoardNode *childNode = new childNode(currNode,childBoard,a*3+j);
                        //  std::shared_ptr<BoardNode> childNode(new BoardNode(currNode,childBoard,a*3+j));
                        auto childNode = std::make_shared<BoardNode>(currNode,childBoard,a*3+j);
                        childNode->father = &currNode;
                        currNode.neighbors.push_back(childNode);
                }

        }
}

/*int hashingVector(Board board) {
        int h = 0;
        for(int i =0; i<board.size(); i++)
                h += board[i]*10^(8-i);
        return h;
   }
   /**
   struct Greater {

        bool operator()(const BoardNode* p1,const BoardNode* p2){
                return p1->priority>p2->priority;
        }
   };
   struct Less {
        bool operator()(const BoardNode* p1,const BoardNode* p2){
                return (p1->hash < p2->hash);
        }
   };
   void SolvePuzzle(BoardNode initalNdoe) {

        std::priority_queue<BoardNode,std::vector<BoardNode>,std::greater<BoardNode> > openset;

   }**/
~BoardNode(){
}
};


/**
 * Print the board info
 * @param board [Board]
 */
void printBoard(Board board) {
        for(int i = 0; i< board.size(); i++) {
                if((i+1)%3 == 0)
                        std::cout << board[i] << std::endl;
                else
                        std::cout << board[i] << ' ';
        }
}


int main() {
        // Test the functions
        // Test cost function and isGoal
        Board Testboard {8,2,3,4,5,6,7,1,0};
        BoardNode root(Testboard);
        int priority = root.manhattan(Testboard);
        if(root.isGoal(Testboard))
                std::cout<<"is goal"<<std::endl;
        else
                std::cout<<"not goal "<<priority<<std::endl;
        // Test FindspacePoistion and Swap function
        std::cout<<root.FindspacePoistion(root.board)<<std::endl;
        printBoard(root.Swap(root.board,root.spacePoistion,5));
        // Test FindNeighbours functions
        root.FindNeighbors(root);
        if(root.neighbors.empty())
                std::cout << "is empty" << '\n';

        for (const auto& i : root.neighbors) {
                printf("\n");
                printBoard(i->board);
                printf("\n");
        }

        return 0;
}
