CC := clang
LDLIBS := -lm

example: example.o i-v_char.o parameter_parser.o
example.o: parameter_parser.h
i-v_char.o parameter_parser.o: i-v_char.h

clean:
	$(RM) *.o
	$(RM) example
