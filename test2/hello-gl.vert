#version 110

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    //gl_Position = gl_Vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_TexCoord[1] = gl_MultiTexCoord1;
}

