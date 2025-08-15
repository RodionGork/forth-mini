# nested calls
# should print *** <cr>
./a.out << STOP
: star 42 emit ;
: tristar star star star 10 emit ;
tristar bye
STOP
