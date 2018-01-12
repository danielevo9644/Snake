OBJ = Snake.o init_object.o collision.o 
CXXFLAGS=-Wall

Snake: $(OBJ)
	g++ -o Snake $(OBJ) `pkg-config --libs allegro-5 allegro_dialog-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_image-5 allegro_audio-5 allegro_acodec-5`

-include dependencies

.PHONY: depend clean cleanall

depend:
	g++ -MM *.cc > dependencies
clean:
	rm *.o
cleanall:
	rm Snake *.o *~
