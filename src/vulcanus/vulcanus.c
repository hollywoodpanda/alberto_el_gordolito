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


int create_instance () {

    printf("creating instance\n");

    /**
     * The extensions available
     */ 
    uint32_t glfw_extension_count = 0;

    /**
     * The extension names
     */ 
    const char** glfw_extensions;

    printf("starting app info\n");

    // APPLICATION INFO
    VkApplicationInfo app_info;

    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    
    app_info.pApplicationName = "Vulcanus";

    app_info.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    
    app_info.pEngineName = "No Engine";

    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);

    app_info.apiVersion = VK_API_VERSION_1_0;

    printf("starting create info\n");

    // INSTANCE CREATE INFO
    VkInstanceCreateInfo create_info;

    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    
    create_info.pApplicationInfo = &app_info;

    glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

    create_info.enabledExtensionCount = glfw_extension_count;

    create_info.ppEnabledExtensionNames = glfw_extensions;

    create_info.enabledLayerCount = 0;

    create_info.flags = 0;

    create_info.ppEnabledLayerNames = NULL;

    create_info.pNext = NULL;

    printf("requesting instance\n");

    // RESULT 
    // @FIXME("segmentation fault!")
    VkResult result = vkCreateInstance(&create_info, NULL, &instance);

    printf("an instance result has been returned\n");

    if (result == VK_SUCCESS) {

        printf("instance result is successful\n");

        return TRUE;
    }

    printf("instance request failed\n");

    return FALSE;

}

void print_extensions () {

    uint32_t extension_count = 0;

    // First we get the extension count...
    vkEnumerateInstanceExtensionProperties(NULL, &extension_count, NULL);

    // Then we create the array with the count's size
    VkExtensionProperties extension_list[extension_count];

    // Filling the extension list with the extensions!
    vkEnumerateInstanceExtensionProperties(
        NULL, 
        &extension_count, 
        extension_list
    );

    // Iterating over the extensions
    for (uint32_t i = 0; i < extension_count; i++) {

        printf(
            "Vulkan extension %i: %s\n", 
            (i + 1), 
            extension_list[i].extensionName
        );

    }

}

void cleanup () {

    printf("cleanup\n");

    vkDestroyInstance(instance, NULL);

    glfwDestroyWindow(window);

    glfwTerminate();

}

void init_window () {

     printf("starting window\n");

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
    
    printf("starting vulkan\n");

    if (create_instance() != TRUE) {

        cleanup();

        exit(-1);

    }

}

void main_loop () {
    
    printf("main loop\n");
    
    while (! glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

}

void vulcanify () {

    printf("vulcanizing\n");

    init_window();

    init_vulkan();

    if (DEBUG) {
        print_extensions();
    }

    main_loop();

    cleanup();

    printf("vulcanize process ended\n");

}