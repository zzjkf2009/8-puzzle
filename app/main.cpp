/**
 * @Author: Zejiang Zeng <yzy>
 * @Date:   2018-02-11T13:47:16-05:00
 * @Email:  zzeng@terpmail.umd.edu
 * @Last modified by:   yzy
 * @Last modified time: 2018-02-21T13:18:14-05:00
 * @License: BSD
 */



#include <vector>
#include <cmath>
#include <iostream>
#include <cassert>
#include <memory>
#include <queue>
# include <set>
#include "BoardNode.hpp"







int main() {

        Board Testboard {3,2,0,1,4,6,7,8,5};
        BoardNode root(Testboard);
        auto initalNode = std::make_shared<BoardNode>(root);
        std::cout << "Ther initalNdoe is " << '\n';
        root.printBoard(initalNode->board);
        root.StoreAllNodes(initalNode);
        std::cout << "###############" << '\n';
        if (bool findorNot = root.SolvePuzzle(initalNode))
                std::cout << "Nice Job" << '\n';
        else
                std::cout << "Not Find" << '\n';

        return 0;
}
