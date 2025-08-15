: inccnt swap 1 + swap ;
: mul3plus1 inccnt 3 * 1 + ;
: step dup 2 mod not ?skip mul3plus1 2 / inccnt dup 1 > ;
: collatz 0 swap step ?again drop 1 + ;
: iter dup . dup collatz . 10 emit 1 + dup 20 < ;
: main 2 iter ?again ;
main
