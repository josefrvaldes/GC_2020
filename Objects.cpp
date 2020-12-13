
/****************************************************************************************

    CarGL (Objects.cpp)

    Grado en Ingenier�a Multimedia.
    Pr�ctica de Gr�ficos por Computador.
    OpenGL con Shaders.
  ---------------------------------------------------------------------------------------

    Noviembre 2012 - Septiembre 2016 (C) Juan Antonio Puchol Garc�a (puchol@dccia.ua.es)


*****************************************************************************************/

#include "Objects.h"
#include "Car.h"
#include <GL/glui.h>
#include <sstream>
#include <string>

#include "load3ds.c"

// Variable para inicializar los vectores correpondientes con los valores iniciales
GLfloat light0_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light0_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light0_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light0_position_c[4] = {-100.0f, 100.0f, 50.0f, 1.0f };

GLfloat light1_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light1_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light1_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light1_position_c[4] = {   0.0f, 100.0f,  0.0f, 1.0f };

GLfloat light2_ambient_c[4]  = {   0.2f,   0.2f,  0.2f, 1.0f };
GLfloat light2_diffuse_c[4]  = {   0.8f,   0.8f,  0.8f, 1.0f };
GLfloat light2_specular_c[4] = {   1.0f,   1.0f,  1.0f, 1.0f };
GLfloat light2_position_c[4] = {   50.0f, 100.0f,  0.0f, 1.0f };

GLfloat mat_ambient_c[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse_c[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat mat_specular_c[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_shininess_c[1] = { 100.0f };

// Matriz de 4x4 = (I)
float view_rotate_c[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float view_position_c[3] = { 0.0, -2.0, -9.0 };

float coloresc_seleccionado[4] = {1.0, 1.0, 0.0, 1.0};
float coloresc_c[2][4] = { {0.1, 1.0, 0.1, 1.0}, {0.5, 0.5, 0.5, 1.0}}; // Color del coche
float coloresr_c[2][4] = { {0.3, 0.3, 0.3, 1.0}, {1.0, 1.0, 1.0, 1.0}}; // Color de la carretera

//************************************************************** Variables de clase

TEscena escena;
TGui    gui;

//************************************************************** Clase TPrimitiva

TPrimitiva::TPrimitiva(int DL, int t)
{

    ID   = DL;
    tipo = t;

    sx = sy = sz = 1;
    rx = ry = rz = 0;
	switch (tipo) {
		case CARRETERA_ID: {  // Creaci�n de la carretera
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/final/carretera.3ds", &num_vertices0);
            break;
		}
		case SUELO_ID: {  // Creaci�n de la carretera
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/final/suelo.3ds", &num_vertices0);
            break;
		}
		case PILA_COCHES_1_ID: {  // Creaci�n de la carretera
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/final/pilas_de_coches/piladecoches1.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/final/pilas_de_coches/piladecoches2.3ds", &num_vertices1);

            break;
		}
		case PILA_COCHES_2_ID: {  // Creaci�n de la carretera
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/final/pilas_de_coches/piladecoches3.3ds", &num_vertices0);
            break;
		}
		case VALLAS_ID: {  // Creaci�n de la carretera
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)


            std::stringstream ssPath;
            // concatenamos el id con el nombre del 3ds, para no repetir c�digo
            ssPath << "../../Modelos/final/vallas/valla" << ID << ".3ds";
            std::string filePath = ssPath.str();
            std::cout << filePath << std::endl;
            modelo0 = Load3DS(&filePath[0], &num_vertices0);
            break;
		}
		case FAROLAS_ID: {
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/final/farolas.3ds", &num_vertices0);
            break;
		}
		case NEUMATICOS_ID: {
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/final/neumaticos.3ds", &num_vertices0);
            break;
		}
		case PALOS_NEUMATICOS_ID: {
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/final/palo_neumaticos.3ds", &num_vertices0);
            break;
		}
		case COCHE_ROTO_ID: {
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/final/pilas_de_coches/cochesuelto.3ds", &num_vertices0);
            break;
		}
		case EDIFICIOS_ID: {
		    tx = ty = tz = 0;

            memcpy(colores, coloresr_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/final/edificios/edificio1.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/final/edificios/edificio2.3ds", &num_vertices1);
            break;
		}
		case COCHE_ID: { // Creaci�n del coche

		    tx = -2.0;
		    ty =  0.0;
		    tz =  0.0;
		    rr =  0.0;

		    memcpy(colores, coloresc_c, 8*sizeof(float));

            //************************ Cargar modelos 3ds ***********************************
            // formato 8 floats por v�rtice (x, y, z, A, B, C, u, v)
            modelo0 = Load3DS("../../Modelos/final/coche5.0.3ds", &num_vertices0);
            modelo1 = Load3DS("../../Modelos/final/rueda2.0.3ds", &num_vertices1);
            break;
		}
	} // switch
}

void __fastcall TPrimitiva::RenderStaticObject(float *modelo, float colores[], int numVertices)
{
    glm::mat4 modelMatrix     = glm::mat4(1.0f); // matriz identidad
    glm::mat4 modelViewMatrix = escena.viewMatrix * modelMatrix;
    glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);

    glUniform4fv(escena.uColorLocation, 1, colores);
    glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo);
    glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo+3);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

void __fastcall TPrimitiva::Render(int seleccion, bool reflejo)
{
    glm::mat4   modelMatrix;
    glm::mat4   modelViewMatrix;
    switch (tipo) {

        case CARRETERA_ID: {
            if (escena.show_road) {
                glStencilFunc(GL_ALWAYS, 0, 0xFF);
                RenderStaticObject(modelo0, colores[0], num_vertices0);
            }
            break;
        }

        case SUELO_ID: {
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            RenderStaticObject(modelo0, colores[0], num_vertices0);
            break;
        }

        case PILA_COCHES_1_ID: {
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            RenderStaticObject(modelo0, colores[0], num_vertices0);
            RenderStaticObject(modelo1, colores[1], num_vertices1);
            break;
        }


        case PILA_COCHES_2_ID: {
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            RenderStaticObject(modelo0, colores[0], num_vertices0);
            break;
        }

        case EDIFICIOS_ID: {
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            RenderStaticObject(modelo0, colores[0], num_vertices0);
            RenderStaticObject(modelo1, colores[1], num_vertices1);
            break;
        }

        case VALLAS_ID: {
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            RenderStaticObject(modelo0, colores[0], num_vertices0);
            break;
        }

        case NEUMATICOS_ID: {
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            RenderStaticObject(modelo0, colores[0], num_vertices0);
            break;
        }

        case PALOS_NEUMATICOS_ID: {
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            RenderStaticObject(modelo0, colores[0], num_vertices0);
            break;
        }

        case FAROLAS_ID: {
            glStencilFunc(GL_ALWAYS, 0, 0xFF);
            RenderStaticObject(modelo0, colores[0], num_vertices0);
            break;
        }
        case COCHE_ID: {
            if (escena.show_car) {
                glStencilFunc(GL_ALWAYS, ID, 0xFF);

                if(seleccion == ID) {
                    glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) coloresc_seleccionado);
                } else {
                    glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[0]);
                }
                // Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo0+3);

                // C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix,glm::vec3(tx, ty, tz));
                modelMatrix     = glm::rotate(modelMatrix, glm::radians(rx),glm::vec3(1,0,0));
                modelMatrix     = glm::rotate(modelMatrix, glm::radians(ry),glm::vec3(0,1,0));
                modelMatrix     = glm::rotate(modelMatrix, glm::radians(rz),glm::vec3(0,0,1));

                modelViewMatrix = escena.viewMatrix * modelMatrix;

                // Env�a nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);


                glDrawArrays(GL_TRIANGLES, 0, num_vertices0);
            }


            if (escena.show_wheels)
            {

                glUniform4fv(escena.uColorLocation, 1, (const GLfloat *) colores[1]);
                // Asociamos los v�rtices y sus normales
                glVertexAttribPointer(escena.aPositionLocation, POSITION_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1);
                glVertexAttribPointer(escena.aNormalLocation, NORMAL_COMPONENT_COUNT, GL_FLOAT, false, STRIDE, modelo1+3);



                const float OFFSET_LEFT_RIGHT = 0.59;
                const float OFFSET_FORWARD = 1.0;
                const float OFFSET_BACK = 1.1;
                const float OFFSET_HEIGHT = 0.2;


                // RUEDA Delantera Izquierda : C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                // llevamos la rueda a su posici�n en la escena
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx+OFFSET_LEFT_RIGHT, ty-OFFSET_HEIGHT, tz+OFFSET_FORWARD));
                // la devolvemos al centro del coche
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(-OFFSET_LEFT_RIGHT, 0, -OFFSET_FORWARD));
                // le aplicamos las rotaciones pertinentes
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));
                // volvemos a colocarla en su posici�n relativa al coche
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(OFFSET_LEFT_RIGHT, 0, OFFSET_FORWARD));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(wheelRotation), glm::vec3(0,1,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                // Envia nuestra ModelView al Vertex Shader
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);




                // RUEDA Delantera Derecha : C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx-OFFSET_LEFT_RIGHT, ty-OFFSET_HEIGHT, tz+OFFSET_FORWARD));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(OFFSET_LEFT_RIGHT, 0, -OFFSET_FORWARD));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(-OFFSET_LEFT_RIGHT, 0, OFFSET_FORWARD));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(wheelRotation), glm::vec3(0,1,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);




                // RUEDA Trasera Izquierda : C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx+OFFSET_LEFT_RIGHT, ty-OFFSET_HEIGHT, tz-OFFSET_BACK));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(-OFFSET_LEFT_RIGHT, 0, OFFSET_BACK));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(OFFSET_LEFT_RIGHT, 0, -OFFSET_BACK));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(180.0), glm::vec3(0,0,1));
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);




                // RUEDA Trasera Derecha : C�lculo de la matriz modelo
                modelMatrix     = glm::mat4(1.0f); // matriz identidad
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(tx-OFFSET_LEFT_RIGHT, ty-OFFSET_HEIGHT, tz-OFFSET_BACK));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(OFFSET_LEFT_RIGHT, 0, OFFSET_BACK));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(ry), glm::vec3(0,1,0));
                modelMatrix     = glm::translate(modelMatrix, glm::vec3(-OFFSET_LEFT_RIGHT, 0, -OFFSET_BACK));
                modelMatrix     = glm::rotate(modelMatrix, (float) glm::radians(rr), glm::vec3(1,0,0));
                modelViewMatrix = escena.viewMatrix * modelMatrix;
                glUniformMatrix4fv(escena.uMVMatrixLocation, 1, GL_FALSE, &modelViewMatrix[0][0]);
                glDrawArrays(GL_TRIANGLES, 0, num_vertices1);
                break;
            }
        }
    } // switch

}

//************************************************************** Clase TEscena

TEscena::TEscena() {

    seleccion = 1;
    num_objects = 0;
    num_cars = 0;

    show_car = 1;
    show_wheels = 1;
    show_road = 1;

    // live variables usadas por GLUI en TGui
    wireframe = 0;
    z_buffer = 1;
    culling = 0;

    scale = 1.0;
    xy_aspect = 1;
    last_x = 0;
    last_y = 0;

    memcpy(view_position, view_position_c, 3*sizeof(float));
    memcpy(view_rotate, view_rotate_c, 16*sizeof(float));

    memcpy(light0_ambient, light0_ambient_c, 4*sizeof(float));
    memcpy(light0_diffuse, light0_diffuse_c, 4*sizeof(float));
    memcpy(light0_specular, light0_specular_c, 4*sizeof(float));
    memcpy(light0_position, light0_position_c, 4*sizeof(float));

    memcpy(light1_ambient, light1_ambient_c, 4*sizeof(float));
    memcpy(light1_diffuse, light1_diffuse_c, 4*sizeof(float));
    memcpy(light1_specular, light1_specular_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));

    memcpy(light2_ambient, light2_ambient_c, 4*sizeof(float));
    memcpy(light2_diffuse, light2_diffuse_c, 4*sizeof(float));
    memcpy(light2_specular, light2_specular_c, 4*sizeof(float));
    memcpy(light2_position, light2_position_c, 4*sizeof(float));

    memcpy(mat_ambient, mat_ambient_c, 4*sizeof(float));
    memcpy(mat_diffuse, mat_diffuse_c, 4*sizeof(float));
    memcpy(mat_specular, mat_specular_c, 4*sizeof(float));
    memcpy(mat_shininess, mat_shininess_c, 1*sizeof(float));
}

void __fastcall TEscena::InitGL()
{
    int tx, ty, tw, th;

    // Habilita el z_buffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glDepthFunc(GL_LESS);

    // Inicializaci�n de GLEW
    std::cout << "Inicializando GLEW" << std::endl << std::endl;
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendedor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // Carga de los Shaders
    std::cout << std::endl << "Cargando Shaders" << std::endl;

    Shader shader;

    std::vector<GLuint> shaders;
    shaders.push_back(shader.LoadShader("../../Shaders/VertexShader.glsl", GL_VERTEX_SHADER));
    //std::cout << "Vertex Shader: " << shader.ReturnShaderID() << std::endl;
    shaders.push_back(shader.LoadShader("../../Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER));
    //std::cout << "Fragment Shader: " << shader.ReturnShaderID() << std::endl;
    shaderProgram = new Program(shaders);

    //std::cout << "Shader Program: " << shaderProgram->ReturnProgramID() << std::endl;

    glUseProgram(shaderProgram->ReturnProgramID());
    //glValidateProgram(shaderProgram->ReturnProgramID());

    aPositionLocation=shaderProgram->attrib(A_POSITION);
    aNormalLocation=shaderProgram->attrib(A_NORMAL);

    uProjectionMatrixLocation=shaderProgram->uniform(U_PROJECTIONMATRIX);
    uMVMatrixLocation=shaderProgram->uniform(U_MVMATRIX);
    uVMatrixLocation=shaderProgram->uniform(U_VMATRIX);
    uColorLocation=shaderProgram->uniform(U_COLOR);

    uLuz0Location=shaderProgram->uniform(U_LUZ0);
    uLuz0I=shaderProgram->uniform(U_LUZ_INTENSITY_0);
    uLuz0X=shaderProgram->uniform(U_LUZ_X_0);
    uLuz0Y=shaderProgram->uniform(U_LUZ_Y_0);
    uLuz0Z=shaderProgram->uniform(U_LUZ_Z_0);

    uLuz1Location=shaderProgram->uniform(U_LUZ1);
    uLuz1I=shaderProgram->uniform(U_LUZ_INTENSITY_1);
    uLuz1X=shaderProgram->uniform(U_LUZ_X_1);
    uLuz1Y=shaderProgram->uniform(U_LUZ_Y_1);
    uLuz1Z=shaderProgram->uniform(U_LUZ_Z_1);

    uLuz2Location=shaderProgram->uniform(U_LUZ2);
    uLuz2I=shaderProgram->uniform(U_LUZ_INTENSITY_2);
    uLuz2X=shaderProgram->uniform(U_LUZ_X_2);
    uLuz2Y=shaderProgram->uniform(U_LUZ_Y_2);
    uLuz2Z=shaderProgram->uniform(U_LUZ_Z_2);

    /*
    std::cout << "a_Position Location: " << aPositionLocation << std::endl;
    std::cout << "a_Normal Location: " << aNormalLocation << std::endl;

    std::cout << "u_ProjectionMatrix Location: " << uProjectionMatrixLocation << std::endl;
    std::cout << "u_MVMatrix Location: " << uMVMatrixLocation << std::endl;
    std::cout << "u_VMatrix Location: " << uVMatrixLocation << std::endl;
    std::cout << "u_Color Location: " << uColorLocation << std::endl;
    std::cout << "u_Luz0 Location: " << uLuz0Location << std::endl;
    */

    // Habilitamos el paso de attributes
    glEnableVertexAttribArray(aPositionLocation);
    glEnableVertexAttribArray(aNormalLocation);

    // Estableciendo la matriz de proyecci�n perspectiva
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    xy_aspect = (float)tw / (float)th;
    projectionMatrix = glm::perspective(45.0f, xy_aspect, 0.1f, 1000.0f);
    glUniformMatrix4fv(uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));


    glUniform1f(escena.uLuz0X,escena.light0_position[0]);
    glUniform1f(escena.uLuz0Y,escena.light0_position[1]);
    glUniform1f(escena.uLuz0Z,escena.light0_position[2]);


    glUniform1f(escena.uLuz1X,escena.light1_position[0]);
    glUniform1f(escena.uLuz1Y,escena.light1_position[1]);
    glUniform1f(escena.uLuz1Z,escena.light1_position[2]);


    glUniform1f(escena.uLuz2X,escena.light2_position[0]);
    glUniform1f(escena.uLuz2Y,escena.light2_position[1]);
    glUniform1f(escena.uLuz2Z,escena.light2_position[2]);
}


/************************** TEscena::AddCar(TPrimitiva *car) *****************/

void __fastcall TEscena::AddCar(TPrimitiva *car)
{
    cars[num_cars] = car;
    num_cars++;
}

/******************** TEscena::AddObject(TPrimitiva *object) *****************/

void __fastcall TEscena::AddObject(TPrimitiva *object)
{
    objects[num_objects] = object;
    num_objects++;
}

/******************** TPrimitiva *TEscena::GetCar(int id) ********************/

TPrimitiva __fastcall *TEscena::GetCar(int id)
{
    TPrimitiva *p=NULL;

    for (int i=0; i<num_cars; i++)
    {
        if (cars[i]->ID==id)
        {
            p = cars[i];
        }

    }
    return(p);
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderCars(bool reflejo) {

    for (int i=0; i<num_cars; i++)
    {
        cars[i]->Render(seleccion, reflejo);
    }
}

/******************** TEscena::RenderCars() **********************************/

void __fastcall TEscena::RenderObjects(bool reflejo) {

    for (int i=0; i<num_objects; i++)
    {
        objects[i]->Render(seleccion, reflejo);
    }
}

/***************************************** TEscena::Render() *****************/

void __fastcall TEscena::Render()
{
    glm::mat4 rotateMatrix;

    glClearColor(1.0, 0.65, 0.45, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);



    switch(camMode) {
    case GENERAL: {
            rotateMatrix    = glm::make_mat4(view_rotate);
            viewMatrix      = glm::mat4(1.0f);
            viewMatrix      = glm::translate(viewMatrix,glm::vec3(view_position[0], view_position[1], view_position[2]));
            viewMatrix      = viewMatrix*rotateMatrix;
            viewMatrix      = glm::scale(viewMatrix,glm::vec3(scale, scale, scale));
        }
        break;

    case THIRD_PERSON: {
            TPrimitiva *coche = GetCar(seleccion);
            if(coche){
                float camX = coche->tx - 3 * sin(glm::radians(coche->ry));
                float camY = coche->ty + 1.3;
                float camZ = coche->tz - 3 * cos(glm::radians(coche->ry));

                glm::vec3 camPos = glm::vec3(camX, camY, camZ);
                glm::vec3 camTarget = glm::vec3(coche->tx, coche->ty + 0.7, coche->tz);
                viewMatrix = glm::lookAt(camPos, camTarget, glm::vec3(0,1,0));
            }
        }
        break;

    case FIRST_PERSON: {
            TPrimitiva *coche = GetCar(seleccion);
            if(coche){
                float camX = coche->tx + 0.f * sin(glm::radians(coche->ry));
                float camY = coche->ty + 0.7;
                float camZ = coche->tz + 0.f * cos(glm::radians(coche->ry));


                float targetX = coche->tx + 3 * sin(glm::radians(coche->ry));
                float targetY = coche->ty + 0.7;
                float targetZ = coche->tz + 3 * cos(glm::radians(coche->ry));

                glm::vec3 camPos = glm::vec3(camX, camY, camZ);
                glm::vec3 camTarget = glm::vec3(targetX, targetY, targetZ);
                viewMatrix = glm::lookAt(camPos, camTarget, glm::vec3(0,1,0));
            }
        }
        break;

    case AEREA: {
            TPrimitiva *coche = GetCar(seleccion);
            if(coche){
                glm::vec3 camPos = glm::vec3(coche->tx,50,coche->tz);
                glm::vec3 camTarget = glm::vec3(coche->tx,0,coche->tz);


                float camUpX = coche->tx + 1000 * sin(glm::radians(coche->ry));
                float camUpY = 50;
                float camUpZ = coche->tz + 1000 * cos(glm::radians(coche->ry));
                glm::vec3 camUp = glm::vec3(camUpX, camUpY, camUpZ);
                viewMatrix = glm::lookAt(camPos, camTarget, camUp);
            }
        }
        break;
    }



    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //viewMatrix      = glm::translate(viewMatrix,glm::vec3(view_position[0], view_position[1], view_position[2]));
    //viewMatrix      = viewMatrix*rotateMatrix;
    //viewMatrix      = glm::scale(viewMatrix,glm::vec3(scale, scale, scale));

    glUniform1i(uLuz0Location, gui.light0_enabled);
    glUniform1f(uLuz0I, gui.light0_intensity);

    glUniform1i(uLuz1Location, gui.light1_enabled);
    glUniform1f(uLuz1I, gui.light1_intensity);

    glUniform1i(uLuz2Location, gui.light2_enabled);
    glUniform1f(uLuz2I, gui.light2_intensity);


    glUniformMatrix4fv(uVMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix)); // Para la luz matrix view pero sin escalado!

    // Dibujar carretera y objetos
    RenderObjects(seleccion);

    // Dibujar coches
    RenderCars(seleccion);

    glutSwapBuffers();
}

// Selecciona un objeto a trav�s del rat�n
void __fastcall TEscena::Pick3D(int mouse_x, int mouse_y)
{
    int res = 0;
    GLint viewport[4];
    int tx,ty,tw,th;

    GLUI_Master.get_viewport_area(&tx,&ty,&tw,&th);
    glGetIntegerv(GL_VIEWPORT,viewport);
    glReadPixels(mouse_x,th - mouse_y + 81, 1, 1, GL_STENCIL_INDEX,GL_UNSIGNED_INT, &res);
    seleccion = res;
    gui.sel = res;
    gui.glui->sync_live();
    //std::cout << "Result of pick3d is " << res << std::endl;
}

//************************************************************** Clase TGui

TGui::TGui()
{
    sel = 1;
    enable_panel2 = 1;
    light0_enabled = 1;
    light1_enabled = 1;
    light2_enabled = 1;

    light0_intensity = 0.8;
    light1_intensity = 0.3;
    light2_intensity = 0.25;

    memcpy(light0_position, light0_position_c, 4*sizeof(float));
    memcpy(light1_position, light1_position_c, 4*sizeof(float));
    memcpy(light2_position, light2_position_c, 4*sizeof(float));
}

void controlCallback(int control)
{
    gui.ControlCallback(control);
}

void __fastcall TGui::Init(int main_window) {

    /****************************************************/
    /*        C�digo con el interfaz Gr�fico GLUI       */
    /****************************************************/
    printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );

    window_id = main_window;

    /*** Crea a ventana lateral ***/
    glui = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_RIGHT );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    // A�ade un panel con texto con el valor de la selecci�n
    GLUI_Panel *panel0 = new GLUI_Panel(glui, "Seleccion");
    GLUI_RadioGroup *radioGroup = new GLUI_RadioGroup(panel0, &sel, SEL_ID, controlCallback);
    glui->add_radiobutton_to_group(radioGroup, "NINGUNO");
    glui->add_radiobutton_to_group(radioGroup, "COCHE 1");
    glui->add_radiobutton_to_group(radioGroup, "COCHE 2");



    GLUI_Panel *panelCams = new GLUI_Panel(glui, "C�maras");
    GLUI_RadioGroup *radioGroupCams = new GLUI_RadioGroup(panelCams, &cam, CAM_ID, controlCallback);
    glui->add_radiobutton_to_group(radioGroupCams, "Normal");
    glui->add_radiobutton_to_group(radioGroupCams, "Primera persona");
    glui->add_radiobutton_to_group(radioGroupCams, "Tercera persona");
    glui->add_radiobutton_to_group(radioGroupCams, "Aerea");


    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    obj_panel = new GLUI_Rollout(glui, "Propiedades", true );

    /***** Control para las propiedades de escena *****/

    //new GLUI_Checkbox( obj_panel, "Modo Alambrico", &escena.wireframe, 1, controlCallback );
    glui->add_column_to_panel(obj_panel, true);
    new GLUI_Checkbox( obj_panel, "Culling", &escena.culling, CULLING_ID, controlCallback );
    new GLUI_Checkbox( obj_panel, "Z Buffer", &escena.z_buffer, Z_BUFFER_ID, controlCallback );
    new GLUI_Checkbox( obj_panel, "Sentido horario", &escena.sentido, SENTIDO_ID, controlCallback );
    new GLUI_Checkbox( obj_panel, "Modo Sombreado", &escena.sombreado, SOMBREADO_ID, controlCallback );

    GLUI_RadioGroup *radioGroup2 = new GLUI_RadioGroup(obj_panel, &escena.modo_vista, MODO_VISTA_ID, controlCallback);
    glui->add_radiobutton_to_group(radioGroup2,"Modo solido");
    glui->add_radiobutton_to_group(radioGroup2,"Modo alambrico");
    glui->add_radiobutton_to_group(radioGroup2,"Modo puntos");


    /******** A�ade controles para las luces ********/

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Luces", false );

    GLUI_Panel *light0 = new GLUI_Panel( roll_lights, "Luz 1" );
    GLUI_Panel *light1 = new GLUI_Panel( roll_lights, "Luz 2" );
    GLUI_Panel *light2 = new GLUI_Panel( roll_lights, "Luz 3" );



    new GLUI_Checkbox( light0, "Encendida", &light0_enabled, LIGHT0_ENABLED_ID, controlCallback );
    light0_spinner = new GLUI_Spinner( light0, "Intensidad:", &light0_intensity, LIGHT0_INTENSITY_ID, controlCallback );
    light0_spinner->set_float_limits( 0.0, 1.0 );
    GLUI_Scrollbar *sb;
    sb = new GLUI_Scrollbar( light0, "X",GLUI_SCROLL_HORIZONTAL, &escena.light0_position[0],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Y",GLUI_SCROLL_HORIZONTAL, &escena.light0_position[1],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light0, "Z",GLUI_SCROLL_HORIZONTAL, &escena.light0_position[2],LIGHT0_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);



    new GLUI_Checkbox( light1, "Encendida", &light1_enabled, LIGHT1_ENABLED_ID, controlCallback );
    light1_spinner = new GLUI_Spinner( light1, "Intensidad:", &light1_intensity, LIGHT1_INTENSITY_ID, controlCallback );
    light1_spinner->set_float_limits( 0.0, 1.0 );
    sb = new GLUI_Scrollbar( light1, "X",GLUI_SCROLL_HORIZONTAL, &escena.light1_position[0],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light1, "Y",GLUI_SCROLL_HORIZONTAL, &escena.light1_position[1],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light1, "Z",GLUI_SCROLL_HORIZONTAL, &escena.light1_position[2],LIGHT1_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);





    new GLUI_Checkbox( light2, "Encendida", &light2_enabled, LIGHT2_ENABLED_ID, controlCallback );
    light2_spinner = new GLUI_Spinner( light2, "Intensidad:", &light2_intensity, LIGHT2_INTENSITY_ID, controlCallback );
    light2_spinner->set_float_limits( 0.0, 1.0 );
    sb = new GLUI_Scrollbar( light2, "X",GLUI_SCROLL_HORIZONTAL, &escena.light2_position[0],LIGHT2_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light2, "Y",GLUI_SCROLL_HORIZONTAL, &escena.light2_position[1],LIGHT2_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);
    sb = new GLUI_Scrollbar( light2, "Z",GLUI_SCROLL_HORIZONTAL, &escena.light2_position[2],LIGHT2_POSITION_ID,controlCallback);
    sb->set_float_limits(-100,100);


    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    /***  Rollout de Opciones ***/
    GLUI_Rollout *options = new GLUI_Rollout(glui, "Opciones", true );
    new GLUI_Checkbox( options, "Dibujar Coche", &escena.show_car );
    new GLUI_Checkbox( options, "Dibujar Ruedas", &escena.show_wheels );
    new GLUI_Checkbox( options, "Dibujar Carretera", &escena.show_road );


    /*** Disable/Enable botones ***/
    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );
    new GLUI_Checkbox( glui, "Bloquear Movimiento", &enable_panel2 );
    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );
    new GLUI_Button( glui, "Resetear Posicion", RESET_ID, controlCallback );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

     // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    new GLUI_StaticText( glui, "  Autor:" );
    new GLUI_StaticText( glui, "  2012-2016 (C) Juan Antonio Puchol  " );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    new GLUI_Separator( glui );

    // A�ade una separaci�n
    new GLUI_StaticText( glui, "" );

    /****** A 'quit' button *****/
    new GLUI_Button( glui, "Salir", 0,(GLUI_Update_CB)exit );

    // Crea la subventana inferior
    glui2 = GLUI_Master.create_glui_subwindow( window_id, GLUI_SUBWINDOW_BOTTOM );

    /**** Link windows to GLUI, and register idle callback ******/
    glui->set_main_gfx_window( window_id );
    glui2->set_main_gfx_window( window_id );

    view_rot = new GLUI_Rotation(glui2, "Rotacion Escena", escena.view_rotate );
    view_rot->set_spin( 1.0 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_xy = new GLUI_Translation(glui2, "Traslacion Escena XY", GLUI_TRANSLATION_XY, escena.view_position );
    trans_xy->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_x =  new GLUI_Translation(glui2, "Traslacion Escena X", GLUI_TRANSLATION_X, escena.view_position );
    trans_x->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_y = new GLUI_Translation( glui2, "Traslacion Escena Y", GLUI_TRANSLATION_Y, &escena.view_position[1] );
    trans_y->set_speed( .005 );
    new GLUI_Column( glui2, false );
    GLUI_Translation *trans_z = new GLUI_Translation( glui2, "Traslacion Escena Z", GLUI_TRANSLATION_Z, &escena.scale );
    trans_z->set_speed( .005 );

}

/**************************************** TGui::ControlCallback() *******************/

void __fastcall TGui::ControlCallback( int control )
{
    switch (control) {
        case LIGHT0_ENABLED_ID: {
            if ( light0_enabled )
                light0_spinner->enable();
            else
                light0_spinner->disable();
            break;
        }
        case LIGHT1_ENABLED_ID: {
            if ( light1_enabled )
                light1_spinner->enable();
            else
                light1_spinner->disable();
            break;
        }
        case LIGHT2_ENABLED_ID: {
            if ( light2_enabled )
                light2_spinner->enable();
            else
                light2_spinner->disable();
            break;
        }
        case LIGHT0_INTENSITY_ID: {

            float v[] = {
                escena.light0_diffuse[0],  escena.light0_diffuse[1],
                escena.light0_diffuse[2],  escena.light0_diffuse[3] };

            v[0] *= light0_intensity;
            v[1] *= light0_intensity;
            v[2] *= light0_intensity;
            glUniform1f(escena.uLuz0I, light0_intensity);
            break;
        }
        case LIGHT1_INTENSITY_ID: {

            float v[] = {
                escena.light1_diffuse[0],  escena.light1_diffuse[1],
                escena.light1_diffuse[2],  escena.light1_diffuse[3] };

            v[0] *= light1_intensity;
            v[1] *= light1_intensity;
            v[2] *= light1_intensity;
            glUniform1f(escena.uLuz1I, light1_intensity);
            break;
        }
        case LIGHT2_INTENSITY_ID: {

            float v[] = {
                escena.light2_diffuse[0],  escena.light2_diffuse[1],
                escena.light2_diffuse[2],  escena.light2_diffuse[3] };

            v[0] *= light2_intensity;
            v[1] *= light2_intensity;
            v[2] *= light2_intensity;
            glUniform1f(escena.uLuz2I, light2_intensity);
            break;
        }
        case LIGHT0_POSITION_ID: {
            glUniform1f(escena.uLuz0X,escena.light0_position[0]);
            glUniform1f(escena.uLuz0Y,escena.light0_position[1]);
            glUniform1f(escena.uLuz0Z,escena.light0_position[2]);
        }
        case LIGHT1_POSITION_ID: {
            glUniform1f(escena.uLuz1X,escena.light1_position[0]);
            glUniform1f(escena.uLuz1Y,escena.light1_position[1]);
            glUniform1f(escena.uLuz1Z,escena.light1_position[2]);
        }
        case LIGHT2_POSITION_ID: {
            glUniform1f(escena.uLuz2X,escena.light2_position[0]);
            glUniform1f(escena.uLuz2Y,escena.light2_position[1]);
            glUniform1f(escena.uLuz2Z,escena.light2_position[2]);

        }
        case ENABLE_ID: {
            glui2->enable();
            break;
        }
        case DISABLE_ID: {
            glui2->disable();
            break;
        }
        case RESET_ID: {
            memcpy(escena.view_position,view_position_c,3*sizeof(float));
            view_rot->reset();
            escena.scale = 1.0;
            break;
        }
        case SEL_ID: {
            escena.seleccion = sel;
            //GLUI_Master.SetFocus(true);
            glutSetWindow( glui->get_glut_window_id() );
            break;
        }
        case CAM_ID: {
            switch(cam) {
                case 0:
                    escena.camMode = TEscena::GENERAL;
                    break;
                case 1:
                    escena.camMode = TEscena::FIRST_PERSON;
                    break;
                case 2:
                    escena.camMode = TEscena::THIRD_PERSON;
                    break;
                case 3:
                    escena.camMode = TEscena::AEREA;
                    break;
            }

            break;
        }

        case CULLING_ID: {
            if(escena.culling){
                glEnable(GL_CULL_FACE);
                glCullFace(GL_FRONT);
            } else {
                glDisable(GL_CULL_FACE);
            }

            break;
        }

        case Z_BUFFER_ID: {
            if(escena.z_buffer){
                glEnable(GL_DEPTH_TEST);

            }else{
                glDisable(GL_DEPTH_TEST);
            }

            break;
        }

        case MODO_VISTA_ID: {
            switch(escena.modo_vista) {
                case 0:
                    glPolygonMode(GL_FRONT, GL_FILL);
                    glPolygonMode(GL_BACK, GL_FILL);
                    break;
                case 1:
                    glPolygonMode(GL_FRONT, GL_LINE);//DELANTERO
                    glPolygonMode(GL_BACK, GL_LINE);//TRASERO
                    break;
                case 2:
                    glPolygonMode(GL_FRONT, GL_POINT);//DELANTERO
                    glPolygonMode(GL_BACK, GL_POINT);//TRASERO
                    break;
                }
            break;

            break;
        }

        case SOMBREADO_ID: {
            glEnable(GL_SHADE_MODEL);
            if(escena.sombreado){
                printf("Sombreado activado...\n");
                glShadeModel(GL_SMOOTH);//SUAVIZADO
            }else{
                printf("Sombreado desactivado...\n");
                glShadeModel(GL_FLAT);//PLANO;
            }

            break;
        }

        case SENTIDO_ID: {
            glEnable(GL_FRONT_FACE);
            if(escena.sentido){
                printf("Sentido antihorario...\n");
                glFrontFace(GL_CCW);//ANTIHORARIO
            }else{
                printf("Sentido horario...\n");
                glFrontFace(GL_CW);//HORARIO
            }
            break;
        }
  } // switch
}

/***************************************** TGui::Idle() ***********/

void __fastcall TGui::Idle( void )
{
  /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != window_id )
    glutSetWindow(window_id);

  /*  GLUI_Master.sync_live_all();  -- not needed - nothing to sync in this
                                       application  */
    if (enable_panel2)

        glui2->enable();
    else
        glui2->disable();

  glutPostRedisplay();
}

/**************************************** TGui::reshape() *************/

void __fastcall TGui::Reshape( int x, int y )
{
    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    glViewport( tx, ty, tw, th );

    escena.xy_aspect = (float)tw / (float)th;
    escena.projectionMatrix = glm::perspective(45.0f, escena.xy_aspect, 0.1f, 1000.0f);
    glUniformMatrix4fv(escena.uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(escena.projectionMatrix));

    //std::cout << "xy aspect: " << escena.xy_aspect << std::endl;

    glutPostRedisplay();
}

/***************************************** gui::motion() **********/

void __fastcall TGui::Motion(int x, int y )
{
    glutPostRedisplay();
}

/***************************************** gui::Mouse() **********/

void __fastcall TGui::Mouse(int button, int button_state, int x, int y )
{
    if(button_state == 0)
        escena.Pick3D(x, y);
}

