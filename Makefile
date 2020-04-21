baseline.out: baseline.c
	gcc -o baseline.out -O3 baseline.c

baseline-easyopt.out: baseline-easyopt.c
	gcc -o baseline-easyopt.out -O3 -fopenmp baseline-easyopt.c

clean:
	rm *.out