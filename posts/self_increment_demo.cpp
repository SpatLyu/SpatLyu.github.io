#include <Rcpp.h>

// [[Rcpp::export]]
int test_increment(){
  const int n = 5;
  // use i++
  for(int i = 0; i < n; i++){
    Rprintf("using post increment: %i - %i \n", i, i++);
  }
  // use ++i
  for(int i = 0; i < n; ++i){
    Rprintf("using pre increment: %i - %i \n", i, ++i);
  }
}
