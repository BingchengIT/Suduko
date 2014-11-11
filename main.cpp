//
//  main.cpp
//  suduko
//
//  Created by Bingcheng Zhu on 2014-10-02.
//  Copyright (c) 2014 Bingcheng.IT. All rights reserved.
//
#include <iostream>
#include <cstdlib>
#include "sudoku.h"

using namespace std;

Sudoku* solve (Sudoku* puzzle) {
    Sudoku* track;
    // puzzle->finalize();
    puzzle->horSolve();
    puzzle->verSolve();
    puzzle->boxSolve();
    int result = puzzle->finalize();
    //    cout << "fault?" << endl;   // test
    //    cout << result << endl;   // test
    
    if (result == -1) {
        //        cout << "" << endl;
        //        cerr << "ERROR" << endl;
        return NULL;
    }
    else if (puzzle->isSolved() == 1) {
        // cout << "111111111"<< endl;
        // cout << "111address :" << puzzle << endl;
        return puzzle;
    }
    else if (result == 0) {
        //        cout << "runhere?" << endl;   // run here test
        //        Sudoku* newpuzzle = puzzle->guess();
        Sudoku * newpuzzle = puzzle->guess();
        //        cout << "run here? newpuzzle" << endl;   // test
        //        cout << *newpuzzle << endl;     // test newpuzzle;
        track = solve(newpuzzle);
        
        //cout << newpuzzle<< endl;
        // solve (newpuzzle);   // re
        if (track == NULL) {
            //            cout << "track" << endl;   // test
            // cout << *track << endl;    // test
            //delete track;
            //            cout << "wronguess and solve the orginal puzzle" << endl;
            //            cout << *puzzle << endl;
            return solve(puzzle);
        }
        else if (track->isSolved()) {
            // cout << "444address: " << track << endl;
            return track;
        }
        else {
            //            cout << "333address: " << newpuzzle << endl;
            return solve (newpuzzle);
        }
        //   cout << "33333333" <<endl;
        //  cout << "333address: " << newpuzzle << endl;
        //   return newpuzzle;
        //cout << "caonima" << endl;
    }
    else {
        // cout << "4444444444" << endl;
        return solve(puzzle);   //re
    }
}


// //  std::string input = ".....4.284.6.....51...3.6.....3.1....87...14....7.9.....2.1...39.....5.767.4.....";
//    //std: string input  "...1.5...14....67..8...24...63.7..1.9.......3.1..9.52...72...8..26....35...4.9..."
//    // std: string input "................................................................................."
//    // "67214539814598367238976245126357481995862174371439852659723618442681793583145926."


//
int main(){
    Sudoku *solvedPuzzle;
    //    int i = 0;
    //    int n = 0; //length
    //
    //
    std::string input;
    string t;
    for (int i = 0; i < 9; i++) {
        cin >> input;
        if (input.size()>10) {
            t = input;
            break;
        }
        t = t + input;
    }
    
    
    Sudoku puzzle = Sudoku(t);
    std::cout << "\n";
    std::cout << puzzle << endl;
    //    std::cout << "\n" << endl;
    puzzle.finalize();
    //    cout << "hi" << endl;            //test
    solvedPuzzle = solve (&puzzle);
    if (solvedPuzzle == NULL) {
        std:: cerr << "ERROR: nonSolvable puzzle" << endl;
    }
    else
        std::cout << *solvedPuzzle;
    return 0;
}
