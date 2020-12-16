#include <iostream>
#include <GLFW/glfw3.h>


int main() {
    std::cout << "Hello, World!" << std::endl;
    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwDefaultWindowHints();
    GLFWwindow* window = glfwCreateWindow(300, 300, "Red Triangle",
                                          nullptr, nullptr);
    if(window == nullptr) {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwShowWindow(window);

    return 0;
}
