
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdio.h>

#include <stdlib.h>

#include "vulcanus.h"

#include "../util/constants.h"

/**
 * The GLFW Window plugged with vulkan
 */ 
GLFWwindow* window;

/**
 * The vulkan instance
 */ 
VkInstance instance;

uint32_t glfw_extension_count = 0;

const char** glfw_extensions;

int create_instance () {

    printf("Creating app_info...\n");

    // First we'll create the app info
    VkApplicationInfo app_info;

    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    
    app_info.pApplicationName = "Vulcanus";

    app_info.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    
    app_info.pEngineName = "No Engine";

    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);

    app_info.apiVersion = VK_API_VERSION_1_0;

    printf("Creating create_info...\n");

    /*
     * All of the create_info struct fields must be filled or we'll
     * end up with segmentation fault.
     */
    VkInstanceCreateInfo create_info;

    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    
    create_info.pApplicationInfo = &app_info;

    glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

    create_info.enabledExtensionCount = glfw_extension_count;

    create_info.ppEnabledExtensionNames = glfw_extensions;

    // Defaulting to 0
    create_info.enabledLayerCount = 0;

    // Defaulting to 0
    create_info.flags = 0;

    // Defaulting to NULL
    create_info.ppEnabledLayerNames = NULL;

    // Defaulting to NULL
    create_info.pNext = NULL;

    printf("Creating the vulkan instance with the calculated create_info and app_info\n");

    // RESULT
    VkResult result = vkCreateInstance(&create_info, NULL, &instance);

    if (result == VK_SUCCESS) {

        printf("Vulkan instance created\n");

        // Success!
        return TRUE;
    }

    printf("Something went wrong while creating instance :-(\n");

    // Something's wrong. We'll inform
    // the caller of the failure with FALSE
    return FALSE;

}

void cleanup () {

    printf("cleanup\n");

    glfwDestroyWindow(window);

    glfwTerminate();

}

void init_window () {

     printf("init_window\n");

    // 1. Calling init
    glfwInit();

    // 2. Hinting it to not use OpenGL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // 3. Disabling resizing for now...
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(
        VULCANUS_WINDOW_WIDTH, 
        VULCANUS_WINDOW_HEIGHT, 
        "Vulcanus", 
        NULL, 
        NULL
    );

    return;

}

void init_vulkan () {
    
    printf("init_vulkan\n");

    if (create_instance() != TRUE) {

        cleanup();

        exit(-1);

    }

}

void main_loop () {
    
    printf("main_loop\n");
    
    while (! glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

}

void vulcanify () {

    init_window();

    init_vulkan();

    main_loop();

    cleanup();

    return;

}