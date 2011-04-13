lib_LTLIBRARIES = libblack.la

libblack_la_SOURCES = \
	BlackEngine.cpp \
	FileImageTexture.cpp \
	FrameBuffer.cpp \
	GameObject.cpp \
	GraphicsContext.cpp \
	HashedString.cpp \
	Message.cpp \
	GameState.cpp \
	ObjectManager.cpp \
	Rect.cpp \
	Shader.cpp \
	Texture.cpp \
	Utils.cpp \
	Vector.cpp \
	PickManager.cpp

libblack_la_CXXFLAGS = -I../include @SDL_CFLAGS@
libblack_la_LDFLAGS = @SDL_LIBS@ @SDL_MIXER_LIBS@ @SDL_IMAGE_LIBS@ @SDL_TTF_LIBS@ @GL_LIBS@
