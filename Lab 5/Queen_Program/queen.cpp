#include <iostream>

using namespace std;

class ChessBoard {
public:
    ChessBoard();
    ChessBoard(int);
    ~ChessBoard();
    void findSolutions();

private:
    const bool available;
    const int squares, norm;
    bool *column, *leftDiagonal, *rightDiagonal;
    int *positionInRow;
    int howMany;

    void putQueen(int);
    void printBoard(ostream&);
    void initializeBoard();
};

ChessBoard::ChessBoard() : available(true), squares(8), norm(squares - 1) {
    initializeBoard();
}

ChessBoard::ChessBoard(int n) : available(true), squares(n), norm(squares - 1) {
    initializeBoard();
}

ChessBoard::~ChessBoard() {
    delete[] column;
    delete[] positionInRow;
    delete[] leftDiagonal;
    delete[] rightDiagonal;
}

void ChessBoard::initializeBoard() {
    column = new bool[squares];
    positionInRow = new int[squares];
    leftDiagonal = new bool[squares * 2 - 1];
    rightDiagonal = new bool[squares * 2 - 1];

    for (int i = 0; i < squares; i++) {
        positionInRow[i] = -1;
        column[i] = available;
    }
    for (int i = 0; i < squares * 2 - 1; i++) {
        leftDiagonal[i] = rightDiagonal[i] = available;
    }
    howMany = 0;
}

void ChessBoard::putQueen(int row) {
    for (int col = 0; col < squares; col++) {
        if (column[col] == available &&
            leftDiagonal[row + col] == available &&
            rightDiagonal[row - col + norm] == available) {

            positionInRow[row] = col;
            column[col] = !available;
            leftDiagonal[row + col] = !available;
            rightDiagonal[row - col + norm] = !available;

            if (row < squares - 1) {
                putQueen(row + 1);
            } else {
                printBoard(cout);
            }

            column[col] = available;
            leftDiagonal[row + col] = available;
            rightDiagonal[row - col + norm] = available;
        }
    }
}

void ChessBoard::findSolutions() {
    putQueen(0);
    cout << howMany << " solutions found.\n";
}

void ChessBoard::printBoard(ostream& out) {
    howMany++;
    out << "Solution #" << howMany << ":" << endl;
    for (int i = 0; i < squares; i++) {
        for (int j = 0; j < squares; j++) {
            if (positionInRow[i] == j) {
                out << "Q ";
            } else {
                out << ". ";
            }
        }
        out << endl;
    }
    out << endl;
}


int main() {
    cout << "Solving the 8-Queen Problem..." << endl << endl;
    ChessBoard board(8);
    board.findSolutions();
    return 0;
}