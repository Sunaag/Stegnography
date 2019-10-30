SRC:= $(wildcard *.c)

OBJ:= $(patsubst *.c, *.o, $(SRC))

LSB.exe: $(OBJ)
	gcc -o $@ $^

clean:
	rm *.o *.exe
