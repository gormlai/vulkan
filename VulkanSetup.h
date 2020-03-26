#ifndef _VULKAN_SETUP_H_
#define _VULKAN_SETUP_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <functional>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

/*
 LICENSE - this file is public domain
 
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 
 */

namespace Vulkan
{
    extern bool validationLayersEnabled;

	enum class BufferType
	{
		Index = 0,
		Vertex,
        Uniform,
	};

    enum class ShaderStage
    {
        Vertex = 0,
        Fragment,
        Compute,
        ShaderStageCount,
    };

    struct Shader
    {
        std::string _filename;
        std::vector<char> _byteCode;
        VkShaderStageFlagBits  _type;
        VkShaderModule _shaderModule;
        
    public:
        Shader(const std::string & filename, VkShaderStageFlagBits type);
    };


    struct VkGraphicsPipelineCreateInfoDescriptor 
    {
        VkGraphicsPipelineCreateInfoDescriptor(
            VkGraphicsPipelineCreateInfo& createInfo,
            std::vector<VkPipelineShaderStageCreateInfo>& pipelineShaderStage,
            VkPipelineVertexInputStateCreateInfo& vertexInputInfo,
            VkPipelineInputAssemblyStateCreateInfo& inputAssemblyInfo,
            VkViewport& viewport,
            VkRect2D& scissor,
            VkPipelineViewportStateCreateInfo& viewportStateCreateInfo,
            VkPipelineRasterizationStateCreateInfo& rasterizerCreateInfo,
            VkPipelineMultisampleStateCreateInfo& multisamplingCreateInfo,
            VkPipelineDepthStencilStateCreateInfo& depthStencilCreateInfo,
            VkPipelineColorBlendAttachmentState& colorBlendAttachmentCreateInfo,
            VkPipelineColorBlendStateCreateInfo& colorBlendingCreateInfo,
            VkPipelineLayoutCreateInfo& pipelineLayoutCreateInfo,
            VkPipelineDynamicStateCreateInfo& dynamicStateCreateInfo,
            std::vector<VkVertexInputBindingDescription>& vertexInputBindingDescriptions,
            std::vector<VkVertexInputAttributeDescription>& vertexInputAttributeDescriptions)
            :  _createInfo(createInfo)
            , _pipelineShaderStage(pipelineShaderStage)
            , _vertexInputInfo(vertexInputInfo)
            , _inputAssemblyInfo(inputAssemblyInfo)
            , _viewport(viewport)
            , _scissor(scissor)
            , _viewportStateCreateInfo(viewportStateCreateInfo)
            , _rasterizerCreateInfo(rasterizerCreateInfo)
            , _multisamplingCreateInfo(multisamplingCreateInfo)
            , _depthStencilCreateInfo(depthStencilCreateInfo)
            , _colorBlendAttachmentCreateInfo(colorBlendAttachmentCreateInfo)
            , _colorBlendingCreateInfo(colorBlendingCreateInfo)
            , _pipelineLayoutCreateInfo(pipelineLayoutCreateInfo)
            , _dynamicStateCreateInfo(dynamicStateCreateInfo)
            , _vertexInputBindingDescriptions(vertexInputBindingDescriptions)
            , _vertexInputAttributeDescriptions(vertexInputAttributeDescriptions)
        {}

        VkGraphicsPipelineCreateInfo& _createInfo;
           
        // helper objects
        std::vector<VkPipelineShaderStageCreateInfo> & _pipelineShaderStage;
        VkPipelineVertexInputStateCreateInfo & _vertexInputInfo;
        VkPipelineInputAssemblyStateCreateInfo & _inputAssemblyInfo;

        VkViewport & _viewport;
        VkRect2D & _scissor;
        VkPipelineViewportStateCreateInfo & _viewportStateCreateInfo;

        VkPipelineRasterizationStateCreateInfo & _rasterizerCreateInfo;
        VkPipelineMultisampleStateCreateInfo & _multisamplingCreateInfo;
        VkPipelineDepthStencilStateCreateInfo & _depthStencilCreateInfo;

        VkPipelineColorBlendAttachmentState & _colorBlendAttachmentCreateInfo;
        VkPipelineColorBlendStateCreateInfo & _colorBlendingCreateInfo;
        VkPipelineLayoutCreateInfo & _pipelineLayoutCreateInfo;
        VkPipelineDynamicStateCreateInfo & _dynamicStateCreateInfo;

        // setting up vertex arrays
        std::vector<VkVertexInputBindingDescription> & _vertexInputBindingDescriptions;
        std::vector<VkVertexInputAttributeDescription> & _vertexInputAttributeDescriptions;

    };

    struct VkComputePipelineCreateInfoDescriptor
    {
    };

    struct VkRenderPassCreateInfoDescriptor
    {
        VkAttachmentReference _colorAttachmentReference;
        VkAttachmentReference _depthAttachmentReference;
        VkSubpassDescription _subpassDescription;
        VkAttachmentDescription _colorAttachment;
        VkAttachmentDescription _depthAttachment;
        VkSubpassDependency _dependency;
        VkRenderPassCreateInfo _createInfo;
        std::array<VkAttachmentDescription,10> _attachmentDescriptions;

        VkRenderPassCreateInfoDescriptor()
        {
            memset(this, 0, sizeof(*this));
        }
    };

        
    typedef std::function<void(VkGraphicsPipelineCreateInfoDescriptor &)> GraphicsPipelineCustomizationCallback;
    typedef std::function<void(VkComputePipelineCreateInfoDescriptor&)> ComputePipelineCustomizationCallback;
    typedef std::function<void(VkRenderPassCreateInfoDescriptor&)> RenderPassCustomizationCallback;


    struct AppDescriptor
    {
        std::string _appName;
        uint32_t _requiredVulkanVersion;
        SDL_Window * _window;
        std::vector<VkPhysicalDevice> _physicalDevices;
        unsigned int _chosenPhysicalDevice;
        std::vector<VkExtensionProperties> _deviceExtensions;
        std::vector<VkSurfaceFormatKHR> _surfaceFormats;
        
        AppDescriptor();
    };
    
    struct BufferDescriptor
    {
        VkBuffer _buffer;
        VkDeviceMemory _memory;
        unsigned int _size;

        BufferDescriptor()
            :_buffer(VK_NULL_HANDLE)
            ,_memory(VK_NULL_HANDLE)
            ,_size(0)
        {
        }
        
        bool fill(VkDevice device, const void * srcData, VkDeviceSize amount);
        bool copyFrom(VkDevice device,
                      VkCommandPool commandPool,
                      VkQueue queue,
                      BufferDescriptor & src,
                      VkDeviceSize amount);

        bool copyTo(VkDevice device,
                    VkCommandPool commandPool,
                    VkQueue queue,
                    VkImage image,
                    unsigned int width,
                    unsigned int height);
    };
    
    struct Mesh;
    typedef std::function<unsigned int (Vulkan::ShaderStage stage, unsigned int uniformIndex, std::vector<unsigned char> &)> UpdateUniformFunction;

	struct Mesh
	{
		BufferDescriptor _vertexBuffer;
		BufferDescriptor _indexBuffer;

		unsigned int _numIndices;
        void * _userData;
        
		Mesh()
            :_numIndices(0)
            ,_userData(nullptr)
		{
		}

	};
    typedef std::shared_ptr<Mesh> MeshPtr;

	struct VulkanCamera
	{
		VulkanCamera() { }
		VulkanCamera(const glm::vec3 & pos, const glm::vec3 & lookat, const glm::vec3 & up)
			:_position(pos)
			, _lookat(lookat)
			, _up(up) {}

		glm::vec3 _position;
		glm::vec3 _lookat;
		glm::vec3 _up;
	};

    struct EffectDescriptor;
    struct Context;
    typedef std::function<bool (AppDescriptor &, Context &, EffectDescriptor &)> RecordCommandBuffersFunction;

    struct UniformAggregate
    {
        VkDescriptorSet _descriptorSet;
        BufferDescriptor _buffer;
        VkSampler _sampler;
        VkImageView _imageView;
    };

    struct Uniform
    {
        VkDescriptorSetLayout _descriptorSetLayout;
        VkDescriptorType _type;
        uint32_t _binding;
        std::vector<UniformAggregate> _frames;
    };

    struct EffectDescriptor
    {
        VkPipeline _pipeline;
        VkPipelineLayout _pipelineLayout;
        std::vector<Shader> _shaderModules;
        std::vector<VkCommandBuffer> _commandBuffers;
        std::vector<MeshPtr> _meshes;

        VkDescriptorPool _descriptorPool; // for image samplers

        VkRenderPass _renderPass; 

        UpdateUniformFunction _updateUniform = [](Vulkan::ShaderStage stage, unsigned int uniformIndex, std::vector<unsigned char>&) { return 0; };
        std::vector<Uniform> _uniforms[(int)(Vulkan::ShaderStage::ShaderStageCount)];

        RecordCommandBuffersFunction _recordCommandBuffers = [](AppDescriptor& appDesc, Context& context, EffectDescriptor& effectDescriptor) { return true; };
        std::string _name;

        EffectDescriptor()
            :_descriptorPool(VK_NULL_HANDLE)
        {
        }

        uint32_t totalSamplerCount() const;
        uint32_t totalImagesCount() const;
        uint32_t totalNumUniformBuffers() const;
        uint32_t totalNumUniforms() const;
        uint32_t totalTypeCount(VkDescriptorType type) const;
        uint32_t totalTypeCount(Vulkan::ShaderStage stage, VkDescriptorType type) const;
        uint32_t addUniformSampler(Vulkan::Context& context, Vulkan::ShaderStage stage);
        uint32_t addUniformImage(Vulkan::Context& context, Vulkan::ShaderStage stage);
        uint32_t addUniformBuffer(Vulkan::Context& context, Vulkan::ShaderStage stage, uint32_t size);
        uint32_t collectDescriptorSetsOfType(VkDescriptorType type, uint32_t frame, VkDescriptorSet* result);
        uint32_t collectDescriptorSets(uint32_t frame, VkDescriptorSet* result);
        void collectDescriptorSetLayouts(std::vector<VkDescriptorSetLayout> & layouts);
        uint32_t collectUniformsOfType(VkDescriptorType type, Uniform** result);
        uint32_t collectUniformsOfType(VkDescriptorType type, Vulkan::ShaderStage stage, Uniform** result);

        bool bindSampler(Vulkan::Context& context, Vulkan::ShaderStage shaderStage, uint32_t binding, VkImageView imageView, VkSampler sampler);
        bool bindImage(Vulkan::Context& context, Vulkan::ShaderStage shaderStage, uint32_t binding, VkImageView imageView);

    };
    typedef std::shared_ptr<EffectDescriptor> EffectDescriptorPtr;

    struct Context
    {
        VkInstance _instance;
        VkPhysicalDevice _physicalDevice;
        VkDevice _device;
        VkPhysicalDeviceProperties _deviceProperties;
        VkPhysicalDeviceFeatures _physicalDeviceFeatures;
        
        VkQueue _presentQueue;
        VkQueue _graphicsQueue;
        
        VkSurfaceKHR _surface;
        VkSurfaceCapabilitiesKHR _surfaceCapabilities;
        VkSurfaceFormatKHR _surfaceFormat;
        
        VkExtent2D _swapChainSize;
        VkSwapchainKHR _swapChain;
        
		// for colour buffer
        std::vector<VkImage> _rawImages;
        std::vector<VkImageView> _colorBuffers;

		// for depth buffer
		std::vector<VkImage> _depthImages;
		std::vector<VkImageView> _depthImageViews;
		std::vector<VkDeviceMemory> _depthMemory;

        std::vector<VkFramebuffer> _frameBuffers;
        
        
        VkDebugUtilsMessengerEXT _debugUtilsCallback;
		VkDebugReportCallbackEXT _debugReportCallback;
		VkAllocationCallbacks * _allocator;
        
        VkCommandPool _commandPool;

        std::vector<VkSemaphore> _renderFinishedSemaphores;
        std::vector<VkSemaphore> _imageAvailableSemaphores;
        std::vector<VkFence> _fences;
        
        VkPipelineCache _pipelineCache;
        VkRenderPass _renderPass;

        unsigned int _currentFrame;
        std::vector<EffectDescriptorPtr> _effects;

        Context();

		const VulkanCamera & getCamera() { return _camera;  }

	private:
		VulkanCamera _camera;

    };

    
    bool addMesh(AppDescriptor& appDesc, 
        Context& context,
        std::vector<unsigned char>& vertexData, 
        std::vector<unsigned char>& indexData, 
        void* userData, 
        EffectDescriptor& effectDescriptor,
        Vulkan::Mesh& result);


    bool handleVulkanSetup(AppDescriptor& appDesc, Context& context);
    bool recreateSwapChain(AppDescriptor& appDesc, Context& context);
    void updateUniforms(AppDescriptor& appDesc, Context& context, uint32_t currentImage);

    bool resetCommandBuffers(Context& context, std::vector<VkCommandBuffer>& commandBuffers);
    bool createShaderModules(AppDescriptor& appDesc, Context& context, std::vector<Shader>& shaders);
    bool initEffectDescriptor(AppDescriptor& appDesc, 
        Context& context, 
        const bool createGraphicsPipeline, 
        GraphicsPipelineCustomizationCallback graphicsPipelineCreationCallback, 
        RenderPassCustomizationCallback renderPassCreationCallback,
        Vulkan::EffectDescriptor& effect);
    bool initEffectDescriptor(AppDescriptor& appDesc, Context& context, ComputePipelineCustomizationCallback computePipelineCreationCallback, Vulkan::EffectDescriptor& effect);

    bool createBuffer(Context& context, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, BufferDescriptor& bufDesc);

    bool createImage(Vulkan::Context & context,
                 unsigned int width,
                 unsigned int height,
                 unsigned int depth,
                 VkFormat requiredFormat,
                 VkImageTiling requiredTiling,
                 VkImageUsageFlags requiredUsage,
                     VkImage& resultImage);

    bool createImageView(Vulkan::Context& context,
        VkImage image,
        VkFormat requiredFormat,
        VkImageAspectFlags requiredAspectFlags,
        VkImageView& result);


    bool transitionImageLayout(Vulkan::Context & context,
                               VkImage image,
                               VkFormat format,
                               VkImageLayout oldLayout,
                               VkImageLayout newLayout);

    bool createUniformBuffer(AppDescriptor& appDesc, Context& context, VkDeviceSize bufferSize, BufferDescriptor& result);



}

#endif
