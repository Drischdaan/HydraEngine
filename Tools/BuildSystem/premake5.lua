VULKAN_SDK = os.getenv('VULKAN_SDK')
DIRECTX_SDK = os.getenv('DXSDK_DIR')

include 'variables.lua'
include 'workspace.lua'

group 'Core'
  include 'projects/hydra.lua'
  
group 'ThirdParty'
  include 'projects/spdlog.lua'

group 'Examples'
  include 'projects/sandbox.lua'