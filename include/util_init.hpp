#ifndef UTIL_INIT_HPP
#define UTIL_INIT_HPP

#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <vulkan/vulkan.h>


VkResult init_global_layer_properties(struct Info &info);

void init_instance_extension_names(struct Info &info);
void init_device_extension_names(struct Info &info);

VkResult init_instance(struct Info &info, char const *const app_short_name);
VkResult init_enumerate_device(struct Info &info, uint32_t gpu_count = 1);

void init_window_size(struct Info &info, int32_t default_width, int32_t default_height);
void init_connection(struct Info &info);
void init_window(struct Info &info);

void init_swapchain_extension(struct Info &info);
VkResult init_device(struct Info &info);

void init_command_pool(struct Info &info);
void init_command_buffer(struct Info &info);
void execute_begin_command_buffer(struct Info &info);
void init_device_queue(struct Info &info);
void init_swap_chain(
    struct Info &info,
    VkImageUsageFlags usageFlags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
                                   VK_IMAGE_USAGE_TRANSFER_SRC_BIT);

void init_depth_buffer(struct Info &info);
void init_uniform_buffer(struct Info &info);
void init_descriptor_and_pipeline_layouts(struct Info &info,
                                          bool use_texture);
void init_renderpass(
    struct Info &info, bool include_depth, bool clear = true,
    VkImageLayout finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

void init_shaders(struct Info &info, const char *vertShaderText,
                  const char *fragShaderText);

void init_framebuffers(struct Info &info, bool include_depth);
void init_vertex_buffer(struct Info &info, const void *vertexData,
                        uint32_t dataSize, uint32_t dataStride,
                        bool use_texture);
void init_descriptor_pool(struct Info &info, bool use_texture);
void init_descriptor_set(struct Info &info, bool use_texture);
void init_pipeline_cache(struct Info &info);
void init_pipeline(struct Info &info, VkBool32 include_depth,
                   VkBool32 include_vi = true);

void init_viewports(struct Info &info);
void init_scissors(struct Info &info);


/**Destructors*/
void destroy_pipeline(                           struct Info &info);
void destroy_pipeline_cache(                     struct Info &info);
void destroy_descriptor_pool(                    struct Info &info);
void destroy_vertex_buffer(                      struct Info &info);
void destroy_framebuffers(                       struct Info &info);
void destroy_shaders(                            struct Info &info);
void destroy_renderpass(                         struct Info &info);
void destroy_descriptor_and_pipeline_layouts(    struct Info &info);
void destroy_uniform_buffer(                     struct Info &info);
void destroy_depth_buffer(                       struct Info &info);
void destroy_swap_chain(                         struct Info &info);
void destroy_command_buffer(                     struct Info &info);
void destroy_command_pool(                       struct Info &info);
void destroy_device(                             struct Info &info);
void destroy_window(                             struct Info &info);
void destroy_instance(                           struct Info &info);


#endif