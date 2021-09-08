//1853971 王天 太阳系
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
using namespace glm;

unsigned int WIDTH = 1024;
unsigned int HEIGHT = 800;
unsigned int num = 0;
unsigned int time = 0;
const unsigned int speed = 3;
const unsigned int DEPTH = 6;
const unsigned int MAXNUM = 2000000;
const unsigned int N = 8;
const unsigned int times = 100;
const float radius = 0.1f;
const float Pi = 3.141592653f;
const float delta = Pi * 2 / times;
float vertices[MAXNUM] = { 0 };
float c[MAXNUM] = { 0 };
float v[MAXNUM] = { 0 };
mat4 projection = perspective(80.0f, float(WIDTH) / float(HEIGHT), 0.1f, 100.0f);
mat4 view = lookAt(vec3(0.0f, -30.0f, -20.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
mat4 standard = mat4(1.0f);

class planet
{
public:
    float r, x, y, z, d, Ts, Tt, R, G, B;
    mat4 model;
    int num_flag;
    planet* parent;
    planet(float rr, float dd, float Tss, float Ttt, float RR, float GG, float BB, planet* p)
    {
        r = rr;
        if (p == NULL)
            x = dd;
        else
            x = dd + p->x;
        y = 0;
        z = 0;
        d = dd;
        Ts = Tss;
        Tt = Ttt;
        R = RR;
        G = GG;
        B = BB;
        parent = p;
        model = mat4(1.0f);
        triangle(x + r, y + 0.0f, z + 0.0f, x + 0.0f, y + r, z + 0.0f, x + 0.0f, y + 0.0f, z + r, 1);
        triangle(x - r, y + 0.0f, z + 0.0f, x + 0.0f, y + 0.0f, z + r, x + 0.0f, y + r, z + 0.0f, 1);
        triangle(x + r, y + 0.0f, z + 0.0f, x + 0.0f, y + 0.0f, z + r, x + 0.0f, y - r, z + 0.0f, 1);
        triangle(x + r, y + 0.0f, z + 0.0f, x + 0.0f, y + 0.0f, z - r, x + 0.0f, y + r, z + 0.0f, 1);
        triangle(x - r, y + 0.0f, z + 0.0f, x + 0.0f, y - r, z + 0.0f, x + 0.0f, y + 0.0f, z + r, 1);
        triangle(x + r, y + 0.0f, z + 0.0f, x + 0.0f, y + 0.0f, z - r, x + 0.0f, y - r, z + 0.0f, 1);
        triangle(x - r, y + 0.0f, z + 0.0f, x + 0.0f, y + r, z + 0.0f, x + 0.0f, y + 0.0f, z - r, 1);
        triangle(x - r, y + 0.0f, z + 0.0f, x + 0.0f, y + 0.0f, z - r, x + 0.0f, y - r, z + 0.0f, 1);
        num_flag = num;
    }
    void triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, unsigned int depth)
    {
        float x4, y4, z4, x5, y5, z5, x6, y6, z6, t;
        if (depth < DEPTH)
        {
            x4 = (x1 + x2) / 2;
            y4 = (y1 + y2) / 2;
            z4 = (z1 + z2) / 2;
            t = sqrt((x4 - x) * (x4 - x) + (y4 - y) * (y4 - y) + (z4 - z) * (z4 - z));
            x4 = x + (x4 - x) / t * r;
            y4 = y + (y4 - y) / t * r;
            z4 = z + (z4 - z) / t * r;
            x5 = (x3 + x2) / 2;
            y5 = (y3 + y2) / 2;
            z5 = (z3 + z2) / 2;
            t = sqrt((x5 - x) * (x5 - x) + (y5 - y) * (y5 - y) + (z5 - z) * (z5 - z));
            x5 = x + (x5 - x) / t * r;
            y5 = y + (y5 - y) / t * r;
            z5 = z + (z5 - z) / t * r;
            x6 = (x1 + x3) / 2;
            y6 = (y1 + y3) / 2;
            z6 = (z1 + z3) / 2;
            t = sqrt((x6 - x) * (x6 - x) + (y6 - y) * (y6 - y) + (z6 - z) * (z6 - z));
            x6 = x + (x6 - x) / t * r;
            y6 = y + (y6 - y) / t * r;
            z6 = z + (z6 - z) / t * r;
            triangle(x1, y1, z1, x4, y4, z4, x6, y6, z6, depth + 1);
            triangle(x4, y4, z4, x5, y5, z5, x6, y6, z6, depth + 1);
            triangle(x4, y4, z4, x2, y2, z2, x5, y5, z5, depth + 1);
            triangle(x6, y6, z6, x5, y5, z5, x3, y3, z3, depth + 1);
        }
        else
        {
            vertices[num] = x1;
            num++;
            vertices[num] = y1;
            num++;
            vertices[num] = z1;
            num++;
            vertices[num] = R;
            num++;
            vertices[num] = G;
            num++;
            vertices[num] = B;
            num++;
            vertices[num] = x2;
            num++;
            vertices[num] = y2;
            num++;
            vertices[num] = z2;
            num++;
            vertices[num] = R;
            num++;
            vertices[num] = G;
            num++;
            vertices[num] = B;
            num++;
            vertices[num] = x3;
            num++;
            vertices[num] = y3;
            num++;
            vertices[num] = z3;
            num++;
            vertices[num] = R;
            num++;
            vertices[num] = G;
            num++;
            vertices[num] = B;
            num++;
        }
    }
    void update()
    {
        if (Tt < 0.0001f)
            return;
        float angle = time / Tt * 360;
        if (angle > 360)
            angle = angle - 360;
        mat4 tr1 = translate(standard, vec3(0 - parent->x, 0 - parent->y, 0));
        mat4 tr2 = translate(standard, vec3(parent->x, parent->y, 0));
        mat4 rt = rotate(standard, radians(angle), vec3(0.0f, 0.0f, 1.0f));
        model = tr2 * rt * tr1;
        planet* now = parent;
        while (now != NULL)
        {
            model = now->model * model;
            now = now->parent;
        }
    }
};

planet Sun(5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, NULL);
planet Mercury(0.6f, 8.0f, 0.0f, 88.0f, 0.2f, 0.4f, 0.6f, &Sun);
planet Venus(1.1f, 12.0f, 0.0f, 225.0, 0.8f, 0.5f, 0.0f, &Sun);
planet Earth(0.9f, 18.0f, 0.0f, 365.0f, 0.1f, 0.5f, 1.0f, &Sun);
planet Moon(0.5f, 2.0f, 0.0f, 30.0f, 0.8f, 0.8f, 0.1f, &Earth);
planet Mars(1.0f, 22.0f, 0.0f, 687.0f, 1.0f, 0.8f, 0.5f, &Sun);
planet Jupiter(1.8f, 35.0f, 0.0f, 4330.0f, 0.9f, 0.7f, 0.0f, &Sun);
planet Saturn(1.4f, 40.0f, 0.0f, 10832.0f, 0.4f, 0.0f, 0.8f, &Sun);
planet* planets[N];

class Shader
{
public:
    unsigned int ID;
    Shader(const char* verPath, const char* fragPath)
    {
        string vertexCode, fragmentCode;
        ifstream vShaderFile, fShaderFile;
        vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
        fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
        try
        {
            vShaderFile.open(verPath);
            fShaderFile.open(fragPath);
            stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
            cout << "vertex着色器内容如下：\n" << vertexCode << endl;
            cout << endl;
            cout << "fragment着色器内容如下：\n" << fragmentCode << endl;
            cout << endl;
        }
        catch (ifstream::failure error)
        {
            cout << "错误：Shader读取文件失败" << endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        unsigned int vertex, fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "vertex");
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(vertex, "fragment");
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
    void use()
    {
        glUseProgram(ID);
    }
    void setInt(const string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setInt(const string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void SetMat(const string& name, const glm::mat4& value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }
    void SetVec(const string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
private:
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                cout << "错误：Shader编译错误: " << type << "\n" << infoLog << "\n ------------------------------------------------------- " << endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                cout << "错误：Shader链接错误: " << type << "\n" << infoLog << "\n ------------------------------------------------------- " << endl;
            }
        }
    }
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)//回调函数，适应窗口大小调整
{
    glViewport(0, 0, width, height);
    WIDTH = width;
    HEIGHT = height;
    projection = perspective(90.0f, float(WIDTH) / float(HEIGHT), 1.0f, 10.0f);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "SolarSystem", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    Shader myshader("solar.vert", "solar.frag");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    planets[0] = &Sun;
    planets[1] = &Mercury;
    planets[2] = &Venus;
    planets[3] = &Earth;
    planets[4] = &Moon;
    planets[5] = &Mars;
    planets[6] = &Jupiter;
    planets[7] = &Saturn;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        int i, j, k, t, num_t = 0, con = 0;
        for (i = 0; i < N; i++)
        {
            if (i == 0)
                t = 0;
            else
                t = planets[i - 1]->num_flag;
            for (j = t; j < planets[i]->num_flag; j++)
            {
                if (j % 6 != 0)
                    continue;
                vec3 vec = vec3(planets[i]->model * vec4(vertices[j], vertices[j + 1], vertices[j + 2], 1.0f));
                v[num_t] = vec[0];
                num_t++;
                v[num_t] = vec[1];
                num_t++;
                v[num_t] = vec[2];
                num_t++;
                v[num_t] = vertices[j + 3];
                num_t++;
                v[num_t] = vertices[j + 4];
                num_t++;
                v[num_t] = vertices[j + 5];
                num_t++;
            }
        }
        myshader.SetMat("Projection", projection);
        myshader.SetMat("View", view);
        myshader.use();
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, num_t * sizeof(float), v, GL_STATIC_DRAW);
        //定义顶点位置属性
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        //定义顶点颜色属性
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, num_t * sizeof(float), v, GL_STATIC_DRAW);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, num_t / 6);
        for (i = 0; i < N; i++)
        {
            con = 0;
            if (planets[i]->parent == NULL)
                continue;
            for (j = 0; j < times; j++)
            {
                float a = j * delta;
                for (k = 0; k < times; k++)
                {
                    float b = k * delta;
                    float x0 = cos(a) * (planets[i]->d + radius + radius * cos(b));
                    float y0 = sin(a) * (planets[i]->d + radius + radius * cos(b));
                    float z0 = 0 - radius * sin(b);
                    a = a + delta;
                    float x1 = cos(a) * (planets[i]->d + radius + radius * cos(b));
                    float y1 = sin(a) * (planets[i]->d + radius + radius * cos(b));
                    float z1 = 0 - radius * sin(b);
                    vec3 vc = vec3(planets[i]->parent->model * vec4(planets[i]->parent->x, planets[i]->parent->y, planets[i]->parent->z, 1.0f));
                    c[con] = x0 + vc[0];
                    con++;
                    c[con] = y0 + vc[1];
                    con++;
                    c[con] = z0 + vc[2];
                    con++;
                    c[con] = 1.0f;
                    con++;
                    c[con] = 1.0f;
                    con++;
                    c[con] = 1.0f;
                    con++;
                    c[con] = x1 + vc[0];
                    con++;
                    c[con] = y1 + vc[1];
                    con++;
                    c[con] = z1 + vc[2];
                    con++;
                    c[con] = 1.0f;
                    con++;
                    c[con] = 1.0f;
                    con++;
                    c[con] = 1.0f;
                    con++;
                }
            }
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, con * sizeof(float), c, GL_STATIC_DRAW);
            //定义顶点位置属性
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
            //定义顶点颜色属性
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, con * sizeof(float), c, GL_STATIC_DRAW);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, con / 6);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
        time = time + speed;
        for (i = 0; i < N; i++)
            planets[i]->update();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}
