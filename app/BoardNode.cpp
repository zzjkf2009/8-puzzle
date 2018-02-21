/**
 * @Author: Zejiang Zeng <yzy>
 * @Date:   2018-02-20T11:55:44-05:00
 * @Email:  zzeng@terpmail.umd.edu
 * @Last modified by:   yzy
 * @Last modified time: 2018-02-21T13:21:18-05:00
 * @License: BSD
 */



 #include <vector>
 #include <cmath>
 #include <iostream>
 #include <cassert>
 #include <memory>
 #include <queue>
 # include <set>
 #include <algorithm>
 #include <fstream>
 #include "BoardNode.hpp"


int BoardNode::FindspacePoistion(Board board) {
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

int BoardNode::hamming(Board board) {
        int hamming = 0;
        for(int i =0; i<board.size(); i++) {
                if (board[i] != 0)
                        hamming += (i+1) == board[i] ? 0 : 1;
        }
        return hamming;
}


int BoardNode::manhattan(Board board) {
        int manhattan = 0;
        for (int i =0; i<board.size(); i++) {
                if (board[i] != i+1 && board[i] != 0)
                        manhattan += std::abs((i+1)/3-board[i]/3)+abs((i+1)%3-board[i]%3);
        }
        return manhattan;
}

Board BoardNode::Swap(const Board &board,const int &i,const int &j) {
        Board NewBoard = board;
        int tem = NewBoard[i];
        NewBoard[i] = NewBoard[j];
        NewBoard[j] = tem;
        return NewBoard;
}


bool BoardNode::isGoal(Board board) {
        for (int i = 0; i<board.size()-1; i++) {
                if(board[i] == i+1)
                        continue;
                else
                        return false;
        }
        return true;
}


bool BoardNode::isEuqal(Board currNode, Board fathernode) {
        return currNode == fathernode;
}

void BoardNode::FindNeighbors( std::shared_ptr<BoardNode> currNode){

        int a = currNode->spacePoistion/3; int b = currNode->spacePoistion%3;
        bool isfather= false;
        for (int i = a-1; i <= a+1; i++) {
                if(currNode->father!=nullptr) {
                        isfather =  i*3+b == currNode->father->spacePoistion ? true : false;
                }
                if (i< 0 || i>2 || i==a || isfather)
                        continue;
                else {
                        Board childBoard = Swap(currNode->board,currNode->spacePoistion,i*3+b);
                        //BoardNode *childNode = new childNode(currNode,childBoard,i*3+b);
                        //  std::shared_ptr<BoardNode> childNode(new BoardNode(currNode,childBoard,i*3+b));
                        auto childNode = std::make_shared<BoardNode>(currNode,childBoard,i*3+b);
                        //childNode->father = currNode;
                        currNode->neighbors.push_back(childNode);
                }

        }
        for (int j = b-1; j <= b+1; j++) {
                if(currNode->father !=nullptr) {
                        isfather =  a*3+j  == currNode->father->spacePoistion ? true : false;
                }
                if (j< 0 || j>2 || j==b || isfather)
                        continue;
                else {
                        Board childBoard = Swap(currNode->board,currNode->spacePoistion,a*3+j);
                        //  BoardNode *childNode = new childNode(currNode,childBoard,a*3+j);
                        //  std::shared_ptr<BoardNode> childNode(new BoardNode(currNode,childBoard,a*3+j));
                        auto childNode = std::make_shared<BoardNode>(currNode,childBoard,a*3+j);
                        //childNode->father = currNode;
                        currNode->neighbors.push_back(childNode);
                }

        }
}


long BoardNode::hashingVector(Board board) {
        long h = 0;
        long decemal = 1;
        std::reverse(board.begin(), board.end());
        for(auto& i : board) {
                h += i*decemal;
                decemal *= 10;
        }

        return h;
}

bool BoardNode::SolvePuzzle(std::shared_ptr<BoardNode> initalNdoe) {
        bool findorNot = false;
        //    std::priority_queue<BoardNode,std::vector<BoardNode>,Greater<BoardNode> > openset;
        MyQueue<std::shared_ptr<BoardNode>,std::vector<std::shared_ptr<BoardNode> >,Greater<std::shared_ptr<BoardNode> > > openset;
        //std::set<std::shared_ptr<BoardNode>,Less<std::shared_ptr<BoardNode> > > closedset;
        std::set<long> closedset;
        openset.push(initalNdoe);
        while(!openset.empty()) {
                std::shared_ptr<BoardNode> topNode = openset.top();
                //printBoard(topNode->board);
                //  std::cout << "The top's priority is "<<topNode->priority << '\n';
                if(isGoal(topNode->board)) {
                        // printseps();
                        std::cout << "Find the goal" << '\n';
                        findorNot = true;
                        printPath(topNode);
                        return findorNot;

                }
                openset.pop();
                closedset.insert(topNode->hash);
                FindNeighbors(topNode);
                //std::cout <<"There are "<<topNode->neighbors.size() <<" neighbors" <<'\n';
                for( auto &i : topNode->neighbors) {
                        // If it is already in the closedset, continue
                        if(closedset.find(i->hash)!= closedset.end()) {
                                //std::cout << "Continued" << '\n';
                                continue;
                        }
                        // if it is not in the openset, add it to openset
                        if(openset.find(i)== openset.end()) {
                                openset.push(i);
                                //printBoard(i->board);
                                //std::cout << "Its priority is "<<i->priority << '\n';
                        }

                        else {
                                BoardNode &inOpen = *(*openset.find(i));
                                if (i.get()->priority < inOpen.priority) {
                                        inOpen.priority = i->priority;
                                        inOpen.father = topNode;
                                }
                        }
                }
        }
        return findorNot;
}


void BoardNode::StoreAllNodes(std::shared_ptr<BoardNode> initalNdoe){
        std::ofstream myfile;
        myfile.open ("StoreAllNodes.txt");
        std::set<std::shared_ptr<BoardNode>,Less<std::shared_ptr<BoardNode> > > openset;
        std::set<std::shared_ptr<BoardNode>,Less<std::shared_ptr<BoardNode> > > closedset;
        openset.insert(initalNdoe);
        while(!openset.empty()) {
                std::shared_ptr<BoardNode> topNode = *openset.begin();
                FindNeighbors(topNode);
                openset.erase(openset.begin());
                closedset.insert(topNode);
                printTXTnodes(topNode->board,myfile);
                for( auto &i : topNode->neighbors) {
                        // If it is already in the closedset, continue
                        if(closedset.find(i)!= closedset.end()) {
                                //std::cout << "Continued" << '\n';
                                continue;
                        }
                        // if it is not in the openset, add it to openset
                        if(openset.find(i)== openset.end()) {
                                openset.insert(i);
                        }
                }

        }
        std::cout << "There are " <<closedset.size()<<" nodes in total"<< '\n';
        myfile.close();
}


void BoardNode::printBoard(Board board) {
        if (board.empty()) {
                std::cout << "It is empty" << '\n';
                return;
        }
        printf("\n");
        for(int i = 0; i< board.size(); i++) {
                if((i+1)%3 == 0)
                        std::cout << board[i] << std::endl;
                else
                        std::cout << board[i] << ' ';
        }
        printf("\n");
}

void BoardNode::printPath(std::shared_ptr<BoardNode> Node) {
        printBoard(Node->board);
        int NumSteps = 0;
        while(Node->father != nullptr) {
                printBoard(Node->father->board);
                Node = Node->father;
                ++NumSteps;
        }
        std::cout << "There are "<<NumSteps<< " steps to solve the puzzle" << '\n';
}


void BoardNode::printTXTnodes(Board board,std::ofstream & fileName) {
        if (board.empty()) {
                return;
        }

        for(int i = 0; i< board.size(); i++) {
                if((i+1)%3 == 0)
                        fileName << board[i] << '\n';
                else
                        fileName << board[i] << ' ';
        }
        fileName<<"###############"<<'\n';

}
