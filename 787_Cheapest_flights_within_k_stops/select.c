for( intj= 0;j< flightsSize; i++ ){
        // vrtx0->vrtx1
        int currDist = *(prev)[ flights[j][1] ]; // current weight( vrtx1 )
        int nextDist = *(prev)[ flights[j][0] ] + flights[j][2] ; // curr weight( vrtx0 ) + new_weight_to( vrtx 1)
        if( nextDist < currDist ){ // Issue: DO I NEED TO UPDATE THE VALUES IN ONE OF THE ARRAYS to copy prev?
            *(curr)[ flights[j][1] ] = nextDist;
        }
    }