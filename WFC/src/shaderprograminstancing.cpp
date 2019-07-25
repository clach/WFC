#include "shaderprograminstancing.h"

ShaderProgramInstancing::ShaderProgramInstancing(GLWidget277* context) :
    ShaderProgram(context), attrTrans(-1), attrRot(-1)
{}

void ShaderProgramInstancing::create(const char *vertfile, const char *fragfile) {
    //ShaderProgram::create(vertfile, fragfile);

    // Allocate space on our GPU for a vertex shader and a fragment shader and a shader program to manage the two
    vertShader = context->glCreateShader(GL_VERTEX_SHADER);
    fragShader = context->glCreateShader(GL_FRAGMENT_SHADER);
    prog = context->glCreateProgram();
    // Get the body of text stored in our two .glsl files
    QString qVertSource = qTextFileRead(vertfile);
    QString qFragSource = qTextFileRead(fragfile);

    char* vertSource = new char[qVertSource.size()+1];
    strcpy(vertSource, qVertSource.toStdString().c_str());
    char* fragSource = new char[qFragSource.size()+1];
    strcpy(fragSource, qFragSource.toStdString().c_str());


    // Send the shader text to OpenGL and store it in the shaders specified by the handles vertShader and fragShader
    context->glShaderSource(vertShader, 1, &vertSource, 0);
    context->glShaderSource(fragShader, 1, &fragSource, 0);
    // Tell OpenGL to compile the shader text stored above
    context->glCompileShader(vertShader);
    context->glCompileShader(fragShader);
    // Check if everything compiled OK
    GLint compiled;
    context->glGetShaderiv(vertShader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        printShaderInfoLog(vertShader);
    }
    context->glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        printShaderInfoLog(fragShader);
    }

    // Tell prog that it manages these particular vertex and fragment shaders
    context->glAttachShader(prog, vertShader);
    context->glAttachShader(prog, fragShader);
    context->glLinkProgram(prog);

    // Check for linking success
    GLint linked;
    context->glGetProgramiv(prog, GL_LINK_STATUS, &linked);
    if (!linked) {
        printLinkInfoLog(prog);
    }

    // Get the handles to the variables stored in our shaders
    attrPos = context->glGetAttribLocation(prog, "vs_Pos");
    attrNor = context->glGetAttribLocation(prog, "vs_Nor");
    attrUV = context->glGetAttribLocation(prog, "vs_UV");
    attrCol = context->glGetAttribLocation(prog, "vs_Col");

    unifModel      = context->glGetUniformLocation(prog, "u_Model");
    unifModelInvTr = context->glGetUniformLocation(prog, "u_ModelInvTr");
    unifViewProj   = context->glGetUniformLocation(prog, "u_ViewProj");
    unifColor      = context->glGetUniformLocation(prog, "u_Color");
    unifSampler2D  = context->glGetUniformLocation(prog, "u_Texture");

    attrTrans = context->glGetAttribLocation(prog, "vs_Trans");
    attrRot = context->glGetAttribLocation(prog, "vs_Rot");
}

void ShaderProgramInstancing::draw(Drawable &d)
{
    useMe();

    if (unifSampler2D != -1)
    {
        context->glUniform1i(unifSampler2D, 0);
        //context->glUniform1i(unifSampler2D, /*GL_TEXTURE*/textureSlot);
    }

    if (attrPos != -1 && d.bindPos()) {
        context->glEnableVertexAttribArray(attrPos);
        context->glVertexAttribPointer(attrPos, 4, GL_FLOAT, false, 0, NULL);
    }

    if (attrNor != -1 && d.bindNor()) {
        context->glEnableVertexAttribArray(attrNor);
        context->glVertexAttribPointer(attrNor, 4, GL_FLOAT, false, 0, NULL);
    }

    if (attrUV != -1 && d.bindUV()) {
        context->glEnableVertexAttribArray(attrUV);
        context->glVertexAttribPointer(attrUV, 2, GL_FLOAT, false, 0, NULL);
    }

    if (attrCol != -1 && d.bindCol()) {
        context->glEnableVertexAttribArray(attrCol);
        context->glVertexAttribPointer(attrCol, 4, GL_FLOAT, false, 0, NULL);
    }
    if (attrTrans != -1 && d.bindTrans()) {
        context->glEnableVertexAttribArray(attrTrans);
        context->glVertexAttribPointer(attrTrans, 3, GL_FLOAT, false, 0, NULL);
    }
    if (attrRot != -1 && d.bindRot()) {
        context->glEnableVertexAttribArray(attrRot);
        context->glVertexAttribPointer(attrRot, 3, GL_FLOAT, false, 0, NULL);
    }

    d.bindIdx();
    context->glDrawElementsInstanced(d.drawMode(), d.elemCount(), GL_UNSIGNED_INT, 0, d.getNumInstances());

    if (attrPos != -1) context->glDisableVertexAttribArray(attrPos);
    if (attrNor != -1) context->glDisableVertexAttribArray(attrNor);
    if (attrUV != -1) context->glDisableVertexAttribArray(attrUV);
    if (attrCol != -1) context->glDisableVertexAttribArray(attrCol);
    if (attrTrans != -1) context->glDisableVertexAttribArray(attrTrans);
    if (attrRot != -1) context->glDisableVertexAttribArray(attrRot);

    context->printGLErrorLog();
}


