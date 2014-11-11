#include "sudoku.h"



using namespace std;


bool Sudoku::eliminate (int row, int col, int val) {
    
    int cellnum = 1;
    while (cellnum < 10) {
        if (cellnum != val) {
            bool remove = puzzle[row][col]->removeCandidate(cellnum);
            if (remove == false)
                return false;
        }
        cellnum++;
    }
    bool BOOL1;
    for (int C = 0; C < 9; C++) {
        // cout << "yoyo" << endl;  //test
        if (C != col && puzzle[row][C]->at(val) && puzzle[row][C]->possibilities() > 1) {
            //            cout << "(finalizehor " << row << C << val << " )" << endl;   //test
            BOOL1 = puzzle[row][C]->removeCandidate(val);
            if (BOOL1 == false)
                return -1;
            if (puzzle[row][C]->possibilities() == 1) {
                finalStack.push(new SolvedCell (row, C, puzzle[row][C]->first()));
            }
        }
    }
    
    
    for (int R = 0; R < 9; R++) {
        // cout << "haha" << endl;  // test
        if (R != row && puzzle[R][col]->at(val) && puzzle[R][col]->possibilities() > 1) {
            //                cout << "(finalizever " << R << col << val << " )" << endl;  // test
            BOOL1 = puzzle[R][col]->removeCandidate(val);
            if (!BOOL1)
                return -1;
            if (puzzle[R][col]->possibilities() == 1) {
                finalStack.push(new SolvedCell (R, col, puzzle[R][col]->first()));
            }
        }
    }
    
    int algorithm1 = row / 3;
    int algorithm2 = col / 3;
    int R, C, C1,R1, maxsizeR, maxsizeC;
    if (algorithm1 == 0) {
        R1 = 0;
        R = R1;
        maxsizeR = 3;
    }
    else if (algorithm1 == 1) {
        R1 = 3;
        R = R1;
        maxsizeR = 6;
    }
    else {
        R1 = 6;
        R = R1;
        maxsizeR = 9;
    }
    if (algorithm2 == 0) {
        C1 = 0;
        C = C1;
        maxsizeC = 3;
    }
    else if (algorithm2 == 1) {
        C1 = 3;
        C = C1;
        maxsizeC = 6;
    }
    else {
        C1 = 6;
        C = C1;
        maxsizeC = 9;
    }
    
    for (R = R1; R < maxsizeR; R++) {
        for (C = C1; C < maxsizeC; C++) {
            //  cout << "lala" << endl;  //test
            if (R != row && C != col && puzzle[R][C]->at(val) && puzzle[R][C]->possibilities() > 1) {
                //                 cout << "(finalizebox " << R << C << val << " )" << endl;  //test
                BOOL1 = puzzle[R][C]->removeCandidate(val);
                if (!BOOL1)
                    return -1;
                if (puzzle[R][C]->possibilities() == 1) {
                    finalStack.push(new SolvedCell (R, C, puzzle[R][C]->first()));
                }
            }
        }
    }
    return 1;
}




Sudoku::Sudoku() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            puzzle[i][j] = new Cell();
        }
    }
}

Sudoku::Sudoku (std::string input) {
    int i = 0;
    for (int j = 0; j < 9; j++) {
        for (int p = 0; p < 9; p++) {
            int num = input[i] - 48;
            if (num > 0) {
                puzzle[j][p] = new Cell(num);
                SolvedCell *answer;
                answer = new SolvedCell(j, p, num);
                finalStack.push(answer);
            }
            else {
                puzzle[j][p] = new Cell();
            }
            i++;
        }
    }
    // finalize();
}




Sudoku::Sudoku (const Sudoku& other) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            puzzle[i][j] = new Cell();
            *puzzle[i][j] = *other.puzzle[i][j];
        }
    }
}



Sudoku::~Sudoku() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            delete puzzle[i][j];
        }
    }
}



Sudoku* Sudoku::guess() {
    int num;
    int R;
    int C;
    int minimum = 10;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            num = puzzle[i][j]->possibilities();
            if (num < minimum && num > 1) {
                minimum = num;
                R = i;
                C = j;
                
            }
        }
    }
    Sudoku* myguess = new Sudoku(*this);
    //    cout << "runhere??" << endl;    //test
    //    cout << "stop value: " << puzzle[R][C]->first() << endl;  // test
    int value = puzzle[R][C]->first();
    //        cout << "1st: "<< R << C << puzzle[R][C]->first() << endl;  // test
    puzzle[R][C]->removeCandidate(value);
    
    if (puzzle[R][C]->possibilities() == 1) {
        finalStack.push(new SolvedCell(R,C,puzzle[R][C]->first()));
        //        cout << "possibilities ==1push2rd: " << puzzle[R][C]->first() << endl;   // test
    }
    myguess->finalStack.push(new SolvedCell(R,C,value));
    //        cout << "(copypush " << R << C << value << " )" << endl;  //test
    
    myguess->finalize();
    return myguess;
}



void Sudoku::horSolve() {
    for (int i = 0; i < 9; i++) {
        for (int num = 1; num < 10; num++) {
            for (int j = 0; j < 9; j++) {
                if (puzzle[i][j]->possibilities() > 1 && puzzle[i][j]->at(num)) {
                    if (finalStack.size() > 0) {
                        if (num == finalStack.top()->val && finalStack.top()->row == i) {
                            delete finalStack.top();
                            finalStack.pop();
                            break;
                        }
                        else {
                            SolvedCell *answer;
                            answer = new SolvedCell(i, j, num);
                            finalStack.push(answer);
                        }
                    }
                    else if (finalStack.size() == 0) {
                        SolvedCell *answer;
                        answer = new SolvedCell(i, j, num);
                        finalStack.push(answer);
                        
                    }
                }
            }
        }
    }
    // finalize();
    
}

void Sudoku::verSolve() {
    for (int i = 0; i < 9; i++) {
        for (int num = 1; num < 10; num++) {
            for (int j = 0; j < 9; j++) {
                if (puzzle[j][i]->possibilities() > 1 && puzzle[j][i]->at(num)) {
                    if (finalStack.size() > 0) {
                        if (num == finalStack.top()->val && finalStack.top()->col == i) {
                            delete finalStack.top();
                            finalStack.pop();
                            break;
                        }
                        else {
                            SolvedCell *answer;
                            answer = new SolvedCell(j, i, num);
                            finalStack.push(answer);
                        }
                    }
                    else if (finalStack.size() == 0) {
                        SolvedCell *answer;
                        answer = new SolvedCell(j, i, num);
                        finalStack.push(answer);
                    }
                }
            }
        }
    }
    //finalize();
}






void Sudoku::boxSolve () {
    // box1
    
    for (int num = 1; num < 10; num++) {
        for (int i = 0; i < 3; i++) {
            bool cond = false;
            for (int j = 0; j < 3; j++) {
                if (puzzle[i][j]->possibilities() > 1 && puzzle[i][j]->at(num)) {
                    if (finalStack.size() > 0) {
                        if (num == finalStack.top()->val) {
                            cond = true;
                            //                             cout << "delete stack: " << finalStack.top()->row<<finalStack.top()->col<<finalStack.top()->val<<endl;
                            delete finalStack.top();
                            finalStack.pop();
                            break;
                        }
                        else {
                            SolvedCell *answer;
                            answer = new SolvedCell(i, j, num);
                            finalStack.push(answer);
                            //                            cout << "( " << finalStack.top()->row<<finalStack.top()->col<<finalStack.top()->val<<" )"<<endl;
                            
                        }
                    }
                    else if (finalStack.size() == 0) {
                        SolvedCell *answer;
                        answer = new SolvedCell(i, j, num);
                        finalStack.push(answer);
                        //                        cout << "[ " << finalStack.top()->row<<finalStack.top()->col<<finalStack.top()->val<<" ]"<<endl;
                    }
                }
            }
            if (cond)
                break;
        }
    }
    
    // box2
    for (int num = 1; num < 10; num++) {
        for (int i = 0; i < 3; i++) {
            bool cond = false;
            for (int j = 3; j < 6; j++) {
                if (puzzle[i][j]->possibilities() > 1 && puzzle[i][j]->at(num)) {
                    if (finalStack.size() > 0) {
                        if (num == finalStack.top()->val) {
                            cond = true;
                            delete finalStack.top();
                            finalStack.pop();
                            break;
                        }
                        else {
                            SolvedCell *answer;
                            answer = new SolvedCell(i, j, num);
                            finalStack.push(answer);
                            
                        }
                    }
                    else if (finalStack.size() == 0) {
                        SolvedCell *answer;
                        answer = new SolvedCell(i, j, num);
                        finalStack.push(answer);
                    }
                }
            }
            if (cond)
                break;
        }
    }
    
    // box3
    for (int num = 1; num < 10; num++) {
        for (int i = 0; i < 3; i++) {
            bool cond = false;
            for (int j = 6; j < 9; j++) {
                if (puzzle[i][j]->possibilities() > 1 && puzzle[i][j]->at(num)) {
                    if (finalStack.size() > 0) {
                        if (num == finalStack.top()->val) {
                            cond = true;
                            delete finalStack.top();
                            finalStack.pop();
                            break;
                        }
                        else {
                            SolvedCell *answer;
                            answer = new SolvedCell(i, j, num);
                            finalStack.push(answer);
                            
                        }
                    }
                    else if (finalStack.size() == 0) {
                        SolvedCell *answer;
                        answer = new SolvedCell(i, j, num);
                        finalStack.push(answer);
                    }
                }
            }
            if (cond)
                break;
        }
    }
    
    // box4
    for (int num = 1; num < 10; num++) {
        for (int i = 3; i < 6; i++) {
            bool cond = false;
            for (int j = 0; j < 3; j++) {
                if (puzzle[i][j]->possibilities() > 1 && puzzle[i][j]->at(num)) {
                    if (finalStack.size() > 0) {
                        if (num == finalStack.top()->val) {
                            cond = true;
                            delete finalStack.top();
                            finalStack.pop();
                            break;
                        }
                        else {
                            SolvedCell *answer;
                            answer = new SolvedCell(i, j, num);
                            finalStack.push(answer);
                            
                        }
                    }
                    else if (finalStack.size() == 0) {
                        SolvedCell *answer;
                        answer = new SolvedCell(i, j, num);
                        finalStack.push(answer);
                    }
                }
            }
            if (cond)
                break;
        }
    }
    
    // box5
    for (int num = 1; num < 10; num++) {
        for (int i = 3; i < 6; i++) {
            bool cond = false;
            for (int j = 3; j < 6; j++) {
                if (puzzle[i][j]->possibilities() > 1 && puzzle[i][j]->at(num)) {
                    if (finalStack.size() > 0) {
                        if (num == finalStack.top()->val) {
                            cond = true;
                            delete finalStack.top();
                            finalStack.pop();
                            break;
                        }
                        else {
                            SolvedCell *answer;
                            answer = new SolvedCell(i, j, num);
                            finalStack.push(answer);
                            
                        }
                    }
                    else if (finalStack.size() == 0) {
                        SolvedCell *answer;
                        answer = new SolvedCell(i, j, num);
                        finalStack.push(answer);
                    }
                }
            }
            if (cond)
                break;
        }
    }
    
    // box6
    for (int num = 1; num < 10; num++) {
        for (int i = 3; i < 6; i++) {
            bool cond = false;
            for (int j = 6; j < 9; j++) {
                if (puzzle[i][j]->possibilities() > 1 && puzzle[i][j]->at(num)) {
                    if (finalStack.size() > 0) {
                        if (num == finalStack.top()->val) {
                            cond = true;
                            delete finalStack.top();
                            finalStack.pop();
                            break;
                        }
                        else {
                            SolvedCell *answer;
                            answer = new SolvedCell(i, j, num);
                            finalStack.push(answer);
                            
                        }
                    }
                    else if (finalStack.size() == 0) {
                        SolvedCell *answer;
                        answer = new SolvedCell(i, j, num);
                        finalStack.push(answer);
                    }
                }
            }
            if (cond)
                break;
        }
    }
    
    // box7
    for (int num = 1; num < 10; num++) {
        for (int i = 6; i < 9; i++) {
            bool cond = false;
            for (int j = 0; j < 3; j++) {
                if (puzzle[i][j]->possibilities() > 1 && puzzle[i][j]->at(num)) {
                    if (finalStack.size() > 0) {
                        if (num == finalStack.top()->val) {
                            cond = true;
                            delete finalStack.top();
                            finalStack.pop();
                            break;
                        }
                        else {
                            SolvedCell *answer;
                            answer = new SolvedCell(i, j, num);
                            finalStack.push(answer);
                            
                        }
                    }
                    else if (finalStack.size() == 0) {
                        SolvedCell *answer;
                        answer = new SolvedCell(i, j, num);
                        finalStack.push(answer);
                    }
                }
            }
            if (cond)
                break;
        }
    }
    
    // box8
    for (int num = 1; num < 10; num++) {
        for (int i = 6; i < 9; i++) {
            bool cond = false;
            for (int j = 3; j < 6; j++) {
                if (puzzle[i][j]->possibilities() > 1 && puzzle[i][j]->at(num)) {
                    if (finalStack.size() > 0) {
                        if (num == finalStack.top()->val) {
                            cond = true;
                            delete finalStack.top();
                            finalStack.pop();
                            break;
                        }
                        else {
                            SolvedCell *answer;
                            answer = new SolvedCell(i, j, num);
                            finalStack.push(answer);
                            
                        }
                    }
                    else if (finalStack.size() == 0) {
                        SolvedCell *answer;
                        answer = new SolvedCell(i, j, num);
                        finalStack.push(answer);
                    }
                }
            }
            if (cond)
                break;
        }
    }
    
    // box9
    for (int num = 1; num < 10; num++) {
        for (int i = 6; i < 9; i++) {
            bool cond = false;
            for (int j = 6; j < 9; j++) {
                if (puzzle[i][j]->possibilities() > 1 && puzzle[i][j]->at(num)) {
                    if (finalStack.size() > 0) {
                        if (num == finalStack.top()->val) {
                            cond = true;
                            delete finalStack.top();
                            finalStack.pop();
                            break;
                        }
                        else {
                            SolvedCell *answer;
                            answer = new SolvedCell(i, j, num);
                            finalStack.push(answer);
                            
                        }
                    }
                    else if (finalStack.size() == 0) {
                        SolvedCell *answer;
                        answer = new SolvedCell(i, j, num);
                        finalStack.push(answer);
                    }
                }
            }
            if (cond)
                break;
        }
    }
    //finalize();
}





int Sudoku:: finalize () {
    bool BOOL;
    
    if (finalStack.size() == 0)
        return 0;
    while (finalStack.size() > 0) {
        int positionr = finalStack.top()->row;
        int positionc = finalStack.top()->col;
        int positionv = finalStack.top()->val;
        delete finalStack.top();
        finalStack.pop();
        BOOL = eliminate(positionr,positionc, positionv);
        if (BOOL == false) {
            //            delete finalStack.top();
            //            finalStack.pop();
            return -1;
        }
        if (isSolved()) {
            while (finalStack.size() != 0) {
                delete finalStack.top();
                finalStack.pop();
            }
        }
        
    }
    
    return 1;
}








bool Sudoku::isSolved() {
    for (int R = 0; R < 9; R++) {
        for (int C = 0; C < 9; C++) {
            if (puzzle[R][C]->possibilities() != 1)
                return false;
        }
    }
    return true;
}




ostream & operator<< (std::ostream & stream, const Sudoku & puzzleState) {
    for (int R = 0; R < 9; R++) {
        for (int C = 0; C < 9; C++) {
            if (puzzleState.puzzle[R][C]->possibilities() > 1)
                stream << ". ";
            else
                stream << puzzleState.puzzle[R][C]->first() << " ";
        }
        stream << "\n";
    }
    return stream;
}