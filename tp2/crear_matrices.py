from random import randint

MAX_DIM = 256

def main():
	
	for dim in range(1, MAX_DIM + 1):
		
		f = open("inputs/{}.txt".format(dim), "w")	
		f.write("{} ".format(dim))
		for i in range(0, 2*(dim**2)):
			numero = randint(1,5)
			f.write(str(numero) + " ")
		f.close()
		
main()
