bin_PROGRAMS = test2

test2_SOURCES = \
	ParticleRenderer.cpp \
	test.cpp

test2_CXXFLAGS = -I../black/include @SDL_CFLAGS@
test2_LDFLAGS = @SDL_LIBS@ @SDL_MIXER_LIBS@ @SDL_IMAGE_LIBS@ @SDL_TTF_LIBS@ @GL_LIBS@ -L../black/src/ -lblack
