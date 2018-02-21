/**
 * @Author: Zejiang Zeng <yzy>
 * @Date:   2018-02-20T11:55:44-05:00
 * @Email:  zzeng@terpmail.umd.edu
 * @Last modified by:   yzy
 * @Last modified time: 2018-02-20T20:19:22-05:00
 * @License: BSD
 */



 #include <vector>
 #include <cmath>
 #include <iostream>
 #include <cassert>
 #include <memory>
 #include <queue>
 #include <set>
 #include <algorithm>
 #include <fstream>
// Dimentionality reduction, convert the 3-by-3 matrix to a 1-by-9 vector
typedef std::vector<int>  Board;
typedef std::vector<int>::size_type vector_size;
template<class T>
class Greater {
public:
bool operator()(const T& p1,const T& p2){
        return p1->priority > p2->priority;
}
};

template<
        class T,
        class Container = std::vector<T>,
        class Compare = Greater <typename Container::value_type>
        > class MyQueue : public std::priority_queue<T, Container, Compare>
{
public:
typedef typename
std::priority_queue<
        T,
        Container,
        Compare>::container_type::const_iterator const_iterator;

const_iterator find(const T&val) const
{
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first!=last) {
                if (*first==val) return first;
                ++first;
        }
        return last;
}
const_iterator end() const {
        auto last = this->c.cend();
        return last;
}
};

template <class T>
struct Less {
        bool operator()(const T& p1,const T& p2){
                return (p1->hash < p2->hash);
        }
};

/**
 * [The class that used to slove the 8-puzzle problem using A* algorithm]
 */
class BoardNode {
public:
Board board;
std::shared_ptr<BoardNode> father;
int priority;
long hash;
int steps;
std::vector<std::shared_ptr<BoardNode> > neighbors;
int spacePoistion;
typedef std::vector<std::shared_ptr<BoardNode> > Neighbors;

/**
 * The constructor of the class BoardNode, when initialize the board info, which
 * is a vector of int,assign its position of the blank space and it fatheras NULL
 * @param initalNdoe [vector<initalNdoe>]
 */
BoardNode(Board initalNdoe) : board(initalNdoe){
        spacePoistion = FindspacePoistion(board);
        steps = 0;
        priority = manhattan(board);
        hash = hashingVector(board);
        father = NULL;
}
/**
 * An other situation to create a BoardNode object by a BoardNode as father node
 * and new board info with new blank space located in an other palce
 * @param rootNode    [BoardNode]
 * @param NewBoard    [Board]
 * @param Newposition [int]
 */
BoardNode(std::shared_ptr<BoardNode> rootNode,Board NewBoard,int Newposition) : father(rootNode),board(NewBoard),spacePoistion(Newposition){
        steps = rootNode->steps+1;
        priority = manhattan(board);
        hash = hashingVector(board);
        father = rootNode;
}

/**
 * Find the positoin of the blank space in the vector. Here I use 0 to represent
 * the blank space
 * @param  board [Board]
 * @return       [int]
 */
int FindspacePoistion(Board board);
/**
 * This is a utility function to calculate the Heuristics distance, which when
 * number is not located where it supposed to be, I mark the distance as 1, otherwise
 * it is 0
 * @param  board [Board]
 * @return       [int]
 */
int hamming(Board board);
/**
 * The other Heuristics function to calculate the distance to its goal
 * @param  board [Board]
 * @return       [int]
 */
int manhattan(Board board);
/**
 * Switch the position of two elements in a vector
 * @param  board [Board]
 * @param  i     [int]
 * @param  j     [int]
 * @return       [Board]
 */
Board Swap(const Board &board,const int &i,const int &j);

/**
 * The verfity if the board state reach the goal state
 * @param  board [Board]
 * @return       [bool]
 */
bool isGoal(Board board);

/**
 * Comparing if tow vector<int> is same
 * @param  currNode   [Board]
 * @param  fathernode [Board]
 * @return            [bool]
 */
bool isEuqal(Board currNode, Board fathernode);
/**
 * Find the neighbors board of the current board state and store them into a vector
 * child state will not move back to his parent's state
 * @param currNode [description]
 */
void FindNeighbors( std::shared_ptr<BoardNode> currNode);


/**
 * Hashing the  board info to a long variable
 * @param  board [vector<int>]
 * @return       [long]
 */
long hashingVector(Board board);

/**
 * Slove the 8-puzzle problem by using a A* algorithm by given a inital Board
 * information
 * @param  initalNdoe [BoardNode]
 * @return            [bool]
 */
bool SolvePuzzle(std::shared_ptr<BoardNode> initalNdoe);

/**
 * [Find all possible nodes when given a inital node and store them into a txt file]
 * @param initalNdoe [BoardNode]
 */
void StoreAllNodes(std::shared_ptr<BoardNode> initalNdoe);


/**
 * Print the board info as a 3-by-3 matrix board
 * @param board [Board]
 */
void printBoard(Board board);
/**
 * [print the path from the goal node back to the start node]
 * @param Node [BoardNode]
 */
void printPath(std::shared_ptr<BoardNode> Node);

/**
 * [Print the node into a txt file]
 * @param board    [Board]
 * @param fileName [fstream]
 */
void printTXTnodes(Board board,std::ofstream & fileName);
/**
 * [Deconstructor]
 */
~BoardNode(){
}
};
