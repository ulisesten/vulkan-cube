#ifndef UTIL_HPP
#define UTIL_HPP

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<vulkan/vulkan.h>

#ifdef WIN32
    /**Testing sleep function*/
    //#include <Windows.h>
#else
    #include <unistd.h>
#endif

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#ifdef __ANDROID__
// Android specific include files.
#include <unordered_map>

// Header files.
#include <android_native_app_glue.h>
#include "shaderc/shaderc.hpp"
// Static variable that keeps ANativeWindow and asset manager instances.
static android_app *Android_application = nullptr;
#elif (defined(VK_USE_PLATFORM_IOS_MVK) || defined(VK_USE_PLATFORM_MACOS_MVK))
#	include <MoltenGLSLToSPIRVConverter/GLSLToSPIRVConverter.h>
#else
#   include "SPIRV/GlslangToSpv.h"
#endif

#if defined(NDEBUG) && defined(__GNUC__)
#define U_ASSERT_ONLY __attribute__((unused))
#else
#define U_ASSERT_ONLY
#endif

#ifdef __linux__
    #include<xcb/xcb.h>
    #include<vulkan/vulkan_xcb.h>
#elif defined(_WIN32)
    #include<Windows.h>
#endif

#define NUM_SAMPLES VK_SAMPLE_COUNT_1_BIT

#define NUM_DESCRIPTOR_SETS 1

#define NUM_VIEWPORTS 1
#define NUM_SCISSORS NUM_VIEWPORTS

#define FENCE_TIMEOUT 100000000

typedef struct {
    VkLayerProperties properties;
    std::vector<VkExtensionProperties> extensions;
} layer_properties;

typedef struct _swap_chain_buffers {
    VkImage image;
    VkImageView view;
} swap_chain_buffer;

struct Info {

    #ifdef _WIN32
        #define APP_NAME_STR_LEN 80
            HINSTANCE connection;        // hInstance - Windows Instance
            char name[APP_NAME_STR_LEN]; // Name to put on the window/icon
            HWND window;                 // hWnd - window handle
    #elif (defined(VK_USE_PLATFORM_IOS_MVK) || defined(VK_USE_PLATFORM_MACOS_MVK))
	    void* window;
    #elif defined(__ANDROID__)
        PFN_vkCreateAndroidSurfaceKHR fpCreateAndroidSurfaceKHR;
    #else  // _WIN32
        xcb_connection_t *connection;
        xcb_screen_t *screen;
        xcb_window_t window;
        xcb_intern_atom_reply_t *atom_wm_delete_window;
    #endif // _WIN32

    bool save_images;

    std::vector<layer_properties> instance_layer_properties;
    std::vector<const char *> instance_extension_names;
    std::vector<const char *> instance_layer_names;
    VkInstance inst;

    std::vector<const char *> device_extension_names;
    std::vector<VkPhysicalDevice> gpus;

    std::vector<VkQueueFamilyProperties> queue_props;
    VkPhysicalDeviceProperties gpu_props;
    VkPhysicalDeviceMemoryProperties memory_properties;

    uint32_t queue_family_count;

    int width, height;

    VkSurfaceKHR surface;

    uint32_t graphics_queue_family_index;
    uint32_t present_queue_family_index;

    VkFormat format;
    VkDevice device;
    VkCommandPool cmd_pool;
    VkCommandBuffer cmd;
    VkQueue graphics_queue;
    VkQueue present_queue;

    uint32_t swapchainImageCount;
    VkSwapchainKHR swap_chain;
    std::vector<swap_chain_buffer> buffers;

    uint32_t current_buffer;

    struct {
        VkFormat format;

        VkImage image;
        VkDeviceMemory mem;
        VkImageView view;
    } depth;

    glm::mat4 Projection;
    glm::mat4 View;
    glm::mat4 Model;
    glm::mat4 Clip;
    glm::mat4 MVP;

    struct {
        VkBuffer buf;
        VkDeviceMemory mem;
        VkDescriptorBufferInfo buffer_info;
    } uniform_data;

    std::vector<VkDescriptorSetLayout> desc_layout;

    VkPipelineLayout pipeline_layout;
    VkRenderPass render_pass;

    VkPipelineShaderStageCreateInfo shaderStages[2];

    VkFramebuffer *framebuffers;

    struct {
        VkBuffer buf;
        VkDeviceMemory mem;
        VkDescriptorBufferInfo buffer_info;
    } vertex_buffer;

    VkVertexInputBindingDescription vi_binding;
    VkVertexInputAttributeDescription vi_attribs[2];

    VkDescriptorPool desc_pool;
    std::vector<VkDescriptorSet> desc_set;

    struct {
        VkDescriptorImageInfo image_info;
    } texture_data;

    VkPipelineCache pipelineCache;
    VkPipeline pipeline;

    VkViewport viewport;
    VkRect2D scissor;

};

void process_command_line_args(struct Info &info, int argc, char *argv[]);
bool memory_type_from_properties(struct Info &info, uint32_t typeBits,
                                 VkFlags requirements_mask,
                                 uint32_t *typeIndex);

bool GLSLtoSPV(const VkShaderStageFlagBits shader_type, const char *pshader,
               std::vector<unsigned int> &spirv);
void init_glslang();
void finalize_glslang();

void wait_seconds(int seconds);
void write_ppm(struct Info &info, const char *basename);

void set_image_layout(struct Info &demo, VkImage image,
                      VkImageAspectFlags aspectMask,
                      VkImageLayout old_image_layout,
                      VkImageLayout new_image_layout,
                      VkPipelineStageFlags src_stages,
                      VkPipelineStageFlags dest_stages);


#endif