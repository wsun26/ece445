/**
    Retrieves the possible moves from a given piece and board
    
    @param none
    @return an 8x8 byte array with piece type and color

    
    look at this link for reference: https://codereview.stackexchange.com/questions/53875/generating-possible-chess-moves
**/

typedef unsigned char byte;

typedef enum{Pawn, Bishop, Rook, Knight, Queen, King} Piece_type;
typedef enum{Black, White} Color_type;
typedef enum{Regular, Opponent, Danger} Style_type

typedef struct{
    Piece_type type = 0;
    Color_type color = 0;
    byte x = 0;
    byte y = 0;
} Piece;

typedef struct{
    byte x = 0;
    byte y = 0;
    Piece * piece = NULL;
    Board * board = NULL;
    Square * getNeighbor(byte dx, byte dy);
} Square;

typedef struct{
    Square * moves = NULL;
    byte * style = NULL;
    int count = 0;
    void clear();
    void append(Square move, byte style);
} PossibleMoves;

typedef struct{
    Square * board = NULL;
    Square * getSquare(byte x, byte y);
    void addPiece(Piece piece);
} Board;


void getPossibleMoves(const Piece * piece, const Board * board, PossibleMoves * moves){
    switch(piece.type){
        case Pawn:
            return getPossibleMoves_pawn(piece, board, moves);
        case Bishop:
            return getPossibleMoves_bishop(piece, board, moves);
        case Rook:
            return getPossibleMoves_rook(piece, board, moves);
        case Knight:
            return getPossibleMoves_knight(piece, board, moves);
        case Queen:
            getPossibleMoves_rook(piece, board, moves);
            return getPossibleMoves_bishop(piece, board, moves);
        case King:
            return getPossibleMoves_king(piece, board, moves);
    }

}

void getPossibleMoves_pawn(const Piece * piece, const Board * board, PossibleMoves * moves){
    byte dy = piece.color ? 1 : -1;
    Square * up = piece.getNeighbor(0, dy);
    if (*up.piece == NULL){
        moves.moves[count] = up;
        moves.style[count] = Regular;
        moves.count++;
        if ((piece.y == 1 && piece.color == White)|| (piece.y == 6 && piece.color == Black)){
            Square * up2 = piece.getNeighbor(0, dy+dy);
            if (*up2.piece == NULL){
                moves.moves[count] = up2;
                moves.style[count] = Regular;
                moves.count++;
            }
        }
    }
    
    Square * leftD = piece.getNeighbor(-1, dy);
    if (*leftD != NULL && *leftD.piece != NULL && piece.isOpponent(*leftD.piece)){
        moves.moves[count] = leftD;
        moves.style[count] = Opponent;
        moves.count++;
    }
    
    Square * rightD = piece.getNeighbor(1, dy);
    if (*rightD != NULL && *rightD.piece != NULL && piece.isOpponent(*rightD.piece)){
        moves.moves[count] = rightD;
        moves.style[count] = Opponent;
        moves.count++;
    }
    return;
}

void getPossibleMoves_bishop(const Piece * piece, const Board * board, PossibleMoves * moves){
    byte row = piece.y;
    byte column = piece.x;
    int i;
    // all moves up & right
    for (i = row + 1, j = column + 1; i < 7 && j < 7; i++, j++){
        Square * square = board.getSquare(i, j);
        if (*square.piece == NULL){
            moves.moves[count] = up2;
            moves.style[count] = Regular;
            moves.count++;
        }
        else if (piece.isOpponent(*square.piece)){
            moves.moves[count] = up2;
            moves.style[count] = Opponent;
            moves.count++;
            break;
        }
        else{
            break;
        }
    }
    // all moves down & right
    for (i = row - 1, j = column + 1; i >= 0 && j < 7; i--, j++){
        Square * square = board.getSquare(i, j);
        if (*square.piece == NULL){
            moves.moves[count] = up2;
            moves.style[count] = Regular;
            moves.count++;
        }
        else if (piece.isOpponent(*square.piece)){
            moves.moves[count] = up2;
            moves.style[count] = Opponent;
            moves.count++;
            break;
        }
        else{
            break;
        }
    }
    // all moves up & left
    for (i = row + 1, j = column - 1; i < 7 && j >= 0; i++, j--){
        Square * square = board.getSquare(i, j);
        if (*square.piece == NULL){
            moves.moves[count] = up2;
            moves.style[count] = Regular;
            moves.count++;
        }
        else if (piece.isOpponent(*square.piece)){
            moves.moves[count] = up2;
            moves.style[count] = Opponent;
            moves.count++;
            break;
        }
        else{
            break;
        }
    }
    // all moves down & left
    for (i = row - 1, j = column - 1; i >= 0 && j >= 0; i--, j--){
        Square * square = board.getSquare(i, j);
        if (*square.piece == NULL){
            moves.moves[count] = up2;
            moves.style[count] = Regular;
            moves.count++;
        }
        else if (piece.isOpponent(*square.piece)){
            moves.moves[count] = up2;
            moves.style[count] = Opponent;
            moves.count++;
            break;
        }
        else{
            break;
        }
    }
    return;
}

void getPossibleMoves_rook(const Piece * piece, const Board * board, PossibleMoves * moves){
    byte row = piece.y;
    byte column = piece.x;
    int i;
    // all moves up
    for (i = row + 1; i < 7; i++){
        Square * square = board.getSquare(i, column);
        if (*square.piece == NULL){
            moves.moves[count] = up2;
            moves.style[count] = Regular;
            moves.count++;
        }
        else if (piece.isOpponent(*square.piece)){
            moves.moves[count] = up2;
            moves.style[count] = Opponent;
            moves.count++;
            break;
        }
        else{
            break;
        }
    }
    // all moves down
    for (i = row - 1; i >= 0; i--){
        Square * square = board.getSquare(i, column);
        if (*square.piece == NULL){
            moves.moves[count] = up2;
            moves.style[count] = Regular;
            moves.count++;
        }
        else if (piece.isOpponent(*square.piece)){
            moves.moves[count] = up2;
            moves.style[count] = Opponent;
            moves.count++;
            break;
        }
        else{
            break;
        }
    }
    // all moves right
    for (i = column + 1; i < 7; i++){
        Square * square = board.getSquare(row, i);
        if (*square.piece == NULL){
            moves.moves[count] = up2;
            moves.style[count] = Regular;
            moves.count++;
        }
        else if (piece.isOpponent(*square.piece)){
            moves.moves[count] = up2;
            moves.style[count] = Opponent;
            moves.count++;
            break;
        }
        else{
            break;
        }
    }
    // all moves left
    for (i = column - 1; i >= 0; i--){
        Square * square = board.getSquare(row, i);
        if (*square.piece == NULL){
            moves.moves[count] = up2;
            moves.style[count] = Regular;
            moves.count++;
        }
        else if (piece.isOpponent(*square.piece)){
            moves.moves[count] = up2;
            moves.style[count] = Opponent;
            moves.count++;
            break;
        }
        else{
            break;
        }
    }
    return;
}

void getPossibleMoves_knight(const Piece * piece, const Board * board, PossibleMoves * moves){
    int[][] offsets = {
        {-2, 1},
        {-1, 2},
        {1, 2},
        {2, 1},
        {2, -1},
        {1, -2},
        {-1, -2},
        {-2, -1}
    };
    for (int[] o : offsets) {
        Square * square = piece.getNeighbour(o[0], o[1]);
        if (square != NULL && square.piece == NULL ) {
            moves.moves[count] = up2;
            moves.style[count] = Regular;
            moves.count++;
        }
        if (square != NULL && piece.isOpponent(*square.piece)){
            moves.moves[count] = up2;
            moves.style[count] = Opponent;
            moves.count++;
        }
    }
    return;
}

void getPossibleMoves_king(const Piece * piece, const Board * board, PossibleMoves * moves){
    int[][] offsets = {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1},
        {1, 1},
        {-1, 1},
        {-1, -1},
        {1, -1}
    };
    for (int[] o : offsets) {
        Square * square = piece.getNeighbour(o[0], o[1]);
        if (square != NULL && square.piece == NULL ) {
            moves.moves[count] = square;
            moves.style[count] = Regular;
            moves.count++;
        }
        if (square != NULL && piece.isOpponent(*square.piece)){
            moves.moves[count] = square;
            moves.style[count] = Opponent;
            moves.count++;
        }
    }
    
}