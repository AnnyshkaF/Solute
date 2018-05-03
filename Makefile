APP := Ste

SRC := main.cpp
SRC += JpegImage.cpp
SRC += stb_image_write.c
SRC += stegrgb.cpp

LIBS := jpeg
LIBS += crypto

all: $(APP)
	@echo "Target '$@' done"

clean:
	$(RM) *.o $(APP)

$(APP): $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(SRC)))
	$(CXX) -o $@ $^ $(addprefix -l,$(LIBS))

.o: %.c
	$(CC) -c -o $@ $^

%.o: %.cpp
	$(CXX) -c -o $@ $^
