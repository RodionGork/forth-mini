# testing loops with ?again
# should print squares up to 361
./a.out << STOP
: prnsqr dup dup * . 10 emit 1 + dup 20 < ;
: test-it 1 prnsqr ?again ;
test-it
bye
STOP
