test: test.c products.so
	gcc -std=c11 -Wall -fmax-errors=10 -Wextra test.c products.so /home/parijat/Codes/mylibs-c/myio/myio.so /home/parijat/Codes/mylibs-c/myalgo/myalgo.so -o test

products.so: products.c products.h
	gcc -std=c11 -Wall -fmax-errors=10 -Wextra -c products.c -o products.so