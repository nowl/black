#include "Black.h"

void Texture::bind() const
{
    //glLoadIdentity();
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, texture );
}

void Texture::unbind() const
{
    glDisable( GL_TEXTURE_2D );
}
