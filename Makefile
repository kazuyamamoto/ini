CC = gcc
CFLAGS = -Wall -g
CFLAGS += -I.
LFLAGS = -LPCUnit -lpcunit

TARGET = alltests
OBJS = main.o
OBJS += ini.o
OBJS += test_ini.o
OBJS += test_sutil.o
OBJS += sutil.o
OBJS += section.o
OBJS += test_section.o
OBJS += key.o
OBJS += test_key.o

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

main.o: ini.h
ini.o: ini.h sutil.h
test_ini.o: ini.h
sutil.o: sutil.h
test_sutil.o: sutil.h
