operator-opt.out: operator-opt.c
	gcc -o operator-opt.out -O3 -fopenmp operator-opt.c

easyopt.out: easyopt.c
	gcc -o easyopt.out -O3 -fopenmp easyopt.c

baseline.out: baseline.c
	gcc -o baseline.out -O3 baseline.c

clean:
	rm *.out