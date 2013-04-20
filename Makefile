CC = gcc
CFLAGS = -Wall -g
CFLAGS += -I.
LFLAGS = -LPCUnit -lpcunit

TARGET = alltests
OBJS = main.o
OBJS += test_ini.o
OBJS += ini.o
OBJS += futil.o


.PHONY: all clean pcunit_register test

all: pcunit_register $(TARGET)

pcunit_register:
	ruby PCUnit/pcunit_register.rb

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJS)
	cd PCUnit && $(MAKE)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LFLAGS)

test: all
	./$(TARGET)

xml: all
	./$(TARGET) verbose | ruby PCUnit/pcunit_xml_output.rb $(OUTPUT)

clean:
	cd PCUnit && $(MAKE) clean
	rm -f *.o $(TARGET)

