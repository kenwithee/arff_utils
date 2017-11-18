all: arff_utils

arff_utils: arff_utils.c
	gcc arff_utils.c -Wall -g -o arff
run:
	./arff
clean:
	rm arff
