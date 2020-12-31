void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = vec4(0.4,0.4,0.4,1);//gl_Color;
    //vertCol = vec4(vertexColor.x,vertexColor.y,vertexColor.z,0.5);
}
