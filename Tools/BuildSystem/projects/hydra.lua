project "Hydra"
  location "%{wks.location}/Source/Engine"
  kind "StaticLib"
  language "C++"
  cppdialect "C++20"
  staticruntime "on"

  targetdir(build_directory)
  objdir(int_build_directory)

  pchSourceLocation = '%{prj.location}/src'
  pchheader 'pch.h'
  pchsource (pchSourceLocation .. '/pch.cpp')

  files {
    '%{prj.location}/src/**.h',
    '%{prj.location}/src/**.cpp',
    '%{prj.location}/src/**.hpp',
    pchSourceLocation .. '/pch.cpp',
  }

  includedirs {
    '%{prj.location}/src',
    '%{prj.location}/src/Private',
    '%{prj.location}/src/Public',
    '%{VULKAN_SDK}/Include',
  }

  libdirs {
    '%{VULKAN_SDK}/Lib',
  }

  links {
    'vulkan-1.lib',
  }

  defines {
    '_CRT_SECURE_NO_WARNINGS'
  }

  -- Kind Filters
  filter 'kind:SharedLib'
    linkoptions { '-IGNORE:4251' }
    disablewarnings { '4251' }
  
    defines {
      '_LINKING_SHARED'
    }
  
  filter 'kind:StaticLib'
    defines {
      '_LINKING_STATIC'
    }
  
  
  
  -- Systen Filters
  filter 'system:windows'
    systemversion 'latest'
  
    filter 'kind:SharedLib'
      defines {
        '_BUILD_LIBRARY',
      }
  
  
  
  -- Configuration Filters
  filter 'configurations:Debug'
    runtime 'Debug'
    symbols 'On'
  
    defines {
      '_CONFIGURATION_DEBUG'
    }
  
  filter 'configurations:Release'
    runtime 'Release'
    optimize 'On'
  
    defines {
      '_CONFIGURATION_RELEASE'
    }
  
  filter 'configurations:Distribution'
    runtime 'Release'
    optimize 'On'
  
    defines {
      '_CONFIGURATION_DISTRIBUTION'
    }