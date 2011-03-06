bin_PROGRAMS = test

test_SOURCES = \
	test.cpp

test_CXXFLAGS = -I../black/include @SDL_CFLAGS@
test_LDFLAGS = @SDL_LIBS@ @SDL_MIXER_LIBS@ @SDL_IMAGE_LIBS@ @SDL_TTF_LIBS@ @GL_LIBS@ -L../black/src/ -lblack
