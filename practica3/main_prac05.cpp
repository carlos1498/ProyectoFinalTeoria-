/*---------------------------------------------------------*/
/* ----------------   Práctica 5 --------------------------*/
/*-----------------    2022-2   ---------------------------*/
/*------------- Alumno            Martinez Ortiz Carlos Daniel          ---------------*/
/*------------- No. de cuenta:       314000170       ---------------*/
//Evidencia practica numero 5
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

void myData(void);
void getResolution(void);

//For Keyboard
float	movX = 0.0f,
		movY = 0.0f,
		movZ = -15.0f;
float	rotY = 0.0f,
		rotX = 0.0f,
		rotZ = 0.0f;
float hombro = 0.0f;
float codo = 0.0f;
float dedo1parte1 = 0.0f;
float dedo1parte2 = 0.0f;
float dedo2parte1 = 0.0f;
float dedo2parte2 = 0.0f;
float dedo3parte1 = 0.0f;
float dedo3parte2 = 0.0f;
float dedo4parte1 = 0.0f;
float dedo4parte2 = 0.0f;
void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{
	GLfloat verticesCubo[] = {
		//Position				//Color
		-0.5f, -0.5f, 0.5f,		//V0 - Frontal
		0.5f, -0.5f, 0.5f,		//V1
		0.5f, 0.5f, 0.5f,		//V5
		-0.5f, -0.5f, 0.5f,		//V0
		-0.5f, 0.5f, 0.5f,		//V4
		0.5f, 0.5f, 0.5f,		//V5

		0.5f, -0.5f, -0.5f,		//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	//V3
		-0.5f, 0.5f, -0.5f,		//V7
		0.5f, -0.5f, -0.5f,		//V2
		0.5f, 0.5f, -0.5f,		//V6
		-0.5f, 0.5f, -0.5f,		//V7

		-0.5f, 0.5f, 0.5f,		//V4 - Izq
		-0.5f, 0.5f, -0.5f,		//V7
		-0.5f, -0.5f, -0.5f,	//V3
		-0.5f, -0.5f, -0.5f,	//V3
		-0.5f, 0.5f, 0.5f,		//V4
		-0.5f, -0.5f, 0.5f,		//V0

		0.5f, 0.5f, 0.5f,		//V5 - Der
		0.5f, -0.5f, 0.5f,		//V1
		0.5f, -0.5f, -0.5f,		//V2
		0.5f, 0.5f, 0.5f,		//V5
		0.5f, 0.5f, -0.5f,		//V6
		0.5f, -0.5f, -0.5f,		//V2

		-0.5f, 0.5f, 0.5f,		//V4 - Sup
		0.5f, 0.5f, 0.5f,		//V5
		0.5f, 0.5f, -0.5f,		//V6
		-0.5f, 0.5f, 0.5f,		//V4
		-0.5f, 0.5f, -0.5f,		//V7
		0.5f, 0.5f, -0.5f,		//V6

		-0.5f, -0.5f, 0.5f,		//V0 - Inf
		-0.5f, -0.5f, -0.5f,	//V3
		0.5f, -0.5f, -0.5f,		//V2
		-0.5f, -0.5f, 0.5f,		//V0
		0.5f, -0.5f, -0.5f,		//V2
		0.5f, -0.5f, 0.5f,		//V1
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCubo), verticesCubo, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 5 - 20222", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	glEnable(GL_DEPTH_TEST);

	Shader myShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");
	myShader.use();

	glm::mat4 viewOp = glm::mat4(1.0f);			//Use this matrix for ALL models
	glm::mat4 projectionOp = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" in order to change how we see the information
	projectionOp = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        my_input(window);

        // render
        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp
		//Mi bloque de dibujo
		/*******************************************/
		glm::mat4 modelOp = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
		//Use "view" in order to affect all models
		viewOp = glm::translate(glm::mat4(1.0f), glm::vec3(movX, movY, movZ));
		viewOp = glm::rotate(viewOp, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
		viewOp = glm::rotate(viewOp, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
		viewOp = glm::rotate(viewOp, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		
		// pass them to the shaders
		myShader.setMat4("model", modelOp);
		myShader.setMat4("view", viewOp);
		myShader.setMat4("projection", projectionOp);

		//Model
		glBindVertexArray(VAO);

		////modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		////modelOp = glm::scale(modelOp, glm::vec3(1.0f, 1.0f, 1.0f));
		////myShader.setMat4("model", modelOp);
		////myShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
		////glDrawArrays(GL_TRIANGLES, 0, 36);	//Dibujo de elemento
		//moverse -1 en x para dibujar la articulaicon (rotacion en Z)
		modelOp = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
		modelOp = glm::rotate(modelOp, glm::radians(hombro), glm::vec3(0.0f, 0.0f, 1.0f));//acumular la tramsformacion
		//trasladarse desde la art hasta el centro del hombro
		//matriz aux antes de escalar A
		modelTemp= modelOp = glm::translate(modelOp, glm::vec3(1.0f, 0.0f, 0.0f));//aux 01 se toma como referencia para dibujar B
		modelOp = glm::scale(modelOp, glm::vec3(2.0f, 1.0f, 1.0f));///escalar el cubo
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);	//Dibujo de elemento A
		//figura b
			//moverse -1 en x desde el centro de A para dibujar la articulaicon del codo (rotacion en Y)
		modelOp = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.0f));
		modelOp = glm::rotate(modelOp, glm::radians(codo), glm::vec3(0.0f, 1.0f, 0.0f));//acumular la tramsformacion
		//trasladarse desde la art hasta el centro del codo
		modelTemp=modelTemp2= modelOp=glm::translate(modelOp, glm::vec3(1.25f, 0.0f, 0.0f));//aix02 estado de B antes de la escala
		modelOp = glm::scale(modelOp, glm::vec3(2.5f, 1.0f, 1.0f));///escalar el cubo
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 1.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);	//Dibujo de elemento B
		//figura E desde el centro de B T(1.25. -.35, 0.375) para al art, R(0,1,0) 
		modelOp = glm::translate(modelTemp, glm::vec3(1.25f, -0.35f, 0.375f));
		modelOp = glm::rotate(modelOp, glm::radians(dedo1parte1), glm::vec3(0.0f, 1.0f, 0.0f));//acumular la tramsformacion
		//trasladarse desde la art hasta el centro del dedo
		modelTemp = modelOp = glm::translate(modelOp, glm::vec3(0.25f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.5f, 0.3f, 0.25f));///escalar el cubo
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);	//Dibujo de elemento E
		//glBindVertexArray(0);
		//figura F 
		// trasladar del centro de E  T(0.25, 0, 0) para la art, Ry, T(0.25, 0, 0) para llegar al centro
		modelOp = glm::translate(modelTemp, glm::vec3(0.25f, 0.0f, 0.0f));
		modelOp = glm::rotate(modelOp, glm::radians(dedo1parte2), glm::vec3(0.0f, 1.0f, 0.0f));//acumular la tramsformacion
		//trasladarse desde la art hasta el centro del dedo
		modelOp = glm::translate(modelOp, glm::vec3(0.25f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.5f, 0.3f, 0.25f));///escalar el cubo
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);	//Dibujo de elemento F
		//glBindVertexArray(0);
		//figura C
		modelOp = glm::translate(modelTemp2, glm::vec3(1.25f, 0.35f, 0.375f));
		modelOp = glm::rotate(modelOp, glm::radians(dedo2parte1), glm::vec3(0.0f, 0.0f, 1.0f));//acumular la tramsformacion
		//trasladarse desde la art hasta el centro del dedo
		modelTemp =modelOp = glm::translate(modelOp, glm::vec3(0.25f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.5f, 0.3f, 0.25f));///escalar el cubo
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);	//Dibujo de elemento C
		//glBindVertexArray(0);
		//figura d
		modelOp = glm::translate(modelTemp, glm::vec3(0.25f, 0.0f, 0.0f));
		modelOp = glm::rotate(modelOp, glm::radians(dedo2parte2), glm::vec3(0.0f, 0.0f, 1.0f));//acumular la tramsformacion
		//trasladarse desde la art hasta el centro del dedo
		modelOp = glm::translate(modelOp, glm::vec3(0.375f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.75f, 0.3f, 0.25f));///escalar el cubo
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);	//Dibujo de elemento D
		//Figura i
		modelOp = glm::translate(modelTemp2, glm::vec3(1.375f, 0.35f, -0.375f));
		modelOp = glm::rotate(modelOp, glm::radians(dedo3parte1), glm::vec3(0.0f, 0.0f, 1.0f));//acumular la tramsformacion
		//trasladarse desde la art hasta el centro del dedo
		modelTemp = modelOp = glm::translate(modelOp, glm::vec3(0.25f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.75f, 0.3f, 0.25f));///escalar el cubo
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);	//Dibujo de elemento i
		//figura J
		modelOp = glm::translate(modelTemp, glm::vec3(0.375f, 0.0f, 0.0f));
		modelOp = glm::rotate(modelOp, glm::radians(dedo3parte2), glm::vec3(0.0f, 0.0f, 1.0f));//acumular la tramsformacion
		//trasladarse desde la art hasta el centro del dedo
		modelOp = glm::translate(modelOp, glm::vec3(0.375f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.75f, 0.3f, 0.25f));///escalar el cubo
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);	//Dibujo de elemento J
		//figura G
		modelOp = glm::translate(modelTemp2, glm::vec3(1.375f, 0.35f, 0.0f));
		modelOp = glm::rotate(modelOp, glm::radians(dedo4parte1), glm::vec3(0.0f, 0.0f, 1.0f));//acumular la tramsformacion
		//trasladarse desde la art hasta el centro del dedo
		modelTemp = modelOp = glm::translate(modelOp, glm::vec3(0.25f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(0.75f, 0.3f, 0.25f));///escalar el cubo
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);	//Dibujo de elemento G
		//Figura H
		modelOp = glm::translate(modelTemp, glm::vec3(0.375f, 0.0f, 0.0f));
		modelOp = glm::rotate(modelOp, glm::radians(dedo4parte2), glm::vec3(0.0f, 0.0f, 1.0f));//acumular la tramsformacion
		//trasladarse desde la art hasta el centro del dedo
		modelOp = glm::translate(modelOp, glm::vec3(0.5f, 0.0f, 0.0f));
		modelOp = glm::scale(modelOp, glm::vec3(1.0f, 0.3f, 0.25f));///escalar el cubo
		myShader.setMat4("model", modelOp);
		myShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);	//Dibujo de elemento J
		glBindVertexArray(0);
		
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotX += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotX -= 0.1f;
	if (hombro <= 90.0f) {
			if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
				hombro += 1.1f;
	}
	if (hombro >= -10.0f) {
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
			hombro -= 1.1f;
	}
	if (codo <= 5.0f) {
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
			codo += 1.1f;
	}
	if (codo >= -100.0f) {
		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
			codo -= 1.1f;
	}
	if (dedo1parte1 <= 5.0f) {
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
			dedo1parte1 += 1.1f;
	}
	if (dedo1parte1 >= -100.0f) {
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
			dedo1parte1 -= 1.1f;
	}
	if (dedo1parte2<= 100.0f) {
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
			dedo1parte2 += 1.1f;
	}
	if (dedo1parte2 >= -5.0f) {
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
			dedo1parte2 -= 1.1f;
	}
	if (dedo2parte1 <= 50.0f) {
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
			dedo2parte1 += 1.1f;
	}
	if (dedo2parte1 >= -75.0f) {
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
			dedo2parte1 -= 1.1f;
	}
	if (dedo2parte2 <= 5.0f) {
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
			dedo2parte2 += 1.1f;
	}
	if (dedo2parte2 >= -100.0f) {
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
			dedo2parte2 -= 1.1f;
	}
	if (dedo3parte1 <= 50.0f) {
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
			dedo3parte1 += 1.1f;
	}
	if (dedo3parte1 >= -75.0f) {
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
			dedo3parte1 -= 1.1f;
	}
	if (dedo3parte2 <= 5.0f) {
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
			dedo3parte2 += 1.1f;
	}
	if (dedo3parte2 >= -100.0f) {
		if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
			dedo3parte2 -= 1.1f;
	}
	if (dedo4parte1 <= 50.0f) {
		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
			dedo4parte1 += 1.1f;
	}
	if (dedo4parte1 >= -75.0f) {
		if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
			dedo4parte1 -= 1.1f;
	}
	if (dedo4parte2 <= 5.0f) {
		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
			dedo4parte2 += 1.1f;
	}
	if (dedo4parte2 >= -100.0f) {
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
			dedo4parte2 -= 1.1f;
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}