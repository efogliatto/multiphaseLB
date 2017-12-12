double vectorMag2( double v[3] ) {

    unsigned int k;

    double mag = 0;

    for( k = 0 ; k < 3 ; k++ ) {

	mag += v[k] * v[k];

    }


    return mag;

}
