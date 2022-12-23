/**
 * @file hello_window_clear.cpp
 * @author Vincent Marias ( @qtf0x )
 * @date 12/21/2022
 *
 * @brief Learn OpenGL - Getting Started
 *        Hello Window
 */

#include <glad/glad.h> // must include GLAD before GLFW, includes GL/gl.h

#include <GLFW/glfw3.h>

#include <iostream>

// window dimensions
constexpr GLsizei WINDOW_WIDTH{800}, WINDOW_HEIGHT{600};

/**
 * @brief initialize GLFW with window hints, check for failure
 *
 * @param CONTEXT_VERSION_MAJOR OpenGL major version number
 * @param CONTEXT_VERSION_MINOR OpenGL minor version number
 * @param OPENGL_PROFILE GLFW macro for OpenGL profile (core/compat)
 * @return GLboolean true if init success; false if init failure
 */
GLboolean setupGLFW(const GLint& CONTEXT_VERSION_MAJOR,
                    const GLint& CONTEXT_VERSION_MINOR,
                    const GLint& OPENGL_PROFILE);

/**
 * @brief initialize GLAD: load all OpenGL function pointers
 *
 * @return GLboolean true if init success; false if init failure
 */
GLboolean setupGLAD();

/**
 * @brief terminate and clean up GLFW context
 *
 * @param window pointer to window to be cleaned up (must be on current thread)
 */
void shutdownGLFW(GLFWwindow*& window);

/**
 * @brief process user keyboard/mouse I/O
 *
 * @param window GLFW window to collect input from
 */
void processInput(GLFWwindow* window);

/**
 * @brief callback function for framebuffer resize
 *
 * @param window GLFW window to query
 * @param width new framebuffer width
 * @param height new framebuffer height
 */
void framebuffer_size_callback([[maybe_unused]] GLFWwindow* window,
                               GLsizei width, GLsizei height);

int main() {
    if (!setupGLFW(3, 3, GLFW_OPENGL_CORE_PROFILE))
        return EXIT_FAILURE;

    // create window object
    auto window{glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello, Window!",
                                 nullptr, nullptr)};

    // make sure the window was generated properly
    if (!window) {
        std::cerr << "[ERROR]: Failed to create GLFW window\n";

        // clean up glfw
        shutdownGLFW(window);

        return EXIT_FAILURE;
    }

    // make context of window main context on current thread
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    if (!setupGLAD()) {
        std::cerr << "Failed to initialize GLAD\n";

        // clean up glfw
        shutdownGLFW(window);

        return EXIT_FAILURE;
    }

    // register window resize callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clean up glfw
    shutdownGLFW(window);

    return EXIT_SUCCESS;
}

// Helper Functions
// =============================================================================

GLboolean setupGLFW(const GLint& CONTEXT_VERSION_MAJOR,
                    const GLint& CONTEXT_VERSION_MINOR,
                    const GLint& OPENGL_PROFILE) {
    // initialize GLFW
    if (!glfwInit()) {
        glfwTerminate();
        return GL_FALSE;
    }

    // OpenGL 3.3 last version to change core functionality
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, CONTEXT_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, CONTEXT_VERSION_MINOR);
    // use core profile for smaller subset of features w/o backwards compat
    glfwWindowHint(GLFW_OPENGL_PROFILE, OPENGL_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    return GL_TRUE;
}

GLboolean setupGLAD() {
    return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void shutdownGLFW(GLFWwindow*& window) {
    // clean up glfw
    if (window)
        glfwDestroyWindow(window);
    window = nullptr;
    glfwTerminate();
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

// Callbacks
// =============================================================================

void framebuffer_size_callback([[maybe_unused]] GLFWwindow* window,
                               GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);
}
