bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target){
    for( int i = 0; i < matrixSize; i++){
        //printf("res: [%d]", binSearch( matrix[i], *matrixColSize, target) );
        if( binSearch( matrix[i], *matrixColSize, target) != -1 ){
            return true;
        }
    }
    return false;
}